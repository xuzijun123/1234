#include<stdio.h>
#include<string.h>
#include<time.h>
#define DIGIT 21
char pow[DIGIT][50] = { 0 };//�洢0��9��DIGIT�η�
int countNumber[10];//0-9�ĸ���
char powDigit[10][DIGIT + 1][DIGIT * 3];//�洢��0-9��21�η���*��0-9�ĸ�����
char countDigit[][3] = { "0","1","2","3","4","5","6","7","8","9","10","11","12",
"13","14","15","16","17","18","19","20","21" };
//�������ӷ�
void add(char* result, char* a, char* b)
{
	int temp[50] = { 0 };
	int k = 0, j, i;
	i = strlen(a) - 1, j = strlen(b) - 1;
	//���
	while (i >= 0 && j >= 0) {
		temp[k++] = (a[i--] - '0') + (b[j--] - '0');
	}
	while (i >= 0)
		temp[k++] = a[i--] - '0';
	while (j >= 0)
		temp[k++] = b[j--] - '0';
	//�����λ��ʹtemp�и���Ԫ�ص�ֵ��0--9֮��
	for (i = 0; i < k; i++) {
		temp[i + 1] += temp[i] / 10;
		temp[i] %= 10;
	}
	while (temp[i] > 9) {
		temp[i + 1] += temp[i] / 10;
		temp[i] %= 10;
		i++;
	}
	//�ѽ������result�ַ�����
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
//������������a>b��
void sub(char* result, char* a, char* b)
{
	int temp[50] = { 0 };
	int k = 0, j, i;
	i = strlen(a) - 1, j = strlen(b) - 1;
	//���
	while (i >= 0 && j >= 0) {
		temp[k++] = (a[i--] - '0') - (b[j--] - '0');
	}
	while (i >= 0)
		temp[k++] = a[i--] - '0';
	//ʹtemp�и���Ԫ�ص�ֵ��0--9֮��
	for (i = 0; i < k - 1; i++) {
		if (temp[i] < 0) {
			temp[i] += 10;
			temp[i + 1] -= 1;
		}
	}
	//�ѽ������result�ַ�����
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
//�������˷�
void multiply(char* result, char* a, char* b)
{
	int temp[50] = { 0 };
	int k = 0, j, i;
	int len1 = strlen(a), len2 = strlen(b);
	//���
	for (i = len1 - 1; i >= 0; i--) {
		k = len1 - 1 - i;
		for (j = len2 - 1; j >= 0; j--) {
			temp[k++] += (a[i] - '0') * (b[j] - '0');
		}
	}
	//�����λ��ʹtemp�и���Ԫ�ص�ֵ��0--9֮��
	for (i = 0; i < k; i++) {
		temp[i + 1] += temp[i] / 10;
		temp[i] %= 10;
	}
	while (temp[i] > 9) {
		temp[i + 1] += temp[i] / 10;
		temp[i] %= 10;
		i++;
	}
	//�ѽ������result�ַ�����
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
//��pow���鸳ֵ�������0��9��DIGIT�η�
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
//�ж��Ƿ���ˮ�ɻ���
int judge()
{
	int i, temp;
	static char sum[50] = { '0',0 };//������һ�εĽ��
	int tempCountNum[10] = { 0 };
	static int laseNum[10] = { 0 };//������һ�εĸ������ֵĸ���
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
//Ѱ��DIGITλˮ�ɻ���
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
	printf("21λˮ�ɻ����У�\n");
	findNumber(9, 0);
	printf("��ʱ:%d ms\n", clock() - start);
	return 0;
}
