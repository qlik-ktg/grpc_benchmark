#!/bin/bash

# set -ex

#pwd
cd $(dirname $0)/../../grpc_benchmark-build
#pwd

./datastreamserver &

sleep 2

#./datastreamclient --num_clients 1 --data_size 10 --num_iterations 10 --chunk_size 64

./datastreamclient --num_clients 1 --data_size 500 --num_iterations 10 --chunk_size 1024

# 2 clients
#./datastreamclient --num_clients 2 --data_size 10 --num_iterations 10 --chunk_size 1024

killall -9 datastreamserver || true
