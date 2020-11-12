#!/bin/sh
trap "" 1
trap "echo trapped" 3 4 5

while true
do
    echo echo
    sleep 5
done
