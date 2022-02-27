#ifndef CHW_ARRAY_H
#define CHW_ARRAY_H

template<typename T>
class Array {
    T *data_;
    int capacity_;

public:
    explicit Array(int capacity)
            :
            capacity_(capacity) {
        data_ = new T[capacity];
    }

    Array(const Array &other)
            :
            capacity_(other.capacity_) {
        data_ = new T[capacity_];
        for (int i = 0; i < capacity_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Array(Array &&other)
            :
            capacity_(other.capacity_),
            data_(other.data_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
    }

    Array(std::initializer_list<T> initialize)
            :
            capacity_(initialize.size()) {
        data_ = new T[capacity_];
        auto it = initialize.begin();
        for (int i = 0; i < capacity_; ++i) {
            data_[i] = *it;
            it++;
        }
    }

    ~Array() {
        delete[] data_;
    }

    Array &operator=(const Array &other) {
        delete[] data_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        for (int i = 0; i < capacity_; ++i) {
            data_[i] = other.data_[i];
        }
        return *this;
    }

    Array &operator=(Array &&other) {
        delete[] data_;
        capacity_ = other.capacity_;
        data_ = other.data_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        return *this;
    }

    Array copy(int from, int count) {
        Array result(count);
        for (int i = from; i < from + count; ++i) {
            result[i - from] = data_[i];
        }
        return result;
    }

    void resize(int new_capacity) {
        if (capacity_ == new_capacity) {
            return;
        }
        if (capacity_ < new_capacity) {
            T *new_data = new T[new_capacity];
            for (int i = 0; i < capacity_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        } else {
            T *new_data = new T[new_capacity];
            for (int i = 0; i < new_capacity; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
    }

    T &operator[](size_t idx) {
        return data_[idx];
    }

    T &operator[](size_t idx) const {
        return data_[idx];
    }

    int size() const {
        return capacity_;
    }
};

#endif //CHW_ARRAY_H
