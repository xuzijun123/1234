#include<stdio.h>
#include<string.h>
#include<time.h>
#define DIGIT 21
char pow[DIGIT][50] = { 0 };//存储0到9的DIGIT次方
int countNumber[10];//0-9的个数
char powDigit[10][DIGIT + 1][DIGIT * 3];//存储（0-9的21次方）*（0-9的个数）
char countDigit[][3] = { "0","1","2","3","4","5","6","7","8","9","10","11","12",
"13","14","15","16","17","18","19","20","21" };
//大整数加法
void add(char* result, char* a, char* b)
{
	int temp[50] = { 0 };
	int k = 0, j, i;
	i = strlen(a) - 1, j = strlen(b) - 1;
	//相加
	while (i >= 0 && j >= 0) {
		temp[k++] = (a[i--] - '0') + (b[j--] - '0');
	}
	while (i >= 0)
		temp[k++] = a[i--] - '0';
	while (j >= 0)
		temp[k++] = b[j--] - '0';
	//处理进位，使temp中各个元素的值在0--9之间
	for (i = 0; i < k; i++) {
		temp[i + 1] += temp[i] / 10;
		temp[i] %= 10;
	}
	while (temp[i] > 9) {
		temp[i + 1] += temp[i] / 10;
		temp[i] %= 10;
		i++;
	}
	//把结果存入result字符串中
	k = i;
	j = 0;
	for (i = k; i >= 0; i--) {
		if (j == 0 && temp[i] == 0)
			continue;
		result[j++] = temp[i] + '0';
	}
	if (j == 0)
		result[j++] = '0';
	result[j] = 0;
}
//大整数减法（a>b）
void sub(char* result, char* a, char* b)
{
	int temp[50] = { 0 };
	int k = 0, j, i;
	i = strlen(a) - 1, j = strlen(b) - 1;
	//相减
	while (i >= 0 && j >= 0) {
		temp[k++] = (a[i--] - '0') - (b[j--] - '0');
	}
	while (i >= 0)
		temp[k++] = a[i--] - '0';
	//使temp中各个元素的值在0--9之间
	for (i = 0; i < k - 1; i++) {
		if (temp[i] < 0) {
			temp[i] += 10;
			temp[i + 1] -= 1;
		}
	}
	//把结果存入result字符串中
	k = i;
	j = 0;
	for (i = k; i >= 0; i--) {
		if (j == 0 && temp[i] == 0)
			continue;
		result[j++] = temp[i] + '0';
	}
	if (j == 0)
		result[j++] = '0';
	result[j] = 0;
}
//大整数乘法
void multiply(char* result, char* a, char* b)
{
	int temp[50] = { 0 };
	int k = 0, j, i;
	int len1 = strlen(a), len2 = strlen(b);
	//相乘
	for (i = len1 - 1; i >= 0; i--) {
		k = len1 - 1 - i;
		for (j = len2 - 1; j >= 0; j--) {
			temp[k++] += (a[i] - '0') * (b[j] - '0');
		}
	}
	//处理进位，使temp中各个元素的值在0--9之间
	for (i = 0; i < k; i++) {
		temp[i + 1] += temp[i] / 10;
		temp[i] %= 10;
	}
	while (temp[i] > 9) {
		temp[i + 1] += temp[i] / 10;
		temp[i] %= 10;
		i++;
	}
	//把结果存入result字符串中
	k = i;
	j = 0;
	for (i = k; i >= 0; i--) {
		if (j == 0 && temp[i] == 0)
			continue;
		result[j++] = temp[i] + '0';
	}
	if (j == 0)
		result[j++] = '0';
	result[j] = 0;
}
//给pow数组赋值，计算出0到9的DIGIT次方
void init()
{
	int i, j;
	strcpy_s(pow[0], "0");
	strcpy_s(pow[1], "1");
	for (i = 2; i <= 9; i++) {
		pow[i][0] = '1';
		for (j = 1; j <= DIGIT; j++)
			multiply(pow[i], pow[i], countDigit[i]);
	}
	for (i = 0; i < 10; i++)
		for (j = 0; j <= DIGIT; j++)
			multiply(powDigit[i][j], pow[i], countDigit[j]);
}
//判断是否是水仙花数
int judge()
{
	int i, temp;
	static char sum[50] = { '0',0 };//保存上一次的结果
	int tempCountNum[10] = { 0 };
	static int laseNum[10] = { 0 };//保存上一次的各个数字的个数
	for (i = 1; i < 10; i++) {
		if ((temp = countNumber[i] - laseNum[i]) < 0) {
			sub(sum, sum, powDigit[i][-temp]);
			laseNum[i] += temp;
		}
		else if (temp > 0) {
			add(sum, sum, powDigit[i][temp]);
			laseNum[i] += temp;
		}
	}
	for (i = 0; i < DIGIT; i++)
		switch (sum[i]) {
		case '0':tempCountNum[0] += 1; break;
		case '1':tempCountNum[1] += 1; break;
		case '2':tempCountNum[2] += 1; break;
		case '3':tempCountNum[3] += 1; break;
		case '4':tempCountNum[4] += 1; break;
		case '5':tempCountNum[5] += 1; break;
		case '6':tempCountNum[6] += 1; break;
		case '7':tempCountNum[7] += 1; break;
		case '8':tempCountNum[8] += 1; break;
		case '9':tempCountNum[9] += 1; break;
		}
	for (i = 0; i < 10; i++)
		if (countNumber[i] != tempCountNum[i])
			return 0;
	puts(sum);
	return 1;
}
//寻找DIGIT位水仙花数
void findNumber(int n, int count)
{
	int i, max = DIGIT;
	int start = 0;
	if (n == 0) {
		countNumber[0] = DIGIT - count;
		judge();
		return;
	}
	switch (n) {
	case 9:max = 9; break;
	case 8:max = 21; break;
	default:max = 20; break;
	}
	for (i = max; i >= start; i--) {
		countNumber[n] = i;
		if (count + i > DIGIT)
			continue;
		if (countNumber[9] == 0 && countNumber[8] < 10)
			return;
		findNumber(n - 1, count + i);
	}
}
int main()
{
	int start = clock();
	init();
	printf("21位水仙花数有：\n");
	findNumber(9, 0);
	printf("用时:%d ms\n", clock() - start);
	return 0;
}
