#include <algorithm>
#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <vector>

using namespace std;

const int MAX_W = 200;

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
        fprintf(stderr, "WIDTH = %d\n", W);

        vector<int> traps;
        bool setTraps[W];
        memset(setTraps, true, sizeof(setTraps));

        priority_queue <Node, vector<Node>, greater<Node>> pque;

        for (int x = 0; x < W; x++) {
            pque.push(Node(x, g_fish[x]));
        }

        double rate = 0.25;

        for (int i = 0; i < 1 && !pque.empty(); i++) {
            Node node = pque.top();
            pque.pop();

            if ((W * rate) < node.x && node.x < W * (1.0 - rate)) {
                traps.push_back(node.x);
            } else {
                setTraps[node.x] = false;
                i--;
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
void getVector(vector <T> &v) { for (int i = 0; i < v.size(); ++i) cin >> v[i]; }

int main() {
    WaterfallFishing wf;
    int S;
    cin >> S;
    vector <string> data(S);
    getVector(data);
    vector<int> ret = wf.placeTraps(data);
    cout << ret.size() << endl;
    for (int i : ret) { cout << i << endl; }
    cout.flush();
}
