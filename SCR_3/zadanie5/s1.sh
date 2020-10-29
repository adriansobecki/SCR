#!/bin/sh

trap "echo trapped" $(seq 1 15)

while true
do
    echo echo
    sleep 5
done
