#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief This function displays the menu and take the choice
 * @param turn The number which tell about the turn 0 means player 1 and 1 means player 2
 * 
 * @return int The number of the choice in the menu
 */
int displayMenu(int turn)
{
    char symbol;
    int choice = 0;
    if (turn == 0)
    {
        symbol = 'X';
    }
    else if (turn == 1)
    {
        symbol = 'O';
    }
    printf("\n******************MENU******************\n");
    printf("---------------Player %d(%c)--------------\n", turn + 1, symbol);
    printf("1: Make your turn.\n");
    printf("2: Undo a Move.\n");
    printf("3: Reset the game.\n");
    printf("4: Redo the latest undone.\n");
    printf("5: Pass the turn to the next player.\n");
    printf("6: Import the game.\n");
    printf("7: Export the game.\n");
    printf("8: Exit the game.");
    printf("\n\tPlease enter your choice: ");
    // This loops make sure that the input is valid
    while (1)
    {
        // if input is int and it lies under the range
        if (scanf("%d", &choice) == 1 && choice > 0 && choice <= 8)
        {
            // exiting the loop because input was valid
            break;
        }
        else
        {
            printf("\tYou entered a wrong choice, please enter again: ");
            //  consuming the invalid tokens
            while (getchar() != '\n')
            {
            }
        }
    }
    return choice;
}

/**
 * @brief This displays the gameboard to the console
 * 
 * @param gameBoard The 2 dimensional character array that store the board
 */
void displayBoard(char gameBoard[3][3])
{
    printf(" \n");
    int i, j;
    for (i = 0; i < 3; i++)
    {
        printf("\t\t\t");
        for (j = 0; j < 3; j++)
        {
            printf("  %c  ", gameBoard[i][j]);
        }
        printf("\n\n");
    }
    printf(" \n ");
}

/**
 * @brief This functions checks the status of the board and determines if game is a tie or some one is winner
 * 
 * @param gameBoard The 2 dimensional character array that store the board
 * @return int The status of game 0, if winner is player 1. 1, if winner is player 2. 2 if game is a tie. -1 if no winner ot tie
 */
int checkWinner(char gameBoard[3][3])
{
    int i, j = 0;

    // checking rows
    for (i = 0; i < 3; i++)
    {
        if ((gameBoard[i][0] == 'X') && (gameBoard[i][1] == 'X') && (gameBoard[i][2] == 'X'))
        {
            return 0;
        }
        else if ((gameBoard[i][0] == 'O') && (gameBoard[i][1] == 'O') && (gameBoard[i][2] == '0'))
        {
            return 1;
        }
    }

    // checking columns
    for (j = 0; j < 3; j++)
    {
        if ((gameBoard[0][j] == 'X') && (gameBoard[1][j] == 'X') && (gameBoard[2][j] == 'X'))
        {
            return 0;
        }
        else if ((gameBoard[0][j] == 'O') && (gameBoard[1][j] == 'O') && (gameBoard[2][j] == 'O'))
        {
            return 1;
        }
    }
    // checking right and left diagonal
    if (((gameBoard[0][0] == 'O') && (gameBoard[1][1] == 'O') && (gameBoard[2][2] == 'O')) ||
        ((gameBoard[0][2] == 'O') && (gameBoard[1][1] == 'O') && (gameBoard[2][0] == 'O')))
    {
        return 1;
    }
    if (((gameBoard[0][0] == 'X') && (gameBoard[1][1] == 'X') && (gameBoard[2][2] == 'X')) ||
        ((gameBoard[0][2] == 'X') && (gameBoard[1][1] == 'X') && (gameBoard[2][0] == 'X')))
    {
        return 0;
    }
    int blankFlag = 0;
    // checking for tie
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            if (gameBoard[i][j] == '-')
            {
                blankFlag = 1;
            }
        }
    // true means that no space left for input so game is a tie
    if (blankFlag == 0)
    {
        return 2;
    }
    return -1;
}

