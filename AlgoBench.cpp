/*
Timing comparison between Insertion Sort and Merge Sort

ARGUMENTS:
    ./main.exe [#elements in array] [#times to run test] "--sorted"(OPTIONAL, makes array order sorted)
    argv[1] -> [INT] :: Number of elements in the array (n) 
    argv[2] -> [INT] :: Number of iteratios to run the test
    argv[3] -> ["--sorted"] :: (Optional) Makes array sorted upon generation
ex/
    ./main.exe 1000 100 "--sorted"
    ./main.exe 10000 1000

Table made by ChatGPT 5.0: 
| Algorithm          | Best Case                 | Average Case   | Worst Case                | Space Complexity    | Stable? |
| ------------------ | ------------------------- | -------------- | ------------------------- | ------------------- | ------- |
| **Insertion Sort** | **O(n)** (already sorted) | **O(n²)**      | **O(n²)** (reverse order) | O(1)                | ✅ Yes  |
| **Merge Sort**     | **O(n log n)**            | **O(n log n)** | **O(n log n)**            | O(n) (extra arrays) | ✅ Yes  |

*/

#include <iostream>
#include <vector> 
#include <chrono> // for timing
#include <random> // for RNG
#include <string> // for stoi()

using namespace std;

/* Function to sort array using insertion sort */
// Code from Geeks For Geeks
void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(vector<int>& arr, int left,int mid, int right) {
                         
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back 
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], 
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], 
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
// Code from Geeks for Geeks
void mergeSort(vector<int>& arr, int left, int right){
    
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Fills content of array with elements (sorted || random)
void fillArray(vector<int> &arr,  bool sorted) {
    if (sorted) {
        for (int i = 0; i < arr.size(); i++) {
            arr[i]=i;
        }
    } else {
        // Modern way to make random numbers
        random_device rng;
        mt19937 gen(rng()); // RNG engine (extremely non-deterministic!)
        uniform_int_distribution<> dist(0,arr.size()-1);
        for (int i = 0; i < arr.size(); i++) {
            arr[i]=dist(gen);
        }
    }
}

void runTest(int n, int iterations, bool sorted) {
    chrono::milliseconds insertionSortSum{0};
    chrono::milliseconds mergeSortSum{0};
    for (int i = 0; i < iterations; i++) {
        vector<int> arr1(n);
        vector<int> arr2(n);
        fillArray(arr1,sorted);
        fillArray(arr2,sorted);
        // INSERTION SORT //
        auto t1 = chrono::high_resolution_clock::now();
        insertionSort(arr1);
        auto t2 = chrono::high_resolution_clock::now(); 
        auto d = chrono::duration_cast<chrono::milliseconds>(t2-t1);
        insertionSortSum+=d;
        // MERGE SORT //
        t1 = chrono::high_resolution_clock::now();
        mergeSort(arr2,0,arr2.size()-1);
        t2 = chrono::high_resolution_clock::now(); 
        d = chrono::duration_cast<chrono::milliseconds>(t2-t1);
        mergeSortSum+=d;
    }
    auto insertionSortAverage = insertionSortSum / iterations;
    auto mergeSortAverage = mergeSortSum / iterations;
    cout 
        << "\n\nInsertion Sort Total: " << insertionSortSum.count() << "ms"
        << "\nInsertion Sort Average: " << insertionSortAverage.count() << "ms"
        << "\n\nMerge Sort Total: " << mergeSortSum.count() << "ms"
        << "\nMerge Sort Average: " << mergeSortAverage.count() << "ms";
}

int main(int argc, char *argv[]) {
    int n;
    int iterations;
    bool sorted = false;
    if (argc < 2) {
        cerr << "\nERROR: Invalid number of arguments";
        return -1;
    } else {
        try {
            n = stoi(argv[1]); // turns string into int
        } catch (const exception &e){
            cerr << "\nERROR: " << e.what();
            return -1;
        }
    }
    if (argc < 3) {
        cerr << "\nERROR: Invalid number of arguments";
        return -1;
    } else {
        try {
            iterations = stoi(argv[2]); // turns string into int
        } catch (const exception &e){
            cerr << "\nERROR: " << e.what();
            return -1;
        }
    }
    if (argc == 4) {
        string argv3 = argv[3];
        if (argv3 == "--sorted") {
            sorted = true;
        } else {
            cerr << "\nERROR: Argument [3] invalid, did you mean --sorted?";
            return -1;
        }
    }
    cout 
        << "Starting Test . . . "
        << "\nN = " << n
        << "\nIterations: " << iterations
        << "\nSorted: ";
        if (sorted) {
            cout << "TRUE";
        } else {
            cout << "FALSE";
        }
    runTest(n,iterations,sorted); 
}


