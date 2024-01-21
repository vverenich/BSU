#include <iostream>
#include <cmath>
#include <clocale>

using namespace std;

void BraunaRobinson(int col, int row)
{
    int** Matrix = new int *[col];
    for (int i = 0; i<col; i++)
        Matrix[i] = new int[row];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> Matrix[i][j];
        }
        cout << endl;
    }
    cout << "Source matrix:" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            cout << Matrix[i][j] << " ";
        cout << endl;
    }
    int N = 0;
    int count = 1; //счетчик
    double alpha = 0, betta = 0;
    double sum1 = 0, sum2 = 0;
    double max = 0, min = 1000000000;
    int A = 1, B = 1; // выбранная стратегия
    double v = 0;//цена игры
    cout << "Number of iterations: ";
    cin >> N;
    auto* p = new double[row];
    auto* q = new double[col];

    auto* max_alpha = new double[row];
    auto* min_betta = new double[col];

    p[0] = 1;
    q[0] = 1;
    for (int i = 1; i<row; i++)
        p[i] = 0;
    for (int i = 1; i<col; i++)
        q[i] = 0;

    while (count <= N) {
        for (int i = 0; i < row; i++) {
            sum1 = 0;
            for (int j = 0; j<col; j++)
                sum1 = sum1 + Matrix[i][j] * q[j];
            max_alpha[i] = sum1;
        }

        max = -10000000;
        for (int i = 0; i < row; i++) {
            if (max<max_alpha[i]) {
                max = max_alpha[i];
                A = i;
            }
        }
        alpha = max;

        for (int j = 0; j < col; j++) {
            sum2 = 0;
            for (int i = 0; i<row; i++)
                sum2 = sum2 + Matrix[i][j] * p[i];
            min_betta[j] = sum2;
        }
        //
        min = 100000000;
        for (int j = 0; j < col; j++) {
            if (min>min_betta[j]) {
                min = min_betta[j];
                B = j;
            }
        }
        betta = min;
        v = (alpha + betta) / 2;

        for (int i = 0; i< row; i++) {
            if (i != A) {
                p[i] = (double)((count*p[i]) / (count + 1));
            }
            else {
                p[i] = (double)((count*p[i] + 1) / (count + 1));
            }
        }

        for (int i = 0; i< col; i++) {
            if (i != B)
                q[i] = (count*q[i]) / (count + 1);
            else
                q[i] = (count*q[i] + 1) / (count + 1);
        }

        count++;
    }

    cout << endl << "******** solution ********" << endl;
    cout << "p = {";
    for (int i = 0; i< row; i++)
        cout << p[i] << " ";
    cout << "}" << endl;
    cout << "q = {";
    for (int i = 0; i< col; i++)
        cout << q[i] << " ";
    cout << "}" << endl;
    cout << "v = " << v << endl;

    for (int i = 0; i < col; i++)
        delete[] Matrix[i];
    delete[] Matrix;

}

int main() {
    setlocale(LC_ALL, "RUS");
    int col = 0, row = 0; // столбцы и строки
    cout << "Number of columns: ";
    cin >> col;
    cout << "Number of rows: ";
    cin >> row;
    BraunaRobinson(col, row);
    system("Pause");
}

//[[3, 7, 1, -2, 2], [2, -5, -4, 0, 2], [1, 6, -3, -5, -1]]
