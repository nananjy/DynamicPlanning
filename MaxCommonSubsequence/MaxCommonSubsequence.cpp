#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

/**
 * 最长公共子序列(POJ 1458)
 * Z=<a, b, f, c>是X=<a, b, c, f, b, c>的子序列
 * 给出序列X和Y, 找到最长的序列Z, 使得Z既是X的子序列又是Y的子序列
 * 动态规划对应的“状态”为两字符串中的位置，“值”为子序列长度MaxLen(i, j)
 * @author 作者名
 */
#define MAX_LEN 1000//宏定义
char str1[MAX_LEN];//字符串X
char str2[MAX_LEN];//字符串Y
int maxLen[MAX_LEN][MAX_LEN];//最长公共子序列长度

int main()
{
	if(scanf("%s%s", str1 +1, str2 +1) > 0) {//输入两字符串, str1+1整体是一个字符串，同时str1[0]=str1[1]
		int length1 = strlen(str1 +1);//获取字符串X的长度
		int length2 = strlen(str2 +1);//获取字符串Y的长度
		
		for(int i = 0; i <= length1; i++)
			maxLen[i][0] = 0;//初始化第0列最大长度maxLen
		for(int i = 0; i <= length2; i++)
			maxLen[0][i] = 0;//初始化第0行最大长度maxLen
		for(int i = 1; i <= length1; i++) {
			for(int j = 1; j <= length2; j++) {
				if(str1[i] == str2[j])
					maxLen[i][j] = maxLen[i -1][j -1] + 1;
				else//这边可以用反证法证明
					maxLen[i][j] = max(maxLen[i -1][j], maxLen[i][j -1]);
			}
		}
		printf("最长公共子序列长度为：%d\n", maxLen[length1][length2]);
	}
	return 0;
}
