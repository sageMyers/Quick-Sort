#include <stdio.h>
#include <stdlib.h>

// Struct to represent a sorted list
typedef struct {
    int size;         // Current number of elements in the list
    int capacity;     // Maximum capacity of the list
    int* data;        // Array to store the elements
} SortedList;
// Function to create a new SortedList
SortedList* createSortedList(int size) {
    SortedList* list = (SortedList*)malloc(sizeof(SortedList)); // Allocate memory for the SortedList structure
    list->size = 0;         // Initialize size to 0
    list->capacity = size;  // Set the maximum capacity
    list->data = (int*)malloc(size * sizeof(int)); // Allocate memory for the array of data
    return list;            // Return the created list
}

// Function to release memory used by the SortedList
void destroySortedList(SortedList* list) {
    free(list->data); // Free memory used by the array
    free(list);       // Free memory used by the SortedList structure
}

// Function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform the partition step of the Quick Sort algorithm
int partition(SortedList* list, int low, int high) {
    int pivot = list->data[low]; // Choose the pivot element
    int i = low + 1;             // Index to track elements smaller than the pivot

    // Loop through the elements
    for (int j = low + 1; j <= high; j++) {
        if (list->data[j] < pivot) {
            swap(&list->data[i], &list->data[j]); // Swap elements if smaller than pivot
            i++;
        }
    }

    // Place the pivot in its correct position
    swap(&list->data[low], &list->data[i - 1]);
    return i - 1; // Return the index of the pivot
}

// Function to perform the Quick Sort algorithm
void quickSort(SortedList* list, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(list, low, high); // Get the pivot index
        quickSort(list, low, pivotIndex - 1);        // Sort the left subarray
        quickSort(list, pivotIndex + 1, high);       // Sort the right subarray
    }
}


// ... Other functions (createSortedList, destroySortedList, partition, quickSort) ...

int main() {
    SortedList* list = createSortedList(100); // Create a new SortedList with capacity 100 (adjust as needed)

   if (rank == 0) {
    // Read numbers from numbers.txt and add them to the list
    FILE* inputFile = fopen("numbers.txt", "r"); // Open input file for reading
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }
   }

    int num;
    while (fscanf(inputFile, "%d", &num) != EOF) { // Read numbers from input file
        list->data[list->size++] = num; // Add number to the list and increase the size
    }
    fclose(inputFile); // Close input file

    // Perform quick sort
    quickSort(list, 0, list->size - 1); // Perform quick sort on the list

    // Write sorted numbers to result.txt
    FILE* outputFile = fopen("result.txt", "w"); // Open output file for writing
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        destroySortedList(list);
        return 1;
    }

    for (int i = 0; i < list->size; i++) {
        fprintf(outputFile, "%d\n", list->data[i]); // Write sorted number to output file
    }
    fclose(outputFile); // Close output file

    destroySortedList(list); // Release memory used by the list

    return 0; // Return 0 to indicate successful execution
}