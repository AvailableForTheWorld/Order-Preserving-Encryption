#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAXN = 1e7;
const int D = 2;
const int INF = 0x3f3f3f;
long long d, root, cur[D], K;
vector<long long> dis_list;

struct cmp
{
    bool operator()(pair<int, long long> &a, pair<int, long long> &b)
    {
        return a.second < b.second;
    }
};

priority_queue<pair<int, long long>, vector<pair<int, long long>>, cmp> Q;

struct Node
{
    long long l, r, pos[D], min_pos[D], max_pos[D];
    inline void init()
    {
        l = r = -1;
        for (int i = 0; i < D; ++i)
        {
            max_pos[i] = min_pos[i] = pos[i];
        }
    }
} Tree[MAXN];

bool operator<(const Node &a, const Node &b)
{
    return a.pos[d] < b.pos[d];
}
void push_up(int p)
{
    long long son[2] = {Tree[p].l, Tree[p].r};
    for (int i = 0; i < 2; ++i)
    {
        if (son[i] == -1)
        {
            continue;
        }
        for (int j = 0; j < D; ++j)
        {
            Tree[p].max_pos[j] = max(Tree[son[i]].max_pos[j], Tree[p].max_pos[j]);
            Tree[p].min_pos[j] = min(Tree[son[i]].min_pos[j], Tree[p].min_pos[j]);
        }
    }
}

void distance(int id)
{
    long long dis_value = 0;
    for (int i = 0; i < D; ++i)
    {
        dis_value += (Tree[id].pos[i] - cur[i]) * (Tree[id].pos[i] - cur[i]);
    }
    dis_list[id] = dis_value;
}

long long subdistance(int id)
{
    int flagA[D] = {0, 0}, flagB[D] = {0, 0}, flagE[D] = {0, 0};
    for (int i = 0; i < D; ++i)
    {
        if (Tree[id].min_pos[i] == Tree[id].max_pos[i])
        {
            flagE[i] = 1;
        }
        if (cur[i] < Tree[id].min_pos[i])
        {
            flagA[i] = -1;
            flagB[i] = -1;
        }
        else if (cur[i] > Tree[id].max_pos[i])
        {
            flagA[i] = flagB[i] = 1;
        }
        else if (cur[i] >= Tree[id].min_pos[i] && cur[i] <= Tree[id].max_pos[i])
        {
            flagA[i] = 0;
            flagB[i] = 0;
        }
    }
    long long minPos[D];
    if (!flagA[0] && !flagB[0] && !flagA[1] && !flagB[1])
    {
        return 0;
    }
    if (!flagE[0] && !flagE[1])
    {
        for (int i = 0; i < D; ++i)
        {
            if (flagA[i] && flagA[i] == flagB[i])
            {
                if (flagA[i] < 0)
                {
                    minPos[i] = Tree[id].min_pos[i];
                }
                else if (flagA[i] > 0)
                {
                    minPos[i] = Tree[id].max_pos[i];
                }
            }
            else
            {
                minPos[i] = cur[i];
            }
        }
    }
    else
    {
        if (flagE[0] && flagE[1])
        {
            minPos[0] = cur[0];
            minPos[1] = cur[1];
        }
        else if (flagE[0])
        {
            minPos[0] = Tree[id].min_pos[0];
            if (cur[0] != Tree[id].min_pos[0])
            {
                minPos[1] = cur[1];
            }
            else
            {
                minPos[1] = abs(Tree[id].min_pos[1] - cur[1]) < abs(Tree[id].max_pos[1] - cur[1]) ? Tree[id].min_pos[1] : Tree[id].max_pos[1];
            }
        }
        else if (flagE[1])
        {
            minPos[1] = Tree[id].min_pos[1];
            if (cur[1] != Tree[id].min_pos[1])
            {
                minPos[0] = cur[0];
            }
            else
            {
                minPos[0] = abs(Tree[id].min_pos[0] - cur[0]) < abs(Tree[id].max_pos[0] - cur[0]) ? Tree[id].min_pos[0] : Tree[id].max_pos[0];
            }
        }
    }
    return (minPos[0] - cur[0]) * (minPos[0] - cur[0]) + (minPos[1] - cur[1]) * (minPos[1] - cur[1]);
}

void queryMinDis(int id)
{
    distance(id);
    pair<int, long long> p{id, dis_list[id]};
    if (Q.size() < K)
    {
        Q.push(p);
    }
    else if (dis_list[id] < dis_list[Q.top().first])
    {
        Q.pop();
        Q.push(p);
    }
    long long dl = subdistance(Tree[id].l);
    long long dr = subdistance(Tree[id].r);
    if (dl < dis_list[id] && Tree[id].l >= 0)
    {
        queryMinDis(Tree[id].l);
    }
    if (dr < dis_list[id] && Tree[id].r >= 0)
    {
        queryMinDis(Tree[id].r);
    }
}

int build(int l, int r, int now)
{
    int mid = (l + r) >> 1;
    d = now;
    nth_element(Tree + l, Tree + mid, Tree + r + 1);
    Tree[mid].init();
    if (l < mid)
    {
        Tree[mid].l = build(l, mid - 1, (now + 1) % D);
    }
    if (r > mid)
    {
        Tree[mid].r = build(mid + 1, r, (now + 1) % D);
    }
    push_up(mid);
    return mid;
}

int main()
{
    cout << "请输保序加密A,B的值:\n";
    int a, b;
    cin >> a >> b;
    ifstream file("NE.txt");
    string line;
    int cnt = 0;
    while (getline(file, line, '\n'))
    {
        char *end, *tmp;
        const char *ch = line.c_str();
        double f = strtod(ch, &end);
        tmp = end;
        long long x = (long long)(f * 1000000 * a + b + rand() % (a - 1) + 0.5);
        Tree[cnt].pos[0] = x;
        f = strtod(tmp, &end);
        x = (long long)(f * 1000000 * a + b + rand() % (a - 1) + 0.5);
        Tree[cnt].pos[1] = x;
        ++cnt;
    }
    cout << "finished: " << cnt << endl;
    file.close();

    dis_list.resize(cnt);

    cout << "请输入近邻点个数K :\n";
    cin >> K;
    cout << "请输入目标坐标: \n";
    double t1, t2;
    cin >> t1 >> t2;
    cur[0] = t1 * 1000000 * a + b + rand() % (a - 1);
    cur[1] = t2 * 1000000 * a + b + rand() % (a - 1);
    root = build(0, cnt - 1, 0);
    cout << "根结点为: " << root << endl;
    queryMinDis(root);
    // for (int i = 0; i < K; ++i)
    // {
    //     cout << "第" << i + 1 << "邻点: " << Tree[Q.top()].pos[0] << " " << Tree[Q.top()].pos[1] << endl;
    //     Q.pop();
    // }
    int j = 0;
    while (Q.size())
    {
        cout << "第" << j + 1 << "邻点: " << (Tree[Q.top().first].pos[0] - b) * 1.0 / (1000000 * a) << " " << (Tree[Q.top().first].pos[1] - b) * 1.0 / (1000000 * a) << " " << Q.top().second << endl;
        Q.pop();
        ++j;
    }
    return 0;
}
