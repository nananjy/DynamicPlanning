#include<cstring>
#include<iostream>
using namespace std;

/**
 * 方块游戏
 * 由score数组中值已知的边界元素(score[i][i][x], i=1,...,blocksNum, x=0,1...,n),
 * 递推出答案score[1][blocksNum][0].
 */
struct Block {
	int color;
	int len;
};
#define MAX_N 210
struct Block blocks[MAX_N];//存放大块
int score[MAX_N][MAX_N][MAX_N];//存放计算结果

int main() {
	int t;//t组测试数据
	cin >>t;
	for(int c = 1; c <= t; c++) {
		int n;//n个方盒
		cin >> n;
		int blocksNum = 1;
		blocks[1].len = 1;
		cin >> blocks[1].color;//第一个方盒的颜色
		for(int j = 2; j <= n; j++) {
			int color;
			cin >> color;//第j个方盒的颜色
			if(color == blocks[blocksNum].color) {
				++blocks[blocksNum].len;
			} else {
				blocks[++blocksNum].color = color;
				blocks[blocksNum].len = 1;
			}
		}
		//score全部置为0，将各种非法情况的分值都置为0
		memset(score, 0, sizeof(score));
		//初始化score数组中的边界元素（对角线元素），供以后递推
		for(int i = 1; i <= blocksNum; ++i) {
			for(int extraLen = 0; extraLen <= n; ++extraLen) {
				score[i][i][extraLen] = (blocks[i].len + extraLen) * (blocks[i].len + extraLen);
			}
		}
		/**
		 * 有score递推，i看作行，j看作列，二维数组[i][j]左下角均为非法情况
		 * 对角线为各个块的记录i*i,i由下到上，j由左到右，依次填充二维数组
		 */
		for(int i = blocksNum; i >= 1; i--) {//开始块从后到前
			for(int j = i +1; j <= blocksNum; ++j) {//结束块从前先后
				for(int extraLen = 0; extraLen <= n; ++extraLen) {
					//求score[i][j][extraLen]
					int newLen = blocks[j].len + extraLen;
					int sc = score[i][j -1][0] + newLen * newLen;
					for(int k = i; k <= j -1; ++k) {
						if(blocks[k].color == blocks[j].color) {
							int tmp = score[k +1][j -1][0] + score[i][k][newLen];
							sc = max(sc, tmp);
						}
					}
					score[i][j][extraLen] = sc;
				}
			}
		}
		cout << "Case" << c << ":" << score[1][blocksNum][0] << endl;
	}
	return 0;
}
