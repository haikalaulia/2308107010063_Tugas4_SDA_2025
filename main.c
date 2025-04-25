#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <psapi.h>
#include "sorting_algorithms.h"

// === Fungsi Tambahan ===

// Fungsi untuk mendapatkan penggunaan memori saat ini oleh proses
size_t ambil_penggunaan_memori_saat_ini() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    return memInfo.WorkingSetSize;
}

// Mengukur waktu dan estimasi memori untuk sorting array integer
// sort_func: fungsi sorting yang digunakan
// arr: array data
// n: jumlah elemen
// memory_used: pointer untuk menyimpan estimasi memori
// Mengembalikan waktu eksekusi dalam detik
double ukur_waktu_sort_int(void (*sort_func)(int[], int), int arr[], int n, size_t *memory_used) {
    clock_t mulai = clock();
    sort_func(arr, n);
    clock_t selesai = clock();
    *memory_used = n * sizeof(int);
    return ((double)(selesai - mulai)) / CLOCKS_PER_SEC;
}

// Mengukur waktu dan estimasi memori untuk sorting array string
// Sama seperti versi integer, namun memperhitungkan panjang string
double ukur_waktu_sort_str(void (*sort_func)(char *[], int), char *arr[], int n, size_t *memory_used) {
    clock_t mulai = clock();
    sort_func(arr, n);
    clock_t selesai = clock();
    *memory_used = n * sizeof(char *);
    for (int i = 0; i < n; i++) *memory_used += strlen(arr[i]) + 1;
    return ((double)(selesai - mulai)) / CLOCKS_PER_SEC;
}

// Membuat salinan array integer
int *salin_array_int(int src[], int n) {
    int *dest = malloc(n * sizeof(int));
    memcpy(dest, src, n * sizeof(int));
    return dest;
}

// Membuat salinan array string (deep copy)
char **salin_array_str(char *src[], int n) {
    char **dest = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) dest[i] = strdup(src[i]);
    return dest;
}

// Membebaskan memori array string
void bebas_array_str(char **arr, int n) {
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
}

// Membaca data integer dari file
int *baca_data_int(const char *filename, int count, size_t *memory_used) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    int *arr = malloc(count * sizeof(int));
    *memory_used = count * sizeof(int);
    for (int i = 0; i < count && fscanf(file, "%d", &arr[i]) == 1; i++);
    fclose(file);
    return arr;
}

// Membaca data string dari file
char **baca_data_str(const char *filename, int count, size_t *memory_used) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    char **arr = malloc(count * sizeof(char *));
    *memory_used = count * sizeof(char *);
    char buffer[100];
    for (int i = 0; i < count && fgets(buffer, sizeof(buffer), file); i++) {
        buffer[strcspn(buffer, "\n")] = '\0';
        arr[i] = strdup(buffer);
        *memory_used += strlen(buffer) + 1;
    }
    fclose(file);
    return arr;
}

// Menjalankan pengujian algoritma sorting dan mencetak hasilnya
void uji_algoritma_sort(FILE *file_hasil, const char *tipe, int ukuran, void *data_asli,
                        void (*fungsi_sort[])(void *, int),
                        const char *nama_algo[], int adalah_string) {
    printf("\n%-10s | %-10s | %-6s | %-12s | %-14s | %-15s\n",
           "Algoritma", "Tipe Data", "Ukuran", "Waktu (detik)", "Est Mem (byte)", "Actual Mem (KB)");
    printf("---------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < 6; i++) {
        size_t est_mem = 0;
        double waktu;
        size_t mem_aktual;
        if (!adalah_string) {
            int *copy = salin_array_int((int *)data_asli, ukuran);
            waktu = ukur_waktu_sort_int((void (*)(int[], int))fungsi_sort[i], copy, ukuran, &est_mem);
            mem_aktual = ambil_penggunaan_memori_saat_ini();
            printf("%-10s | %-10s | %-6d | %-12.6f | %-14zu | %-15zu\n",
                   nama_algo[i], tipe, ukuran, waktu, est_mem, mem_aktual / 1024);
            fprintf(file_hasil, "%s,%s,%d,%.6f,%zu,%zu\n",
                    nama_algo[i], tipe, ukuran, waktu, est_mem, mem_aktual / 1024);
            free(copy);
        } else {
            char **copy = salin_array_str((char **)data_asli, ukuran);
            waktu = ukur_waktu_sort_str((void (*)(char *[], int))fungsi_sort[i], copy, ukuran, &est_mem);
            mem_aktual = ambil_penggunaan_memori_saat_ini();
            printf("%-10s | %-10s | %-6d | %-12.6f | %-14zu | %-15zu\n",
                   nama_algo[i], tipe, ukuran, waktu, est_mem, mem_aktual / 1024);
            fprintf(file_hasil, "%s,%s,%d,%.6f,%zu,%zu\n",
                    nama_algo[i], tipe, ukuran, waktu, est_mem, mem_aktual / 1024);
            bebas_array_str(copy, ukuran);
        }
    }
}

// === Program Utama ===
int main() {
    int ukuran_data[] = {10000, 50000, 100000, 250000, 50000, 1000000, 1500000, 2000000};
    int jumlah_ukuran = sizeof(ukuran_data) / sizeof(ukuran_data[0]);

    FILE *file_hasil = fopen("sorting_results.csv", "w");
    if (!file_hasil) {
        perror("Gagal membuka file hasil");
        return 1;
    }
    fprintf(file_hasil, "Algorithm,Data Type,Size,Time (seconds),Memory (estimated bytes),Memory (actual KB)\n");

    const char *nama_algo[] = {"Bubble", "Selection", "Insertion", "Merge", "Quick", "Shell"};
    void (*sort_int[])(void *, int) = {
        (void (*)(void *, int))bubble_sort_int,
        (void (*)(void *, int))selection_sort_int,
        (void (*)(void *, int))insertion_sort_int,
        (void (*)(void *, int))merge_sort_int,
        (void (*)(void *, int))quick_sort_int,
        (void (*)(void *, int))shell_sort_int
    };
    void (*sort_str[])(void *, int) = {
        (void (*)(void *, int))bubble_sort_str,
        (void (*)(void *, int))selection_sort_str,
        (void (*)(void *, int))insertion_sort_str,
        (void (*)(void *, int))merge_sort_str,
        (void (*)(void *, int))quick_sort_str,
        (void (*)(void *, int))shell_sort_str
    };

    for (int i = 0; i < jumlah_ukuran; i++) {
        int ukuran = ukuran_data[i];
        printf("\n--- Pengujian ukuran: %d ---\n", ukuran);

        size_t dummy_mem;
        int *data_int = baca_data_int("data_angka.txt", ukuran, &dummy_mem);
        if (data_int) {
            uji_algoritma_sort(file_hasil, "angka", ukuran, data_int, sort_int, nama_algo, 0);
            free(data_int);
        } else {
            printf("Gagal membaca file data_angka.txt\n");
        }

        char **data_str = baca_data_str("data_kata.txt", ukuran, &dummy_mem);
        if (data_str) {
            uji_algoritma_sort(file_hasil, "kata", ukuran, data_str, sort_str, nama_algo, 1);
            bebas_array_str(data_str, ukuran);
        } else {
            printf("Gagal membaca file data_kata.txt\n");
        }
    }

    fclose(file_hasil);
    printf("\nSemua pengujian selesai. Hasil disimpan di sorting_results.csv\n");
    return 0;
}