Name: [Haikal Auli]
NPM: [2308107010063]

Tujuan Tugas
Membandingkan kinerja 6 algoritma sorting klasik (Bubble, Selection, Insertion, Merge, Quick, Shell) dalam mengurutkan data integer dan string dengan berbagai ukuran.

Isi Tugas
Implementasi semua algoritma dalam file sorting_algorithms.h untuk tipe int dan string.

Program utama (main.c):
Membaca data dari file (data_angka.txt, data_kata.txt)
Melakukan pengujian sorting untuk setiap algoritma
Mengukur waktu eksekusi dan penggunaan memori
Menyimpan hasil ke file sorting_results.csv

Eksperimen
Ukuran data diuji dari 10.000 hingga 2.000.000 elemen.
Hasil pengujian menunjukkan bahwa:
Merge Sort, Quick Sort, dan Shell Sort unggul pada data besar.
Bubble, Selection, Insertion Sort hanya cocok untuk data kecil.
Sorting string membutuhkan waktu dan memori lebih besar dibanding angka.

Kesimpulan
Algoritma dengan kompleksitas O(n log n) lebih cocok untuk dataset besar. Quick Sort tercepat, Merge Sort paling stabil, dan Shell Sort efisien serta mudah diimplementasikan.