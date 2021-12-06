#include <iostream>
using namespace std;
struct MinHeap {
    int* data;
    int size;
    int capacity;
};

MinHeap* Creat(int maxSize) {
    MinHeap* H = (MinHeap*)malloc(sizeof(MinHeap));
    H->data = (int*)malloc(sizeof(int)*(maxSize+1));
    H->size = 0;
    H->capacity = maxSize;
    H->data[0] = INT_MIN;
    return H;
}

bool isFull(MinHeap* H) {
    return H->size == H->capacity;
}

bool isEmpty(MinHeap* H) {
    return H->size == 0;
}

void Insert(int x, MinHeap* H) {
    if (isFull(H)) {
        printf("already full\n");
        return;
    }
    int i = ++H->size;
    for (; H->data[i/2] > x; i/=2) {
        H->data[i] = H->data[i/2];
    }
    H->data[i] = x;
}

int DeletaMin(MinHeap* H) {
    if (isEmpty(H)) {
        printf("Heap is empty\n");
    }
    int maxEle = H->data[1];
    int parent = 1, child;
    int temp = H->data[H->size--];
    for (; parent*2 <= H->size; parent = child) {
        child = parent*2;
        if ((child != H->size) && H->data[child] > H->data[child+1]) {
            child++;
        }
        if (temp < H->data[child]) {
            break;
        }
        H->data[parent] = H->data[child];
    }
    H->data[parent] = temp;
    return maxEle;
}

int main()
{
    
    return 0;
}