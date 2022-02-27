#ifndef CHW_SORTS_H
#define CHW_SORTS_H

#include <utility>
#include "array.h"
#include <string>

template<typename T>
struct ISort {
    virtual std::string name() = 0;

    virtual void sort(Array<T> &data) = 0;

    virtual ~ISort() = default;
};

template<typename T>
struct SelectionSort : public ISort<T> {
    inline std::string name() override {
        return "Selection sort";
    }

    inline void sort(Array<T> &data) override {
        for (int idx = 0; idx < (data.size() - 1); ++idx) {
            size_t smallest_idx = idx;
            for (int j = idx + 1; j < data.size(); ++j) {
                if (data[j] < data[smallest_idx]) {
                    smallest_idx = j;
                }
            }
            std::swap(data[idx], data[smallest_idx]);
        }
    }
};

template<typename T>
struct BubbleSort : public ISort<T> {
    inline std::string name() override {
        return "Bubble sort";
    }

    inline void sort(Array<T> &data) override {
        for (int i = 0; i < data.size(); ++i) {
            for (int j = i + 1; j < data.size(); ++j) {
                if (data[i] > data[j]) {
                    std::swap(data[i], data[j]);
                }
            }
        }
    }
};

template<typename T>
struct BubbleSortIverson : public ISort<T> {
    inline std::string name() override {
        return "Bubble Iverson sort";
    }

    inline void sort(Array<T> &data) override {
        for (int i = data.size(); i > 1; --i) {
            bool iverson_value = false;
            for (int j = 1; j < i; ++j) {
                if (data[j] < data[j - 1]) {
                    std::swap(data[j], data[j - 1]);
                    iverson_value = true;
                }
            }
            if (!iverson_value) {
                return;
            }
        }
    }
};

template<typename T>
struct InsertSort : public ISort<T> {
    inline std::string name() override {
        return "Insert sort";
    }

    inline void sort(Array<T> &data) override {
        for (int i = 1; i < data.size(); ++i) {
            T temp = data[i];
            int idx = i - 1;
            while (idx >= 0 && data[idx] > temp) {
                data[idx + 1] = data[idx];
                data[idx] = temp;
                idx--;
            }
        }
    }
};

template<typename T>
struct BinaryInsertSort : public ISort<T> {
    inline std::string name() override {
        return "Binary insert sort";
    }

    inline void sort(Array<T> &data) override {
        for (int idx = 1; idx < data.size(); ++idx) {
            if (data[idx - 1] > data[idx]) {
                T temp = data[idx];
                int left = 0;
                int right = idx - 1;
                do {
                    int middle = (left + right) / 2;
                    if (data[middle] < temp) {
                        left = middle + 1;
                    } else {
                        right = middle - 1;
                    }
                } while (left <= right);
                for (int j = idx - 1; j >= left; --j) {
                    data[j + 1] = data[j];
                }
                data[left] = temp;
            }
        }
    }
};

template<typename T>
struct CountSort : public ISort<T> {
    inline std::string name() override {
        return "Count sort";
    }

    inline void sort(Array<T> &data) override {
        int min = data[0];
        int max = data[0];
        for (int i = 1; i < data.size(); ++i) {
            if (data[i] < min) {
                min = data[i];
            } else {
                if (data[i] > max) {
                    max = data[i];
                }
            }
        }
        Array<size_t> counts(max - min + 1);
        for (int i = 0; i < counts.size(); ++i) {
            counts[i] = 0;
        }
        for (int i = 0; i < data.size(); ++i) {
            counts[data[i] - min]++;
        }

        size_t index = 0;
        for (int i = 0; i < counts.size(); ++i) {
            for (int j = 0; j < counts[i]; ++j) {
                data[index++] = i + min;
            }
        }
    }
};

template<typename T>
struct RadixSort : public ISort<T> {
    inline std::string name() override {
        return "Radix sort";
    }

    inline static uint32_t digit(uint32_t number, int index) {
        uint32_t mask = 255 << (8 * index);
        return (number & mask) >> (8 * index);
    }

