#ifndef CHW_EXECUTOR_H
#define CHW_EXECUTOR_H

#include <fstream>
#include "sorts.h"
#include <chrono>

class Executor {
    Array<ISort<int> *> sort_options_;
public:
    Executor()
            :
            sort_options_(11) {
        sort_options_[0] = new SelectionSort<int>();
        sort_options_[1] = new BubbleSort<int>();
        sort_options_[2] = new BubbleSortIverson<int>();
        sort_options_[3] = new InsertSort<int>();
        sort_options_[4] = new BinaryInsertSort<int>();

        sort_options_[5] = new CountSort<int>();
        sort_options_[6] = new RadixSort<int>();
        sort_options_[7] = new MergeSort<int>();
        sort_options_[8] = new HoareSort<int>();
        sort_options_[9] = new LomutoSort<int>();

        sort_options_[10] = new HeapSort<int>();
    }

    ~Executor() {
        for (int i = 0; i < sort_options_.size(); ++i) {
            delete sort_options_[i];
        }
    }

    void execute(std::ofstream &out_50_300, std::ofstream &out_100_4100) {
        Array<int> numbers_from_0_to_5_(4100);
        Array<int> numbers_from_0_to_4000_(4100);
        Array<int> numbers_almost_sorted_(4100);
        Array<int> numbers_in_reverse_order_(4100);

        for (int i = 0; i < numbers_from_0_to_5_.size(); ++i) {
            numbers_from_0_to_5_[i] = rand() % 5;
            numbers_from_0_to_4000_[i] = rand() % 4000;

            if (i % 1000 == 0 && i >= 1000) {
                for (int j = 0; j < 10; ++j) {
                    numbers_almost_sorted_[i - j] = i - 10 + j;
                }
            } else {
                numbers_almost_sorted_[i] = i;
            }

            numbers_in_reverse_order_[i] = numbers_in_reverse_order_.size() - i;
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
                auto array = numbers_from_0_to_5_.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_50_300 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_from_0_to_4000_.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_50_300 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_almost_sorted_.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_50_300 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_in_reverse_order_.copy(0, i);

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
                auto array = numbers_from_0_to_5_.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_100_4100 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_from_0_to_4000_.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_100_4100 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_almost_sorted_.copy(0, i);

                auto start = std::chrono::high_resolution_clock::now();
                sort_options_[j]->sort(array);
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                out_100_4100 << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << ";";
            }
            for (int j = 0; j < sort_options_.size(); ++j) {
                auto array = numbers_in_reverse_order_.copy(0, i);

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
