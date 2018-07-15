#include <iostream>
#include <fstream>

using namespace std;

double det(int i, int j, int k, int n, double** m, double* d);
double** rem (int i, int j, int n, double** m);

int main()
{
    ifstream file("smallinput.txt");
    int n;
    file >> n;

    double **matrix = new double*[n];
    for (int i = 0; i < n; ++i)
        matrix[i] = new double[n];

    for (int i=0; i < n; i++)
        for (int j=0; j < n; j++)
            file >> matrix[i][j];

    int length = n*(n+1)*(2*n+1)/6;
    double *determinant = new double [length];

    for (int i = 0; i < length; ++i)
        determinant[i] = 0;

    double d = det(0, 0, n, n, matrix, determinant);

    ofstream output("out.txt");
    output << "The determinant of the " << n << "x" << n << " matrix is " << d;

    cout << "The determinant of the " << n << "x" << n << " matrix is " << d << endl;
    for (int i = 0; i < length; ++i)
        cout << determinant[i] << endl;
}

double det(int i, int j, int k, int n, double** m, double* d)
{
    int t = 0;
    for (int a = k, b = 0; a > 1; a--, b++)
        t += (n-b)*(n-b);

    int index = t + (n-k+1)*i + j;

    if (d[index] != 0)
        return d[index];

    if (k == 1)
        return m[0][0];

    if (k == 2)
        return m[0][0]*m[1][1] - m[0][1]*m[1][0];

    double** m1 = rem(1,1, k, m);
    double** m2 = rem(k,k, k, m);
    double** m3 = rem(1,k, k, m);
    double** m4 = rem(k,1, k, m);
    double** m5 = rem(1,1, k-1, m2);

    double dm1 = det(i+1, j+1, k-1, n, m1, d);
    double dm2 = det(i, j, k-1, n, m2, d);
    double dm3 = det(i, j+1, k-1, n, m3, d);
    double dm4 = det(i+1, j, k-1, n, m4, d);
    double dm5 = det(i+1, j+1, k-2, n, m5, d);

    double result = (dm1*dm2 - dm3*dm4)/dm5;
    d[index] = result;
    return result;
}

double** rem(int i, int j, int k, double **m)
{
    double** matrix = new double*[k-1];
    for (int i = 0; i < k-1; ++i)
        matrix[i] = new double[k-1];

    for (int x = 0; x < k-1; x++)
        for (int y = 0; y < k-1; y++)
            matrix[x][y] = m[x+(i%k)][y+(j%k)];

    return matrix;
}
