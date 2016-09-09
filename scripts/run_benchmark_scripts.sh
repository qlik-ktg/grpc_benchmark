#!/bin/bash

memory_cleanup() {
    echo 1 > /proc/sys/vm/drop_caches
    echo 2 > /proc/sys/vm/drop_caches
    echo 3 > /proc/sys/vm/drop_caches
}

# perform tests with memory mapped turned off
memory_cleanup

#./run_benchmark_test.py -l c++Ext -r '(.*)ping_pong(.*)'
