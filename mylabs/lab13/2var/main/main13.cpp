#include <iostream>
#include "lab13.h"
using namespace std;

// TODO: Доп Сделать класс день родждения который будет уноследован от Даты. 
// Поля: Год, месяц, дни
// В конструктор аргумент (сколько дней человек прожил). Высчитывается год рождения от текущей.
// Перегрузка разности, между людьми, сеттеры гетеры


int main() {

    cout << Date(5) + 4 << endl;
    cout << Date(5) + Date(4) << endl;
    Date d1 = Date(5) + Date(4);
    d1++;
    cout << d1 << endl;


    // cout << "Sum: " << d1 + d2 << endl;
    cout << endl;
}