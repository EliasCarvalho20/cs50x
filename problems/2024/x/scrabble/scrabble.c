#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int sum_char(int letters_len, string player_string) {
    int total_points = 0;
    for (int i = 0; i < strlen(player_string); i++) {
        for (int j = 0; j < letters_len; j++) {
            if (ispunct(player_string[i])) {
                continue;
            }
            if (toupper (player_string[i]) == letters[j]) {
                total_points += points[j];
            }
        }
    }
    return total_points;
}

int main(void) {
    int letters_len = strlen(letters);
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    int points_player1 = sum_char(letters_len, player1);
    int points_player2 = sum_char(letters_len, player2);

    if (points_player1 == points_player2) {
        printf("Tie!");
    }
    else if (points_player1 > points_player2) {
        printf("Player 1 wins");
    }
    else {
        printf("Player 2 wins");        
    }
    return 0;
}
