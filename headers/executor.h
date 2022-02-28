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

        initializeTable(out_50_300);
        initializeTable(out_100_4100);

        // 50 - 300
        for (int i = 50; i <= 300; i += 10) {
            out_50_300 << i << ";";
            testSorts(numbers_from_0_to_5, i, out_50_300);
            testSorts(numbers_from_0_to_4000, i, out_50_300);
            testSorts(numbers_almost_sorted, i, out_50_300);
            testSorts(numbers_in_reverse_order, i, out_50_300);
            out_50_300 << std::endl;
        }

        // 100 - 4100
        for (int i = 100; i <= 4100; i += 100) {
            out_100_4100 << i << ";";
            testSorts(numbers_from_0_to_5, i, out_100_4100);
            testSorts(numbers_from_0_to_4000, i, out_100_4100);
            testSorts(numbers_almost_sorted, i, out_100_4100);
            testSorts(numbers_in_reverse_order, i, out_100_4100);
            out_100_4100 << std::endl;
        }

        // Debug - info
        std::ofstream input("input.txt");
        std::ofstream output("output.txt");

        for (int i = 0; i < 4100; ++i) {
            input << numbers_from_0_to_5[i] << " ";
        }
        input << std::endl;
        for (int i = 0; i < 4100; ++i) {
            input << numbers_from_0_to_4000[i] << " ";
        }
        input << std::endl;
        for (int i = 0; i < 4100; ++i) {
            input << numbers_almost_sorted[i] << " ";
        }
        input << std::endl;
        for (int i = 0; i < 4100; ++i) {
            input << numbers_in_reverse_order[i] << " ";
        }
        input << std::endl;

        HeapSort<int> debug_sort;
        debug_sort.sort(numbers_from_0_to_5);
        debug_sort.sort(numbers_from_0_to_4000);
        debug_sort.sort(numbers_almost_sorted);
        debug_sort.sort(numbers_in_reverse_order);

        for (int i = 0; i < 4100; ++i) {
            output << numbers_from_0_to_5[i] << " ";
        }
        output << std::endl;
        for (int i = 0; i < 4100; ++i) {
            output << numbers_from_0_to_4000[i] << " ";
        }
        output << std::endl;
        for (int i = 0; i < 4100; ++i) {
            output << numbers_almost_sorted[i] << " ";
        }
        output << std::endl;
        for (int i = 0; i < 4100; ++i) {
            output << numbers_in_reverse_order[i] << " ";
        }
        output << std::endl;

        input.close();
        output.close();
    }

private:
    inline void initializeTable(std::ofstream &out) {
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
    }

    inline void testSorts(const Array<int> &array_src, int idx, std::ofstream &out) {
        for (int i = 0; i < sort_options_.size(); ++i) {
            auto array = array_src.copy(0, idx);

            auto start = std::chrono::high_resolution_clock::now();
            sort_options_[i]->sort(array);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            out << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() << ";";
        }
    }
};

#endif //CHW_EXECUTOR_H
