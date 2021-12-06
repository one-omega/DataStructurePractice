#include <iostream>
using namespace std;
struct MaxHeap{
    int* data;
    int size;
    int capacity;
};

MaxHeap* Creat(int maxSize) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->data = (int*)malloc((maxSize+1)*sizeof(int));
    heap->size = 0;
    heap->capacity = maxSize;
    heap->data[0] = 10000;
    return heap;
}

bool isFull(MaxHeap* heap) {
    return heap->size == heap->capacity;
}

void Insert(MaxHeap* heap, int item) {
    // heap->data[0]为哨兵，放的是定义域内的最大元素,元素插入时一定不可能比heap->data[0]大
    if (isFull(heap)) {
        printf("already full\n");
        return;
    }
    int i = ++heap->size;
    for (; heap->data[i/2] < item; i /= 2) {
        heap->data[i] = heap->data[i/2];
    }
    heap->data[i] = item;
}

int DeleteMax(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("already empty\n");
        return -1;
    }
    int maxItem = heap->data[1];
    int temp = heap->data[heap->size--];
    int parent = 1, child;
    for (; parent*2 <= heap->size; parent = child) {
        child = parent * 2;
        if (child < heap->size && heap->data[child+1] > heap->data[child]) {
            child++;
        }
        if (temp > heap->data[child]) {
            break;
        } else {
            heap->data[parent] = heap->data[child];
        }
    }
    heap->data[parent] = temp;
    return maxItem;
}

int main() {
    MaxHeap* heap = Creat(100);
    while (1) {
        int num;
        cin >> num;
        if (num == -1) break;
        Insert(heap,num);
    }
    for (int i = 1; i <= heap->size; i++) {
        printf("%d ",heap->data[i]);
    }
    return 0;
}