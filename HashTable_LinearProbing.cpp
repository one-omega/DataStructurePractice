#include <bits/stdc++.h>
using namespace std;
struct LNode {
    int data;
    LNode* next;
};
typedef LNode* List;
struct HashTable {
    int TableSize;
    LNode* lists;
};

HashTable* Creat(int size) {
    HashTable* H = (HashTable*)malloc(sizeof(HashTable));
    H->TableSize = size;
    H->lists = (LNode*)malloc(size*sizeof(LNode));
    for (int i = 0; i < size; i++) {
        H->lists[i].data = 0;
        H->lists[i].next = NULL;
    }
    return H;
}

int Hash(int TableSize, int value) {
    return value % TableSize;
}

LNode* Find(HashTable* H, int value) {
    int pos = Hash(H->TableSize, value);
    LNode* node = H->lists[pos].next;
    while (node && node->data != value) {
        node = node->next;
    }
    return node;
}

bool Insert(HashTable* H, int value) {
    LNode* p = Find(H, value);
    if (!p) {
        int index = Hash(H->TableSize, value);
        LNode* newNode = (LNode*)malloc(sizeof(LNode));
        newNode->data = value;
        newNode->next = H->lists[index].next;
        H->lists[index].next = newNode;
        return true;
    } else {
        printf("The value is already inserted\n");
        return false;
    }
}

void DestroyTable(HashTable* H) {
    for (int i = 0; i < H->TableSize; i++) {
        LNode* node = H->lists[i].next;
        while (node) {
            LNode* temp = node->next;
            free(node);
            node = temp;
        }
    }
    free(H->lists);
    free(H);
}

int main() {
    int size;
    cin >> size;
    int num;
    HashTable* H = Creat(size);
    while (cin >> num && num != -1) {
        Insert(H, num);
    }
    while (cin >> num && num != -1) {
        LNode* node = Find(H, num);
        if (node) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}