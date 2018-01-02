#include<cstring>
#include<cstdio>
#include<iostream>
using namespace std;

/**
 * 计算最长上升子序列
 * 上升序列：对于一个序列(b1, b2, ..., bs), b1 < b2 < ... < bs
 */
 #define MAX_N 1000
 int N;//
 int b[MAX_N +1];//存放输入序列
 int maxLen[MAX_N +1];//存放每个数到序列开始的最大子序列

 int main() {
 	int N;
	scanf("%d", &N);//输入序列长度(1 <= N <= 1000)
	for(int i = 1; i <= N; i++)
		scanf("%d", &b[i]);//输入序列中的每个数字
	maxLen[1] = 1;//初始化第一个数的序列个数1
	for(int i = 2; i <= N; i++) {
		//每次求以第i个数为终点的最长上升子序列的长度
		int tmp = 0;//存放满足条件的第i个数左边的上升子序列的长度
		for(int j = 1; j < i; j++) {
			if(b[i] > b[j] && tmp < maxLen[j]) {
				tmp = maxLen[j];//获得当前最大子序列长度
			}
		}
		maxLen[i] = tmp + 1;//第i个数字对应的最大子序列
	}
	int maxL = -1;//最长子序列
	for(int i = 1; i <= N; i++) {
		if(maxL < maxLen[i])
			maxL = maxLen[i];
	}
	printf("%d\n", maxL);//输出最长子序列
	return 0;
 }
