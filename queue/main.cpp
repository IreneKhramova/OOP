#include <iostream>

using namespace std;

/* Вариант 3 */
class Queue
{
private:
    int maxLen;
    double *arr; //очередь
    int end, begin; //указатели очереди, end - первое свободное место
    int count;//кол-во эл-тов

public:
    Queue(int n)
    {
        maxLen = n;
        end = begin = 0;
        arr = new double[maxLen];
        count = 0;
    }
    // помещение в очередь
    void put(double val)
    {
        if(isFull())
        {
            cout << "Очередь заполнена" << endl;
            return;
        }
        arr[end++] = val;
        count++;
        if(end==maxLen)
            end=0;
    }

    //взятие из очереди
    /* передает в val значение эл-та,
       возвращает false, если очередь пуста,
       и true в противном случае */
    bool get(double &val)
    {
        if(isEmpty())
        {
            cout << "Очередь пуста" << endl;
            return false;
        }
        val = arr[begin];
        begin++;
        count--;
        if(begin==maxLen)
            begin=0;
        return true;
    }

    //проверка на пустоту
    bool isEmpty()
    {
        if(count == 0)
            return true;
        return false;
    }

    //проверка, что очередь заполнена целиком
    bool isFull()
    {
        if(count == maxLen)
            return true;
        return false;
    }

    ~Queue()
    {
        delete [] arr;
    }

    //вывод очереди
    void printq()
    {
        if(isEmpty())
        {
            cout << "Очередь пуста" << endl;
            return;
        }
        if(begin < end)
        {
            for(int i=begin; i<end; i++)
                cout << arr[i] << endl;
        }
        else
        {
            for(int i=begin; i<maxLen; i++)
                cout << arr[i] << endl;
            for(int i=0; i<end; i++)
                cout << arr[i] << endl;
        }
    }
};

int main()
{
    // Пример использования
    Queue q(5);
    if(q.isEmpty())
        cout << "Очередь пуста" << endl;
    if(q.isFull())
        cout << "Очередь заполнена" << endl;
    double a;
    if(q.get(a))
    cout << a << endl;

    q.put(42);
    q.put(37);
    q.put(1.1);
    q.put(2.5);
    q.put(7.89);
    if(q.isEmpty())
        cout << "Очередь пуста" << endl;
    if(q.isFull())
        cout << "Очередь заполнена" << endl;
    //q.printq();
    if(q.get(a))
        cout << a << endl;
    if(q.get(a))
        cout << a << endl;
    if(q.get(a))
        cout << a << endl;
    cout << "------------------" << endl;
    q.put(112);
    q.put(99);
    q.printq();
    q.put(555.555);
    if(q.isEmpty())
        cout << "Очередь пуста" << endl;
    if(q.isFull())
        cout << "Очередь заполнена" << endl;
    q.printq();
    q.put(77);
    return 0;
}
