#include "geometry.hpp"

Point findpos_3drones(int id, vector<Angle> ang)
{
    int id1, id2;
    double alpha, beta;
    for (auto i : ang)
    {  // 找到最后一组均不为0的编号
        if (i.id1 && i.id2) id1 = i.id1, id2 = i.id2;
    }

    for (auto i : ang)
    {  // 无人机编号相加?
        if (i.id1 + i.id2 == id1) alpha = i.alpha;
        else if (i.id1 + i.id2 == id2) beta = i.alpha;
    }

    Circle O1, O2;
    O1 = get_circle(id, ass[0], ass[id1], alpha);
    O2 = get_circle(id, ass[0], ass[id2], beta);

    // 圆心坐标
    double x1 = O1.O.x, y1 = O1.O.y;
    double x2 = O2.O.x, y2 = O2.O.y;

    double lambda = (x2*(x2-x1)+y2*(y2-y1))/(O1.O-O2.O).norm2();
    Point tmp = O1.O*2*lambda + O2.O*2*(1-lambda);
    
    return tmp;
}

// 以0，1，i，一共3个点作为基准点，计算夹角，以id为中心点
Point find_position(int id, vector<int> drone)
{
    sort(drone.begin(), drone.end()); // 升序
    vector<Angle> ang;

    for (int i = 0; i < drone.size(); i ++)
    {
        for (int j = i + 1; j < drone.size(); j ++)
        {
            double l1 = (p[id] - p[drone[i]]).norm();
            double l2 = (p[id] - p[drone[j]]).norm();
            double l3 = (p[drone[i]] - p[drone[j]]).norm();
            double a = acos((l1*l1 + l2*l2 - l3*l3) / (2*l1*l2)); // 余弦公式求角度
            ang.push_back(Angle(drone[i], drone[j], id, a));
        }
    }
    return findpos_3drones(id, ang);
}

double evaluate()
{
    double ans = 0;
    for (int i = 0; i <= 9; i ++)
        ans += (p[i] - ass[i]).norm2();
    return ans;
}

pair<double, int> search(int deep, int las)
{
    if (deep == 0) return make_pair(evaluate(), las);

    Point tmp[N];
    for (int i = 0; i <= 9; i ++) tmp[i] = p[i];
    double ans = 1e100, s = -1;

    for (int i = 2; i <= 9; i ++)
    {
        vector<int> drone;
        drone.push_back(0);
        drone.push_back(1);
        drone.push_back(i); // 0, 1外还需要一台无人机锁定位置

        for (int j = 2; j <= 9; j ++)
        {
            if (i == j) continue;
            Point pnt = find_position(j, drone);
            p[j] = p[j] + ass[j] - pnt; // OR + OR_exp - OT
        }

        pair<double, int> nw = search(deep - 1, i); // 层数-1，las为
        if (nw.first < ans)  ans = nw.first, s = i; // 更新答案

        for (int j = 2; j <= 9; j ++) p[j] = tmp[j]; // 恢复
    }
    return make_pair(ans, s);
}

int main()
{
    srand(time(0));
    int n = 9;

    //for (int i = 0; i <= 9; i ++)
        // cin >> d[i] >> theta[i]; // 读入无人机的初始位置

    ifstream file("data.txt");
    int cnt = 0;
    while (!file.eof())
    {
        file >> d[cnt] >> theta[cnt];
        cnt ++;
    }

    for (int i = 0; i <= 9; i ++) cout << d[i] << " " << theta[i] << endl;

    for (int i = 1; i <= 9; i ++)
    {
        theta[i] = theta[i] / 180 * pi; // 角度转弧度制
        p[i].x = d[i] * cos(theta[i]); // \rho * cos\theta 实际的x
        p[i].y = d[i] * sin(theta[i]); // \rho * sin\theta 实际的y
        // assessment 
        ass[i].x = 100 * cos(40.0 * (i - 1) / 180 * pi);  // 标准化的圆周的x
        ass[i].y = 100 * sin(40.0 * (i - 1) / 180 * pi); // 标准化圆周y
    }

    cout << evaluate() << endl; // l2 loss函数

    for (int i = 1; i <= 20; i ++)
    {
        double ans = 1e100;
        int s = search(3, -1).second; // 搜索，最大层数，以及枚举的该无人机编号

        cout << "times: " << i << endl << "use: 0 1" << s << endl;
        vector<int> drone;

        drone.push_back(0);
        drone.push_back(1);
        drone.push_back(s);

        for (int j = 2; j <= 9; j ++)
        {
            if (j == s) continue;
            Point pnt = find_position(j, drone);
            p[j] = p[j] + ass[j] - pnt;
        }

        for (int i = 0; i <= 9; i ++)
            cout << p[i].x << " " << p[i].y << endl;
        
        cout << evaluate() << endl;
        puts("-------------");
    }

    for (int i = 0; i <= 9; i ++)
        cout << ass[i].x << " " << ass[i].y << endl;
    puts("----------------");
    return 0;
}
