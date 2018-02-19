# reusable_barrier
Using semaphores provided by semaphore.h, implement a function barrier_wait(int barrier) that a thread can invoke in order to 
synchronize on a barrier

The argument is an integer number that identifies the barrier. In this way, threads can synchronize, for example, on two different 
barriers: 0 and 1. Assume that the total number of barriers is given (N_BARRIERS), as well as the total number of threads (N_THREADS), 
and that N_THREADS threads synchronize on each barrier.

The barrier should be reusable, meaning that after it has been used to synchronize a group of N_THREADS threads, it can be immediately 
reused to synchronize the next group of N_THREADS threads. Threads should have this format:

void *my_thread(arg *a) { <br />
    int i; <br />
    for(i=0;i<10;i++) { <br />
        puts("*"); <br />
        barrier_wait(0); <br />
        puts("\t+"); <br />
        barrier_wait(1); <br />
    } <br />
} <br />
Assuming N_THREADS equal to 3, the expected output is of the form: <br />
* <br />
* <br />
* <br />
    + <br />
    + <br />
    + <br />
* <br />
* <br />
* <br />
    + <br />
    + <br />
    + <br />
* <br />
* <br />
* <br />
    + <br />
    + <br />
    + <br />
* <br />
* <br />
* <br />
    + <br />
    + <br />
    + <br />
etc.
