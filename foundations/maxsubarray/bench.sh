#!/bin/bash

for i in {1000000..200000}; do
    echo "n = $i:";
    echo "recursive:"
    start=$(date +%s%3N)
    echo "$i" | xargs ./recursive
    end=$(date +%s%3N)
    echo "$end - $start" | bc
done