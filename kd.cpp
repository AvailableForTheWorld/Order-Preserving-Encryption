#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 1e7;
const int D = 2;
const int INF = 0x3f3f3f;
long long d, root, cur[D], K;
vector<long long> dis_list;
priority_queue<int> Q;

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
    long long dimension[D];
    for (int i = 0; i < D; ++i)
    {
        dimension[i] = min((Tree[id].min_pos[i] - cur[i]) * (Tree[id].min_pos[i] - cur[i]), (Tree[id].max_pos[i] - cur[i]) * (Tree[id].max_pos[i] - cur[i]));
    }
    return min(dimension[0], dimension[1]);
}

void queryMinDis(int id)
{
    distance(id);
    if (Q.size() < K)
    {
        Q.push(id);
    }
    else if (dis_list[id] < dis_list[Q.top()])
    {
        Q.pop();
        Q.push(id);
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
    cout << "中间值" << Tree[mid].pos[0] << endl;
    return mid;
}

int main()
{
    cout << "请输入坐标点个数N :\n";
    int n;
    cin >> n;
    dis_list.resize(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < D; ++j)
        {
            cin >> Tree[i].pos[j];
        }
    }
    cout << "请输入近邻点个数K :\n";
    cin >> K;
    cout << "请输入目标坐标: \n";
    cin >> cur[0] >> cur[1];
    root = build(0, n - 1, 0);
    cout << "根结点为: " << root << endl;
    queryMinDis(root);
    cout << "最近邻点: " << Tree[Q.top()].pos[0] << " " << Tree[Q.top()].pos[1] << endl;
    return 0;
}
