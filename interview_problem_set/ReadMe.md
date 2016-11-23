# Just a set of problems for interview preparing mind recalling (concept mostly with little code)

### you should always keep the following in mind. And these things are not precise description but an reminding.
 
* <font color="green" size="4">
Data structure & Algorithm
</font>
    * Linked list
        * Singly linked list
        * Doubly linked list
        * Circular linked list
    * Stack
    * Queue
    * Search
        * Linear search
        * Binary search
        * Interpolation search
        * Hash table
    * Sorting

        * Bubble :

            * Bubble sort is a simple algorithm repeatedly steps through compare adjacent items and swap if in the wrong order.

        * Insertion :
            
            * Insertion sort is a simple algorithm swap the item in orignal array one item at a time.

        * Selection :
            
            * Selection sort is a in-place comparison algorithm emplace the minimun one at a time.

        * Merge :

            * An Effecient D&C algorithm. First, divide into smallest unit. Second, compare each eles with adjacent and merge them.

        * Shell :

            * Shell sort is an in-place comparison sort and a generalization of insertion sort. It need a gap sery to active, for the N turn of running, it would devide data into separate subarrays whose eles have a distance of gap[N], then perform insertion sort.

        * Quick :

            * Quick sort is a D&C algorithm. First divides a large array into two smaller sub-arrays (low-ele and high-ele). Second recursively sort the sub-array.
        
        * Timsort :

            * Timesort is a hybrid algorithm, derived from merge sort and insertion sort. It's designed to take advantage of partial orderings that exist in most real-world data. **check wikipedia** 

        * Counting

            * Counting sort is integer sorting where variation in items is not significantly greater than number of items.

        * Heap

            * Heap sort can be thought of an improved selection sort, dividing its input into a sorted and an unsorted region, it iteratively shrinks the unsorted region by extracting the largest element into sorted region.

        * Radix
            
            * Radix sort sorts every digits, from least significant to most significant.

        * Bucket

            * Bucket sort distributed elements into a number of buckets, sort each bucket.

    * Graph & Tree
        * Depth first traversal & Breadth first traversal
        * tree traversal : pre-order in-order post-order
        * AVL
        * Spanning tree
        * Heap
    * More Hashing
    * Recursion
    * Iteration
    * D&C
    * DP
    * Greedy
    * Backtrace
    

* <font color="green" size="4">
Computer network(tcp/ip illustrated volume)
</font>

    * Concept

    * Fundemental

    * Advanced

* <font color="green" size="4">
Cpp(c++Primer5th & modern c++)
</font>

* <font color="green" size="4">
Computer architecture(csapp) 
</font>

* <font color="green" size="4">
Operating system & system programming(TLPI & AUPE & modern OS) 
</font>

    * System call 
        
        * Concept : system call is implement by kernel with a interface defined by POSIX, like C-standard library. What is tricky is that these function in c-standard library have the same name of 'real system call' and also reffered directly  'system call'. open() is a 'system call', fopen() is a 'library call'.

        * Atomicity : An uninterruptible step, which is a necessary requirement for correct operation of many system calls. Kernel guarantees that all of the steps in a system call are completed as a single operation.
        <font color="red"> Read more about "Concurrency programming" </font>

    * I/O
<font color="red">
 check epoll_example 
</font>

        * Universal operation : open() read() write() close(), 'file offset' lseek(), which are defined in <unistd.h>
        
        * Buffering : read() write() only simply copy data between a user-space buffer and a buffer in the kernel 'buffer cache'. Use large buffer when working with large data. There are some function about buffer in stdio. U can find API to control kernel buffering in <unistd.h>

        * Atomicity : use flags to make open() return an error if the file already exist, which makes process to ensure that it's the creator of a file.

        * File descriptor : the per-process file descriptor table -> system-wide table of open file description -> the file system i-node table.
<font color="red">
 check the figure in tlpi page 95
</font>

        * Nonblocking I/O and I/O multiplexing : nonblocking is that If an I/O operation can't be done immediately, it would return an error instead of blocking. Multiplexing is that not like traditional way (a process performs I/O on one file descriptor at a time or multiple thread) like poll() & select().
But signal-driven I/O is better performance than poll() when monitoring large numbers of fd. epoll() is like poll() but have the performance like signal-driven I/O.
<font color="red">
 Read more about "network programming" 
</font>

    * File system
        
        * Concept : Device file, Disk and partition, I-node, Ext2, Virtual File System, Single Directory Hierarchy & Mount Points

        * File Attributes

        * Unix File Permission scheme

        * Directories and links

        * File Monitor

    * Process

        * Signal

        * Process Creation

        * Process Termination

        * Monitor Child Process

        * Program Execution

        * Process Scheduling
        
        * Process Resouces
    
    * Thread

        * Fundamental

        * Synchronization

        * Thread Safety

        * Thread Canceling

    * Other

        * Time Granularity 

    * IPC(only POSIX IPC here)

        * Pipe :
        used in shell, pass data between "related" process. Pipe is actually a byte stream. (pipe(filedes) returns two open file descriptors in array filedes, one for write, one for read)

        * FIFOs :
        a variation of pipe concept, which can pass data between any process. (mkfifo(const char* pathname, mode_t mode) to create FIFO

        * Message queue :
        allow processes to exchange data in form of messages.(mq_open() to creates a new message queue or obtains an existing queue)

        * Semaphore :
        not used to transfer data, they allow processes to synchronize their action (access to a block of shared memory). Actually, semaphore is a kernel-maintained integer whose value is restricted to being greater than or equal to zero. (sem_open() API to create a new semaphore)

        * Signal :
        signal (SIGXXXX) are more often described as "software interrupts". The question how signal works is quite complicated which can be devided into three aspects : 1.signal delivery 2.signal generation (signal() to change the disposition of a signal)
<font color="red">
You should avoid any signal-based design as possible. It's very unclean approach, Signals can get lost, signal handles operate in strange context and shouldn't do very much, and it's all around an ugly design.
</font>

        * Shared memory :
        allows multiple processes to share the same region(shm_open() to creates a new shared memory segment or obtains an existing segment)

        * Related topics : Socket, RPC

* <font color="green" size="4">
 Concurrency Programming & Network Programming (Socket & MIT-6.033 & chenshuo book)
</font> 

* <font color="green" size="4"> 
 Distributed system(MIT-6.824) 
</font>

* <font color="green" size="4">
 Common tools implement 
</font>
