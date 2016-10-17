#include <iostream>
#include <vector>
#include <stack>


class Timsort {
private:
    int n;
    int minrun;
    std::vector<int> indexes;
    std::vector<int> runSizes;

    struct RUN {
        int startInArray;
        int runSize;
    };

    int getMinrun(int n) {
        int r = 0;
        while (n >= 64) {
            r |= n & 1;
            n >>= 1;
        }
        return n + r;
    }

    void createAndFillIndexes() {
        for (int i = 0; i < n; ++i) {
            indexes.push_back(i);
        }
    }

    void defineRunSizes() {
        int counter = 1;
        bool flag = true;
        bool start = false;

        if (n < 2) {
            invert(0, 1);
            runSizes.push_back(2);
            return;
        }

        int currentPoint = addNewSection(0);
        runSizes.push_back(currentPoint);
        while (currentPoint + 1 < n) {
            int startPoint = currentPoint;
            currentPoint = addNewSection(currentPoint);
            runSizes.push_back(currentPoint - startPoint);
        }
        if (currentPoint < n) {
            runSizes.push_back(1);
        }
    }

    int addNewSection(int start) {
        int currentEnd = start + 1;
        if (compare(indexes[start], indexes[start + 1]) > 0) {
            while (currentEnd + 1 < n && compare(indexes[currentEnd], indexes[currentEnd + 1]) > 0) {
                ++currentEnd;
            }
            invert(start, currentEnd);
            currentEnd = pourTheEnd(start, currentEnd);
        } else {
            while (currentEnd + 1 < n && compare(indexes[currentEnd], indexes[currentEnd + 1]) <= 0) {
                ++currentEnd;
            }
            currentEnd = pourTheEnd(start, currentEnd);
        }
        return ++currentEnd;
    }

    int pourTheEnd(int start, int currentEnd) {
        if ((currentEnd - start + 1) < minrun) {
            while ((currentEnd - start + 1) != minrun && currentEnd + 1 < n) {
                ++currentEnd;
            }
            insertionSort(start, currentEnd);
        }
        return currentEnd;
    }

    void insertionSort(int start, int end) {
        if ((end - start + 1) == 1) return;

        for (int i = start + 1; i <= end; ++i) {
            if (compare(indexes[i - 1], indexes[i]) > 0) {
                int step = i;
                while (compare(indexes[step - 1], indexes[step]) > 0 && step != start) {
                    int temp = indexes[step - 1];
                    indexes[step - 1] = indexes[step];
                    indexes[step] = temp;
                    --step;
                }
            }
        }

    }

    void invert(int start, int end) {
        int count = (end - start + 1) / 2;

        for (int i = 0; i < count; ++i) {
            auto temp = indexes[start + i];
            indexes[start + i] = indexes[end - i];
            indexes[end - i] = temp;
        }
    }

    void mergeSort() {
        if (runSizes.size() < 2) return;
        std::vector<RUN> runs = getStackForMerge();
        while (runs.size() > 2) {
            print(indexes);
            if (runs[0].runSize > (runs[1].runSize + runs[2].runSize) && (runs[1].runSize > runs[2].runSize)) {
                mergeTwoSection(runs[0], runs[1]);
                runs[0].runSize += runs[1].runSize;
                runs.erase(runs.begin() + 1);
            } else {
                if (runs[0].runSize > runs[2].runSize) {
                    mergeTwoSection(runs[1], runs[2]);
                } else {
                    mergeTwoSection(runs[0], runs[1]);
                }
                if (runs[0].runSize > runs[2].runSize) {
                    runs[1].runSize += runs[2].runSize;
                    runs.erase(runs.begin() + 2);
                } else {
                    runs[0].runSize += runs[1].runSize;
                    runs.erase(runs.begin() + 1);
                }
            }
        }
        mergeTwoSection(runs[0], runs[1]);
    }

    void mergeTwoSection(RUN p1, RUN p2) {
        std::vector<int> tempIndexses;
        for (int i = p1.startInArray, j = 0; i < (p1.startInArray + p1.runSize); ++i, ++j) {
            tempIndexses.push_back(indexes[i]);
        }
        int i = 0, j = p2.startInArray, k = p1.startInArray;
        while (i < p1.runSize && j < (p2.startInArray + p2.runSize)) {
            int compr = compare(tempIndexses[i], indexes[j]);
            switch (compr) {
                case 1:
                    indexes[k] = indexes[j];
                    ++j;
                    break;
                case -1:
                    indexes[k] = tempIndexses[i];
                    ++i;
                    break;
                case 0:
                    indexes[k++] = indexes[j];
                    indexes[k] = tempIndexses[i];
                    ++i;
                    ++j;
                    break;
            }
            ++k;
        }
        while (i < p1.runSize) {
            indexes[k++] = tempIndexses[i++];
        }
        while (j < (p2.startInArray + p2.runSize)) {
            indexes[k++] = indexes[j++];
        }
    }

    std::vector<RUN> getStackForMerge() {
        std::vector<RUN> runs;
        int start = 0;
        for (int i = 0; i < runSizes.size(); ++i) {
            RUN run;
            run.runSize = runSizes[i];
            run.startInArray = start;
            runs.push_back(run);
            start += run.runSize;
        }
        return runs;
    }


public:

    std::vector<int> sort(const int size) {
        n = size;

        createAndFillIndexes();
        minrun = getMinrun(n);
        defineRunSizes();
        mergeSort();

        return indexes;
    }

    virtual int compare(int i1, int i2) = 0;
    virtual void print(std::vector<int> indexes) = 0;
};


class intTimsort : public Timsort {
private:
    int n;
    int *array;
public:
    intTimsort(int n, int *array) : n(n), array(array) {}

    int compare(int i1, int i2) override {
        if (i1 == i2) return 0;
        if (array[i1] == array[i2]) return 0;
        return array[i1] < array[i2] ? -1 : 1;
    }

    void print(std::vector<int> indexes) override {
        std::cout << "\nРезультат: ";
        for (int i = 0; i < n; ++i) {
            std::cout << array[indexes[i]] << " ";
        }
    }

    void updateArrayBySort(std::vector<int> indexes) {
        int *newArray = new int[n];
        for (int i = 0; i < n; ++i) {
            newArray[i] = array[indexes[i]];
        }
        array = newArray;
    }

    bool checkValidOfSort() {
        for (int i = 1; i < n; ++i) {
            if (compare(i - 1, i) > 0) {
                return false;
            }
        }
        return true;
    }
};

class doubleTimsort : public Timsort {
private:
    int n;
    double *array;
public:
    doubleTimsort(int n, double *array) : n(n), array(array) {}

    int compare(int i1, int i2) override {
        if (i1 == i2) return 0;
        if ((array[i1] - array[i2]) < 0.000001) return 0;
        return array[i1] < array[i2] ? -1 : 1;
    }

    void print(std::vector<int> indexes) override {
        std::cout << "\nРезультат: ";
        for (int i = 0; i < n; ++i) {
            std::cout << array[indexes[i]] << " ";
        }
    }
};
