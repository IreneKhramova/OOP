#include <iostream>
#include<fstream>
#include <string>
#include<locale>
#include <iomanip>
using namespace std;

int main()
{
    const int N=33;
    ifstream fin("in2.txt");
    setlocale(LC_ALL,"rus");
    if(!fin.is_open())
        cout << "File didn't open\n";
    else
    {
        const double statistics[N]={0.07998, 0.01592, 0.04533, 0.01687, 0.02977, 0.08483, 0.00013,
                              0.0094, 0.01641, 0.07367, 0.01208, 0.03486, 0.04343, 0.03203, 0.067,
                              0.10983, 0.02804, 0.04746, 0.05473, 0.06318, 0.02615, 0.00267, 0.00966,
                              0.00486, 0.0145, 0.00718, 0.00361, 0.00037, 0.01898, 0.01735, 0.00331,
                              0.00639, 0.02001};

        int letter[2][N];
        for(int i=0; i<N; i++)
        {
            letter[1][i]=0;
             letter[0][i]=224+i;
        }
        letter[0][N-1]=184;//ё

        int cnt=0;
        int c;

        while((c = fin.get()) != EOF)
        {
            //cout << (char)c << " " << c << endl;
            char t=tolower(c);//(char)c;
            int code=(int)tolower(c);
            //cout << t << " " << code << endl;
            if(((code >= 224) && (code <= 255)) || (code==184))
            {
                //считаем, сколько раз встретилась буква
                //cout << t << " " << code << endl;
                if(code==184)//ё
                    letter[1][N-1]++;
                else
                    letter[1][code-224]++;
                //кол-во букв в тексте
                cnt++;
            }
        }

        //cout << cnt << endl;
        double freq[N];//частотность
        for(int i=0; i<N; i++)
        {
            freq[i]=(double)letter[1][i] / cnt;
        }

        ofstream fout("out.txt");
        fout << "#     frequency in text   statistic\n";
        for(int i=0; i<N; i++)
        {
            fout << i+1 << ") ";
            if(i<6)
                fout << (char)letter[0][i] << " \t" << setw(13) << freq[i] << "  \t" << setw(9) << statistics[i] << endl;
            else if(i==6)
                fout << (char)letter[0][N-1] << " \t" << setw(13) << freq[N-1] << "  \t" << setw(9) << statistics[N-1] << endl;
            else
                fout << (char)letter[0][i-1] << " \t" << setw(13) << freq[i-1] << "  \t" << setw(9) << statistics[i-1] << endl;

        }
        fout.close();
    }
    return 0;
}
