// includes
#include <iostream>
#include <chrono>

// constants
constexpr int ARRAY_SIZE = 100;

// namespaces
using std::cout;
using std::endl;

// helper functions
void FillArray(int arrayToFill[], int size);
void Swap(int* a, int* b);
void PrintArray(int arr[], int size);
int Partition(int arr[], int low, int high);
uint32_t GetNanos();

// sorting algorithms
void QuickSort(int arr[], int low, int high);

// fill the array with a random number between 1 and 100
void FillArray(int arrayToFill[], int size)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        arrayToFill[i] = rand() % ARRAY_SIZE + 1;
    }
}

// swap two elements
void Swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// prints the array
void PrintArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }    
    cout << endl;
}

// takes the last element as a pivot
// places pivot in the correct position
// places all elements < pivot to the left
// places all elements > pivot to the right
int Partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot 
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot 
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element 
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// returns the duration in nanoseconds
uint32_t GetNanos()
{
    using namespace std::chrono;
    return static_cast<uint32_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}

// quick sort algorithm
// low = starting index
// high = ending index
void QuickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = Partition(arr, low, high);

        // Separately sort elements before 
        // partition and after partition 
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

int main()
{
    // create the array
    int dataSet[ARRAY_SIZE]{};
    // seed the random generator
    srand(time(nullptr));
    // fill the array according to the size
    FillArray(dataSet, ARRAY_SIZE);

    // get the size of the array
    int n = sizeof(dataSet) / sizeof(dataSet[0]);
    uint32_t StartNanos = GetNanos();
    // run the quick sort algorithm
    QuickSort(dataSet, 0, n - 1);
    uint32_t EndNanos = GetNanos();

    cout << "Quick Sort took: " << (EndNanos - StartNanos) << "ns" << endl;
    cout << "Sorted array: \n";
    PrintArray(dataSet, n);
    return 0;
}