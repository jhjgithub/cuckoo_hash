#ifndef __ASSOC_CUCKOO_H__
#define __ASSOC_CUCKOO_H__

#include <stdint.h>
#include <pthread.h>

/////////////////////////////////

/*
 * enable huge table to reduce TLB misses
 */
//#define CUCKOO_ENABLE_HUGEPAGE

/*
 * enable parallel cuckoo
 */
#define MEMC3_ASSOC_CUCKOO_WIDTH 1

////////////////////////////////

/*
 * The maximum number of cuckoo operations per insert,
 * we use 128 in the submission
 * now change to 500
 */
#define MAX_CUCKOO_COUNT 500


/*
 * the structure of a bucket
 */
#define BUCKET_SLOT_SIZE 4

#define FG_LOCK_COUNT 8192
#define FG_LOCK_MASK (FG_LOCK_COUNT - 1)

/* Initial power multiplier for the hash table */
#define HASHPOWER_DEFAULT 25
//#define HASHPOWER_DEFAULT 16

#define IS_SLOT_EMPTY(cukht, i, j) (cukht->buckets[i].tags[j] == 0)
#define IS_TAG_EQUAL(cukht, i, j, tag) ((cukht->buckets[i].tags[j] & cukht->tag_mask) == tag)

#define RET_PTR_ERR 	((void*)-1)

/////////////////////////////////////////////////

typedef int32_t (*cuckoo_cmp_key)(const void *key1, const void *key2, const size_t key_len);
typedef uint8_t tag_t;
typedef __int128_t int128_t;
typedef __uint128_t uint128_t;
typedef pthread_spinlock_t cuckoo_spinlock_t;

typedef struct cuckoo_item_s {
	const void	*key;
	size_t		key_len;
	void		*value;
} cuckoo_item_t ;

#if 0
typedef struct cuckoo_slot_s {
	uint32_t	hash;
	//uint32_t  notused;
	ValueType	data;
}  __attribute__((__packed__)) cuckoo_slot_t;
#else
typedef void *cuckoo_slot_t;
#endif

typedef struct bucket {
	tag_t			tags[BUCKET_SLOT_SIZE];     // 4bytes
	//uint8_t			notused[4];             // ???
	cuckoo_slot_t	slots[BUCKET_SLOT_SIZE];
}  __attribute__((__packed__)) cuckoo_bucket_t;

typedef struct cuckoo_path_s {
	size_t			cp_buckets[MEMC3_ASSOC_CUCKOO_WIDTH];
	size_t			cp_slot_idxs[MEMC3_ASSOC_CUCKOO_WIDTH];
	cuckoo_slot_t	cp_slots[MEMC3_ASSOC_CUCKOO_WIDTH];
} cuckoo_path_t;

typedef struct cuckoo_hashtable_ {
	cuckoo_bucket_t		*buckets;
	cuckoo_cmp_key		cb_cmp_key;
	cuckoo_spinlock_t	*fg_locks;
	cuckoo_path_t		*cuk_path;

	uint32_t			idx_victim;
	uint32_t			num_error;
	uint32_t			num_kick;
	uint32_t			num_items;
	uint32_t			num_moves;

	uint32_t			hash_power;
	uint64_t			hash_size;
	uint64_t			hash_mask;

	uint64_t			tag_power;
	uint64_t			tag_mask;
} cuckoo_hash_table_t;


/////////////////////////////////////////

cuckoo_hash_table_t* cuckoo_init_hash_table(const int32_t hashpower_init, cuckoo_cmp_key cmp_key);
void cuckoo_destroy_hash_table(cuckoo_hash_table_t *cukht);
void* cuckoo_find(cuckoo_hash_table_t *cukht, const char *key, const size_t nkey);
int32_t cuckoo_insert(cuckoo_hash_table_t *cukht, const char *key, const size_t klen, void *data);
void* cuckoo_delete(cuckoo_hash_table_t *cukht, const char *key, const size_t nkey);


#endif