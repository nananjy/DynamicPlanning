#include<iostream>
#include<cstdio>
using namespace std;

/**
 * 递归实现数字三角形，输出MaxSum(1, 1)
 * 以d(r, j)表示第r行第j个数字，MaxSum(r, j)代表从第r行第j个数字到底边的最佳路径和
 * @author 作者名
 */
#define MAX_NUM 100//C中的宏定义，在编译器编译之前对你的代码进行字符串替换
int d[MAX_NUM + 10][MAX_NUM + 10];//数字三角形
int N;//数字三角形行数

/**
 * 计算路径最大和
 * @param r 行
 * @param j 列
 * @return 从第i行第j列到底边的路径和
 */
int MaxSum(int r, int j)
{
	if(r == N)
		return d[r][j];//底边的路径和即为数字本身
	return max(MaxSum(r +1, j), MaxSum(r +1, j +1)) + d[r][j];//当前数字加下面几行的最大和
}

/**
 * 输入主函数
 */
int main()
{
	scanf("%d", &N);//输入行数
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= i; j++)
			scanf("%d", &d[i][j]);//输入数字三角形
	printf("%d", MaxSum(1, 1));//调用计算路径和函数，输出最佳路径和
	return 0;
}
