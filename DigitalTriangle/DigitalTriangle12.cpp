#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

/**
 * 由底向上，从N-1行向上逐行递推实现数字三角形
 * @author 作者名
 */
#define MAX_NUM 100//宏定义，编译器编译之前对代码进行字符串替换
int d[MAX_NUM + 10][MAX_NUM + 10];//存放数字三角形
int N;//存放行数
int maxSum[MAX_NUM + 10][MAX_NUM + 10];//存放当前路径和

int main()
{
	int i, j;
	scanf("%d", &N);//输入数字三角形行数
	for(i = 1; i <= N; i++)
		for(j = 1; j <= i; j++)
			scanf("%d", &d[i][j]);//输入数字三角形
	for(j = 1; j <= N; j++)
		maxSum[N][j] = d[N][j];//第N行的最大路径和即为数字本身
	for(i = N; i > 1; i--)
		for(j = 1; j < i; j++)
		{//从maxSum[N-1]这行元素开始向上逐行递推
			if(maxSum[i][j] > maxSum[i][j+1])
				maxSum[i-1][j] = maxSum[i][j] + d[i-1][j];
			else
				maxSum[i-1][j] = maxSum[i][j+1] + d[i-1][j];
		}
	printf("%d", maxSum[1][1]);//输出最佳路径和maxSum[1][1]
	return 0;
}
