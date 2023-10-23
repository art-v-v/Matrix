#include <iostream>
#include "windows.h"
using namespace std;

const int MAX_SIZE = 6;

//Пошук визначника
double determinant(double matrix[MAX_SIZE][MAX_SIZE], int size) {
    if (size == 1)//1х1 матриця
        return matrix[0][0];
    if (size == 2)//2х2 матриця
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];

    //3х3+ матриця
    double det = 0;
    for (int i = 0; i < size; i++) {
        double submatrix[MAX_SIZE][MAX_SIZE];
        for (int j = 1; j < size; j++) {
            int col = 0;
            for (int k = 0; k < size; k++) {
                if (k == i) continue;
                submatrix[j - 1][col] = matrix[j][k];
                col++;
            }
        }
        det += pow(-1, i) * matrix[0][i] * determinant(submatrix, size - 1);
    }
    return det;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//Вивід звичайного дробу, якщо це можливо
void division(double a, double b) {
    int gcdValue = gcd(abs(a), abs(b));
    a /= gcdValue;
    b /= gcdValue;

    if (b == 1) {
        cout << a;
    }
    else if (b == -1) {
        cout << -a;
    }
    else {
        cout << a << "/" << b;
    }
}

int main() {
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);

    //Створення масиву
    cout << "Введіть розмірність матриці: ";
    int size; cin >> size;
    double matrix[MAX_SIZE][MAX_SIZE];

    //Перевірка можливості заданого розміру
    if (size < 1 || size > MAX_SIZE) {
        cout << "Неможливе значення";
        system("pause");
        return 0;
    }

    cout << "---------------------------------------------------\n";

    //Ввід матриці в масив
    cout << "Введіть елементи матриці:\n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cin >> matrix[j][i];
        }
    }

    cout << "---------------------------------------------------\n";

    //посилання на функцію і вивід визначника
    double det = determinant(matrix, size);
    cout << "Визначник = " << det << endl;

    cout << "---------------------------------------------------\n";

    //Перевірка на можливість пошуку
    if (det == 0) {
        cout << "Неможливо знайти обернену матрицю при det = 0." << endl;
        system("pause");
        return 0;
    }


    //Створення спорідненої матриці
    double minor[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int col = 0;
            double submatrix[MAX_SIZE][MAX_SIZE];
            for (int k = 0; k < size; k++) {
                if (k == i) continue;
                int row = 0;
                for (int l = 0; l < size; l++) {
                    if (l == j) continue;
                    submatrix[row][col] = matrix[k][l];
                    row++;
                }
                col++;
            }
            minor[i][j] = pow(-1, (i + j)) * determinant(submatrix, size - 1);
        }
    }

    //Заповнення оберненої матриці та вивід у дробовому форматі
    double inverse[MAX_SIZE][MAX_SIZE];
    cout << "Обернена матриця:\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            inverse[i][j] = minor[i][j] / det;
            (division(minor[i][j], det));
            cout << "\t";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}
