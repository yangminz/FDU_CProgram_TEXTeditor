/*	File: �ı��༭����.h
	���ı��༭����ͷ�ļ�����������
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* �������������ĺ궨��		*/
#define	QUIT	0
#define	HELP	1
#define	READ	2
#define	WRITE	3
#define	PRINT	4
#define	FIND	5
#define	DELETE	6
#define	REPLACE	7
#define	INSERT	8
#define	ADD		9
#define	ERROR	10
/* ���д���ı��Ľṹ����		*/
#define LINE 80
#define TEXT struct text
TEXT
{
	char textline[LINE];
	TEXT *next;
};
/* �����ı�������ָ��Head									*/
TEXT * Head;			/* Head->nextָ�������׽�㣬		*/
						/* ������ʼ��Head->next=NULL		*/
/* ������н��������ָ��Empty								*/
TEXT * Empty;			/* ���н��������ָ��				*/
/* �����ı���ָ��											*/
int TotalLine;			/* ���һ�е��к�(������)����ֵΪ0	*/
int ThisLine;			/* ��ǰ�ı����к�					*/


/* ��������н��ͽ����ȫ�ֱ���	*/
short	cmdData[2]; 		/* ������ֲ���������			*/
short	numData; 			/* ���ֲ���������±꣬��ʼΪ0	*/
char	cmdStr[3][40]; 		/* ����ַ�����������			*/
short	numStr; 			/* �ַ�����������±꣬��ʼΪ0 	*/
