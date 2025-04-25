# Tugas 4 - Struktur Data dan Algoritma 2025

**Student Information:**
- Name: [Haikal Auli]
- NPM: [2308107010063]

## About This Project

This project implements and analyzes the performance of six different sorting algorithms:
- Bubble Sort
- Selection Sort 
- Insertion Sort
- Merge Sort
- Quick Sort
- Shell Sort

The algorithms are tested with both integer and string data of various sizes (from 10,000 to 2,000,000 elements) to compare their efficiency in terms of execution time.

## Project Structure

- `sorting_algorithms.h`: Header file containing implementations of all sorting algorithms
- `data_generator.c`: Program to generate random numbers and words for testing
- `main.c`: Main program that runs experiments and measures performance
- `sorting_results.csv`: Output file containing performance measurements

## How to Run

1. First, compile and run the data generator:
   ```
   gcc data_generator.c -o data_generator
   ./data_generator
   ```

2. Then, compile and run the main program:
   ```
   gcc main.c -o sorting_test
   ./sorting_test
   ```

3. The program will generate a CSV file with the sorting results

## Memory Usage Analysis

For memory usage analysis, you can use valgrind:

```
valgrind --tool=massif ./sorting_test
```

This will generate a massif.out file that can be analyzed with:

```
ms_print massif.out.[pid] > memory_analysis.txt
```

## Analysis Summary

The experimental results show that:

1. O(n²) algorithms (Bubble, Selection, Insertion) perform significantly worse than O(n log n) algorithms (Merge, Quick, Shell) as data size increases
2. Quick Sort generally performs the best for random data
3. Memory usage is higher for Merge Sort due to its auxiliary space requirements
4. String sorting requires more resources than integer sorting due to the additional overhead of string comparisons

[More detailed analysis will be included in the final report]