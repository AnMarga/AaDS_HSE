#include <bits/stdc++.h>

using namespace std;


#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define __min(a,b) (((a) < (b)) ? (a) : (b))


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


void z_func(string s, vector<int>& z) {
    int left = 0, right = 0;
    for (size_t i = 1; i < s.size(); ++i) {
        z[i] = __max(0, __min(z[i - left], right - i));
        while((i + z[i]) < s.size() and s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if ((i + z[i]) > right) {
            left = i;
            right = i + z[i];
        }
    }
}


int main() {
    string s;
    cin >> s;
    vector<int> p(s.size(), 0);
    //vector<int> z(s.size(), 0);

    prefix_func(s, p);
    
    /*
    z_func(s, z);

    int ans = 0;
    size_t i = 0;
    while (i < s.size() and p[i] == 0) {
        ++ans;
        ++i;
    }
    cout << ans << "\n";

    for (auto elem : p) {
        cout << elem << " ";
    }

    cout << "\n";

    for (auto elem : z) {
        cout << elem << " ";
    }

    cout << "\n";
    */

    cout << s.size() - p[s.size() - 1];
    
    return 0;
}