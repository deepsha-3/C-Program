#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6

char words[MAX_WORDS][WORD_LENGTH + 1];
int word_count = 0;

void load_words(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    while (fscanf(file, "%s", words[word_count]) == 1) {
        if (strlen(words[word_count]) == WORD_LENGTH) {
            for (int i = 0; i < WORD_LENGTH; i++) {
                words[word_count][i] = tolower(words[word_count][i]);
            }
            word_count++;
        }
        if (word_count >= MAX_WORDS) break;
    }

    fclose(file);
    printf("Loaded %d words\n", word_count);
}

void print_guess_feedback(const char* guess, const char* target) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == target[i]) {
            printf("\033[0;32m%c\033[0m", toupper(guess[i])); // Green for correct position
        } else if (strchr(target, guess[i]) != NULL) {
            printf("\033[0;33m%c\033[0m", toupper(guess[i])); // Yellow for correct letter, wrong position
        } else {
            printf("\033[0;37m%c\033[0m", toupper(guess[i])); // White for incorrect letter
        }
    }
    printf("\n");
}

int is_valid_guess(const char* guess) {
    if (strlen(guess) != WORD_LENGTH) return 0;
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (!isalpha(guess[i])) return 0;
    }
    return 1;
}

int main() {
    srand(time(NULL));
    load_words("words.txt");

    if (word_count == 0) {
        printf("No words loaded. Please check your word list file.\n");
        return 1;
    }

    const char* target_word = words[rand() % word_count];
    char guess[WORD_LENGTH + 1];
    int attempts = 0;

    printf("Welcome to Wordle!\n");
    printf("Try to guess the %d-letter word. You have %d attempts.\n", WORD_LENGTH, MAX_ATTEMPTS);

    while (attempts < MAX_ATTEMPTS) {
        printf("\nAttempt %d/%d. Enter your guess: ", attempts + 1, MAX_ATTEMPTS);
        scanf("%s", guess);

        for (int i = 0; i < WORD_LENGTH; i++) {
            guess[i] = tolower(guess[i]);
        }

        if (!is_valid_guess(guess)) {
            printf("Invalid guess. Please enter a %d-letter word.\n", WORD_LENGTH);
            continue;
        }

        attempts++;

        print_guess_feedback(guess, target_word);

        if (strcmp(guess, target_word) == 0) {
            printf("\nCongratulations! You've guessed the word in %d attempts!\n", attempts);
            return 0;
        }
    }

    printf("\nSorry, you've run out of attempts. The word was: %s\n", target_word);
    return 0;
}