#include<iostream>
#include<cstdio>
using namespace std;

/**
 * 递归实现数字三角形
 * 从上到下，从左到右先计算出一个路径和，然后选择当前数字右边的数字计算路径，由下到上，计算最佳路径和
 * @author 作者名
 */
#define MAX_NUM 100//C中的宏定义，在编译器编译之前对你的代码进行字符串替换
int d[MAX_NUM + 10][MAX_NUM + 10];//数字三角形
int N;//数字三角形行数
int maxSum, sum;//保存最佳路径和，当前路径和

/**
 * 计算路径最大和
 * @param r 行
 * @param j 列
 * @param flag 上一个节点的位置，用于获取当前数字右边的数字
 */
void MaxSum(int r, int j, int flag)
{
	if(r <= N) {
		sum += d[r][j];//将当前数字加到当前路径和
		MaxSum(r +1, j, j);//递归到下一行数字
		sum -= d[r][j];//包含当前数字的路径和已经计算完成，将其从路径和减去
		if(j == flag) {//计算当前数字右边的数字对应的路径和
			MaxSum(r, j+1, flag);
		}
	} else if(maxSum < sum) {
		maxSum = sum;//获取最大路径和
	}
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
	MaxSum(1, 1, 0);//调用计算最佳路径和函数
	printf("%d", maxSum);//输出最佳路径和
	return 0;
}
