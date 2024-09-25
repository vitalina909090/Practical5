#include <iostream>
#include <Windows.h>
#include <cassert>

using namespace std;

class Plural {
    int* nums;
    int size;

public:
    Plural() : nums(nullptr), size(0) {}

    ~Plural() {
        delete[] nums;
    }

    Plural(const Plural& other) : size(other.size) {
        nums = new int[size];
        for (int i = 0; i < size; i++) {
            nums[i] = other.nums[i];
        }
    }


    void add(int element) {
        for (int i = 0; i < size; i++) {
            if (nums[i] == element) {
                return; 
            }
        }
        int* new_nums = new int[size + 1];
        for (int i = 0; i < size; i++) {
            new_nums[i] = nums[i];
        }
        new_nums[size++] = element; 

        delete[] nums;
        nums = new_nums; 
    }

    friend Plural operator+(const Plural& plural, int element) {
        Plural result = plural;
        result.add(element);
        return result;
    }

    friend Plural operator+(const Plural& plural1, const Plural& plural2) {
        Plural result = plural1;
        for (int i = 0; i < plural2.size; i++) {
            result.add(plural2.nums[i]);
        }
        return result;
    }

    Plural& operator=(const Plural& other) {
        if (this != &other) {
            delete[] nums;

            size = other.size;
            nums = new int[size];
            for (int i = 0; i < size; i++) {
                nums[i] = other.nums[i];
            }
        }
        return *this;
    }

    int operator[](int index) const {
        assert(index >= 0 && index < size);
        return nums[index];
    }

    int& operator[](int index) {
        assert(index >= 0 && index < size);
        return nums[index];
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            cout << nums[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Plural p1;
    p1.add(1);
    p1.add(2);
    p1.add(3);

    Plural p2;
    p2.add(3);
    p2.add(4);
    p2.add(5);

    Plural p3 = p1 + 6;
    Plural p4 = p1 + p2;

    p3.print();
    p4.print();

    p4[1] = 8;
    p4.print();
    cout << p4[1] << endl;

    return 0;
}
