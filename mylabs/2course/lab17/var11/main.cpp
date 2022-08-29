// TASK
// 11. Сделать реализацию множества set (на основе массива с сортировкой) для хранения только уникальных элементов.
//      insert(const T& value)
//      bool find(const T& value)
//      size() возвращает количество элементов в множестве
//      set intersect(const set& s) --- пересечение (бросает исключение при пересечении с пустым множеством)
//      operator<< для вывода

#include "lab17.h"
#include "iostream"

int main(int argc, char const *argv[])
{
    cset<int> b11;
    b11.insert(4);
    b11.insert(4);
    b11.insert(5);
    b11.insert(3);

    cset<int> b12(b11);
    cset<int> b13;
    b12.insert(12);
    b12.insert(11);
    cout << b11 << endl;
    cout << b12 << endl;
    try
    {
        cout << b11.intersect(b12) << '\n';
    }
    catch(CsetException& e)
    {
        cerr << e.get() << '\n';
        throw e;
    }
    
    
    cout << b11.find(4) << endl;
    return 0;
}
// int to str
