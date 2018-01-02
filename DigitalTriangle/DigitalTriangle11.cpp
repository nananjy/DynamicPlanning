#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

/**
 * 利用动态规划思想求解数字三角形(POJ 1163), 题目来源IOI 1994
 * 将一个问题分解为子问题递归求解，并且将中间结果保存以避免重复计算的办法
 * 1.问题具有最优子结构性质（问题的最优解所包含的子问题的解也是最优的）
 * 2.无后效性（当前若干个状态值一旦确定，此后过程的演变就只和这若干个状态值有关，与之前采取哪种方式演变到若干个状态无关）
 * 问题描述：求出累加和最大的最佳路径上的数字之和，
 * 路径上每一步只能从一个数走到下一层和它最近的左边的数或右边的数。
 * @author 作者名
 */
#define MAX_NUM 100
int d[MAX_NUM + 10][MAX_NUM + 10];//存放待计算的数字三角形
int N;//存放行数
int maxSum[MAX_NUM + 10][MAX_NUM + 10];//存放当前数字到底边的最佳路径之和

/**
 * 计算路径和
 * @r 数字三角形的行
 * @j 数字三角形的列
 * @return 从第i行第j列的数字到底边的最佳路径和
 */
int MaxSum(int r, int j)
{
	if(r == N)
		return d[r][j];//底边数字的路径和即为数字本身
	if(maxSum[r+1][j] == -1)//如果MaxSum(r+1, j)没有计算过
		maxSum[r+1][j] = MaxSum(r+1, j);
	if(maxSum[r+1][j+1] == -1)//如果MaxSum(r+1, j+1)没有计算过
		maxSum[r+1][j+1] = MaxSum(r+1, j+1);
	if(maxSum[r+1][j] > maxSum[r+1][j+1])
		return maxSum[r+1][j] + d[r][j];
	return maxSum[r+1][j+1] + d[r][j];//返回当前数字到底边的最佳路径和
}

/**
 * 输入数字三角形
 */
int main()
{
	scanf("%d", &N);//输入行数
	//将maxSum全部置成-1, 表示开始所有的MaxSum(r, j)都没有计算过
	memset(maxSum, -1, sizeof(maxSum));
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= i; j++)
			scanf("%d", &d[i][j]);//输入数字三角形
	printf("%d", MaxSum(1, 1));//输出最佳路径和
	return 0;
}
