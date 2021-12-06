#include <bits/stdc++.h>
#define MAXSIZE 100000
using namespace std;
typedef enum{occupied, empty, deleted} EntryType;;
struct HashEntry {
    int data;
    EntryType state;
};
struct HashTable {
    int TableSize;
    HashEntry* HashEntries;
};

int NextPrime(int TalbleSize) {
    int init = (TalbleSize % 2) ? TalbleSize + 2 : TalbleSize + 1; //大于TalbeSize的下一个奇数
    while (init <= MAXSIZE) {
        int i = sqrt(init);
        for ( ; i > 2; i--) {
            if (init % i == 0) break; 
        }
        if (i == 2 && i % 4 == 3) break;
        else init += 2;
    }
    return init;
}

HashTable* CreatTable(int TableSize) {
    TableSize = NextPrime(TableSize);
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->TableSize = TableSize;
    table->HashEntries = (HashEntry*)malloc(TableSize * sizeof(HashEntry));
    for (int i = 0; i < TableSize; i++) {
        table->HashEntries[i].state = empty;
    }
    return table;
}

int Hash(int value, int mod) {
    return value % mod;
}

int Find(HashTable* H, int value) {
    int cnt = 0;
    int newPos, CurrentPos;
    newPos = CurrentPos = Hash(value, H->TableSize);
    while (H->HashEntries[newPos].state != empty && H->HashEntries[newPos].data != value) {
        if (++cnt % 2) {
            newPos = CurrentPos + (cnt + 1) * (cnt + 1) / 4;
            newPos %= H->TableSize;
        } else {
            newPos = CurrentPos - cnt * cnt / 4;
            while (newPos < 0) {
                newPos += H->TableSize;
            }
        }
    }
    return newPos;
}

bool Insert(HashTable* H, int value) {
    int pos = Find(H, value);
    if (H->HashEntries[pos].state != occupied) {
        H->HashEntries[pos].data = value;
        H->HashEntries[pos].state = occupied;
        return true;
    } else {
        printf("The position is occupied\n");
        return false;
    }
}

int main() {
    int size;
    scanf("%d",&size);
    HashTable* H = CreatTable(size);
    int num;
    while (cin >> num && num != -1) {
        Insert(H, num);
    }
    while (cin >> num && num != -1) {
        int index = Find(H, num);
        if (H->HashEntries[index].state == occupied) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    free(H->HashEntries);
    free(H);
    return 0;
}