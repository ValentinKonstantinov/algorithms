//15. Реализовать алгоритм  Дейкстры  поиска  кратчайших путей
//из заданной вершины во все остальные вершины. Проиллюстрировать
//по шагам этапы его выполнения. Конечные  результаты  показать в
//таблице. По запросам  выдать  кратчайшие пути  с  их  длиной  в
//указанные пользователем вершины (9).
//оприентированность, 10000, проверка на изолированность, выводить предыдущие вершины в итерациях алгоритма
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
using namespace std;

void print_menu()
{
    //system("cls"); // очищаем экран
    printf("\n What do you want to do?\n");
    printf("1. initialization of connections\n");
    printf("2. running the algorithmt\n");
    printf("3. show the way\n");
    printf("5. Exit\n");
};

int main()
{
    system("cls");
    int SIZE;
    printf("enter the number of vertices: ");
    scanf("%d", &SIZE);
    int a[SIZE][SIZE]; // матрица связей
    int d[SIZE];       // минимальное расстояние
    int v[SIZE];       // посещенные вершины
    int l[SIZE][50];   //исторя пути

    int variant;
    int begin_index = 0;
    ifstream inf;
    // system("chcp 1251"); // почему то не работает
    do
    {
        print_menu();
        // получаем номер выбранного пункта меню
        scanf("%d", &variant);
        switch (variant)
        {
        case 1:
            inf.open("input.txt");
            // Инициализация матрицы связей
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    a[i][j] = 0;
                };
                for (int j = 0; j < 50; j++)
                {
                    l[i][j] = -1;
                }
            }
            do //Инициализация вершин и расстояний
            {
                int i, j, temp;
                inf >> i;
                inf >> j;
                inf >> temp;
                a[i - 1][j - 1] = temp;
                // a[j - 1][i - 1] = temp;
            } while (!inf.eof());
            inf.close();
            // Ввод матрицы связей
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                    printf("%5d ", a[i][j]);
                printf("\n");
            };

            for (int i = 0; i < SIZE; i++)
            {
                d[i] = 10000;
                v[i] = 1;
            };
            printf("enter starting vertex: ");
            scanf("%d", &begin_index);
            begin_index = --begin_index;
            d[begin_index] = 0;
            // Шаг алгоритма
            // char w; //для работы по шагам
            break;

        case 2:
            int temp, minindex, min;
            int tempL;
            tempL = 0;
            int step;
            step = 0;
            do
            {
                //system("pause");
                getch();
                for (int i = 0; i < SIZE; i++)
                {
                    int j;
                    for (j = 0; l[i][j] > -1; j++)
                    {
                    };
                    if (v[i] == 0)
                    {

                        printf("%3d!(%1d)  ", d[i], l[i][j - 1]);
                    }
                    else
                    {
                        if (d[i] == 10000)
                        {
                            printf("   @     ");
                        }
                        else
                        {
                            printf("%4d(%1d)  ", d[i], l[i][j - 1]);
                        }
                    };
                };
                printf("\n");
                minindex = 10000;
                min = 10000;
                for (int i = 0; i < SIZE; i++)
                { // Если вершину ещё не обошли и вес меньше min
                    if ((v[i] == 1) && (d[i] < min))
                    { // Переприсваиваем значения
                        min = d[i];
                        minindex = i;
                    }
                };
                // Добавляем найденный минимальный вес
                // к текущему весу вершины
                // и сравниваем с текущим минимальным весом вершины

                if (minindex != 10000)
                {
                    v[minindex] = 0;
                    for (int i = 0; i < SIZE; i++)
                    {
                        if (v[i] != 0)
                        {
                            l[i][step] = tempL;
                        };
                        if (a[minindex][i] > 0)
                        {
                            temp = min + a[minindex][i];
                            //l[i][step] = tempL;
                            if (temp < d[i])
                            {
                                d[i] = temp;
                                if (v[i] != 0)
                                {
                                    l[i][step] = minindex + 1;
                                    tempL = minindex + 1;
                                };
                            }
                        }
                    };
                };
                step = ++step;
            } while (minindex < 10000);
            // Вывод кратчайших расстояний до вершин
            //printf("\nshortest distance to vertices: \n");
            // for (int i = 0; i < SIZE; i++)
            //    printf("%5d ", d[i]);
            break;

        case 3:
            // Восстановление пути
            int ver[SIZE]; // массив посещенных вершин
            int end;
            printf("\nenter the end vertex number: ");
            scanf("%d", &end);
            end = end - 1;       // индекс конечной вершины = 5 - 1
            ver[0] = end + 1;    // начальный элемент - конечная вершина
            int k = 1;           // индекс предыдущей вершины
            int weight = d[end]; // вес конечной вершины
            if (weight == 10000)
            {
                printf("\n no way \n");
            }
            else
            {
                while (end != begin_index) // пока не дошли до начальной вершины
                {
                    for (int i = 0; i < SIZE; i++) // просматриваем все вершины
                        if (a[i][end] != 0)        // если связь есть
                        {
                            int tempM = weight - a[i][end]; // определяем вес пути из предыдущей вершины
                            if (tempM == d[i])              // если вес совпал с рассчитанным
                            {                               // значит из этой вершины и был переход
                                weight = tempM;             // сохраняем новый вес
                                end = i;                    // сохраняем предыдущую вершину
                                ver[k] = i + 1;             // и записываем ее в массив
                                k++;
                            }
                        }
                };

                // Вывод пути (начальная вершина оказалась в конце массива из k элементов)
                printf("\nshortest way\n");
                for (int i = k - 1; i >= 0; i--)
                    printf("%3d ", ver[i]);
                //break;
            };
        }
    } while (variant != 5);
}
