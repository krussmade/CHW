#ifndef CHW_EXECUTOR_H
#define CHW_EXECUTOR_H

#include <fstream>
#include "sorts.h"
#include <chrono>

// Класс выполнения замеров
class Executor {
    // Массив всех видов сортировок
    Array<ISort<int> *> sort_options_;
public:
    Executor()
            :
            sort_options_(12) {
        // Добавление всех видов сортировок
        int idx = 0;
        sort_options_[idx++] = new SelectionSort<int>();
        sort_options_[idx++] = new BubbleSort<int>();
        sort_options_[idx++] = new BubbleSortWithTheFirstIversonCondition<int>();
        sort_options_[idx++] = new BubbleSortWithTheFirstAndTheSecondIversonConditions<int>();
        sort_options_[idx++] = new InsertSort<int>();
        sort_options_[idx++] = new BinaryInsertSort<int>();

        sort_options_[idx++] = new CountSort<int>();
        sort_options_[idx++] = new RadixSort<int>();
        sort_options_[idx++] = new MergeSort<int>();
        sort_options_[idx++] = new HoareSort<int>();
        sort_options_[idx++] = new LomutoSort<int>();

        sort_options_[idx++] = new HeapSort<int>();
    }

    ~Executor() {
        for (int i = 0; i < sort_options_.size(); ++i) {
            delete sort_options_[i];
        }
    }

    void execute(std::ofstream &out, int from, int to, int step) {
        Array<int> numbers_from_0_to_5(4100);
        Array<int> numbers_from_0_to_4000(4100);
        Array<int> numbers_almost_sorted(4100);
        Array<int> numbers_in_reverse_order(4100);

        for (int i = 0; i < numbers_from_0_to_5.size(); ++i) {
            numbers_from_0_to_5[i] = rand() % 5;
            numbers_from_0_to_4000[i] = rand() % 4000;

            if (i % 1000 == 0 && i >= 1000) {
                for (int j = 0; j < 10; ++j) {
                    numbers_almost_sorted[i - j] = i - 10 + j;
                }
            } else {
                numbers_almost_sorted[i] = i;
            }

            numbers_in_reverse_order[i] = numbers_in_reverse_order.size() - i;
        }

        out << ";";
        for (int i = 0; i < sort_options_.size(); ++i) {
            out << sort_options_[i]->name() << " 0 - 5;";
        }

        for (int i = 0; i < sort_options_.size(); ++i) {
            out << sort_options_[i]->name() << " 0 - 4000;";
        }

        for (int i = 0; i < sort_options_.size(); ++i) {
            out << sort_options_[i]->name() << " almost sorted;";
        }

        for (int i = 0; i < sort_options_.size(); ++i) {
            out << sort_options_[i]->name() << " in reverse order;";
        }
        out << std::endl;

        for (int i = from; i <= to; i += step) {
            out << i << ";";
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_from_0_to_5.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_from_0_to_4000.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_almost_sorted.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_in_reverse_order.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() << ";";
            }
            out << std::endl;
        }
    }

    void execute(std::ofstream &out_50_300, std::ofstream &out_100_4100) {
        Array<int> numbers_from_0_to_5(4100);
        Array<int> numbers_from_0_to_4000(4100);
        Array<int> numbers_almost_sorted(4100);
        Array<int> numbers_in_reverse_order(4100);

        for (int i = 0; i < numbers_from_0_to_5.size(); ++i) {
            numbers_from_0_to_5[i] = rand() % 5;
            numbers_from_0_to_4000[i] = rand() % 4000;

            if (i % 1000 == 0 && i >= 1000) {
                for (int j = 0; j < 10; ++j) {
                    numbers_almost_sorted[i - j] = i - 10 + j;
                }
            } else {
                numbers_almost_sorted[i] = i;
            }

            numbers_in_reverse_order[i] = numbers_in_reverse_order.size() - i;
        }

        out_50_300 << ";";
        out_100_4100 << ";";
        for (int i = 0; i < sort_options_.size(); ++i) {
            out_50_300 << sort_options_[i]->name() << " 0 - 5;";
            out_100_4100 << sort_options_[i]->name() << " 0 - 5;";
        }

        for (int i = 0; i < sort_options_.size(); ++i) {
            out_50_300 << sort_options_[i]->name() << " 0 - 4000;";
            out_100_4100 << sort_options_[i]->name() << " 0 - 4000;";
        }

        for (int i = 0; i < sort_options_.size(); ++i) {
            out_50_300 << sort_options_[i]->name() << " almost sorted;";
            out_100_4100 << sort_options_[i]->name() << " almost sorted;";
        }

        for (int i = 0; i < sort_options_.size(); ++i) {
            out_50_300 << sort_options_[i]->name() << " in reverse order;";
            out_100_4100 << sort_options_[i]->name() << " in reverse order;";
        }

        out_50_300 << std::endl;
        out_100_4100 << std::endl;

        // 50 - 300
        for (int i = 50; i <= 300; i += 10) {
            out_50_300 << i << ";";
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_from_0_to_5.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_50_300 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_from_0_to_4000.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_50_300 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_almost_sorted.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_50_300 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_in_reverse_order.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_50_300 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            out_50_300 << std::endl;
        }

        // 100 - 4100
        for (int i = 100; i <= 4100; i += 100) {
            out_100_4100 << i << ";";
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_from_0_to_5.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_100_4100 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_from_0_to_4000.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_100_4100 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_almost_sorted.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_100_4100 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_in_reverse_order.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_100_4100 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            out_100_4100 << std::endl;
        }
    }
};

#endif //CHW_EXECUTOR_H
