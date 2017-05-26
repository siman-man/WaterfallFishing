//C++11
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <vector>
#include <cassert>

using namespace std;

const int MAX_W = 200;

unsigned long long xor128() {
    static unsigned long long rx = 123456789, ry = 362436069, rz = 521288629, rw = 88675123;
    unsigned long long rt = (rx ^ (rx << 11));
    rx = ry;
    ry = rz;
    rz = rw;
    return (rw = (rw ^ (rw >> 19)) ^ (rt ^ (rt >> 8)));
}

int g_fish[MAX_W];
int W;

class WaterfallFishing {
public:
    int char2int(char ch) {
        if ('0' <= ch && ch <= '9') {
            return ch - '0';
        } else {
            return ch - 'A' + 10;
        }
    }

    void init(vector <string> &data) {
        memset(g_fish, 0, sizeof(g_fish));

        W = data[0].size();

        for (int i = 0; i < (int) data.size(); i++) {
            for (int x = 0; x < W; x++) {
                int num = char2int(data[i][x]);
                g_fish[x] += num;
            }
        }
    }

    vector<int> placeTraps(vector <string> data) {
        init(data);
        fprintf(stderr, "W = %d\n", W);
        // put traps in all locations on the river
        vector<int> traps;
        int limit = 10;

        map<int, bool> check;

        while (traps.size() < W / 20) {
            for (int j = 0; j < W; ++j) {
                if (g_fish[j] >= limit && !check[j]) {
                    traps.push_back(j);
                    check[j] = true;
                }
            }

            limit--;
        }
        return traps;
    }
};
// -------8<------- end of solution submitted to the website -------8<-------

template<class T>
void getVector(vector <T> &v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

int main() {
    WaterfallFishing wf;
    int S;
    cin >> S;
    vector <string> data(S);
    getVector(data);

    vector<int> ret = wf.placeTraps(data);
    cout << ret.size() << endl;
    for (int i : ret)
        cout << i << endl;
    cout.flush();
}