/**
 * @brief This function make sure that valid rows and column numbers are entered
 * 
 * @return int The valid input in range
 */
int inputNumber()
{
    int number = -1;
    while (1)
    {
        // if input is int and it lies under the range
        if (scanf("%d", &number) == 1 && number >= 1 && number <= 3)
        {
            // as index starts from 0
            number = number - 1;
            // exiting the loop because input was valid
            break;
        }
        else
        {
            printf("\tYou entered a wrong choice, please enter again (1-3): ");
            //  consuming the invalid tokens
            while (getchar() != '\n')
            {
            }
        }
    }
    return number;
}

/**
 * @brief This copies the state from one array to second array which is needed when redo undo of moves are done
 *
 * @param source The 2 dimensional board which needs to be copied
 * @param destination The array in which the board will be stored
 */
void copyState(char source[3][3], char destination[3][3])
{
    int i, j = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            destination[i][j] = source[i][j];
        }
    }
}
/**
 * @brief This function takes the block choice and update the gameBoard
 * 
 * @param gameBoard The 2 dimensional character array that store the board
 * @param allMoves The 3 dimensional array that stores all of the boards state when a move is done 
 * @param turn The variable that will tell about player's turn
 * @param moveNumber The overall move number in the game passed as reference so changes reflect back in main 
 */
void makeTurn(char gameBoard[3][3], char allMoves[12][3][3], int turn, int *moveNumber)
{
    printf("\nPlayer %d's turn\n", turn + 1);
    while (1)
    {
        printf("Enter the row number: ");
        int row = inputNumber();
        printf("Enter the column number: ");
        int column = inputNumber();

        if (turn == 0 && gameBoard[row][column] == '-') // replacing block with the symobol os player 1
        {
            gameBoard[row][column] = 'X';
            break;
        }
        else if (turn == 1 && gameBoard[row][column] == '-') // replacing block with the symobol os player 2
        {
            gameBoard[row][column] = 'O';
            break;
        }
        else if (gameBoard[row][column] == 'X')
        {
            printf("\n\tThis space is already taken by X.\n");
        }
        else if (gameBoard[row][column] == 'O')
        {
            printf("\n\tThis space is already taken by O.");
        }
    }

    // copying the current state in all the moves so undo and redo can be performed
    *moveNumber = *moveNumber + 1;
    copyState(gameBoard, allMoves[*moveNumber]);
}
/**
 * @brief This functions resets the board and the game
 * 
 * @param gameBoard The 2 dimensional character array that store the board
 */
void resetTheGame(char gameBoard[3][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            gameBoard[i][j] = '-';
        }
    }
    printf("Game reset successfully.\n");
}
/**
 * @brief This function undo the moves
 * 
 * @param gameBoard The 2 dimensional character array that store the board values
 * @param allMoves The 3 dimensional array that stores all of the boards state when a move is placed 
 * @param turn The variable to detect the player's turn
 * @param moveNumber The overall move number in the game
 * @param undoNumber The number of the move when undone
 * @return int Return 1 if successful and 0 if not successful
 */
int undoMove(char gameBoard[3][3], char allMoves[12][3][3], int turn, int *moveNumber, int *undoNumber)
{
    printf("\nPlayer %d did undo\n", turn + 1);
    // printf("Undo number is %d\n", *undoNumber);
    // printf("Move number is %d\n", *moveNumber);

    // if only the first move is done
    if (*undoNumber == 1)
    {
        resetTheGame(gameBoard);
        *undoNumber = *undoNumber - 1;
        return 1;
    }
    else if (*undoNumber > 1) //checking if undoing is possible
    {
        *undoNumber = *undoNumber - 1;
        copyState(allMoves[*undoNumber], gameBoard);
        printf("Undo done\n");
        return 1;
    }
    else
    {
        printf("Undo can not be performed at this moment\n");
    }
    return 0;
}

