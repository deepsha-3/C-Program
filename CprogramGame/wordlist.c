#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

char words[MAX_WORDS][MAX_WORD_LENGTH];
int word_count = 0;

void load_words(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    while (fgets(words[word_count], MAX_WORD_LENGTH, file) != NULL) {
        words[word_count][strcspn(words[word_count], "\n")] = 0; // Remove newline
        if (strlen(words[word_count]) > 0) {
            word_count++;
        }
        if (word_count >= MAX_WORDS) break;
    }

    fclose(file);
    printf("Loaded %d words from %s\n", word_count, filename);
}

void scramble_word(char* word, char* scrambled) {
    int len = strlen(word);
    strcpy(scrambled, word);

    for (int i = len - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = scrambled[i];
        scrambled[i] = scrambled[j];
        scrambled[j] = temp;
    }
}

void to_lowercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int main() {
    srand(time(NULL));
    load_words("wordlist.txt");

    if (word_count == 0) {
        printf("No words loaded. Please check your word list file.\n");
        return 1;
    }

    printf("Welcome to the Word Scramble Game!\n");
    printf("Try to guess the original word from the scrambled letters.\n");

    while (1) {
        int index = rand() % word_count;
        char scrambled[MAX_WORD_LENGTH];
        char guess[MAX_WORD_LENGTH];

        scramble_word(words[index], scrambled);

        printf("\nScrambled word: %s\n", scrambled);
        printf("Your guess (or 'quit' to exit): ");
        scanf("%s", guess);

        to_lowercase(guess);

        if (strcmp(guess, "quit") == 0) {
            printf("Thanks for playing! Goodbye!\n");
            break;
        }

        to_lowercase(words[index]);

        if (strcmp(guess, words[index]) == 0) {
            printf("Correct! The word was: %s\n", words[index]);
        } else {
            printf("Sorry, that's not correct. The word was: %s\n", words[index]);
        }
    }

    return 0;
}