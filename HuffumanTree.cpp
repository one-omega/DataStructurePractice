#include <bits/stdc++.h>
using namespace std;

typedef struct HNode *HuffumanTree;
struct HNode {
    int weight;
    HuffumanTree left;
    HuffumanTree right;
};

struct MinHeap {
    HuffumanTree* data;
    int size;
    int capacity;
};

void PercDown(MinHeap* H, int index) {
    HNode* X = H->data[index];
    int parent = index, child;
    for (; parent*2 <= H->size; parent = child) {
        child = parent*2;
        if ((child != H->size) && H->data[child]->weight > H->data[child+1]->weight) {
            child++;
        }
        if (X->weight < H->data[child]->weight) break;
        H->data[parent] = H->data[child];
    }
    H->data[parent] = X;
}

void BuildMinHeap(MinHeap* H) {
    for (int i = H->size; i > 0; i--) {
        PercDown(H, i);
    }
}

HuffumanTree DeletaMin(MinHeap* H) {
    HuffumanTree minEle = H->data[1];
    int parent = 1, child;
    HuffumanTree temp = H->data[H->size--];
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
    return minEle;
}

void Insert(MinHeap* H, HuffumanTree x) {
    int i = ++H->size;
    for (; H->data[i/2]->weight > x->weight; i/=2) {
        H->data[i] = H->data[i/2];
    }
    H->data[i] = x;
}

HuffumanTree Huffuman(MinHeap* H) {
    HuffumanTree T;
    BuildMinHeap(H);
    int n = H->size;
    for (int i = 1; i < n; i++) {
        T = (HuffumanTree)malloc(sizeof(HNode));
        T->left = DeletaMin(H);
        T->right = DeletaMin(H);
        T->weight = T->left->weight + T->right->weight;
        Insert(H, T);
    }
    return DeletaMin(H);
}


int main()
{
    MinHeap* H = (MinHeap*)malloc(sizeof(MinHeap));
    HuffumanTree node = (HuffumanTree)malloc(sizeof(HNode));
    node->weight = INT_MIN;
    int n; //元素个数
    scanf("%d",&n);
    H->size = n;
    H->data = (HuffumanTree*)malloc( (n+1) * sizeof(HuffumanTree));
    H->data[0] = node;
    for (int i = 1; i <= n; i++) {
        HuffumanTree newNode = (HuffumanTree)malloc(sizeof(HNode));
        scanf("%d",&newNode->weight);
        H->data[i] = newNode;
    }
    HuffumanTree HT = Huffuman(H);
    printf("%d\n",HT->weight);
    return 0;
}