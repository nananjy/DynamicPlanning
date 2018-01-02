#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

/**
 * 实现数字三角形路径和最大
 * 用一维数组取代二维数组进行递推、节省空间的技巧叫“滚动数组”，时间复杂度O(N*N)
 * @author 作者名
 */
#define MAX_NUM 100//宏定义，编译器编译之前进行代码替换
int d[MAX_NUM][MAX_NUM];//存放数字三角形
int N, *maxSum;//分别存放数字三角形行数和当前路径的一位数组

int main()
{
	int i, j;
	scanf("%d", &N);//输入数字三角形行数
	for(i = 1; i <= N; i++)
		for(j = 1; j <= i; j++)
			scanf("%d", &d[i][j]);//输入数字三角形
	maxSum = d[N];//maxSum指向第N行
	for(i = N; i > 1; i--)
		for(j = 1; j < i; j++)//存放当前路径
			maxSum[j] = max(maxSum[j], maxSum[j+1]) + d[i-1][j];
	printf("%d", maxSum[1]);//输出最佳路径maxSum[1]
	return 0;
}
