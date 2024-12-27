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

// ������� ��� ���������� ��������� �����
void Alg_Prima(int n, int** matr, int* selected)
{
    int no_edge;
    int** mst_matrix = (int**)malloc(n * sizeof(int*)); // ������� ������������ ��������� ������

    for (int i = 0; i < n; i++)
    {
        mst_matrix[i] = (int*)calloc(n, sizeof(int)); // ��������� ������
    }

    for (int i = 0; i < n; i++)
    {
        selected[i] = false;
    }

    no_edge = 0;
    selected[0] = true;

    int x, y;
    int sum = 0;

    printf("�����  :  ���\n");

    while (no_edge < n - 1)
    {
        int min = INF;
        x = 0;
        y = 0;

        for (int i = 0; i < n; i++)
        {
            if (selected[i]) // ���� ��������
            {
                for (int j = 0; j < n; j++)
                {
                    if (!selected[j] && matr[i][j]) // ���� �� �������� � ���� ����� ����� ������� � ��������� 
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

        // ��������� ������� ������������ ��������� ������
        mst_matrix[x][y] = matr[x][y];
        mst_matrix[y][x] = matr[x][y];

        selected[y] = true;
        no_edge++;
    }

    printf("\n��������� ������������ ��������� ������: %d\n", sum);
    fprintf(file, "\n��������� ������������ ��������� ������: %d\n", sum);
    fprintf(file, "\n=========================================================================\n");
    printf("\n=========================================================================\n");

    // ����� ������� ������������ ��������� ������
    printf("\n������� ������������ ��������� ������:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", mst_matrix[i][j]);
        }
        printf("\n");
    }

    // ����������� ������, ���������� ��� ������� ������������ ��������� ������
    for (int i = 0; i < n; i++)
    {
        free(mst_matrix[i]);
    }
    free(mst_matrix);
}


// ������� ��� ������ �������
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

    int** matr; // ��������� ��� ������� ����������
    int* selected; // ������ ��� ������������ ��������� ������
    int* stp; // ������ �������� ������
    int n, d;

    printf("����� ����������! �������� ���� �� ������� ����, ����� ������:\n\n");
    printf("1. �������������� ��������� �������. (������� 1)\n");
    printf("2. ������ ���� (������� 2)\n");
    printf("3. ��������� ����� (������� 3)\n");
    printf("=========================================================================\n");

    d = _getch(); // ��������� ����� ������������

    if (d == '1')
    {
        printf("\n������� ������ �������: ");
        scanf("%d", &n);
        printf("=========================================================================\n");

        stp = (int*)calloc(n, sizeof(int)); // �������������� ������ ��������
        selected = (int*)malloc(n * sizeof(int)); // ��������� ������ ��� ������ ������������
        matr = (int**)malloc(n * sizeof(int*)); // ��������� ������ ��� ������ ����������

        for (int i = 0; i < n; i++)
        {
            matr[i] = (int*)malloc(n * sizeof(int)); // ��������� ������ ��� ������� ��������
        }

        for (int i = 0; i < n; i++) // ��������� ������� ��������� �����
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                {
                    matr[i][j] = 0; // ������������ �������� ����� ����
                }
                else if (i < j)
                {
                    matr[i][j] = rand() % 80 + 1; // ��������� ���� �� 1 �� 80
                    matr[j][i] = matr[i][j];
                }
                if (matr[i][j] > 0)
                {
                    stp[i]++;
                }
            }
        }

        printf("\n���������:\n");
        Output(matr, n);

        for (int i = 0; i < n; i++)
        {
            if (stp[i] == 0)
            {
                printf("�������� �� �������� ��� ������� ������������� ������\n");
                exit(0);
            }
        }

        Alg_Prima(n, matr, selected);

        // ����������� ������
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
        printf("\n������� ������ �������: ");
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
                    printf("������� [%d][%d]: %d\n", i, j, matr[i][j]);
                }
                else if (i < j)
                {
                    printf("������� ������� [%d][%d]: ", i, j);
                    scanf("%d", &matr[i][j]);
                    matr[j][i] = matr[i][j];
                }
                if (matr[i][j] > 0)
                {
                    stp[i]++;
                }
            }
        }

        printf("���������:\n");
        Output(matr, n);

        for (int i = 0; i < n; i++)
        {
            if (stp[i] == 0)
            {
                printf("�������� �� �������� ��� ������� ������������� ������\n");
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
        printf("����� ��������.\n");
        exit(0);
    }

    return 0;
}
