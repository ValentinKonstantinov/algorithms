//#include "stdafx.h"
//13. В файле имеется телефонный справочник,  включающий имена
//владельцев телефонов.  Организовать быстрый поиск  по  номерам
//телефонов   с   помощью   хеширования.  Обеспечить  дополнение
//и удаление записей справочника (11).
#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
struct PfoneBook
{
    int Number;
    char Name[30];
    int Flag;
};
PfoneBook Book;

void hashFuncAdd(int &index, PfoneBook Book, int &size)
{
    int capacity = 13;
    ifstream File_1("Book.dat", ios::in);
    index = Book.Number % capacity;
    PfoneBook Temp;
    File_1.seekg((index) * sizeof(PfoneBook), ios_base::beg);
    File_1.read(reinterpret_cast<char *>(&Temp), sizeof(PfoneBook));
    size_t ht_step = 0;
    while (Temp.Flag == 1 && (Temp.Number != Book.Number))
    {
        ++ht_step;
        index = (index + ht_step * ht_step) % capacity;
        File_1.seekg((index) * sizeof(PfoneBook), ios_base::beg);
        File_1.read(reinterpret_cast<char *>(&Temp), sizeof(PfoneBook));
    };
    if ((Temp.Number == Book.Number) && (Temp.Flag == 1))
    {
        --size;
    };
    File_1.close();
}
void init()
{
    // system("cls"); // clrscr(); – для компилятора Borland C++ 5.02
    ofstream File_1("Book.dat", ios::app);
    File_1.clear();
    if (!File_1.is_open())
    {
        cerr << "Нельзя открыть файл!\n";
        system("pause"); // или _getch();
        exit(1);
    }

    Book.Number = 1;
    Book.Name[0] = 'a';
    Book.Flag = 0;
    int i;
    for (i = 0; i < 13; ++i)
    {
        File_1.write(reinterpret_cast<const char *>(&Book), sizeof(PfoneBook));
    }

    File_1.close();
    system("pause");
} // или _getch();

void view()
{
    // system("cls"); // clrscr(); – для компилятора Borland C++ 5.02
    ifstream File_1("Book.dat", ios::in);

    if (!File_1.is_open())
    {
        cerr << "Нельзя открыть файл!\n";

        exit(1);
    }
    while (!File_1.eof())
    {
        File_1.read(reinterpret_cast<char *>(&Book), sizeof(PfoneBook));
        if (!File_1.eof())
        {
            cout << "number " << Book.Number;
            cout << " name " << Book.Name;
            cout << " flag " << Book.Flag << " \n";
        }
    }
    File_1.close();
};

void hashFuncGet(int &index, PfoneBook Book)
{
    int capacity = 13;
    ifstream File_1("Book.dat", ios::in);
    index = Book.Number % capacity;
    PfoneBook Temp;
    File_1.seekg((index) * sizeof(PfoneBook), ios_base::beg);
    File_1.read(reinterpret_cast<char *>(&Temp), sizeof(PfoneBook));
    size_t ht_step = 0;
    while (Temp.Flag == 2 || (Temp.Flag == 1 && (Temp.Number != Book.Number)))
    {
        ++ht_step;
        index = (index + ht_step * ht_step) % capacity;
        File_1.seekg((index) * sizeof(PfoneBook), ios_base::beg);
        File_1.read(reinterpret_cast<char *>(&Temp), sizeof(PfoneBook));
    };
    if (Temp.Flag == 1)
    {
        cout << "number " << Temp.Number << " name " << Temp.Name << endl;
    }
    else
    {
        cout << "number not found" << endl;
    }

    File_1.close();
};

