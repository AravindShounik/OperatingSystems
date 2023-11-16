The goal of this code is to implement a program to stimulate the Rate-Monotonic and Earliest-Deadline-First scheduling algorithms.

Here, the file inp-params.txt should be of the form

<number of processes>
<it should contain n lines in this format>
<pid> <t> <p> <k>


This program has 2 files Assign3-RMS-cs20btech11055.cpp and Assign3-EDF-cs20btech11055.cpp
Here, the file Assign3-RMS-cs20btech11055.cpp gives 2 files as output which are RMS-Log.txt and RMS-Stats.txt
Here, RMS-Log.txt contains log of all the processes taking place and the order they have taken place in.
and the file RMS-Stats.txt contains the information about number of processes terminated and the average waiting time of the RMS scheduling

To run Assign3-RMS-cs20btech11055.cpp you have to use the commands

g++ -std=c++17 Assign3-RMS-cs20btech11055.cpp -o Assign3-RMS-cs20btech11055
./Assign3-RMS-cs20btech11055

Here, the file Assign3-EDF-cs20btech11055.cpp gives 2 files as output which are EDF-Log.txt and EDF-Stats.txt
Here, EDF-Log.txt contains log of all the processes taking place and the order they have taken place in.
and the file EDF-Stats.txt contains the information about number of processes terminated and the average waiting time of the EDF scheduling

To run Assign3-EDF-cs20btech11055.cpp you have to use the commands

g++ -std=c++17 Assign3-EDF-cs20btech11055.cpp -o Assign3-EDF-cs20btech11055
./Assign3-EDF-cs20btech11055
