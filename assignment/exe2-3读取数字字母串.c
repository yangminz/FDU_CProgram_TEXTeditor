/*	File: exe2-3读取数字字母串.c
	【习题2-3】从文本文件的各行文本中读取任意个数据。
				逐行输出获取的有效数据。
	需要读取的数据为整型数或者仅含字母的字符串。
	数据的个数和顺序是随机的，或者说是任意的。
	数据用空字符分隔，忽略以标点符号引起的所有字符。
	请运行："可运行的exe2-3输入数字字母串.exe"，
		体会程序功能和输出格式。
	示例文本文件： "exe2-3File.txt"
	填写以下缺失的程序。
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define LINE 80

void getNum(char *buf, int k, int *num)
{
	int sign=1;
	/* 补齐以下程序，完成获取整型数的功能	*/
	if(buf[k] == '-')
	{
		sign = -1;
		(k)++;
	}
	*num = 0;
	while(isdigit(buf[k]))
	{
		*num = *num * 10 + buf[k]-'0';
		(k)++;
	}
	*num *=sign;
}

void getStr(char *buf, int k, char *str)
{
	int i=0;
	/* 补齐以下程序，完成获取字符串的功能	*/
	while(isalpha(buf[k]))
	{
		str[i] = buf[k];
		(k)++;
		i++;
	}
	str[i] = '\0';
}

void getData(char *buf, int *nNum, int num[], int *nStr, char str[][20])
{
	int k;
	k = 0;

	
	while((buf[k] != '\0') && (buf[k] != '\n'))
	{
		while(buf[k] == ' ' || buf[k] == '\t')
		(k)++;
		
		if(isdigit(buf[k]) || buf[k] == '-')
			/* 填写调用getNum函数，获取整型数的语句		*/
		{
			getNum( buf, k, num );
			*nNum += 1;
			num[*nNum + 1] = *num;
		}

		if(isalpha(buf[k]))
			/* 填写调用getStr函数，获取字符串的语句		*/
		{
			getStr( buf, k, *str );
			*nStr += 1;
			strcpy(str[*nStr+1],*str);
		}
		while(buf[k] != ' ' && buf[k] != '\t' && buf[k] != '\0' && buf[k] != '\n')
			(k)++;
	}
}

void main()
{
	FILE *fp;
	char buf[LINE], inFile[20];
	int  i, nNum, num[10], nStr;
	char str[10][20];

	printf("请输入文件名: ");
	scanf("%s", inFile);
	if((fp = fopen(inFile, "r")) == NULL)
	{
		printf("无法打开文件\n", inFile);
		system("pause");
		exit(0);
	}

	while( fgets(buf, LINE, fp) )
	{
		printf("获取文本: %s", buf);
		nNum = nStr = -1;
		getData(buf, &nNum, num, &nStr, str);
		for(i=0; i<=nNum;)
			printf("整型数 %d: %d\n", ++i, num[i]);
		for(i=0; i<=nStr; )
			printf("字符串 %d: %s\n", ++i, str[i]);
	}
	system("pause");
}
/*
请输入文件名: exe2-3File.txt
获取文本:   -2 abc 8    string
整型数 1: -2
整型数 2: 8
字符串 1: abc
字符串 2: string
获取文本:
获取文本: 8     china  6  9  printf("
整型数 1: 8
整型数 2: 6
整型数 3: 9
字符串 1: china
字符串 2: printf
获取文本:    4    6 fudan6 3  stracosed
整型数 1: 4
整型数 2: 6
整型数 3: 3
字符串 1: fudan
字符串 2: stracosed
*/