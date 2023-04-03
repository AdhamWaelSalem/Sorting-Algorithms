#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void BubbleSort(int array[], int size);
void SelectionSort(int array[], int size);
void InsertionSort(int array[], int size);
void MergeSort(int array[], int size);
void HeapSort(int array[], int size);
void Heapify(int array[],int size, int root);
void BuildMaxHeap(int array[],int size);
void QuickSort(int array[], int size);
void GenerateArray(int array[], int size);
void PrintArray(int array[], int size);
double MeasureTime(void (*Sort)(int *,int),int array[],int size);
void CloneArray(int array[], int size, const int base[]);
int CheckSorted(const int array[],int size);
void Swap(int *a, int *b);


int main() {
    srand(time(NULL));

    char a[] = {"Bubble Sort"};
    char b[] = {"Selection Sort"};
    char c[] = {"Insertion Sort"};
    char d[] = {"Merge Sort"};
    char e[] = {"Heap Sort"};
    char f[] = {"Quick Sort"};

    char *Sorts [6] = {a,b,c,d,e,f};

    void (*SortFunction[6]) (int *, int) = {&BubbleSort, &SelectionSort, &InsertionSort, &MergeSort, &HeapSort, &QuickSort};

    int base_10[10];
    int base_100[100];
    int base_1000[1000];
    int base_10000[10000];
    int base_100000[100000];
    int * base[5] = {base_10, base_100, base_1000, base_10000, base_100000};

    GenerateArray(base_10, 10);
    GenerateArray(base_100, 100);
    GenerateArray(base_1000, 1000);
    GenerateArray(base_10000, 10000);
    GenerateArray(base_100000, 100000);

    int array_10[10];
    int array_100[100];
    int array_1000[1000];
    int array_10000[10000];
    int array_100000[100000];
    int * array[5] = {array_10, array_100, array_1000, array_10000, array_100000};

    double Time[6][5];

    for (int i = 0; i < 5; ++i) {
        printf("\t\t%d",(int) pow(10,i + 1));
    }
    printf("\n");

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 5; ++j) {
            CloneArray(array[j], (int) pow(10,j + 1), base[j]);
        }
        printf("%s\t",Sorts[i]);
        for (int j = 0; j < 5; ++j) {
            Time[i][j] = MeasureTime(SortFunction[i], array[j], (int) pow(10,j + 1));
            printf("%lf\t",Time[i][j]);
        }
        printf("\n");

    }
//    int size = 300000;
//    int *array = (int*) malloc(size * sizeof(int));
//    int *base = (int*) malloc(size * sizeof(int));
//    printf("\t\t%d\n",size);
//    clock_t start,end;
//    double time;
//    char *s;
//    int true;
//    GenerateArray(base,size);
//    for (int i = 0; i < 6; ++i) {
//        CloneArray(array,size,base);
////        s = Sorts[i];
////        printf("%s\t",s);
//        start = clock();
//        (SortFunction[i])(array, size);
//        end = clock();
//        time = ((double) (end - start));
//        printf("%lf\n",time);
////        true = CheckSorted(array,size);
////        printf("%d\n", true);
//    }
//    free(array);
//    return 0;
}

void BubbleSort(int array[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (array[j] > array[j+1]) {
                Swap(array+j,array+j+1);
            }
        }
    }
}
void SelectionSort(int array[], int size) {
    int current;

    for (int i = 0; i < size; ++i) {
        current = i;
        for (int j = i + 1; j < size; ++j) {
            if (array[j] < array [current]) {
                current = j;
            }
        }
        if (current != i) {
            Swap(array+current,array+i);
        }
    }
}
void InsertionSort(int array[], int size) {
    int value;
    int j;
    for (int i = 1; i < size; ++i) {
        value = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > value) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = value;
    }
}
void MergeSort(int array[], int size) {

    if (size < 2) return;
    int mid = size/2;
    int left[mid], right[size - mid];
    for (int i = 0; i < mid; ++i) {
        left[i] = array[i];
    }
    for (int i = 0; i < size - mid; ++i) {
        right[i] = array[i + mid];
    }
    MergeSort(left,mid);
    MergeSort(right, size - mid);
    int l = 0, r = 0,a = 0;
    while (l < mid && r < size - mid) {
        if(left[l] <= right[r]) {
            array[a++] = left[l++];
        } else {
            array[a++] = right[r++];
        }
    }
    for (; l < mid; ++l) {
        array[a++] = left[l];
    }
    for (; r < size - mid; ++r) {
        array[a++] = right[r];
    }
}
void HeapSort(int array[], int size) {
    heapsort:
    if (size < 2) return;
    BuildMaxHeap(array,size);
    Swap(array,array+size-1);
//    HeapSort(array,size - 1);
    size = size - 1;
    goto heapsort;
}
void Heapify(int array[],int size, int root) {
    int left,right,max;
    heapify:
    left = 2 * root + 1;
    right = 2 * root + 2;
    max = root;
    if (left < size && array[max] < array[left]) max = left;
    if (right < size && array[max] < array[right]) max = right;
    if (max != root) {
//        int temp = array[max];
//        array[max] = array[root];
//        array[root] = temp;
        Swap(array+max,array+root);
//        Heapify(array,size,max);
        root = max;
        goto heapify;
    }

}
void BuildMaxHeap(int array[],int size) {
    for (int i = size/2 - 1; i >= 0; --i) {
        Heapify(array,size,i);
    }
}
void QuickSort(int array[], int size) {
    int pivot,l,r;
    quicksort:
    if (size < 2) return;
    pivot = size - 1;
    l = 0;
    r = size - 2;
    while (l < r) {
        if(array[l] <= array[pivot]) {
            l++;
            continue;
        }
        if(array[r] > array[pivot]) {
            r--;
            continue;
        }
        Swap(array+r,array+l);
        l++;
        r--;
    }
    if(array[r] <= array[pivot]) r++;
    Swap(array+r,array+pivot);
    pivot = r;
    QuickSort(array+pivot+1,size-pivot-1);
    //    QuickSort(array,pivot);
    size = pivot;

    goto quicksort;
}
void GenerateArray(int array[], int size){
    for (int i = 0; i < size; ++i) {
        array[i] = (int) (pow(-1,rand() % 2) * (rand() * size) /(rand()+1)) ;
    }
}
void PrintArray(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d\t",array[i]);
    }
    printf("\n");
}
double MeasureTime(void (*Sort)(int *,int ),int array[],int size){
    clock_t start,end;
    start = clock();
    (*Sort)(array, size);
    end = clock();
    return ((double) (end - start));
}
void CloneArray(int array[], int size, const int base[]){
    for (int i = 0; i < size; ++i) {
        array[i] = base[i];
    }
}
void Swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int CheckSorted(const int array[],int size) {
    for (int j = 0; j < size - 1; ++j) {
        if (array[j] > array[j+1]) return 0;
    }
    return 1;
}