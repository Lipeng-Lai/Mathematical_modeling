#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>
#include <queue>
#include <cstring>
#include <map>
using namespace std;

const int N = 300, M = N << 1;
int h[N], e[M], ne[M], w[M], idx;
int dist[N];
bool st[N];

struct Points
{
    int id;
    int x, y;
    int color_id;
};

struct Edges
{
    int id1, id2;
    double distance;
};

typedef pair<int, int> PII;
int t = 114;
int s = 1, s_n = s + t; // 起点的出点和起点的入点

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    priority_queue<PII, vector<PII>, greater<>> heap;
    heap.push({0, s});
    dist[s] = 0;

    int prev[N];  // 用于记录路径

    while (!heap.empty())
    {
        PII t = heap.top();
        heap.pop();

        if (st[t.second])  // 跳过已处理的点
            continue;

        st[t.second] = true;

        for (int i = h[t.second]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t.second] + w[i])
            {
                dist[j] = dist[t.second] + w[i];
                prev[j] = t.second;  // 记录路径

                heap.push({dist[j], j});
            }
        }
    }

    // 打印经过的点的编号
    int current = t + 114;  // 终点编号
    vector<int> path;
    while (current != s)
    {
        path.push_back(current);
        current = prev[current];
    }
    path.push_back(s);

    cout << "114号经过的点的编号：";
    for (int i = path.size() - 1; i >= 0; i-=2)
    {
        cout << path[i] << " ";
    }
    cout << endl;
}


int main()
{
    Points center_points[N];
    ifstream file("center_points_label.txt");
    int point_id = 0;
    while (!file.eof())
    {
        int point_x, point_y, color_id;
        file >> point_x >> point_y >> color_id;
        
        if (color_id == 1) color_id = 3;
        else if (color_id == 2) color_id = 4;
        else if (color_id == 3) color_id = 2;
        else if (color_id == 4) color_id = 1;

        center_points[++ point_id] = {point_id, point_x, point_y, color_id};
        // cout << point_id << " " << point_x << " " << point_y << " " << color_id << endl;

        if (point_id == 114) break;
    }

    // cout << point_id << endl;

    int n = point_id;
    Edges edges[N * N];
    int edge_id = 0;
    for (int i = 1; i <= n; i ++)
    {
        for (int j = i + 1; j <= n; j ++)
        {
            double distance = sqrt(pow(center_points[i].x - center_points[j].x, 2) + pow(center_points[i].y - center_points[j].y, 2));
            if (distance <= 100)
            {
                edges[++edge_id] = {i, j, distance};
            }
        }
    }

    // 建图

    memset(h, -1, sizeof h);

    for (int i = 1; i <= t; i ++)
    {
        add(i, i + t, center_points[i].color_id); // 起点的出点和起点的入点 权值是颜色值
    }

    for (int i = 1; i <= edge_id; i ++)
    {
        add(edges[i].id1 + t, edges[i].id2, 0); // 该点的出点到另外一个点的入点 权值是0
    }

    dijkstra();

    cout << dist[114 + t] << endl;

    return 0;
}

