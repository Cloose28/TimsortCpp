#include <iostream>
#include "timsort.cpp"

int main() {
    int size = 13;
    int array[] = {1, 5, 3, 8, 7, 8, 1, 2, 6, 3, 1, 5, 3};

    intTimsort obj(size, array);

    std::cout << "Изначальный массив: ";
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }

    int *indexes = obj.sort(size);
    obj.updateArrayBySort(indexes);
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

    if (obj.checkValidOfSort()) {
        std::cout << "\nСортировка успешна";
    } else {
        std::cout << "\nМассив не отсортирован";
    }
    return 0;
}