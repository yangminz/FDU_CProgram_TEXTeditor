/*	File: exe2-3��ȡ������ĸ��.c
	��ϰ��2-3�����ı��ļ��ĸ����ı��ж�ȡ��������ݡ�
				���������ȡ����Ч���ݡ�
	��Ҫ��ȡ������Ϊ���������߽�����ĸ���ַ�����
	���ݵĸ�����˳��������ģ�����˵������ġ�
	�����ÿ��ַ��ָ��������Ա���������������ַ���
	�����У�"�����е�exe2-3����������ĸ��.exe"��
		�������ܺ������ʽ��
	ʾ���ı��ļ��� "exe2-3File.txt"
	��д����ȱʧ�ĳ���
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define LINE 80

void getNum(char *buf, int k, int *num)
{
	int sign=1;
	/* �������³�����ɻ�ȡ�������Ĺ���	*/
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
	/* �������³�����ɻ�ȡ�ַ����Ĺ���	*/
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
			/* ��д����getNum��������ȡ�����������		*/
		{
			getNum( buf, k, num );
			*nNum += 1;
			num[*nNum + 1] = *num;
		}

		if(isalpha(buf[k]))
			/* ��д����getStr��������ȡ�ַ��������		*/
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

	printf("�������ļ���: ");
	scanf("%s", inFile);
	if((fp = fopen(inFile, "r")) == NULL)
	{
		printf("�޷����ļ�\n", inFile);
		system("pause");
		exit(0);
	}

	while( fgets(buf, LINE, fp) )
	{
		printf("��ȡ�ı�: %s", buf);
		nNum = nStr = -1;
		getData(buf, &nNum, num, &nStr, str);
		for(i=0; i<=nNum;)
			printf("������ %d: %d\n", ++i, num[i]);
		for(i=0; i<=nStr; )
			printf("�ַ��� %d: %s\n", ++i, str[i]);
	}
	system("pause");
}
/*
�������ļ���: exe2-3File.txt
��ȡ�ı�:   -2 abc 8    string
������ 1: -2
������ 2: 8
�ַ��� 1: abc
�ַ��� 2: string
��ȡ�ı�:
��ȡ�ı�: 8     china  6  9  printf("
������ 1: 8
������ 2: 6
������ 3: 9
�ַ��� 1: china
�ַ��� 2: printf
��ȡ�ı�:    4    6 fudan6 3  stracosed
������ 1: 4
������ 2: 6
������ 3: 3
�ַ��� 1: fudan
�ַ��� 2: stracosed
*/