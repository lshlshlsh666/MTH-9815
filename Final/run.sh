#!/bin/bash

mkdir -p build
cd build || exit

cmake ..

if make -j8; then
    ./generate_data

    ./trading_system &
    server_pid=$!
    sleep 3
    
    # start all clients in background
    ./load_price &
    ./load_trade &
    ./load_market &
    ./load_inquiry &
    
    # trap SIGINT and terminate all processes
    trap 'kill $server_pid; pkill -P $$; exit' SIGINT

    # wait all processes to exit
    wait

    # kill all processes
    kill $server_pid
    pkill -P $$

    cd ..

else
    echo "Build failed"
fi
