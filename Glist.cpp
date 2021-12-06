#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
struct Term {
    int val;
};
typedef struct GNode PtrToHeader;
struct GNode {
    GNode* down;
    GNode* right;
    int col;
    int row;
    union {
        PtrToHeader* next;
        Term term;
    };
};

GNode* CreatMLink() {
    GNode* header = (GNode*)malloc(sizeof(GNode));
    int c,r,t;
    scanf("%d%d%d",&c,&r,&t);   //行，列，非零元素个数
    header->col = c;
    header->row = r;
    header->term.val = t;
    int s = max(c,r);
    GNode* hds[s+1];
    hds[0] = header;
    for (int i = 1; i <= s; i++) {
        GNode* hd = (GNode*)malloc(sizeof(GNode));
        memset(hd,0,sizeof(0));
        hd->down = hd;
        hd->right = hd;
        hds[i] = hd;
        hds[i-1]->next = hds[i];
    }
    hds[s]->next = hds[0];
    for (int i = 0; i < t; i++) {
        int v;
        scanf("%d%d%d",&c,&r,&v);   //行，列，值
        GNode* TermNode = (GNode*)malloc(sizeof(GNode));
        TermNode->col = c;
        TermNode->row = r;
        TermNode->term.val = v;
        //插入第c行链表中。从头节点开始按列遍历，找到TermNode的上一个节点
        GNode* pre = hds[c];
        while (pre->right != hds[c] && pre->right->row < r) {
            pre = pre->right;
        }
        TermNode->right = pre->right;
        pre->right = TermNode;
        //插入第r列链表中。从头节点按行开始遍历，找到TermNode的上一个节点
        pre  = hds[r];
        while (pre->down != hds[r] && pre->down->col < c) {
            pre = pre->down;
        }
        TermNode->down = pre->down;
        pre->down = TermNode;
    }
    return header;
}

void print(GNode* Header) {
    GNode* hd = Header;
    int colum = 1;
    while (hd->next != Header && colum <= Header->col) {
        hd = hd->next;
        GNode* Gnode = hd;
        int index = 1;
        while (Gnode->right != hd) {
            Gnode = Gnode->right;
            while (index < Gnode->row) {
                printf("0 ");
                index++;
            }
            printf("%d ",Gnode->term.val);
            index++;
        }
        while (index <= Header->row) {
            printf("0 ");
            index++;
        }
        printf("\n");
        colum++;
    }
}

int main()
{
    GNode* Header = CreatMLink();
    print(Header);
    return 0;
}