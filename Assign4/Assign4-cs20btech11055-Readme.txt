This code implements TAS,CAS and Bounded_Waiting Algorithms with CAS Mutual Exclusion (ME) algorithms using C++

This program creates n threads and runs a process which goes into critical section k times in each thread 

CAS:
    To compile CAS:
        g++ -std=c++17 -o cas SrcAssign4-cas-cs20btech11055.cpp
    To run CAS:
        ./cas
TAS:
    To compile TAS:
        g++ -std=c++17 -o tas SrcAssign4-tas-cs20btech11055.cpp
    To run TAS:
        ./tas
CAS_BOUNDED:
    To compile CAS_BOUNDED:
        g++ -std=c++17 -o cas-b SrcAssign4-cas-b-cs20btech11055.cpp
    To run CAS_BOUNDED:
        ./cas-b

The Input file should be in the form inp-params.txt in the format

<n> <k> <lambda1> <lambda2>