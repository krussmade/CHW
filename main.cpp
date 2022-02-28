#include <iostream>
#include "headers/executor.h"


int main() {
    Executor executor;

    std::ofstream out_50_300("C:\\users\\tagir\\desktop\\50_300.csv");
    std::ofstream out_100_4100("C:\\users\\tagir\\desktop\\100_4100.csv");

    executor.execute(out_50_300, 50, 300, 10);
    executor.execute(out_100_4100, 100, 4100, 100);
}
