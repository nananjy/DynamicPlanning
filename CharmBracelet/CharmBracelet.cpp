#include<iostream>
#include<algorithm>
using namespace std;

/**
 * Charm Bracelet(POJ 4131)，背包问题
 * 1：将第1个物品放到大于等于其体积的背包中
 * 2：使用滚动数组实现动态规划程序
 */
int N, M;//N为物品个数，M为背包容积
struct Item {
	int w, d;//w为物品体积，d为物品价格
};
Item items[3500];//物品结构体
int f[13000];//价格 

int main() {
	cin >> N >> M;
	for(int i = 1; i <= N; ++i)//输入N个物品
		cin >> items[i].w >> items[i].d;
	for(int j = 0; j <= M; ++j)//给容积为j的背包赋初值
		if(items[1].w <= j)//或为第一个物品
			f[j] = items[1].d;
		else
			f[j] = 0;//或为0 
	for(int i = 2; i <= N; ++i) {//遍历其余物品
		for(int j = M; j >= 0; --j) {
			if(items[i].w <= j)
				f[j] = max(f[j], f[j -items[i].w] + items[i].d);
		}
	}
	cout << f[M] << endl;
	return 0;
}
