#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h> /* assert() */

#define CELL_MAX (4 * 4 - 1)
#define ROWS 5
#define COLS 5

// Empleo la constante ROWS para determinar el tamaño del tablero en varias funciones
// Podria utilizar otra constante distinta, pero como es exactamente el mismo numero, sirve

// Corregir: generalizacion para verificar celdas iguales

// Funcion que crea las separaciones entre filas
void print_sep(int length)
{
    printf("\t ");
    for (int i = 0; i < length; i++)
        printf("................");
    printf("\n");
}
// Funcion que imprime el tablero
void print_board(char board[ROWS][COLS])
{
    int cell = 0;

    print_sep(ROWS);
    for (int row = 0; row < ROWS; ++row)
    {
        for (int column = 0; column < COLS; ++column)
        {
            printf("\t | %d: %c ", cell, board[ROWS][COLS]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(ROWS);
    }
}
// Funcion que determina el ganador
char get_winner(char board[ROWS][COLS])
{
    char winner = '-';
    // Ciclo que determina las filas
    for (int i = 0; i < ROWS; i++)
    {
        if (board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] == board[i][3])
        {
            winner = board[i][0];
            return winner;
        }
        // Es importante determinar si la celda es no vacía, ya que sino el juego nunca 'progresará'
    }
    // Ciclo que determina las columnas
    for (int j = 0; j < ROWS; j++)
    {
        if (board[0][j] != '-' && board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[2][j] == board[3][j])
        {
            winner = board[0][j];
            return winner;
        }
    }
    // Ciclo que determina las diagonales
    if (board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] == board[3][3])
    {
        winner = board[0][0];
        return winner;
    }
    if (board[0][3] != '-' && board[0][3] == board[1][2] && board[1][2] == board[2][1] && board[2][1] == board[3][0])
    {
        winner = board[0][3];
        return winner;
    }
    return winner;
}

// Funcion que determina la existencia de celdas libres
bool has_free_cell(char board[ROWS][COLS])
{
    // Necesitamos nuevamente generar el tablero, ya que no podemos acceder manualmente a las celdas
    bool free_cell = false;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < ROWS; j++)
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

    char board[ROWS][COLS] = {
        {'-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-'}};

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
            int row = cell / ROWS;
            int colum = cell % COLS;
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
