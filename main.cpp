#include <iostream>
#include "timsort.cpp"


int main() {
    int size = 40;
    int array[] = {1, 8, 5, 7, 2, 6, 3, 2, 8, 1, 1, 8, 5, 7, 2, 6, 3, 2, 8, 1, 1, 8, 5, 7, 2, 6, 3, 2, 8, 1, 1, 8, 5, 7, 2, 6, 3, 2, 8, 1};

    intTimsort obj(size, array);

    std::cout << "Изначальный массив: ";
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }

    std::vector<int> indexes = obj.sort(size);
    obj.updateArrayBySort(indexes);

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