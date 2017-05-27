//C++11
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <queue>
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

struct Node {
    int x;
    int fishCount;

    Node(int x = -1, int fishCount = -1) {
        this->x = x;
        this->fishCount = fishCount;
    }

    bool operator>(const Node &n) const {
        return fishCount < n.fishCount;
    }
};

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
            int sumFish = 0;

            for (int x = 0; x < W; x++) {
                int num = char2int(data[i][x]);
                sumFish += num;
                g_fish[x] += num;
            }

            fprintf(stderr, "%s : %2d\n", data[i].c_str(), sumFish);
        }
    }

    vector<int> placeTraps(vector <string> data) {
        init(data);
        fprintf(stderr, "W = %d\n", W);
        // put traps in all locations on the river
        vector<int> traps;
        int days = data.size();
        bool setTraps[W];

        memset(setTraps, true, sizeof(setTraps));

        map<int, bool> check;

        /*j
        setTraps[0] = false;
        setTraps[W - 1] = false;
         */

        for (int x = 0; x < W; x++) {
            if (g_fish[x] <= days / 2) {
                //setTraps[x] = false;
            }
        }

        for (int x = 1; x < W - 1; x++) {
            if (g_fish[x - 1] >= g_fish[x] && g_fish[x] <= g_fish[x + 1]) {
                //setTraps[x] = false;
            }
            if (g_fish[x - 1] > 2 * g_fish[x] || 2 * g_fish[x] < g_fish[x + 1]) {
                //setTraps[x] = false;
            }
        }

        priority_queue <Node, vector<Node>, greater<Node>> pque;

        for (int x = 0; x < W; x++) {
            Node node(x, g_fish[x]);

            pque.push(node);
        }

        for (int i = 0; i < W * 0.1; i++) {
            Node node = pque.top();
            pque.pop();

            if (setTraps[node.x]) {
                traps.push_back(node.x);

                for (int d = 0; d < W / 8; d++) {
                    if (node.x > d) setTraps[node.x - (d + 1)] = false;
                    if (node.x < W - (d + 1)) setTraps[node.x + (d + 1)] = false;
                }
            }
        }

        while (!pque.empty()) {
            Node node = pque.top();
            pque.pop();
            setTraps[node.x] = false;
        }

        for (int x = 0; x < W; ++x) {
            fprintf(stderr, "%d", setTraps[x]);
        }

        fprintf(stderr, "\n");

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
