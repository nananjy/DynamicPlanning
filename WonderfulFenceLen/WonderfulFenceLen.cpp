#include<iostream>
#include<cstring>
using namespace std;

/**
 * 美妙栅栏(POJ 1037)
 * N个木棒组成，长度分别为1,2,...,N.除两端的木棒外，每根木棒要么比左右的两根长，要么短。
 * 对满足条件的所有栅栏，按照字典序（从左到右，从低到高）
 * 输入：测试数据组数K(1 <= K <= 100),接下来的K行每行描述一组输入数据。
 * 每组输入数据包括两整数N和C.N(1 <= N <= 20)表示栅栏的木棒数，C表示栅栏的排序号
 * 输出：第C个栅栏每根木棒的长度。
 */
const int UP = 1;//第一根长度小于第二根的升序排列
const int DOWN = 0;//第一根长度大于第二根的升序排列
const int MAXN = 25;
long long E[MAXN][MAXN][2];//在win32中长度为8个字节
//E[i][k][UP]是S(i)中以第k短的木棒打头的UP排列数，第k短指i跟中第k短
//E[i][k][DOWN]是S(i)中以第k短的木棒打头的DOWN排列数

void Init(int n) {//求出E数组，n是木棒总数，复杂度为n^3
	memset(E, 0, sizeof(E));//初始化E数组
	E[1][1][UP] = E[1][1][DOWN] = 1;
	for(int i = 2; i <= n; i++) {
		for(int k = 1; k <= i; k++) {//枚举第一根木棒的长度，第k短
			for(int N = 1; N <= k -1; N++)//枚举第二根木棒的长度，比第一根短
				E[i][k][DOWN] += E[i -1][N][UP];
			for(int m = k; m < i; m++)//枚举第二根木棒的长度，比第一根长，注意i根中去掉第k短后的i-1根中k~i-1 
				E[i][k][UP] += E[i -1][m][DOWN];
		}
	}
	//n根木棒的总美妙排列数是Sum{E[n][k][DOWN] + E[n][k][UP]}, k = 1,2,...,n;
}

void PerfectFence(int n, long long C) {//输出n根木棒的第C个美妙排列，排序计数O(n^2)
	int seq[MAXN];//最终要输出的答案，seq[i]就是第i根木棒的长度
	int used[MAXN];//木棒是否用过
	memset(used, 0, sizeof(used));
	for(int i = 1; i <= n; i++) {//依次确定每一个位置i的木棒
		int k;
		int No = 0;
		//长度为k的木棒是剩下的n-i+1根木棒中第No短的，No从1开始算
		for(k = 1; k <= n; k++) {//枚举位置i的木棒长度k
			long long skipped = 0;//位置i放k所能形成的美妙排列数
			if(!used[k]) {
				++No;//k是剩下的木棒中第No短的
				if(i == 1)
					skipped = E[n][No][UP] + E[n][No][DOWN];
				else {
					if(k > seq[i -1] && (i == 2 || seq[i -2] > seq[i -1]))
						skipped = E[n - i + 1][No][DOWN];//合法放置
					else if(k < seq[i -1] && (i == 2 || seq[i -2] < seq[i -1]))
						skipped = E[n - i + 1][No][UP];//合法放置
				}
				if(skipped >= C)
					break;
				else
					C -= skipped;//跳过一些美妙排列
			}
		}
		used[k] = true;
		seq[i] = k;//位置i确定要放长度为k的木棒
	}
	for(int i = 1; i <= n; i++) {
		printf("栅栏第i个位置放置的木棒长度为%d\n", seq[i]);
	}
	printf("\n");
}

int main() {
	int T, n;
	long long c;
	Init(20);
	scanf("%d", &T);
	while(T--) {
		scanf("%d%lld", &n, &c);
		PerfectFence(n, c);
	}
	return 0;
}
