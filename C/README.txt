Collection of C programs demonstrating understanding of algorithms, memory management, process management, and threading.

Duplicate Address Finder:

Build with make all. Input text file from stdin.
Determines if address entries might be duplicates, and prints out potential duplicates. Uses a linked list to store the entries and searches them for possible duplicates.

Process Scheduler:

Build with make all. Input text file with various commands to run from stdin.
Schedules and executes processes in a round robin scheduling format. 3 different version, each building on top of the other. The final version (usps.c) schedules hundreds of processes and prints system status reports on these processes taken from Unix proc folder.

Threaded Network Driver Simulation:

Build with make all.
Sends and receives packets from a simulated network device with simulated network latency. Uses bounded buffers and pthreads to ensure packets are delivered and received without dropping them. Implementation of nearly all object files unknown, only header files present as clues to how the driver works.