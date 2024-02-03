#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h> /* assert() */

#define CELL_MAX (3 * 3 - 1)

// Funcion que crea las separaciones entre filas
void print_sep(int length)
{
    printf("\t ");
    for (int i = 0; i < length; i++)
        printf("................");
    printf("\n");
}
// Funcion que imprime el tablero
void print_board(char board[3][3])
{
    int cell = 0;

    print_sep(3);
    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(3);
    }
}
// Funcion que determina el ganador
char get_winner(char board[3][3])
{
    char winner = '-';
    // Ciclo que determina las filas
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            winner = board[i][0];
            return winner;
        }
        // Es importante determinar si la celda es no vacía, ya que sino el juego nunca 'progresará'
    }
    // Ciclo que determina las columnas
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] != '-' && board[0][j] == board[1][j] && board[1][j] == board[2][j])
        {
            winner = board[0][j];
            return winner;
        }
    }
    // Ciclo que determina las diagonales
    // Al ser unicamente 2 casos y muy distintos, por simple pattern matching se completa la funcion
    if (board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        winner = board[0][0];
        return winner;
    }
    if (board[0][2] != '-' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        winner = board[0][2];
        return winner;
    }
    return winner;
}

// Funcion que determina la existencia de celdas libres
bool has_free_cell(char board[3][3])
{
    // Necesitamos nuevamente generar el tablero, ya que no podemos acceder manualmente a las celdas
    bool free_cell = false;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '-')
            {
                free_cell = true;
                break;
            }
        }
        if (free_cell)
        {
            break;
        }
    }
    return free_cell;
}

int main(void)
{
    printf("[TicTacToe:]\n");

    char board[3][3] = {
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'}};

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board))
    {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0)
        {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX)
        {
            int row = cell / 3;
            int colum = cell % 3;
            if (board[row][colum] == '-')
            {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            }
            else
            {
                printf("\nCelda ocupada!\n");
            }
        }
        else
        {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-')
    {
        printf("Empate!\n");
    }
    else
    {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
