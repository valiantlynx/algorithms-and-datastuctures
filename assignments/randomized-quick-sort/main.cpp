#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

using namespace std;

// Partition the array
// This function selects a random pivot, places it at the end, and partitions the array around the pivot
template <typename T>
int partition(vector<T> &arr, int low, int high) {
    int randomPivot = low + rand() % (high - low + 1);
    swap(arr[randomPivot], arr[high]); // Move the pivot(random) to the end
    T pivot = arr[high];
    int i = low - 1;

    // Partitioning the array around the pivot
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]); // Place pivot in its correct position
    return i + 1;
}

// Randomized Quick Sort
// This function sorts the array by recursively partitioning it using a random pivot
template <typename T>
void randomizedQuickSort(vector<T> &arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high); // Partition the array and get pivot index
        randomizedQuickSort(arr, low, pivotIndex - 1); // Recursively sort elements before pivot
        randomizedQuickSort(arr, pivotIndex + 1, high); // Recursively sort elements after pivot
    }
}

// Normal Quick Sort
// This function sorts the array using the classic Quick Sort algorithm
template <typename T>
int normalPartition(vector<T> &arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void normalQuickSort(vector<T> &arr, int low, int high) {
    if (low < high) {
        int pivotIndex = normalPartition(arr, low, high);
        normalQuickSort(arr, low, pivotIndex - 1);
        normalQuickSort(arr, pivotIndex + 1, high);
    }
}

// Merge Sort
// This function merges two sorted halves of the array
template <typename T>
void merge(vector<T> &arr, int lb, int mid, int ub) {
    int i = lb, j = mid + 1, k = 0;
    vector<T> temp(ub - lb + 1);
    while (i <= mid && j <= ub) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= ub) {
        temp[k++] = arr[j++];
    }
    for (i = lb, k = 0; i <= ub; ++i, ++k) {
        arr[i] = temp[k];
    }
}

// This function recursively sorts the array using Merge Sort
template <typename T>
void mergeSort(vector<T> &arr, int lb, int ub) {
    if (lb < ub) {
        int mid = (lb + ub) / 2;
        mergeSort(arr, lb, mid); // Sort the first half
        mergeSort(arr, mid + 1, ub); // Sort the second half
        merge(arr, lb, mid, ub); // Merge the sorted halves
    }
}

// Function to handle user input and perform sorting
template <typename T>
void sortArray() {
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;
    if (n <= 0) {
        cout << "Invalid input. The array must contain at least one element." << endl;
        return;
    }

    vector<T> arr(n);
    cout << "Enter the elements of the array: " << endl;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    vector<T> arrCopy1 = arr; // Create a copy of the array for Merge Sort comparison
    vector<T> arrCopy2 = arr; // Create a copy of the array for Normal Quick Sort comparison

    // Measure Randomized Quick Sort time
    auto start = chrono::high_resolution_clock::now();
    randomizedQuickSort(arr, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();
    auto quickSortDuration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Output the sorted array using Randomized Quick Sort
    cout << "The sorted array using Randomized Quick Sort is: " << endl;
    for (const auto &element : arr) {
        cout << element << " ";
    }
    cout << endl;
    cout << "Time taken by Randomized Quick Sort: " << quickSortDuration << " microseconds" << endl;

    // Measure Merge Sort time
    start = chrono::high_resolution_clock::now();
    mergeSort(arrCopy1, 0, n - 1);
    end = chrono::high_resolution_clock::now();
    auto mergeSortDuration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Output the sorted array using Merge Sort
    cout << "The sorted array using Merge Sort is: " << endl;
    for (const auto &element : arrCopy1) {
        cout << element << " ";
    }
    cout << endl;
    cout << "Time taken by Merge Sort: " << mergeSortDuration << " microseconds" << endl;

    // Measure Normal Quick Sort time
    start = chrono::high_resolution_clock::now();
    normalQuickSort(arrCopy2, 0, n - 1);
    end = chrono::high_resolution_clock::now();
    auto normalQuickSortDuration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Output the sorted array using Normal Quick Sort
    cout << "The sorted array using Normal Quick Sort is: " << endl;
    for (const auto &element : arrCopy2) {
        cout << element << " ";
    }
    cout << endl;
    cout << "Time taken by Normal Quick Sort: " << normalQuickSortDuration << " microseconds" << endl;
}

int main() {
    srand(time(0)); // Seed the random number generator

    char type;
    cout << "Enter 'i' for integers or 'f' for floating-point numbers: ";
    cin >> type;

    if (type == 'i') {
        sortArray<int>(); // Sort an array of integers
    } else if (type == 'f') {
        sortArray<float>(); // Sort an array of floating-point numbers
    } else {
        cout << "Invalid input type." << endl;
    }

    return 0;
}