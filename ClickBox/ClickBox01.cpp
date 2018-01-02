#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

/**
 * 方盒游戏(POJ 1390)
 * N个box摆成一排，每个方盒有自己的颜色，连续摆放的同颜色方盒构成一个“大块”(block)
 * 玩家每点击一个方盒，其所在大块就会消失，若大块中有k个方盒，玩家获得k*k个积分
 * 输入：第一行测试数据t(1<=t<=15)组，每组数据包括两行，第一行是方盒个数n(1<=n<=200)，第二行代表方盒颜色的n个整数[1, n]
 * 输出最高积分
 * “递归+记录计算结果”编程，动态规划（空间换时间）
 */
struct Block {//表示一个大块
	int color;
	int len;
};
#define MAX_N 210
struct Block blocks[MAX_N];//存放所有的大块信息

int ClickBox(int i, int j, int extraLen)
{
	int newLen = blocks[j].len + extraLen;
	if(i == j)
		return newLen * newLen;
	int sc = ClickBox(i, j -1, 0) + newLen * newLen;//大块Q单独消去的情况
	for(int k = j -1; k >= i; k--) {//枚举可能和大块j合并的大块k 
		if(blocks[k].color == blocks[j].color) {
			int tmp = ClickBox(k +1, j -1, 0) + ClickBox(i, k, newLen);
			sc = max(sc, tmp);
		}
	}
	return sc;
}

int main()
{
	int t;//t组数据
	cin >>t;
	for(int c = 1; c <= t; c++) {
		int n;//n个方块
		cin >> n;
		int blocksNum = 1;//大块总数
		blocks[1].len = 1;//初始化第一个大块的个数
		cin >> blocks[1].color;//第一个大块的颜色
		for(int j = 2; j <= n; j++) {
			int color;
			cin >> color;
			if(color == blocks[blocksNum].color)
				++blocks[blocksNum].len;
			else {
				++blocksNum;//大块总数加一
				blocks[blocksNum].len = 1;
				blocks[blocksNum].color = color;
			}
		}
		cout << "Case" << c << ":" << ClickBox(1, blocksNum, 0) << endl;
	}
}
