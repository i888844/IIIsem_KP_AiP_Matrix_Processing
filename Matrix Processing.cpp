#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "windows.h"
#include "locale.h"

#pragma warning(disable: 4996)

double** create_matrix(int rows, int columns)
{
    double** matrix = (double**)calloc(rows, sizeof(double*));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (double*)calloc(columns, sizeof(double));
    }
    return matrix;
}

void output_matrix(double** matrix, int columns, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%10.2lf", matrix[i][j]);
        }
        printf("\n");
    }
}

void copy_matrix(double** destination, double** source, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            destination[i][j] = source[i][j];
        }
    }
}

void free_matrix(double** matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void fill_matrix_rand(double** matrix, int rows, int columns)
{
    srand(time(NULL));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] = ((double)rand() / (double)RAND_MAX) * 200.0 - 100.0;
            printf("%10.2lf", matrix[i][j]);
        }
        printf("\n");
    }
}

void fill_matrix_from_keyboard(double** matrix, int rows, int columns) {
    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("Введите элемент в позиции [%d][%d]: ", i, j);
            scanf_s("%lf", &matrix[i][j]);
        }
    }
}

void fill_matrix_from_file(double** matrix, int rows, int columns, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("[Ошибка]: Не удалось открыть файл.\n");
        exit(1);
    }
    double number = 0.0;
    srand(time(NULL));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            number = 0.0;
            if (fscanf(file, "%lf", &number) == 1)
            {
                matrix[i][j] = number;
            }
            else
            {
                matrix[i][j] = ((double)rand() / (double)RAND_MAX) * 200.0 - 100.0;
            }
        }
    }
    fclose(file);
}

double max_module(double** matrix, int rows, int columns)
{
    double max_module_value = -999.0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (fabs(matrix[i][j]) > max_module_value)
            {
                max_module_value = fabs(matrix[i][j]);
            }
        }
    }
    return max_module_value;
}

double min_module(double** matrix, int rows, int columns)
{
    double min_module_value = 999.0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (fabs(matrix[i][j]) < min_module_value)
            {
                min_module_value = fabs(matrix[i][j]);
            }
        }
    }
    return min_module_value;
}

double avg_main_diagonal(double** matrix, int rows, int columns)
{
    int count_values_main_diagonale = 0;
    double avg_main_diagonale = 0.0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (i == j)
            {
                avg_main_diagonale += matrix[i][j];
                count_values_main_diagonale++;
            }
        }
    }
    avg_main_diagonale /= count_values_main_diagonale;
    return avg_main_diagonale;
}

void divide_matrix(double** matrix, int rows, int columns, double divisor)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] /= divisor;
            printf("%10.2f", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int columns = 0;
    int rows = 0;
    int cmd = 0;
    printf("Введите размер матрицы (столбцы строки): ");
    scanf_s("%i %i", &columns, &rows);
    while (columns <= 0)
    {
        printf("[Ошибка]: количество столбцов матрицы не может быть меньше или равно нулю. Введите количество столбцов матрицы: ");
        scanf_s("%i", &columns);
    }
    while (rows <= 0)
    {
        printf("[Ошибка]: количество строк матрицы не может быть меньше или равно нулю. Введите количество строк матрицы: ");
        scanf_s("%i", &rows);
    }
    double** original_matrix = create_matrix(rows, columns);
    printf("Выберите метод заполнения матрицы:\n");
    printf("1. Сформировать матрицу случайным образом.\n");
    printf("2. Сформировать матрицу вводом с клавиатуры.\n");
    printf("3. Сформировать матрицу данными из файла.\n");
    printf("0. Завершить работу программы.\n");
    printf("Введите номер действия: ");
    scanf_s("%i", &cmd);
    while (cmd < 0 || cmd > 3)
    {
        printf("[Ошибка]: выбран неверный номер действия. Введите номер действия: ");
        scanf_s("%i", &cmd);
    }
    switch (cmd)
    {
        case 0:
        {
            return 0;
            break;
        }
        case 1:
        {
            fill_matrix_rand(original_matrix, rows, columns);
            break;
        }
        case 2:
        {
            fill_matrix_from_keyboard(original_matrix, rows, columns);
            break;
        }
        case 3:
        {
            char filename[256];
            printf("Введите название файла с форматом (пример: filename.txt): ");
            scanf_s("%255s", &filename, sizeof(filename));
            fill_matrix_from_file(original_matrix, rows, columns, filename);
            output_matrix(original_matrix, columns, rows);
            break;
        }
    }
    double max_module_value = max_module(original_matrix, rows, columns);
    double min_module_value = min_module(original_matrix, rows, columns);
    double avg_main_diagonale = avg_main_diagonal(original_matrix, rows, columns);
    printf("Максимальный по модулю элемент матрицы равен %.2f\n", max_module_value);
    printf("Минимальный по модулю элемент матрицы равен %.2f\n", min_module_value);
    printf("Среднее арефметическое значение главной диагонали матрицы равно %.2f\n", avg_main_diagonale);
    printf("\nМатрица, полученная путём деления элементов на максимальный по модулю элемент:\n");
    double** after_division_on_max_module = create_matrix(rows, columns);
    copy_matrix(after_division_on_max_module, original_matrix, rows, columns);
    divide_matrix(after_division_on_max_module, rows, columns, max_module_value);
    printf("\nМатрица, полученная путём деления элементов на минимальный по модулю элемент:\n");
    double** after_division_on_min_module = create_matrix(rows, columns);
    copy_matrix(after_division_on_min_module, original_matrix, rows, columns);
    divide_matrix(after_division_on_min_module, rows, columns, min_module_value);
    printf("\nМатрица, полученная путём деления элементов на среднее арифметическое главной диагонали:\n");
    double** after_division_on_avg_main_diagonale = create_matrix(rows, columns);
    copy_matrix(after_division_on_avg_main_diagonale, original_matrix, rows, columns);
    divide_matrix(after_division_on_avg_main_diagonale, rows, columns, avg_main_diagonale);
    free_matrix(original_matrix, rows);
    free_matrix(after_division_on_max_module, rows);
    free_matrix(after_division_on_min_module, rows);
    free_matrix(after_division_on_avg_main_diagonale, rows);
    return 0;
}