/**
 * @brief This function redo the moves that are undone
 * 
 * @param gameBoard The 2 dimensional character array that store the board values
 * @param allMoves The 3 dimensional array that stores all of the boards state when a move is placed 
 * @param turn The variable to detect the player's turn
 * @param moveNumber The overall move number in the game
 * @param undoNumber The number of the move when undone
 * @return int Return 1 if successful and 0 if not successful
 */
int redoMove(char gameBoard[3][3], char allMoves[12][3][3], int turn, int *moveNumber, int *undoNumber)
{
    printf("\nPlayer %d did redo\n", turn + 1);
    // printf("Undo number is %d\n", *undoNumber);
    // printf("Move number is %d\n", *moveNumber);
    // if the undo moves are performed
    if (*undoNumber < *moveNumber)
    {
        // increasing the position to the next move which is undone
        *undoNumber = *undoNumber + 1;
        // copying it in to the board
        copyState(allMoves[*undoNumber], gameBoard);
        printf("REDO done\n");
        return 1;
    }
    else // Display a message that it is not possible
    {
        printf("Can not perform more undo\n");
    }
    return 0;
}

/**
 * @brief This function export the game to file
 * 
 * @param gameBoard The 2 dimensional character array that store the board values
 * @param allMoves The 3 dimensional array that stores all of the boards state when a move is placed 
 * @param moveNumber The overall move number in the game
 * @param undoNumber The number of the move when undone
 * @param turn The variable to detect the player's turn
 * @param moveDone The variable which stores the total move
 * @param latestUndone The variable which stores the latest undone move number 
 */

void exportGame(char gameBoard[3][3], char allMoves[12][3][3], int moveDone, int moveNumber, int latestUndone, int turn)
{
    //clearing the extra tokens
    while (getchar() != '\n')
    {
    }
    char fileName[40];
    printf("Enter the file name to save the game configuration: ");
    fgets(fileName, 40, stdin);
    strtok(fileName, "\n");
    FILE *file;
    file = fopen(fileName, "wb");

    if (file == NULL)
    {
        printf("Error while open file.\n");
        return;
    }
    // writing int values
    fprintf(file, "%d\n", turn);
    fprintf(file, "%d\n", latestUndone);
    fprintf(file, "%d\n", moveNumber);
    fprintf(file, "%d\n", moveDone);

    //writing current state of board
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            fprintf(file, "%c ", gameBoard[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    // writing all moves
    int k = 0;
    for (k = 0; k < 12; k++)
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                fprintf(file, "%c ", allMoves[k][i][j]);
            }
            fprintf(file, "\n");
        }
        fprintf(file, "\n");
    }
    // closing file
    fclose(file);
    printf("Game saved to %s\n", fileName);
}

/**
 * @brief This function impport the game from a file
 * 
 * @param gameBoard The 2 dimensional character array that store the board values
 * @param allMoves The 3 dimensional array that stores all of the boards state when a move is placed 
 * @param moveNumber The overall move number in the game
 * @param undoNumber The number of the move when undone
 * @param turn The variable to detect the player's turn
 * @param moveDone The variable which stores the total move
 * @param latestUndone The variable which stores the latest undone move number 
 */

void importGame(char gameBoard[3][3], char allMoves[12][3][3], int *moveDone, int *moveNumber, int *latestUndone, int *turn)
{
    //clearing the extra tokens
    while (getchar() != '\n')
    {
    }
    char fileName[40];
    printf("Enter the file name to import the game: ");
    fgets(fileName, 40, stdin);
    strtok(fileName, "\n");
    FILE *file;
    file = fopen(fileName, "rt");

    if (file == NULL)
    {
        printf("Error while reading the file.\n");
        return;
    }
    // importing variables
    fscanf(file, "%d\n", turn);
    fscanf(file, "%d\n", latestUndone);
    fscanf(file, "%d\n", moveNumber);
    fscanf(file, "%d\n", moveDone);
    printf("%d\n%d\n%d\n%d\n", *turn, *latestUndone, *moveNumber, *moveDone);

    // importing current state of board
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            fscanf(file, "%c ", &gameBoard[i][j]);
        }
        fscanf(file, "\n");
    }
    fscanf(file, "\n");
    // importing moves
    int k = 0;
    for (k = 0; k < 12; k++)
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                fscanf(file, "%c ", &allMoves[k][i][j]);
            }
            fscanf(file, "\n");
        }
        fscanf(file, "\n");
    }
    // closing file
    fclose(file);
    printf("Game imported from %s\n", fileName);
}
/**
 * @brief starting point of the program
 * 
 * @param argc argument count given when running the executable
 * @param argv argument values given
 * @return int return status
 */
