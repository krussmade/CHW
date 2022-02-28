#include <iostream>
#include "headers/executor.h"


int main() {
    Executor executor;

    std::ofstream out_50_300("50_300.csv");
    std::ofstream out_100_4100("100_4100.csv");

    executor.execute(out_50_300, out_100_4100);
}
