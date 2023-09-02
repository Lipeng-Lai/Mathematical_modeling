#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>
#include <queue>
#include <cstring>
#include <map>
using namespace std;

struct Points
{
    int id;
    int x, y;
};

struct Edges
{
    int id1, id2;
    double distance;
};

const int N = 150;
double g[N][N];
double dist[N];
bool st[N];
int s = 1;

void dijkstra()
{
    int prev[N]; // 用于记录每个节点的前驱节点
    for (int i = 1; i <= N; i ++)
    {
        dist[i] = 10000000000.0;
        prev[i] = -1;
    }
    memset(st, 0, sizeof st);
    dist[s] = 0;

    int n = 115;
    for (int i = 1; i <= n; i ++ )
    {
        int t = -1;
        for (int j = 1; j <= n; j ++ )
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;
        st[t] = true;
        for (int j = 1; j <= n; j ++ )
        {
            if (dist[j] > dist[t] + g[t][j])
            {
                dist[j] = dist[t] + g[t][j];
                prev[j] = t; // 记录节点j的前驱节点是t
            }
        }
    }

    // 打印从节点1到节点111的路径
    int current = 111;
    vector<int> path;
    while (current != -1)
    {
        path.push_back(current);
        current = prev[current];
    }
    reverse(path.begin(), path.end());

    cout << "从1到111的路径经过的节点编号: ";
    for (int node : path)
    {
        cout << node << " ";
    }
    cout << endl;
}

int main()
{
    Points center_points[N];
    ifstream file("center_points.txt");
    int point_id = 1;
    while (!file.eof())
    {
        int point_x, point_y;
        file >> point_x >> point_y;
        center_points[point_id] = {point_id, point_x, point_y};
        point_id ++;
    }

    int n = point_id - 1;
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

    for (int i = 1; i <= N; i ++)
    {
        for (int j = 1; j <= N; j ++)
        {
            g[i][j] = 10000000000.0;
        }
    }

    for (int i = 1; i <= edge_id; i ++)
    {
        g[edges[i].id1][edges[i].id2] = edges[i].distance;
        g[edges[i].id2][edges[i].id1] = edges[i].distance;
    }

    dijkstra();

    return 0;
}
