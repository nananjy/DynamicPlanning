#include<algorithm>
#include<iostream>
using namespace std;

/**
 * 滑雪(POJ 1088)
 * 计算一个区域中的最大滑坡，区域由二维数组给出，数组每个数字代表点的高度
 * “人人为我”型动态规划递推实现，L(i, j)表示从点(i, j)出发的最长滑行长度，所有点按高度从小到大排序，从小到大计算滑行长度
 * @author 作者名
 */
struct Point {
	int r, c;
	int h;
	bool operator < (const Point &p) const {//重载运算符
		return h < p.h;
	}
} points[10100];//用一维数组存储所有点，以便排序处理
int field[110][110];//存放点的高度
int L[110][110];//L[i][j]是从(i, j)出发的最长滑行长度
int R, C;//行，列

int main() {
	cin >> R >> C;
	for(int i = 0; i < R; i++) {
		for(int j = 0; j < C; j++) {
			cin >> field[i][j];//点的高度
			points[i * C + j].h = field[i][j];
			points[i * C + j].r = i;
			points[i * C + j].c = j;
			L[i][j] = 1;//初始最大滑坡长度为1
		}
	}
	sort(points, points + R * C);//区域中的点按高度排序
	for(int i = 1; i < R * C; ++i) {//每次循环求points[i]的L值,i从1开始是由于第0个点的L=1已经是最大值
		int r = points[i].r;
		int c = points[i].c;
		if(r > 0 && field[r -1][c] < field[r][c])
			L[r][c] = max(L[r][c], L[r -1][c] +1);
		if(c > 0 && field[r][c -1] < field[r][c])
			L[r][c] = max(L[r][c], L[r][c -1] +1);
		if(r < R -1 && field[r +1][c] < field[r][c])
			L[r][c] = max(L[r][c], L[r +1][c] +1);
		if(c < C -1 && field[r][c +1] < field[r][c])
			L[r][c] = max(L[r][c], L[r][c +1] +1);
	}
	int maxLen = 0;//存放最长滑坡长度
	for(int i = 0; i < R; ++i)
		for(int j = 0; j < C; ++j)
			maxLen = max(maxLen, L[i][j]);
	cout << maxLen << endl;
	return 0;
}
