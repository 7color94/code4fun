#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

// Problem: https://nanti.jisuanke.com/t/15552

struct transform {
    double x, y;
    double xx, yy;
} transforms[510];

int n;

// const double eps = 1e-4;

bool is_zero(double x, double eps=1e-4) {
    return fabs(x) < eps;
}

double a, b, dx, dy, scale, theta;

// 从解线性方程组角度 求解参数
bool calculate_para(int i, int j) {
    double x1 = transforms[i].x, xx1 = transforms[i].xx;
    double y1 = transforms[i].y, yy1 = transforms[i].yy;
    double x2 = transforms[j].x, xx2 = transforms[j].xx;
    double y2 = transforms[j].y, yy2 = transforms[j].yy;

    // only if x1 != x2 and y1 != y2
    b = ((yy2 - yy1) * (x2 - x1) - (xx2 - xx1) * (y2 - y1)) / ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + 1e-18);
    a = ((xx2 - xx1) - b * (y1 - y2)) / (x2 - x1 + 1e-18);
    //a = ((yy2 - yy1) - b * (x2 - x1)) / (y2 - y1);

    dx = xx1 - a * x1 + b * y1;
    dy = yy1 - b * x1 - a * y1;

    return 1;
}

double dis(double delta_x, double delta_y) {
    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

// 从几何角度 求解参数
/*
bool calculate_para(int i, int j) {
    double delta_x = transforms[i].x - transforms[j].x;
    double delta_y = transforms[i].y - transforms[j].y;
    double delta_xx = transforms[i].xx - transforms[j].xx;
    double delta_yy = transforms[i].yy - transforms[j].yy;

    if (is_zero(dis(delta_x, delta_y), 1e-18)) return 0;

    scale = dis(delta_xx, delta_yy) / dis(delta_x, delta_y);

    // theta = atan2(delta_x, delta_y) - atan2(delta_xx, delta_yy);
    theta = atan2(delta_yy, delta_xx) - atan2(delta_y, delta_x);

    dx = transforms[i].xx - scale * (transforms[i].x * cos(theta) - transforms[i].y * sin(theta));
    dy = transforms[i].yy - scale * (transforms[i].x * sin(theta) + transforms[i].y * cos(theta));

    return 1;
}
*/

int main() {
    ifstream cin("in.txt");
    cin >> n;
    double x, y, xx, yy;
    for (int i = 0; i < n; i++) {
        cin >> x >> y >> xx >> yy;
        transforms[i].x = x;
        transforms[i].y = y;
        transforms[i].xx = xx;
        transforms[i].yy = yy;
    }

    if (n == 1) {
        // Case: n == 1
        printf("%.11lf\n", 0.0);
        printf("%.11lf\n", 1.0);
        printf("%.11lf %.11lf\n", transforms[0].xx - transforms[0].x, transforms[0].yy - transforms[0].y);
        return 0;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // use transform #i, j to calculate [a, b, dx, dy]
            if (calculate_para(i, j) == 0) continue;

            int count = 0;
            for (int c = 0; c < n; c++) {
                // check [a, b, dx, dy]
                x = transforms[c].x; y = transforms[c].y;
                xx = transforms[c].xx; yy = transforms[c].yy;

                // 解线性方程组角度
                double ddxx = (a * x - b * y + dx) - xx;
                double ddyy = (b * x + a * y + dy) - yy;

                // 几何角度
                // double ddxx = scale * (x * cos(theta) - y * sin(theta)) + dx - xx;
                // double ddyy = scale * (x * sin(theta) + y * cos(theta)) + dy - yy;

                if (is_zero(ddxx) && is_zero(ddyy)) count++;

                // Note: (n + 1) / 2. Case: n is odd number
                if (count >= (n + 1) / 2) {

                    // calculate [theta, scale, dx, dy]
                    double scale = sqrt(a * a + b * b);
                    if (scale <= 0 || scale > 10) break;
                    double theta = acos(a / scale);

                    printf("%.11lf\n", theta);
                    printf("%.11lf\n", scale);
                    printf("%.11lf %.11lf\n", dx, dy);

                    return 0;
                }
            }
        }
    }

    // n > 1 And no solution
    printf("%.11lf\n", theta);
    printf("%.11lf\n", scale);
    printf("%.11lf %.11lf\n", dx, dy);

    return 0;
}
