This code implements two solutions using semaphores for the Reader-Writers Problem. One solution with reader preference (Readers-Writers) and one fair solution (Fair-Readers-Writers).

This program creates nw writer threads and nr reader threads and runs the reader and writer sections for kw and kr times in each thread.

Readers-Writers:
    To compile Readers-Writers:
        g++ -std=c++17 -o rw Assign5-rw-cs20btech11055.cpp -lpthread
    To run Readers-Writers:
        ./rw

Fair Readers-Writers:
    To compile Fair-Readers-Writers:
        g++ -std=c++17 -o rw Assign5-rw-cs20btech11055.cpp -lpthread
    To run Readers-Writers:
        ./frw

The input file should be in the form inp-params.txt in the format

<nw> <nr> <kw> <kr> <l1> <l2>