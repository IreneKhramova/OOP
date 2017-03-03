#include <iostream>
#include<fstream>
#include<cmath>

using namespace std;

void getMatr(double **mas, double **p, int i, int j, int m);
double determinant(double **mas, int m);

int main()
{
    ifstream aIn("a.in.txt");
    ifstream bIn("b.in.txt");
    if(!aIn.is_open() || !bIn.is_open())
        cout << "Files didn't open\n";
    else
    {
        int N;
        aIn >> N;
        bool isCorrect=1;

        double **a = new double*[N];
        for(int i=0; i<N; i++)
            a[i] = new double[N];

        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
            {
                int t;
                aIn >> t;
                if(isdigit(t))
                    a[i][j]=t;
                else
                {
                    ofstream fout("x.out.txt");
                    fout << "Матрица задана неправильно" << endl;
                    fout.close();
                    isCorrect=0;
                    break;
                }
            }


        aIn.close();
        if(isCorrect)
        {
            double det=determinant(a, N);//определитель
            double eps=1e-7;
            if(abs(det)<eps)//==0
            {
                ofstream fout("x.out.txt");
                //нет решений или их бесконечно много
                fout << "Определитель матрицы равен нулю, значит матрица необратима." << endl;
                fout.close();
            }
            else
            {
                double *b = new double[N];
                double *x = new double[N];

                for(int j=0; j<N; j++)
                {
                    x[j]=0;

                    int t;
                    bIn >> t;
                    if(isdigit(t))
                        b[j]=t;
                    else
                    {
                        ofstream fout("x.out.txt");
                        fout << "Матрица задана неправильно" << endl;
                        fout.close();
                        isCorrect=0;
                        break;
                    }

                }
                if(isCorrect)
                {
                    double **aTemp = new double*[N];
                    for(int i=0; i<N; i++)
                        aTemp[i] = new double[N];

                    for(int i=0; i<N; i++)
                        for(int j=0; j<N; j++)
                            aTemp[i][j]=a[i][j];

                    //обратная матрица
                    double **aInvert = new double*[N];
                    for(int i=0; i<N; i++)
                        aInvert[i] = new double[N];

                    for(int i=0; i<N; i++)
                        for(int j=0; j<N; j++) // E
                            if(i==j)
                                aInvert[i][j]=1;
                            else
                                aInvert[i][j]=0;

///////////////////////обратная матрица - метод Гаусса///////////////////


                    double temp;
                    //прямой ход
                    for (int k = 0; k < N; k++)
                    {
                        temp = aTemp[k][k];

                        //получаем единицу в a[k][k]
                        for (int j = 0; j < N; j++)
                        {
                            aTemp[k][j] /= temp;
                            aInvert[k][j] /= temp;
                        }

                        for (int i = k + 1; i < N; i++)
                        {
                            temp = aTemp[i][k];
                            /*получаем нули под единицей -
                            вычитаем из i-ой строки k-ую, умноженную на коэф a[i][k] */
                            for (int j = 0; j < N; j++)
                            {
                                aTemp[i][j] -= aTemp[k][j] * temp;
                                aInvert[i][j] -= aInvert[k][j] * temp;
                            }
                        }

            /*for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                    cout << aTemp[i][j] << "  ";
                cout << endl;
            }
            cout << endl;*/
                }

                    //обратный ход
                    for (int k = N - 1; k > 0; k--)
                    {
                        for (int i = k - 1; i >= 0; i--)
                        {
                            temp = aTemp[i][k];
                            //получаем нули над единицами
                            for (int j = 0; j < N; j++)
                            {
                                aTemp[i][j] -= aTemp[k][j] * temp;
                                aInvert[i][j] -= aInvert[k][j] * temp;
                            }
                        }
                    }

//////////////////////решение/////////////////////////////////

                    //x = aInvert * b
                    for(int i=0; i<N; i++)
                        for(int j=0; j<N; j++)
                            x[i] += aInvert[i][j] * b[j];

                    ofstream fout("x.out.txt");
                    for(int i=0; i<N; i++)
                        fout << x[i] << endl;


//////////////////////проверка/////////////////////////////

                    //A * x = b
                    fout << "\nПроверка:\nA*x\tb\n";
                    double t=0;
                    for(int i=0; i<N; i++)
                    {
                        t=0;
                        for(int j=0; j<N; j++)
                            t += a[i][j] * x[j];
                        fout << t << "\t" << b[i] << "\n";
                    }


 /////////////////////////////////////////////////////////

                    fout.close();

                    delete [] b;
                    delete [] x;

                    for(int i=0; i<N; i++)
                        delete [] aTemp[i];
                    delete [] aTemp;

                    for(int i=0; i<N; i++)
                        delete [] aInvert[i];
                    delete [] aInvert;
                }
            }
            bIn.close();

            for(int i=0; i<N; i++)
                delete [] a[i];
            delete [] a;
        }
    }
    return 0;
}


// Получение матрицы без i-й строки и j-го столбца
void getMatr(double **mas, double **p, int i, int j, int m)
{
    int di, dj;
    di = 0;
    for (int ki = 0; ki<m - 1; ki++)
    {
        // проверка индекса строки
        if (ki == i)
            di = 1;
        dj = 0;
        for (int kj = 0; kj<m - 1; kj++)
        {
            // проверка индекса столбца
            if (kj == j)
                dj = 1;
            p[ki][kj] = mas[ki + di][kj + dj];
        }
    }
}
// Рекурсивное вычисление определителя
double determinant(double **mas, int m)
{
    double d=0;
    double **p;
    p = new double*[m];
    for (int i = 0; i<m; i++)
        p[i] = new double[m];
    int k = 1; //(-1) в степени i
    if (m<1)
        cout << "Определитель вычислить невозможно!";
    if (m == 1)
    {
        d = mas[0][0];
        return(d);
    }
    if (m == 2)
    {
        d = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);
        return(d);
    }
    if (m>2)
    {
        for (int i = 0; i<m; i++)
        {
            getMatr(mas, p, i, 0, m);
            d += k * mas[i][0] * determinant(p, m-1);
            k = -k;
        }
    }

    for(int i=0; i<m; i++)
            delete [] p[i];
        delete [] p;

    return(d);
}
