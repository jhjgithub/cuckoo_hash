**Bucketized Cuckoo Hashtable**
=====================

Cuckoo Hashing is a state-of-the-art technology to store data and find them. The time complexity of look-up is O(1) and for insertion also O(1). The maximum load factor, however, is 50% when the data could not be inserted. This is a major drawback to be solved.

Bucketized Cuckoo Hashing, BCH, is one of the solutions. With Cuckoo Hashing, a bucket could store only one data, kicked-out immediately if the collision is raised. What if the bucket might have more rooms to save data. Kicking-out would put off even though there is the collision caused. It is the main conception of Bucketized Cuckoo Hashing. Each bucket has its own slots and its maximum load factor is 95%. But the time complexity is also constant, O(n * 2), where n is slots of a bucket.

This library will be used for Session table with Linux Kernel Module. The table may handle more than 500 Million entries under 10 or 40 Gbps NICs. 

## Benchmark Test:

* OS: Ubuntu 16.04
* CPU: Intel(R) Xeon(R) CPU E5-2650 v2 @ 2.60GHz
* DRAM: 16GB
* Test Material: random length 9,462,148 words
* Benchmark Test Result:
<pre><code>
===== Start Benchmark test: Bucketized Cuckoo Hashing ===== 
Hashtable size: 8388608
Insert Exec time: 0.779468429 sec, Count:9462148, Per nsec:82 
Adding key pairs: 9462148 
Cuckoo Movements: 1066 
Search Exec time: 1.109744371 sec, Count:9462148, Per nsec:117 
lookup key pairs: 9462148 of 9462148 
</code></pre>

## References: 

Cuckoo Hashing, by Rasmus Pagh and Flemming Friche Rodler. 
- http://www.it-c.dk/people/pagh/papers/cuckoo-jour.pdf

Cuckoo Stash, by Adam Kirsch, Michael Mitzenmacher and Udi Wieder. 
- https://www.eecs.harvard.edu/~michaelm/postscripts/esa2008full.pdf

MurmurHash3, by Austin Appleby. 
- http://en.wikipedia.org/wiki/MurmurHash
- https://github.com/aappleby/smhasher

Hashtable Implementation Using Cuckoo Hashing. 
- http://warpzonestudios.com/hashtable-cuckoo/

Algorithmic Improvements for Fast Concurrent Cuckoo Hashing.
- https://www.cs.princeton.edu/~mfreed/docs/cuckoo-eurosys14-slides.pdf

Lock-free Cuckoo Hashing.
- http://excess-project.eu/publications/published/CuckooHashing_ICDCS.pdf
- https://www.google.co.kr/url?sa=t&rct=j&q=&esrc=s&source=web&cd=11&ved=0ahUKEwja7I3z1I3WAhWMTLwKHYB6CTc4ChAWCCMwAA&url=http%3A%2F%2Fwww.cse.chalmers.se%2F~tsigas%2Fpapers%2FSLIDES%2FICDCS14.pptx&usg=AFQjCNEEgcXObBJPNVyF1p5gU9svBzQBaw
- https://github.com/eourcs/LockFreeCuckooHash
- https://eourcs.github.io/LockFreeCuckooHash/
- https://github.com/vigneshjathavara/Lock-Free-Cuckoo-Hashing

Algorithmic Improvements for Fast Concurrent Cuckoo Hashing.
- https://www.cs.princeton.edu/~mfreed/docs/cuckoo-eurosys14.pdf
- https://www.usenix.org/system/files/conference/nsdi13/nsdi13-final197.pdf

Sorting Cuckoo
- http://www.kics.or.kr/Home/UserContents/20170412/170412_100537439.pdf

Horton Tables
- https://www.usenix.org/system/files/conference/atc16/atc16_paper-breslow.pdf
