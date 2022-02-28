#include <iostream>
#include "headers/executor.h"

//1) ПиАА 2022, Адамян Эдвард Ваагнович, БПИ203
//2) Адамян Эдвард Ваагнович группа БПИ203
//3) CLion
//4) Сделана вся кодовая База, Графики
//5) Не сделан отчет

int main() {
    Executor executor;

    std::ofstream out_50_300("50_300.csv");
    std::ofstream out_100_4100("100_4100.csv");

    executor.execute(out_50_300, out_100_4100);
}
