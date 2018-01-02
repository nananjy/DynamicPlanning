#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

/**
 * 灌溉草场(POJ 2373)
 * 草场上长度为L的线段上有N头奶牛（活动范围开区间(S, E)）吃草，奶牛活动范围可重叠
 * 线段上安装喷水头，喷洒半径可调节[A, B](1 <= A <= B <= 1000), A,B都是整数
 * 1.线段上每个整点恰好位于一个喷水头的喷洒范围
 * 2.每头奶牛活动范围要位于一个喷水头的喷洒范围
 * 3.任何喷水头的喷洒范围不可越过线段的两端（左端0，右端L）
 * 求最少喷头数量,复杂度最大为O(L*logL)
 * 思路：先安放好最右边的喷头，F(X)表示安装完喷头后，喷洒范围恰好覆盖直线上的区间[0, X]时，最少需要的喷头数
 * F(X)若有解，需满足
 * 1.X为偶数（喷头的覆盖范围长度是偶数）
 * 2.X所在位置不会出现奶牛，即X不属于任何一个区间(S, E)
 * 3.X >= 2A
 * 4.当X > 2B时，存在Y属于[X-2B, X-2A]且Y满足上面条件
 */
const int INFINITE = 1 << 30;// 
const int MAXL = 1000010;//最长线段
const int MAXN = 1010;//最多奶牛头数
int F[MAXL];//F[L]即最少喷头数
int cows[MAXL];//cows[i]表示点i位于多少头奶牛的活动范围内
int cowVary[MAXL];//cowVary[i]表示经过点i时，所处奶牛区间数的变化量
int N, L, A, B;//N为奶牛个数，L为线段长度，A,B为喷头的调节范围
struct Fx {
	int x; int F;
	bool operator < (const Fx &a) const { return F > a.F;}//在优先队列中F值越小的越优先
	Fx(int xx = 0, int ff = 0):x(xx), F(ff) {}
};
priority_queue <Fx> qFx;//STL(模板库)的优先列表qFx，添加、删除元素的时间复杂度为O(logn),n为队列中元素个数

int main() {
	cin >> N >> L; 
	cin >> A >> B;//喷头调节范围
	A <<= 1; B <<= 1;//A, B的定义变为覆盖的直径
	memset(cowVary, 0, sizeof(cowVary));//初始化奶牛区间数的变化量
	for(int i = 0; i < N; i++) {
		int s, e;
		cin >> s >> e;
		++cowVary[s +1];//从s +1起进入一个奶牛区
		--cowVary[e];//从e起退出一个奶牛区
	}
	int inCows = 0;//表示当前农夫的奶牛数,当前点位于多少个奶牛区间内
	for(int i = 0; i <= L; i++) {//算出每个点位于多少个奶牛区间内，cows是标记数组，花O(L)时间计算
		F[i] = INFINITE;//喷头数F[i]初始化为无穷大
		inCows += cowVary[i];
		cows[i] = inCows;
	}
	for(int i = A; i <= B; i += 2) {//初始化优先列表qFx,为了下一步计算F(B+2)
		if(!cows[i]) {//i点无奶牛出没
			F[i] = 1;//喷头数F[i]值为1
			if(i <= B + 2 - A)
				//在求F[i]时，确保队列中的点x <= i - A, 避免其对i右边的点可能有用，无法从队列中取出抛弃，算法无法继续
				qFx.push(Fx(i, 1));
		}
	}
	for(int i = B + 2; i <= L; i += 2) {//此循环每次求出i点的F(i)
		if(!cows[i]) {
			Fx fx;
			while(!qFx.empty()) {//将不能覆盖到i-B区域的x点从队列中删去，保留[i-B,i-A] 
				fx = qFx.top();
				if(fx.x < i - B)
					qFx.pop();
				else
					break;
			}
			if(!qFx.empty())//找到最少的喷头数+1
				F[i] = fx.F + 1;
		}
		if(F[i - A + 2] != INFINITE) {//为计算i+2做准备
			qFx.push(Fx(i - A + 2, F[i - A + 2]));
		}
	}
	if(F[L] == INFINITE)//没有符合要求的喷水头安装方案，返回-1
		cout << -1 << endl;
	else//输出最少的喷水头个数
		cout << F[L] << endl;
	return 0;
}
