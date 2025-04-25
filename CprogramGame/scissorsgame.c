#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int player_choice, computer_choice;
    const char* choices[] = {"Rock", "Paper", "Scissors"};
    
    // Seed the random number generator
    srand(time(NULL));
    
    printf("Let's play Rock Paper Scissors!\n");
    
    while (1) {
        // Get player's choice
        printf("Enter your choice (0 for Rock, 1 for Paper, 2 for Scissors, or -1 to quit): ");
        scanf("%d", &player_choice);
        
        if (player_choice == -1) {
            printf("Thanks for playing! Goodbye!\n");
            break;
        }
        
        if (player_choice < 0 || player_choice > 2) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }
        
        // Generate computer's choice
        computer_choice = rand() % 3;
        
        // Display choices
        printf("You chose: %s\n", choices[player_choice]);
        printf("Computer chose: %s\n", choices[computer_choice]);
        
        // Determine winner
        if (player_choice == computer_choice) {
            printf("It's a tie!\n");
        } else if ((player_choice == 0 && computer_choice == 2) ||
                   (player_choice == 1 && computer_choice == 0) ||
                   (player_choice == 2 && computer_choice == 1)) {
            printf("You win!\n");
        } else {
            printf("Computer wins!\n");
        }
        
        printf("\n");
    }
    
    return 0;
}