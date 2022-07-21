#include <iostream>
#include <string>

#define GRID_SIZE 3

using namespace std;

class Game {

private:
    char grid[GRID_SIZE][GRID_SIZE];

public:
    void generate_grid() {
        int number = 1;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++){
                grid[i][j] = to_string(number).c_str()[0];
                number += 1;
            } 
        }
    }

    void show_grid() {
        printf("\n------------\n");
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++){
                printf(" %c |", grid[i][j]);
            } 
            printf("\n------------\n");
        }
    }

    void ask_user_move() {
        string input;

        while (true) {
            puts("Player 1s turn: Choose where to move"); //using instead of printf as it automatically gives new line.
            getline(cin, input);

            if (input != "") {
                char first = input.c_str()[0];
                if (first >= '1' && first <= '9') {
                    int first_num = first - '0';
                    int index = first_num -  1; //0-8

                    int row = index / 3;
                    int col = index % 3;

                    char grid_pos = grid[row][col];

                    if (grid_pos == 'X' || grid_pos == 'O') {
                        puts("The chosen position is already taken.");
                    } else {
                        grid[row][col] = 'X';
                        break;
                    }
                } else {
                    puts("Please insert a number in the range of 1-9.");
                }
            } else {
                puts("Please enter something!");
            }
        } 
    }

    void checkWins() {
        const char* win_moves[8] = {
            "123",
            "456",
            "789",
            "147",
            "258",
            "369",
            "159",
            "753"
        };

        for (int i = 0; i < 8; i++) {
            bool winner = true;
            char prev_pos = '0';
            const char* win_move = win_moves[i];

            for (int j = 0; j < 3; j++ ) {
                char character = win_move[j];

                int first_num = character - '0';
                int grid_space = first_num - 1;

                int row = grid_space / GRID_SIZE;
                int col = grid_space % GRID_SIZE;

                char grid_char = grid[row][col];

                if (prev_pos == '0') {
                    prev_pos = grid_char;
                } else if (prev_pos == grid_char) {
                    continue;
                } else {
                    winner = false;
                    break;
                }
            }
            if (winner) {
                puts("****** Winner Winner Chicken Dinner *****");
                exit(0);
                break;
            }
        }
    }

    void AI_turn() {
        while (true) {
            int ai_choice = (rand() % 9) + 1;
            int row = (ai_choice - 1) / GRID_SIZE;
            int col = (ai_choice - 1) % GRID_SIZE;

            char grid_pos = grid[row][col];

            if (grid_pos == 'X' || grid_pos == 'O') {
                continue;
            } else {
                printf("The Ai played at %d. \n", ai_choice);
                grid[row][col] = 'O';
                break;

            }
        }
    }

    void secondPlayerTurn() {
        string input;
        while (true) {
            puts("Player 2s turn: Choose where to move"); 
            getline(cin, input);

            if (input != "") {
                char first = input.c_str()[0];
                if (first >= '1' && first <= '9') {
                    int first_num = first - '0';
                    int index = first_num -  1; //0-8

                    int row = index / 3;
                    int col = index % 3;

                    char grid_pos = grid[row][col];

                    if (grid_pos == 'X' || grid_pos == 'O') {
                        puts("The chosen position is already taken.");
                    } else {
                        grid[row][col] = 'O';
                        break;
                    }
                } else {
                    puts("Please insert a number in the range of 1-9.");
                }
            } else {
                puts("Please enter something!");
            }
        } 
    }
    bool playWithAi() {
        string input;
        while (true) {
            puts("Play against AI or person? ");
            getline(cin, input);
            if (input == "Ai" || input == "AI" || input == "ai") {
                return true;
            } else {
                return false;
            }
        }
    }
    
    Game() {
        generate_grid();
        show_grid();
        checkWins();

        while (true) {
            ask_user_move();
            show_grid();
            checkWins();
            secondPlayerTurn();
            show_grid();
            checkWins();
        }
    }
};



int main(int argc, char *argv[]) {
    Game game;
    return 0;

}