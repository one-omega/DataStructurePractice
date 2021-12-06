#include <iostream>
#include <set>
using namespace std;

struct HuffumanTree {
    int weight;
    HuffumanTree* left;
    HuffumanTree* right;
};

struct MinHeap {
    HuffumanTree** data;
    int size;
    int capacity;
};

MinHeap* Creat(int maxSize) {
    MinHeap* H = (MinHeap*)malloc(sizeof(MinHeap));
    H->data = (HuffumanTree**)malloc(sizeof(HuffumanTree*) * (maxSize+1));
    H->size = 0;
    H->capacity = maxSize;
    H->data[0]->weight = INT_MIN;
    return H;
}

bool isFull(MinHeap* H) {
    return H->size == H->capacity;
}

bool isEmpty(MinHeap* H) {
    return H->size == 0;
}

void Insert(HuffumanTree* t, MinHeap* H) {
    if (isFull(H)) {
        printf("already full\n");
        return;
    }
    int i = ++H->size;
    for (; H->data[i/2]->weight > t->weight; i/=2) {
        H->data[i] = H->data[i/2];
    }
    H->data[i] = t;
}

HuffumanTree* DeletaMin(MinHeap* H) {
    if (isEmpty(H)) {
        printf("Heap is empty\n");
    }
    HuffumanTree* maxEle = H->data[1];
    int parent = 1, child;
    HuffumanTree* temp = H->data[H->size--];
    for (; parent*2 <= H->size; parent = child) {
        child = parent*2;
        if ((child != H->size) && H->data[child]->weight > H->data[child+1]->weight) {
            child++;
        }
        if (temp->weight < H->data[child]->weight) {
            break;
        }
        H->data[parent] = H->data[child];
    }
    H->data[parent] = temp;
    return maxEle;
}

HuffumanTree* Huffuman(MinHeap* heap) {
    HuffumanTree* H;
    for (int i = 1; i < heap->size; i++) {
        H->left = DeletaMin(heap);
        H->right = DeletaMin(heap);
        H->weight = H->left->weight + H->right->weight;
        Insert(H,heap);
    }
    H = DeletaMin(heap);
    return H;
}


int main()
{

    return 0;
}