int main(int argc, char **argv)
{
    int winner = 0;       // The number which have the status about the winner
    int moveDone = 0;     // When a player will do a move he has to pass it until he undo
    int moveNumber = 0;   // The overall move number
    int latestUndone = 0; // The number which tracks the undo
    int turn = 0;         // The number to detect the player's turn
    char allMoves[12][3][3] = {0};
    // 3D array will store all of the moves
    char gameBoard[3][3] = {{'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'}}; // The game board
    printf("******************Welcome to the Tick Tock Game******************\n");
    displayBoard(gameBoard); // Display the board at start

    // Init array with '-'
    int i, j, k;
    for (i = 0; i < 12; i++)
        for (j = 0; j < 3; j++)
            for (k = 0; k < 3; k++)
                allMoves[i][j][k] = '-';

    while (1)
    {
        int choice = displayMenu(turn);
        switch (choice)
        {
        case 1:
        {
            if (moveDone == 0)
            {
                moveDone = 1;
                makeTurn(gameBoard, allMoves, turn, &moveNumber);
                latestUndone = moveNumber;
            }
            else
            {
                printf("\n\tMove already done!\n");
            }
            break;
        }
        case 2:
        {
            // if undo is successfull
            if (undoMove(gameBoard, allMoves, turn, &moveNumber, &latestUndone))
            {
                // make the player to do a move
                moveDone = 0;
            }
            break;
        }
        case 3:
        {
            // resetting the moves
            resetTheGame(gameBoard);
            moveDone = 0;
            latestUndone = 0;
            moveNumber = 0;
            break;
        }
        case 4:
        {
            // if the redo is done
            if (redoMove(gameBoard, allMoves, turn, &moveNumber, &latestUndone))
            {
                // stop the player to make another move
                moveDone = 1;
            }
            break;
        }
        case 5: // Passing turn
        {
            // switching turns
            if (turn == 0)
            {
                turn = 1;
            }
            else
            {
                turn = 0;
            }
            moveDone = 0;
            // when the players is passed the redo history is erased
            moveNumber = latestUndone;
            break;
        }
        case 6:
        {
            importGame(gameBoard, allMoves, &moveDone, &moveNumber, &latestUndone, &turn);
            break;
        }
        case 7:
        {
            exportGame(gameBoard, allMoves, moveDone, moveNumber, latestUndone, turn);
            break;
        }
        case 8:
        {
            while (getchar() != '\n')
            {
            }
            printf("Good Bye!\n");
            printf("Do you want to export the game (Y/N)?  ");
            char c = 'N';
            c = getchar();
            if (c == 'Y' || c == 'y')
            {
                exportGame(gameBoard, allMoves, moveDone, moveNumber, latestUndone, turn);
            }
            return 1; //exiting the game
        }
        }
        displayBoard(gameBoard);
        winner = checkWinner(gameBoard);
        // if game has no spaces left
        if (winner != -1)
        {
            break;
        }
    }
    if (winner == 0)
    {
        printf("\n\t*********Player 1 Won(X)*********\n");
    }
    else if (winner == 1)
    {
        printf("\n\t*********Player 2 Won(O)*********\n");
    }
    else if (winner == 2)
    {
        printf("\n\t*******It is a tie*******\n");
    }

    printf("Good Bye!\n");
    return 2;
}
