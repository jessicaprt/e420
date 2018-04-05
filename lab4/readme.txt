To build all the required outputs do

    make

This will result in four different server executables
made utilizing different synchronization methods:

    original.out
    shared_parallel_static.out
    shared_parallel_dynamic.out
    shared_parallel_guided.out

To run any of the implementations:

    ./shared_parallel_static.out [THREAD_COUNT]