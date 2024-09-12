#include <bits/stdc++.h>

using namespace std;


void prefix_func(string s, vector<int>& p) {
    for (size_t i = 1; i < s.size(); ++i) {
        int k = p[i - 1];
        while (k > 0 and s[k] != s[i]) {
            k = p[k - 1];
        }
        if (s[k] == s[i]) {
            ++k;
        }
        p[i] = k;
    }
}


int main() {
    string s;
    cin >> s;
    vector<int> p(s.size(), 0);

    prefix_func(s, p);

    for (auto elem : p) {
        cout << elem << " ";
    }

    return 0;
}