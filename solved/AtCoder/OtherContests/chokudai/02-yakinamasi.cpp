#include <bits/stdc++.h>
#include <stdlib.h>
//#include <boost/functional/hash.hpp>
//example: unordered_set< pair<int,int>,boost::hash< std::pair<int, int> > > used;
//priority_queue< pair<int,pair<int,int> >, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int> > > > pqueue;    //cost, vertex(行き先)
using namespace std;

#define MODULE 1000000007
#define MP make_pair
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second

template<class T,class U>inline void chmin(T &t,U f){if(t>f)t=f;}
template<class T,class U>inline void chmax(T &t,U f){if(t<f)t=f;}
template<typename A, size_t N, typename T>
inline void Fill(A (&array)[N], const T &val){ //usage: int dp[10][10]; Fill(dp,INF);
    std::fill( (T*)array, (T*)(array+N), val );
}

typedef pair<int, int> P;
typedef long long LL;
const int INF = INT_MAX / 2;    //int_max->2*e+9 LLの時はLLONG_MAX

//---エラトステネスのふるい  n以下の素数を列挙--------------- O(nlog(logn))
vector<LL> getPrimesEratos(LL n){
    LL rootN= static_cast<long>(sqrt(n));
    bool prime[n+1];
    fill(prime,prime+n+1,true);
    prime[0]=prime[1]=false;
    for (LL i = 2; i <= rootN ; i++) {  //√nを超えないすべての素数で割り切れなければnは素数
        if(prime[i]) {
            for (LL j = i * 2; j <= n; j+=i) prime[j] = false;
        }
    }
    vector<LL> res;
    for(LL i=0;i<=n;i++){
        if(prime[i])
            res.push_back(i);
    }
    return res;
}

//素因数分解
map<LL, LL> primeDecomposition(LL num, vector<LL> &primes) {
    map<LL, LL> res;
    for (int i = 0; i < primes.size(); ++i) {
        while (num % primes[i] == 0) {
            num /= primes[i];
            res[primes[i]]++;
        }
    }
    return res;
}




//メルセンヌ・ツイスタよりも高速な乱数生成
//C++11以上
class xor128{
public:
    static constexpr unsigned min(){ return 0u; }
    static constexpr unsigned max(){ return UINT_MAX; }
    unsigned operator()(){ return random(); }   //ファンクタ
    xor128(){
        // シードが与えられない時はシステムからシードを生成
        std::random_device rd;
        w=rd();

        for(int i=0;i<10;i++){  // 数回空読み(不要?)
            random();
        }
    }
    xor128(unsigned s){ w=s; }
private:
    unsigned x=123456789u,y=362436069u,z=521288629u,w;
    unsigned random(){
        unsigned t;
        t = x ^ (x << 11);
        x = y; y = z; z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
};


LL getTime(){
    time_t aclock;
    aclock = time(NULL);  //1970年1月1日0時0分0秒（UTC）からの経過秒数
    return aclock; //secで返す
    /*
    struct tm* newTime;
    char* now;
    newtime = localtime(&aclock);        // tm構造体への変換
    now     = asctime(newtime);          // 文字列への変換
    */
}

LL getScore(vector<int> seq){

}

//やきなまし
//http://shindannin.hatenadiary.com/entry/20121224/1356364040
vector <int> mirrorSequenceSI(LL sec)
{
    vector<LL> primes=getPrimesEratos(100000);
    xor128 ran;

    vector <int> currentSeq;
    vector<map<LL,LL>> currentDecomposed;

    // 現在の状態の初期化。この部分は問題によっていろいろなので、あまり気にしないでください。
    const int L = 5;
    const int MAXN = 100;
    for (int i = 0; i < MAXN; i++)
    {
        currentSeq.push_back(0);
    }

    for (int i = 0; i < MAXN; ++i) {
        currentDecomposed.push_back(primeDecomposition(currentSeq[i],primes));
    }

    vector <int>    bestSeq         = currentSeq;           // ベストの状態
    vector<map<LL,LL>> bestDecomposed=currentDecomposed;
    double          bestScore       = getScore(currentSeq); // ベストスコア。getScoreは、状態からスコアを求める関数
    double          currentScore    = bestScore;            // 現在のスコア
    {
        const LL saTimeStart    = getTime();            // 焼きなまし開始時刻。getTimeは、時間を返す関数
        const LL saTimeEnd      = saTimeStart+sec;     // 焼きなまし終了時刻。m_startTimeはこのプログラム自体の開始時間
        LL saTimeCurrent        = saTimeStart;          // 現在の時刻

        while ((saTimeCurrent = getTime()) < saTimeEnd) // 焼きなまし終了時刻までループ
        {
            vector <int> nextSeq(currentSeq);       // 次の状態
            nextSeq[ran()%MAXN] = ran()%(L-1);  // 次の状態を求める。ランダムで1要素選んで、変えてみる。

            const double nextScore = getScore(nextSeq);

            // 最初t=0のときは、スコアが良くなろうが悪くなろうが、常にnextを使用
            // 最後t=Tのときは、スコアが改善したときのみ、nextを使用
            const LL T = saTimeEnd-saTimeStart;         // 焼きなましにかける時間
            const LL t = saTimeCurrent-saTimeStart;     // 焼きなまし法開始からの時間
            const LL R = 10000;
            // スコアが悪くなったときでも、次の状態に移動する遷移する場合はtrue。１次関数を使用。
            const bool FORCE_NEXT = R*(T-t)>T*(ran()%R);

            // スコアが良くなった or 悪くなっても強制遷移
            if (nextScore>currentScore || (FORCE_NEXT && currentScore>0.0f) )
            {
                currentScore = nextScore;
                currentSeq = nextSeq;
                printf("current Score=%.8f time=%lld\n",currentScore,t);
            }

            // ベストスコアは保存しておく。
            if(currentScore>bestScore)
            {
                bestScore = currentScore;
                printf("New best Score=%.8f time=%lld\n",bestScore,t);
                bestSeq = currentSeq;
            }
        }
    }

    // ベストスコアをしたときの状態を返す。
    return bestSeq;
}

int main(){
    ios::sync_with_stdio(false); //cout<< fixed << setprecision(10);

}