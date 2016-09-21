#!/bin/bash

# set -ex

#pwd
cd $(dirname $0)/../../grpc_benchmark-build
#pwd

#./datastreamserver &

#sleep 2


# ####### 1 client
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 10 --num_iterations 10 --chunk_size 64
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 10 --num_iterations 10 --chunk_size 128
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 10 --num_iterations 10 --chunk_size 256
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 10 --num_iterations 10 --chunk_size 512
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 10 --num_iterations 10 --chunk_size 1024

# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 50 --num_iterations 10 --chunk_size 64
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 50 --num_iterations 10 --chunk_size 128
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 50 --num_iterations 10 --chunk_size 256
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 50 --num_iterations 10 --chunk_size 512
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 50 --num_iterations 10 --chunk_size 1024


# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 100 --num_iterations 10 --chunk_size 64
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 100 --num_iterations 10 --chunk_size 128
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 100 --num_iterations 10 --chunk_size 256
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 100 --num_iterations 10 --chunk_size 512
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 1 --data_size 100 --num_iterations 10 --chunk_size 1024

####### 2 clients
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 10 --num_iterations 10 --chunk_size 64
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 10 --num_iterations 10 --chunk_size 128
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 10 --num_iterations 10 --chunk_size 256
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 10 --num_iterations 10 --chunk_size 512
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 10 --num_iterations 10 --chunk_size 1024

# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 50 --num_iterations 10 --chunk_size 64
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 50 --num_iterations 10 --chunk_size 128
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 50 --num_iterations 10 --chunk_size 256
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 50 --num_iterations 10 --chunk_size 512
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 50 --num_iterations 10 --chunk_size 1024


# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 100 --num_iterations 10 --chunk_size 64
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 100 --num_iterations 10 --chunk_size 128
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 100 --num_iterations 10 --chunk_size 256
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 100 --num_iterations 10 --chunk_size 512
# ./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 2 --data_size 100 --num_iterations 10 --chunk_size 1024


####### 3 clients
./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 10 --num_iterations 10 --chunk_size 64
./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 10 --num_iterations 10 --chunk_size 128
./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 10 --num_iterations 10 --chunk_size 256
./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 10 --num_iterations 10 --chunk_size 512
./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 10 --num_iterations 10 --chunk_size 1024

./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 50 --num_iterations 10 --chunk_size 64
./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 50 --num_iterations 10 --chunk_size 128
./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 50 --num_iterations 10 --chunk_size 256
./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 50 --num_iterations 10 --chunk_size 512
./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 50 --num_iterations 10 --chunk_size 1024


./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 100 --num_iterations 10 --chunk_size 64
./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 100 --num_iterations 10 --chunk_size 128
./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 100 --num_iterations 10 --chunk_size 256
./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 100 --num_iterations 10 --chunk_size 512
./datastreamclient --address 10.88.5.100 --port 50051 --num_clients 3 --data_size 100 --num_iterations 10 --chunk_size 1024



# killall -9 datastreamserver || true
