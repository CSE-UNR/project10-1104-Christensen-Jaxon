// Jaxon Christensen
// Project 10 

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define WORD_LENGTH 5
#define MAX_GUESSES 6

// Function prototypes
bool loadWord(char word[]);
bool isValidGuess(char guess[]);
void toLowerStr(char str[]);
void checkGuess(char guess[], char word[], char result[], char markers[]);
void displayGuesses(char guesses[][WORD_LENGTH + 1], char markers[][WORD_LENGTH + 1], int numGuesses);
void playGame();

int main() {
    playGame();
    return 0;
}

// Reads the mystery word from word.txt
bool loadWord(char word[]) {
    FILE *file = fopen("word.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open word.txt\n");
        return false;
    }
    fscanf(file, "%5s", word);
    fclose(file);
    return true;
}

// Checks if guess is exactly 5 letters and alphabetic
bool isValidGuess(char guess[]) {
    if (strlen(guess) != WORD_LENGTH) return false;
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (!isalpha(guess[i])) return false;
    }
    return true;
}

// Converts a string to lowercase
void toLowerStr(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Compares guess to the mystery word, sets capitalization and ^ markers
void checkGuess(char guess[], char word[], char result[], char markers[]) {
    bool used[WORD_LENGTH] = { false };
    for (int i = 0; i < WORD_LENGTH; i++) {
        result[i] = tolower(guess[i]);
        markers[i] = ' ';
        if (guess[i] == word[i]) {
            result[i] = toupper(guess[i]);
            used[i] = true;
        }
    }
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result[i] == toupper(result[i])) continue;
        for (int j = 0; j < WORD_LENGTH; j++) {
            if (!used[j] && guess[i] == word[j]) {
                markers[i] = '^';
                used[j] = true;
                break;
            }
        }
    }
    result[WORD_LENGTH] = '\0';
    markers[WORD_LENGTH] = '\0';
}

// Displays all guesses with ^ markers and formatting
void displayGuesses(char guesses[][WORD_LENGTH + 1], char markers[][WORD_LENGTH + 1], int numGuesses) {
    for (int i = 0; i < numGuesses; i++) {
        printf("%s\n", guesses[i]);
        printf("%s\n", markers[i]);
    }
}

// Main game logic
void playGame() {
    char word[WORD_LENGTH + 1];
    if (!loadWord(word)) return;

    char input[100];
    char guesses[MAX_GUESSES][WORD_LENGTH + 1];
    char markers[MAX_GUESSES][WORD_LENGTH + 1];
    char originalGuesses[MAX_GUESSES][WORD_LENGTH + 1];
    int guessCount = 0;

    while (guessCount < MAX_GUESSES) {
        if (guessCount < MAX_GUESSES - 1) {
            printf("GUESS %d! Enter your guess: ", guessCount + 1);
        } else {
            printf("FINAL GUESS : ");
        }

        scanf("%s", input);
        toLowerStr(input);

        while (!isValidGuess(input)) {
            printf("Your guess must be 5 letters long.\n");
            printf("Please try again: ");
            scanf("%s", input);
            toLowerStr(input);
        }

        strcpy(originalGuesses[guessCount], input);
        checkGuess(input, word, guesses[guessCount], markers[guessCount]);
        guessCount++;

        printf("===============================\n");
        displayGuesses(guesses, markers, guessCount);

        if (strcmp(originalGuesses[guessCount - 1], word) == 0) {
            printf("You guessed the word!\n");
            return;
        }
    }

    printf("You lost, better luck next time!\n");
}