    inline void sort(Array<T> &data) override {
        int counter[256];
        for (int index = 0; index < sizeof(T); ++index) {
            for (int j = 0; j < 256; ++j) {
                counter[j] = 0;
            }
            for (int j = 0; j < data.size(); ++j) {
                T digit_value = digit(data[j], index);
                counter[digit_value]++;
            }
            int count = 0;
            for (int j = 0; j < 256; ++j) {
                int temp = counter[j];
                counter[j] = count;
                count += temp;
            }
            Array<T> second_data(data.size());
            for (int j = 0; j < data.size(); ++j) {
                uint32_t digit_value = digit(data[j], index);
                second_data[counter[digit_value]] = data[j];
                counter[digit_value]++;
            }
            data = second_data;
        }
    }
};

template<typename T>
struct MergeSort : public ISort<T> {
    inline std::string name() override {
        return "Merge sort";
    }

    inline void sort(Array<T> &data) override {
        mergeSort(data, 0, data.size());
    }

    void mergeSort(Array<T> &data, size_t start, size_t end) {
        if (end - start < 2) {
            return;
        }
        if (end - start == 2) {
            if (data[start] > data[start + 1]) {
                std::swap(data[start], data[start + 1]);
            }
            return;
        }
        mergeSort(data, start, start + (end - start) / 2);
        mergeSort(data, start + (end - start) / 2, end);
        Array<T> second_data(end - start);
        size_t count = 0;
        size_t first_start = start;
        size_t first_end = start + (end - start) / 2;
        size_t second_start = first_end;
        while (count < end - start) {
            if (first_start >= first_end ||
                (second_start < end && data[second_start] <= data[first_start])) {
                second_data[count++] = data[second_start++];
            } else {
                second_data[count++] = data[first_start++];
            }
        }
        for (size_t i = start; i < end; ++i) {
            data[i] = second_data[i - start];
        }
    }
};

template<typename T>
struct HoareSort : public ISort<T> {
    inline std::string name() override {
        return "Hoare sort";
    }

    inline void sort(Array<T> &data) override {
        quickSort(data, 0, data.size() - 1);
    }

    void quickSort(Array<T> &data, int first, int last) {
        T pivot = data[(first + last) / 2];
        int index = first;
        int jndex = last;
        while (index <= jndex) {
            while (data[index] < pivot) {
                index++;
            }
            while (data[jndex] > pivot) {
                jndex--;
            }
            if (index <= jndex) {
                std::swap(data[index++], data[jndex--]);
            }
        }
        if (index < last) {
            quickSort(data, index, last);
        }
        if (first < jndex) {
            quickSort(data, first, jndex);
        }
    }
};

template<typename T>
struct LomutoSort : public ISort<T> {
    inline std::string name() override {
        return "Lomuto sort";
    }

    inline void sort(Array<T> &data) override {
        quickSort(data, 0, data.size() - 1);
    }

    int partition(Array<T> &data_, int first, int last) {
        int pivot = last;
        int index = first;
        for (int i = first; i < last; ++i) {
            if (data_[i] <= data_[pivot]) {
                std::swap(data_[index++], data_[i]);
            }
        }
        std::swap(data_[index], data_[last]);
        return index;
    }

    void quickSort(Array<T> &data_, int first, int last) {
        if (first < last) {
            int partition_value = partition(data_, first, last);
            quickSort(data_, first, partition_value - 1);
            quickSort(data_, partition_value + 1, last);
        }
    }
};

template<typename T>
struct HeapSort : public ISort<T> {
    inline std::string name() override {
        return "Heap sort";
    }

    inline void sort(Array<T> &data) override {
        for (int i = data.size() / 2 - 1; i >= 0; --i) {
            heapify(data, data.size(), i);
        }
        for (int i = data.size() - 1; i >= 0; --i) {
            std::swap(data[0], data[i]);
            heapify(data, i, 0);
        }
    }

    void heapify(Array<T> &data, int len, int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < len && data[left] > data[largest]) {
            largest = left;
        }
        if (right < len && data[right] > data[largest]) {
            largest = right;
        }

        if (largest != index) {
            std::swap(data[index], data[largest]);
            heapify(data, len, largest);
        }
    }
};

#endif //CHW_SORTS_H
