#include <iostream>
#include <vector>
#include <stack>


class Timsort {
private:
    int n;
    int minrun;
    int *indexes;
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
        int *indexes = new int[n];
        for (int i = 0; i < n; ++i) {
            indexes[i] = i;
        }
        this->indexes = indexes;
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
        while (currentPoint + 2 < n) {
            int startPoint = currentPoint;
            currentPoint = addNewSection(currentPoint);
            runSizes.push_back(currentPoint - startPoint + 1);
        }
        if (currentPoint + 1 < n) {
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
            while ((start - currentEnd + 1) != minrun && currentEnd + 1 < n) {
                ++currentEnd;
            }
            insertionSort(start, currentEnd);
        }
        return currentEnd;
    }

    void insertionSort(int start, int end) {
        if ((end - start + 1) == 1) return;

        for (int i = start + 1; i < (end - start + 1); ++i) {
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
        for (int i = 0; i < runs.size() - 1; ++i) {
            RUN first = getMin(runs, runs[0].runSize);
        }


    }

    RUN getMin(std::vector<RUN> runs, int currentMin) {
        return runs[0];
    }

    void mergeTwoSection(RUN p1, RUN p2){

    }

    std::vector<RUN> getStackForMerge(){
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

    int *sort(const int size) {
        if (size < 2)
            return nullptr;
        n = size;

        createAndFillIndexes();
        minrun = getMinrun(n);
        defineRunSizes();
        mergeSort();

        return indexes;
    }

    virtual int compare(int i1, int i2) = 0;
};


class intTimsort : public Timsort {
private:
    int n;
    int *array;
public:
    intTimsort(int n, int *array) : n(n), array(array) {}

    int compare(int i1, int i2) override {
        if (i1 == i2)
            return 0;
        return array[i1] < array[i2] ? -1 : 1;
    }
};


