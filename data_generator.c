#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function to generate random numbers
void generate_random_numbers(const char *filename, int count, int max_value) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File tidak dapat dibuka");
        return;
    }
    
    srand(time(NULL)); // Inisialisasi seed
    for (int i = 0; i < count; i++) {
        int num = rand() % max_value;
        fprintf(fp, "%d\n", num);
    }
    
    fclose(fp);
    printf("Successfully generated %d random numbers in %s\n", count, filename);
}

// Function to generate random words
void random_word(char *word, int length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < length; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        word[i] = charset[key];
    }
    word[length] = '\0';
}

void generate_random_words(const char *filename, int count, int max_word_length) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File tidak dapat dibuka");
        return;
    }
    
    srand(time(NULL));
    char word[100];
    for (int i = 0; i < count; i++) {
        int length = (rand() % (max_word_length - 3)) + 3; // panjang kata minimal 3
        random_word(word, length);
        fprintf(fp, "%s\n", word);
    }
    
    fclose(fp);
    printf("Successfully generated %d random words in %s\n", count, filename);
}

int main() {
    // Generate 2,000,000 random numbers
    generate_random_numbers("data_angka.txt", 2000000, 2000000);
    
    // Generate 2,000,000 random words
    generate_random_words("data_kata.txt", 2000000, 20);
    
    return 0;
}