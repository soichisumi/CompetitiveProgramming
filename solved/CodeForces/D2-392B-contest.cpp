#include <bits/stdc++.h>
//#include <boost/functional/hash.hpp>
//example: unordered_set< pair<int,int>,boost::hash< std::pair<int, int> > > used;
//priority_queue< pair<int,pair<int,int> >, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int> > > > pqueue;    //cost, vertex(行き先)
using namespace std;

#define MODULE 1000000007
#define MP make_pair
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second
#define CONTAINS(x, y) (x.find(y)!=x.end()) //x<T1,T2>, T1 y
#define getPair(x) MP(x->first,x->second)

template<class T, class U>
inline void chmin(T &t, U f) { if (t > f)t = f; }

template<class T, class U>
inline void chmax(T &t, U f) { if (t < f)t = f; }

template<typename A, size_t N, typename T>
inline void Fill(A (&array)[N], const T &val) { //usage: int dp[10][10]; Fill(dp,INF);
    std::fill((T *) array, (T *) (array + N), val);
}

typedef pair<int, int> P;
typedef long long LL;
const int INF = INT_MAX / 2;    //int_max->2*e+9 LLの時はLLONG_MAX
/*const int MAXN = 100001;

struct edge {
    edge(int to, int cost) : to(to), cost(cost) {}
    int to, cost;
};
vector<edge> graph[MAXN];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};*/

//-----Template---------
string s;
string loop = "!!!!";

int counterR = 0;
int counterG = 0;
int counterB = 0;
int counterY = 0;

void countUp(char c) {
    switch (c) {
        case 'R':
            counterR++;
            break;
        case 'G':
            counterG++;
            break;
        case 'B':
            counterB++;
            break;
        case 'Y':
            counterY++;
            break;
        default:
            break;
    }
}

bool check(string str) {
    return str[0] != '!' && str[1] != '!' && str[2] != '!' && str[3] != '!';
}

int main() {
    ios::sync_with_stdio(false); //cout<< fixed << setprecision(10);
    //cout<<setw(4)<<setfill('0')<<"hoge"<<endl;
    cin >> s;
    int index = 0;
    while (index < s.length() && s[index] == '!')
        index++;

    for (int i = index; i < s.length(); ++i) {
        if(s[i]!='!')
            loop[(i - index) % 4] = s[i];
        if (check(loop))
            break;
    }
    if (!check(loop)) {
        set<char> memo;
        memo.insert('R');
        memo.insert('G');
        memo.insert('B');
        memo.insert('Y');
        for (int i = 0; i < 4; ++i) {
            memo.erase(loop[i]);
        }
        for (int i = 0; i < 4; ++i) {
            if (loop[i] == '!') {
                char tmp = *(memo.begin());
                loop[i] = tmp;
                memo.erase(tmp);
            }
        }
    }

    index %= 4;

    string rloop = loop;
    reverse(rloop.begin(), rloop.end());

    for (int i = 0; index - 1 - i >= 0; ++i) {
        if (s[index - 1 - i] == '!')
            countUp(rloop[i]);
    }
    for (int i = index; i < s.length(); ++i) {
        if (s[i] == '!')
            countUp(loop[(i - index) % 4]);
    }
    cout << counterR << " " << counterB << " " << counterY << " " << counterG << endl;
}