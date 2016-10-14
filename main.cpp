#include <iostream>
#include "timsort.cpp"

int main() {
    int size = 10;
    int array[] = {1, 5, 3, 4, 8, 8, 1, 2, 6, 6};

    intTimsort obj(size, array);

    std::cout << "Изначальный массив: ";
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }

    int *indexes = obj.sort(size);
    if (indexes == nullptr) {
        std::cout << "Здесь нечего сортировать!";
        return 0;
    }

    std::cout << "\nИндексы: ";
    for (int i = 0; i < size; ++i) {
        std::cout << indexes[i] << " ";
    }

    std::cout << "\nРезультат: ";
    for (int i = 0; i < size; ++i) {
        std::cout << array[indexes[i]] << " ";
    }

    return 0;
}