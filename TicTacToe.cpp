#include <iostream>
#include <typeinfo>
#include <limits>
#include <ctime>

using namespace std;

/**
 * @brief Checks the spaces array for patterns.
 *
 * @param a Moves done so far in the game.
 * @param b The spaces array.
 * @param c Player symbol
 * @param d Npc symbol.
 * @param return Returns an int (0 no win), (1) player win, (2) npc win.
 */
int checkWin(int moves, char (&spaces)[3][3], char player, char npc)
{
    // Check for rows.
    for (auto &row : spaces)
    {
        int playerScore = 0;
        int npcScore = 0;
        for (auto &cell : row)
        {
            if (cell == player)
            {
                playerScore += 1;
            }
            else if (cell == npc)
            {
                npcScore += 1;
            }
        };
        // Check 3 in a row.
        if (playerScore == 3)
        {
            return 1;
        }
        else if (npcScore == 3)
        {
            return 2;
        }
    };

    // Check columns
    for (int col = 0; col < 3; ++col)
    {
        int playerScore = 0;
        int npcScore = 0;
        for (int row = 0; row < 3; ++row)
        {
            if (spaces[row][col] == player)
                playerScore++;
            else if (spaces[row][col] == npc)
                npcScore++;
        }
        if (playerScore == 3)
            return 1;
        if (npcScore == 3)
            return 2;
    }

    // Check main diagonal
    int playerDiag1 = 0;
    int npcDiag1 = 0;

    for (int i = 0; i < 3; ++i)
    {
        if (spaces[i][i] == player)
            playerDiag1++;
        else if (spaces[i][i] == npc)
            npcDiag1++;
    }

    if (playerDiag1 == 3)
        return 1;

    if (npcDiag1 == 3)
        return 2;

    // Check anti-diagonal
    int playerDiag2 = 0;
    int npcDiag2 = 0;

    for (int i = 0; i < 3; ++i)
    {
        if (spaces[i][2 - i] == player)
            playerDiag2++;
        else if (spaces[i][2 - i] == npc)
            npcDiag2++;
    }

    if (playerDiag2 == 3)
        return 1;
    if (npcDiag2 == 3)
        return 2;

    return 0;
};

/**
 * @brief Checks if anyone won and if not wether its a tie.
 *
 * @param a Checks the return of the "checkWin" function to see if anyone won.
 * @param b Moves done in the game.
 * @param return Returns true if tie.
 */
bool checkTie(int win, int moves)
{
    if (win == 0 && moves == 9)
    {
        return true;
    }

    return false;
};

/**
 * @brief Places the npc markers in the spaces array.
 *
 * @param a The spaces array.
 * @param b Uses the npc marker.
 */
void npcMove(char (&spaces)[3][3], char npc)
{
    int number;
    srand(time(0));

    // Npc marking.
    while (true)
    {
        // Generate random number.
        number = rand() % 9;
        // Find out what subarray the number belongs to.
        int row = number / 3;
        int col = number % 3;

        if (spaces[row][col] == ' ')
        {
            spaces[row][col] = npc;
            break;
        };
    };
};

/**
 * @brief Places the player markers in the spaces array.
 *
 * @param a The spaces array.
 * @param b Uses the player marker.
 */
void playerMove(char (&spaces)[3][3], char player)
{
    int number;

    do
    {
        cout << "Enter where you want to place your marker (1-9):";
        cin >> number;
        number--;
        // Find out what subarray the number belongs to.
        int row = number / 3;
        int col = number % 3;

        if (cin.fail())
        {
            cout << " Invalid input, please enter a number !" << endl;
            cin.clear();
            // Flush the buffer or you get endless outputs for the error xd.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (number > 8 || number < 0)
        {
            cout << "Enter a valid number" << endl;
        }
        else if (spaces[row][col] == ' ')
        {
            spaces[row][col] = player;
            break;
        }
        else
        {
            cout << "That box is already marked !" << endl;
        };
    } while (!number > 0 || !number < 8);
};

/**
 * @brief Creates a TicTacToe board using the spaces array.
 *
 * @param a Spaces array determines moves and empty spaces.
 */
void drawBoard(char (&spaces)[3][3]) // Passing as a reference, need the "begin()" and "end()" else pointer just gives address not size.
{
    // Loop to create a 3x3 grid.
    for (int i = 0; i < 3; ++i)
    {
        // Top layer.
        std::cout << "     |     |     \n";

        // Itterate through the spaces array to populate the locations with data.
        for (int j = 0; j < 3; ++j)
        {
            std::cout << "  " << spaces[i][j];
            if (j < 2)
                std::cout << "  |";
        };
        std::cout << "\n";

        if (i < 2)
        {
            std::cout << "_____|_____|_____\n";
        }
        else
        {
            std::cout << "     |     |     \n";
        };
    };
};

int main()
{
    // Count the number of moves
    int moves = 0;

    char player = ' ';
    char npc = ' ';
    bool running = true;

    // Array holding locations of characters.
    char spaces[3][3] = {};

    // Fill array with empty values, as to not declare them manually.
    for (auto &row : spaces)
    {
        for (auto &cell : row)
        {
            cell = ' ';
        };
    };

    // Ask the player what character they want to be.
    cout << "Please select your character (O/X):" << endl;

    // Take their input.
    cin >> player;
    // Turn their input in caps.
    player = toupper(player);

    // Check they picked one of the two options if not repromt.
    while (player != 'O' && player != 'X')
    {
        cout << "Please select a valid character (O/X)!" << endl;

        // Clear input before they enter anything new.
        cin.clear();

        // Assing the input to player and capitalize it again.
        cin >> player;
        player = toupper(player);
    };

    // Assing the other value to the computer.
    if (player == 'X')
    {
        npc = 'O';
    }
    else
    {
        npc = 'X';
    }

    // Draw the board
    drawBoard(spaces);

    // Declare true on player first turn if they chose 'X'.
    bool playerTurn = (player == 'X');

    while (running)
    {
        // Choose who goes first based on the mark the player chose.
        if (playerTurn == true)
        {
            playerMove(spaces, player);
        }
        else
        {
            npcMove(spaces, npc);
        };

        moves += 1;

        // Draw the board again to reflect markers.
        cout << "\n\n"
             << endl;
        drawBoard(spaces);

        // Check for winner or tie after 3 moves.
        if (moves >= 3)
        {
            int win = checkWin(moves, spaces, player, npc);

            // If player won.
            if (win == 1)
            {
                cout << "\n"
                     << " You won over your techno Lord ! " << endl;
                return 0;
            }
            // If npc won.
            else if (win == 2)
            {
                cout << "\n"
                     << " The npc has slaughtered you !" << endl;
                return 0;
            }
            // If you've both been losers.
            else
            {
                bool tie = false;
                tie = checkTie(win, moves);

                if (tie == true)
                {
                    cout << "\n"
                         << "The gods grew tired of your game and have anihilated you two" << endl;
                }
            };
        };

        playerTurn = !playerTurn;
    };
    return 0;
};
