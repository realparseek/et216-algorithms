#include <iostream>
#include <chrono>
#include <random>
#include <vector>

// Пузырьковая сортировка
void bubbleSort(std::vector<int>& a)
{
    int n = static_cast<int>(a.size());

    for (int i = 0; i < n-1; i++)
    {
        bool swapped = false;

        for (int j = 0; j < n-i-1; j++)
        {
            if (a[j] > a[j+1])
            {
                std::swap(a[j], a[j+1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

// Сортировка вставками
void insertionSort(std::vector<int>& a)
{
    for (unsigned int i = 1; i < a.size(); ++i)
    {
        int key = a[i];
        unsigned int j = i;

        while (j > 0 && a[j - 1] > key)
        {
            a[j] = a[j-1];
            --j;
        }

        a[j] = key;
    }
}

// Быстрая сортировка
void quickSortRange(std::vector<int>& a, int left, int right)
{
    int i = left;
    int j = right;

    int pivot = a[left + (right-left)/2];

    while (i <= j)
    {
        while (a[i] < pivot)
            i++;

        while (a[j] > pivot)
            j--;

        if (i <= j)
        {
            std::swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (left < j) quickSortRange(a, left, j);
    if (i < right) quickSortRange(a, i, right);
}

void quickSort(std::vector<int>& a)
{
    if (!a.empty())
    {
        quickSortRange(a, 0, static_cast<int>(a.size()) - 1);
    }
}

template <typename SortFunction>
double measureTime(
    const std::vector<int>& source,
    SortFunction sortFunction,
    int repeats)
{
    double totalTime = 0.0;
    long long guard = 0;

    for (int r = 0; r < repeats; ++r)
    {
        std::vector<int> a = source;

        auto start = std::chrono::high_resolution_clock::now();

        sortFunction(a);

        auto finish = std::chrono::high_resolution_clock::now();

        totalTime += std::chrono::duration<double, std::milli>(finish-start).count();
    }

    return totalTime / repeats;
}

// Главная функция
int main()
{
    const std::vector<int> sizes =
    {
        1000,
        2000,
        5000,
        10000,
        20000
    };
    const int repeats = 3;

    std::mt19937 rng;
    std::uniform_int_distribution<int> dist(0, 1000000);

    setlocale(LC_ALL, "rus");

    std::cout << std::left
        << std::setw(8) << "N"
        << std::setw(18) << "Bubble, ms"
        << std::setw(18) << "Insertion, ms"
        << std::setw(18) << "Quick, ms"
        << '\n';

    for (int n : sizes)
    {
        std::vector<int> data(n);

        for (int& x : data)
            x = dist(rng);

        double bubbleTime =
            measureTime(data, bubbleSort, repeats);

        double insertionTime =
            measureTime(data, insertionSort, repeats);

        double quickTime =
            measureTime(data, quickSort, repeats);

        std::cout << std::left
            << std::setw(8) << n
            << std::setw(18) << bubbleTime
            << std::setw(18) << insertionTime
            << std::setw(18) << quickTime
            << '\n';
    }

    return 0;
}