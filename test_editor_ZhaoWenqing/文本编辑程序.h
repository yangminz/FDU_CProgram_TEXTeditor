/*	File: 文本编辑程序.h
	【文本编辑程序】头文件：定义数据
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* 操作命令函数代码的宏定义		*/
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
/* 逐行存放文本的结构定义		*/
#define LINE 80
#define TEXT struct text
TEXT
{
	char textline[LINE];
	TEXT *next;
};
/* 定义文本行链表指针Head									*/
TEXT * Head;			/* Head->next指向链表首结点，		*/
						/* 即：初始令Head->next=NULL		*/
/* 定义空闲结点链表首指针Empty								*/
TEXT * Empty;			/* 空闲结点链表首指针				*/
/* 定义文本行指针											*/
int TotalLine;			/* 最后一行的行号(总行数)，初值为0	*/
int ThisLine;			/* 当前文本的行号					*/


/* 存放命令行解释结果的全局变量	*/
short	cmdData[2]; 		/* 存放数字参数的数组			*/
short	numData; 			/* 数字参数数组的下标，初始为0	*/
char	cmdStr[3][40]; 		/* 存放字符参数的数组			*/
short	numStr; 			/* 字符参数数组的下标，初始为0 	*/
