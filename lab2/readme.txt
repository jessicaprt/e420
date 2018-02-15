NOTE: The Read Write lock implementation was based from
the ECE 420 Chapter 2 lecture notes

To build all the required outputs do

    make

This will result in four different server executables
made utilizing different synchronization methods:

    server_single_mutex.out
    server_multiple_mutex.out
    server_single_rwlock.out
    server_multiple_rwlock.out

To run any of the server implementations do:

    ./server_single_mutex.out [PORT] [ARRAY_SIZE]

To run the client given that a server is running do:

    ./client [PORT] [ARRAY_SIZE]