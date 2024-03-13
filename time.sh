#!/bin/bash

PROGRAMS=("sq_mat_ver_mult" "sq_mat_ver_mult_mpi" "sq_mat_ver_mul_openmp_tile" "sq_mat_ver_mul_mpi_tile")
SIZES=(64 128 256 512 1024 2048 4096 8192 16384 32768)

for program in "${PROGRAMS[@]}"; do
    for size in "${SIZES[@]}"; do
        total_time=0
        for (( i=1; i<=10; i++ )); do
            output=$(./$program $size) # Assuming all programs are executable
            time_taken=$(echo "$output" | grep -o '[0-9.]\+')
            total_time=$(echo "$total_time + $time_taken" | bc)
            echo "$i, $program, $size, $time_taken secs, $(echo "scale=6; $total_time / $i" | bc) secs" >> results.csv
        done
    done
done