void getNum()
{
    int N;
    cout << "Number ";
    cin >> Book.Number;
    hashFuncGet(N, Book);
};
void changes(int &size)
{
    int N;

    cout << "Number ";
    cin >> Book.Number;
    cin.sync();
    cout << "Name: ";
    cin >> Book.Name;
    Book.Flag = 1;
    hashFuncAdd(N, Book, size);
    ++size;
    ofstream File_1("Book.dat", ios_base::in | ios_base::out);
    if (!File_1.is_open())
    {
        cerr << "Нельзя открыть файл!\n";

        exit(1);
    }
    File_1.seekp((N) * sizeof(PfoneBook), ios_base::beg);
    File_1.write(reinterpret_cast<const char *>(&Book), sizeof(PfoneBook));
    cout << "num is added" << endl;
    File_1.close();

} // или _getch();

void addf(int &size, int maxSize)
{
    int N;
    ifstream InFile("test.txt", ios::in);
    for (size; ((!InFile.eof()) && (size < maxSize)); ++size)
    {
        InFile >> Book.Number;
        InFile >> Book.Name;
        Book.Flag = 1;
        hashFuncAdd(N, Book, size);
        ofstream File_1("Book.dat", ios_base::in | ios_base::out);
        if (!File_1.is_open())
        {
            cerr << "Нельзя открыть файл!\n";
            system("pause"); // или _getch();
            exit(1);
        };
        File_1.seekp((N) * sizeof(PfoneBook));
        File_1.write(reinterpret_cast<const char *>(&Book), sizeof(PfoneBook));
        File_1.close();
    };
    if (size >= maxSize)
    {
        cout << "file is full" << endl;
    }
    else
    {
        cout << "file added" << endl;
    };
    InFile.close();
    system("pause");
};

void delNum(int &size)
{
    int index;
    cout << "Number ";
    cin >> Book.Number;
    int capacity = 13;
    ifstream File_1("Book.dat", ios::in);
    index = Book.Number % capacity;
    PfoneBook Temp;
    File_1.seekg((index) * sizeof(PfoneBook), ios_base::beg);
    File_1.read(reinterpret_cast<char *>(&Temp), sizeof(PfoneBook));
    size_t ht_step = 0;
    while (Temp.Flag == 2 || (Temp.Flag == 1 && (Temp.Number != Book.Number)))
    {
        ++ht_step;
        index = (index + ht_step * ht_step) % capacity;
        File_1.seekg((index) * sizeof(PfoneBook), ios_base::beg);
        File_1.read(reinterpret_cast<char *>(&Temp), sizeof(PfoneBook));
    };
    File_1.close();
    if (Temp.Flag = 1)
    {
        ofstream File_1("Book.dat", ios_base::in | ios_base::out);
        if (!File_1.is_open())
        {
            cerr << "Нельзя открыть файл!\n";

            exit(1);
        };
        Temp.Flag = 2;
        File_1.seekp((index) * sizeof(PfoneBook), ios_base::beg);
        File_1.write(reinterpret_cast<const char *>(&Temp), sizeof(PfoneBook));
        --size;
        cout << "num is del" << endl;
        File_1.close();
    }
    else
    {
        cout << "num not found" << endl;
    };
}

void Menu(int &size, int maxSize)
{
    int Ch = 13;
    while (Ch != 9)
    {
        //system("cls"); // clrscr(); – для компилятора Borland C++ 5.02
        cout << "     ###  Menu  ###\n";
        cout << "1. INIT \n";
        cout << "2. READ \n";
        cout << "3. REDACT \n";
        cout << "4. ADDF \n";
        cout << "5. getNum \n";
        cout << "6. delNum \n";
        cout << "9. END \n";
        cout << " number of entries" << size << endl;
        scanf("%d", &Ch);
        switch (Ch)
        {
        case 1:
            init();
            break;
        case 2:
            view();
            break;
        case 3:
            if (size < maxSize)
            {
                changes(size);
            }
            else
            {
                cout << "file is full" << endl;
            };
            break;
        case 4:
            addf(size, maxSize);
            break;
        case 5:
            getNum();
            break;
        case 6:
            delNum(size);
            break;
        case 9:
            Ch = 9;
        }
    }
}
int main()
{
    setlocale(LC_ALL, "Rus");
    int maxSize = 10;
    int size = 0;
    Menu(size, maxSize);
    system("pause");
    return 0;
}