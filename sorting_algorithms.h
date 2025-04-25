#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Bubble Sort
 * 
 * Prinsip Kerja:
 * Mengulangi proses pemeriksaan sepasang elemen bersebelahan dan menukarnya
 * jika berada dalam urutan yang salah. Proses ini terus dilakukan hingga tidak ada lagi
 * elemen yang perlu ditukar.
 */
void bubble_sort_int(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void bubble_sort_str(char *arr[], int n) {
    int i, j;
    char *temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j], arr[j+1]) > 0) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

/**
 * Selection Sort
 * 
 * Prinsip Kerja:
 * Menemukan elemen terkecil dari bagian tidak terurut lalu menukarnya
 * dengan elemen pertama dari bagian tersebut. Proses ini diulangi sampai seluruh array terurut.
 */
void selection_sort_int(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void selection_sort_str(char *arr[], int n) {
    int i, j, min_idx;
    char *temp;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (strcmp(arr[j], arr[min_idx]) < 0) {
                min_idx = j;
            }
        }
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

/**
 * Insertion Sort
 * 
 * Prinsip Kerja:
 * Memasukkan setiap elemen ke dalam posisi yang sesuai dalam bagian array
 * yang telah terurut dengan menggeser elemen-elemen yang lebih besar.
 */
void insertion_sort_int(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void insertion_sort_str(char *arr[], int n) {
    int i, j;
    char *key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/**
 * Merge Sort
 * 
 * Prinsip Kerja:
 * Algoritma divide-and-conquer yang membagi array menjadi dua bagian,
 * melakukan sorting secara rekursif pada kedua bagian tersebut,
 * lalu menggabungkannya kembali dalam keadaan terurut.
 */
void merge_int(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_int_helper(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_int_helper(arr, l, m);
        merge_sort_int_helper(arr, m + 1, r);
        merge_int(arr, l, m, r);
    }
}

void merge_sort_int(int arr[], int n) {
    merge_sort_int_helper(arr, 0, n - 1);
}

void merge_str(char *arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    char **L = (char **)malloc(n1 * sizeof(char *));
    char **R = (char **)malloc(n2 * sizeof(char *));

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_str_helper(char *arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_str_helper(arr, l, m);
        merge_sort_str_helper(arr, m + 1, r);
        merge_str(arr, l, m, r);
    }
}

void merge_sort_str(char *arr[], int n) {
    merge_sort_str_helper(arr, 0, n - 1);
}

/**
 * Quick Sort
 * 
 * Prinsip Kerja:
 * Memilih satu elemen sebagai pivot, kemudian mempartisi array sehingga elemen
 * lebih kecil dari pivot berada di kiri dan yang lebih besar berada di kanan,
 * lalu melakukan rekursi pada masing-masing bagian.
 */
int partition_int(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1, temp;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return i + 1;
}

void quick_sort_int_helper(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition_int(arr, low, high);
        quick_sort_int_helper(arr, low, pi - 1);
        quick_sort_int_helper(arr, pi + 1, high);
    }
}

void quick_sort_int(int arr[], int n) {
    quick_sort_int_helper(arr, 0, n - 1);
}

int partition_str(char *arr[], int low, int high) {
    char *pivot = arr[high];
    int i = low - 1;
    char *temp;

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return i + 1;
}

void quick_sort_str_helper(char *arr[], int low, int high) {
    if (low < high) {
        int pi = partition_str(arr, low, high);
        quick_sort_str_helper(arr, low, pi - 1);
        quick_sort_str_helper(arr, pi + 1, high);
    }
}

void quick_sort_str(char *arr[], int n) {
    quick_sort_str_helper(arr, 0, n - 1);
}

/**
 * Shell Sort
 * 
 * Prinsip Kerja:
 * Pengembangan dari insertion sort, dengan melakukan sorting pada elemen-elemen
 * yang memiliki jarak tertentu (gap). Gap dikurangi secara bertahap hingga menjadi 1.
 */
void shell_sort_int(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void shell_sort_str(char *arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            char *temp = arr[i];
            int j;
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

#endif
