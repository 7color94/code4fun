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
using namespace std;

struct segment {
    int start, end;
    segment(int s, int e): start(s), end(e) {} 
};

int N;

bool compareBySE(const segment &a, const segment &b) {
    if (a.start == b.start) return a.end < b.end;
    return a.start < b.start;
}

int main() {
    ifstream cin("in.txt");
    cin >> N;

    int start, end;
    vector<segment> segs;
    for (int i = 0; i < N; i++) {
        cin >> start >> end;
        segment seg = segment(start, end);
        segs.push_back(seg);
    }

    std::sort(segs.begin(), segs.end(), compareBySE);

    // for (int i = 0; i < segs.size(); i++) {
    //     cout << segs[i].start << " " << segs[i].end << endl;
    // }

    int ans = 0;
    multiset<int> st;
    for (int i = 0; i < segs.size(); i++) {
        set<int>::iterator it = st.begin();  
        while(it != st.end()) {
            if (segs[i].start >= (*it)) it = st.erase(it);
            else break;  
        }
        st.insert(segs[i].end);
        ans = max(ans, (int)st.size());
    }

    cout << ans << endl;

    return 0;
}