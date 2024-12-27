#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include <iostream>
#include <locale.h>
#include <windows.h>
#include <cstring>
#include <fstream>

using namespace std;

#define INF 9999999

FILE* file = fopen("text.txt", "a");

// Функция для реализации алгоритма Прима
void Alg_Prima(int n, int** matr, int* selected)
{
    int no_edge;
    int** mst_matrix = (int**)malloc(n * sizeof(int*)); // Матрица минимального остовного дерева

    for (int i = 0; i < n; i++)
    {
        mst_matrix[i] = (int*)calloc(n, sizeof(int)); // Заполняем нулями
    }

    for (int i = 0; i < n; i++)
    {
        selected[i] = false;
    }

    no_edge = 0;
    selected[0] = true;

    int x, y;
    int sum = 0;

    printf("Ребро  :  Вес\n");

    while (no_edge < n - 1)
    {
        int min = INF;
        x = 0;
        y = 0;

        for (int i = 0; i < n; i++)
        {
            if (selected[i]) // коль отмечена
            {
                for (int j = 0; j < n; j++)
                {
                    if (!selected[j] && matr[i][j]) // коль не отмечена и есть ребра между текущей и следующей 
                    {
                        if (min > matr[i][j])
                        {
                            min = matr[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }

        sum += matr[x][y];

        printf("%d - %d : %d\n", x, y, matr[x][y]);
        fprintf(file, "%d - %d : %d\n", x, y, matr[x][y]);

        // Обновляем матрицу минимального остовного дерева
        mst_matrix[x][y] = matr[x][y];
        mst_matrix[y][x] = matr[x][y];

        selected[y] = true;
        no_edge++;
    }

    printf("\nСтоимость минимального остовного дерева: %d\n", sum);
    fprintf(file, "\nСтоимость минимального остовного дерева: %d\n", sum);
    fprintf(file, "\n=========================================================================\n");
    printf("\n=========================================================================\n");

    // Вывод матрицы минимального остовного дерева
    printf("\nМатрица минимального остовного дерева:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", mst_matrix[i][j]);
        }
        printf("\n");
    }

    // Освобождаем память, выделенную под матрицу минимального остовного дерева
    for (int i = 0; i < n; i++)
    {
        free(mst_matrix[i]);
    }
    free(mst_matrix);
}


// Функция для вывода матрицы
void Output(int** matr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", matr[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int** matr; // Указатель для массива указателей
    int* selected; // Массив для отслеживания выбранных вершин
    int* stp; // Массив степеней вершин
    int n, d;

    printf("Добро пожаловать! Выберите один из пунктов меню, чтобы начать:\n\n");
    printf("1. Автоматическая генерация матрицы. (нажмите 1)\n");
    printf("2. Ручной ввод (нажмите 2)\n");
    printf("3. Завершить сеанс (нажмите 3)\n");
    printf("=========================================================================\n");

    d = _getch(); // Получение ввода пользователя

    if (d == '1')
    {
        printf("\nВведите размер матрицы: ");
        scanf("%d", &n);
        printf("=========================================================================\n");

        stp = (int*)calloc(n, sizeof(int)); // Инициализируем массив степеней
        selected = (int*)malloc(n * sizeof(int)); // Выделение памяти под массив отслеживания
        matr = (int**)malloc(n * sizeof(int*)); // Выделение памяти под массив указателей

        for (int i = 0; i < n; i++)
        {
            matr[i] = (int*)malloc(n * sizeof(int)); // Выделение памяти для массива значений
        }

        for (int i = 0; i < n; i++) // Генерация массива случайных чисел
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                {
                    matr[i][j] = 0; // Диагональные элементы равны нулю
                }
                else if (i < j)
                {
                    matr[i][j] = rand() % 80 + 1; // Случайные веса от 1 до 80
                    matr[j][i] = matr[i][j];
                }
                if (matr[i][j] > 0)
                {
                    stp[i]++;
                }
            }
        }

        printf("\nРезультат:\n");
        Output(matr, n);

        for (int i = 0; i < n; i++)
        {
            if (stp[i] == 0)
            {
                printf("Алгоритм не работает при наличии изолированных вершин\n");
                exit(0);
            }
        }

        Alg_Prima(n, matr, selected);

        // Освобождаем память
        free(stp);
        free(selected);
        for (int i = 0; i < n; i++)
        {
            free(matr[i]);
        }
        free(matr);
    }

    if (d == '2')
    {
        printf("\nВведите размер матрицы: ");
        scanf("%d", &n);

        stp = (int*)calloc(n, sizeof(int));
        selected = (int*)malloc(n * sizeof(int));
        matr = (int**)malloc(n * sizeof(int*));

        for (int i = 0; i < n; i++)
        {
            matr[i] = (int*)malloc(n * sizeof(int));
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                {
                    matr[i][j] = 0;
                    printf("Элемент [%d][%d]: %d\n", i, j, matr[i][j]);
                }
                else if (i < j)
                {
                    printf("Введите элемент [%d][%d]: ", i, j);
                    scanf("%d", &matr[i][j]);
                    matr[j][i] = matr[i][j];
                }
                if (matr[i][j] > 0)
                {
                    stp[i]++;
                }
            }
        }

        printf("Результат:\n");
        Output(matr, n);

        for (int i = 0; i < n; i++)
        {
            if (stp[i] == 0)
            {
                printf("Алгоритм не работает при наличии изолированных вершин\n");
                exit(0);
            }
        }

        Alg_Prima(n, matr, selected);

        free(stp);
        free(selected);
        for (int i = 0; i < n; i++)
        {
            free(matr[i]);
        }
        free(matr);
    }

    if (d == '3')
    {
        printf("Сеанс завершён.\n");
        exit(0);
    }

    return 0;
}
