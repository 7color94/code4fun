#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <cstring>
#include <cmath>
#include <climits>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <unordered_map>
using namespace std;

int N, heap_size;
int A[100050];

void swap(int i, int j) {
    int t = A[i];
    A[i] = A[j];
    A[j] = t;
}

void max_heapify(int i) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int largest = -1;
    if (left <= heap_size && A[left] > A[i]) largest = left;
    else largest = i;
    if (right <= heap_size && A[right] > A[largest]) largest = right;
    if (largest != i) {
        swap(i, largest);
        max_heapify(largest);
    }
}

void swim(int k) {
    while (k > 1 && A[k / 2] < A[k]) {
        swap(k / 2, k);
        k = k / 2;
    }
}

int extract_max() {
    int ans = A[1];
    A[1] = A[heap_size];
    heap_size = heap_size - 1;
    max_heapify(1);
    return ans;
}

int main() {
    ifstream cin("in.txt");
    
    cin >> N;
    memset(A, 0, sizeof(A));
    heap_size = 0;

    while (N--) {
        char oop;
        cin >> oop;
        if (oop == 'A') {
            int w;
            cin >> w;
            A[++heap_size] = w;
            swim(heap_size);
        } else {
            int ans = extract_max();
            cout << ans << endl;
        }
    }

    return 0;
}