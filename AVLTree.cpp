#include <iostream>
#include <queue>
using namespace std;
typedef struct AVLNode AVLTree;
struct AVLNode {
    int data;
    AVLTree* left;
    AVLTree* right;
    int height;
};
int Max(int a, int b) {
    return a > b ? a : b;
}

int GetHeight(AVLTree* T) {
    if (T) {
        return T->height;
    } else {
        return -1;
    }
}

AVLTree* SingleLeftRotation(AVLTree* A) {
    AVLTree* B = A->left;
    A->left = B->right;
    B->right = A;
    A->height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;
    B->height = Max(GetHeight(B->left), GetHeight(A)) + 1;
    return B;
}

AVLTree* SingleRightRotation(AVLTree* A) {
    AVLTree* B = A->right;
    A->right = B->left;
    B->left = A;
    A->height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;
    B->height = Max(GetHeight(A), GetHeight(B->right)) + 1;
    return B;
}

AVLTree* DoubleLeftRightRotation(AVLTree* A) {
    A->left = SingleRightRotation(A->left);
    return SingleLeftRotation(A);   //return C
}

AVLTree* DoubleRightLfetRotation(AVLTree* A) {
    A->right = SingleLeftRotation(A->right);
    return SingleRightRotation(A);  // return C
}

AVLTree* Insert(AVLTree* T, int X) {
    if (!T) {
        T = (AVLTree*)malloc(sizeof(AVLTree));
        T->data = X;
        T->left = T->right = NULL;
        T->height = 0;
    } else if (X < T->data) {
        T->left = Insert(T->left, X);
        if (GetHeight(T->left) - GetHeight(T->right) == 2) {
            if (X < T->left->data) {
                T = SingleLeftRotation(T);
            } else {
                T = DoubleLeftRightRotation(T);
            }
        }
    } else if (X > T->data) {
        T->right = Insert(T->right, X);
        if (GetHeight(T->right) - GetHeight(T->left) == 2) {
            if (X < T->right->data) {
                T = DoubleRightLfetRotation(T);
            } else {
                T = SingleRightRotation(T);
            }
        }
    }
    T->height = Max(GetHeight(T->left),GetHeight(T->right)) + 1;
    return T;
}

void LevelOrderTraversal(AVLTree* T) {
    if (!T) {
        return;
    }
    queue<AVLNode*> que;
    que.push(T);
    int h = T->height;
    while (!que.empty()) {
        AVLNode* node = que.front();
        que.pop();
        if (h == node->height) {
            printf("%d(%d) ",node->data,node->height);
        } else {
            printf("\n%d(%d) ",node->data,node->height);
            h = node->height;
        }
        if (node->left) {
            que.push(node->left);
        }
        if (node->right) {
            que.push(node->right);
        }
    }
}

int main()
{
    AVLTree* T = NULL;
    while (1) {
        int x;
        cin >> x;
        if (x == -1) break;
        T = Insert(T, x);
    }
    LevelOrderTraversal(T);
    cout << endl;
    return 0;
}