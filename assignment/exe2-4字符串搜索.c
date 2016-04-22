/*	File: exe2-4字符串搜索.c
	【习题2-4】在文件的各行文本text中搜索(寻找)字符串str。
	【作业要求】读入文本文件，按照以下程序中规定的结构定义，
				按照输入顺序逐行存储文本行。
				读入待搜索的字符串文件，对每一行字符串，
				在已存储的文本行中搜索该字符串，
				输出所有匹配的文本行到屏幕。
				填写以下缺失的程序。
	【示例程序】可运行的exe2-4字符串搜索.exe
	【示例文本文件】exe2-4File.txt
	【示例字符串文件】exe2-4str.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* 逐行存放文本的结构定义	*/
#define LINE 80
#define TEXT struct text
TEXT
{
	char textline[LINE];
	TEXT *next;
};

/* 读入文本文件的函数	*/

TEXT *readFile(FILE *fp)
{
	char buf[LINE];
	TEXT *head=NULL, *tail=NULL, *node;

	while(fgets(buf, LINE, fp))
	{
		if((node = (TEXT*)malloc(sizeof(TEXT))) == NULL)
			exit(0);
		strcpy(node->textline, buf);
		if(tail == NULL)
		{
			node->next = tail; 			/* 空链表的后插入语句 	*/
			head = tail = node;
		}
		else
		{
			node->next = tail->next;	/* 非空链表的后插入语句 */
			tail = tail->next = node;
		}
	}
	return head;
}

/* 搜索字符串的函数	*/
int search( char *text, char *str )
{
	/* 填写以下缺失的程序	*/
	char *ptext,*pstr;
	short k;
	for(k = 0; *text; text++, k++)
	{
		for(ptext = text, pstr = str; 
			*pstr != '\0' && *ptext == *pstr;
			ptext++, pstr++)
			;
		if((*pstr == '\0')||(*pstr == '\n'))
			return(k);
	}
	return (EOF);
}

/* 输出搜索结果的函数	*/
void findStr(TEXT *head)
{
	TEXT *node;
	FILE *strFp;
	char strFile[20], buf[LINE];
	int n;

	printf("请输入待搜索的字符串文件名: ");
	scanf("%s", strFile);
	if((strFp = fopen(strFile, "r")) == NULL)
		exit(0);

	while(fgets(buf, LINE, strFp))
	{
		/* 填写以下缺失的程序	*/
		node=head;
		n = 1;

		printf("\n待搜索的字符串:%s",buf);
		printf("搜索的结果：各行的文本为\n");
		while(node!=NULL)
		{
			if(search(node->textline, buf) != -1)
			{
				printf("%-8d%s", n, node->textline);
			}
			node=node->next; n++;
		}
	}
}

int main()
{
	FILE *inFp;
	TEXT *head=NULL;
	char inFile[20];

	printf("请输入文本文件名: ");
	scanf("%s", inFile);
	if((inFp = fopen(inFile, "r")) == NULL)
	{
		printf("无法打开文件\n", inFile);
		system("pause");
		exit(0);
	}

	head = readFile(inFp);
	findStr(head);

	system("pause");
}
/*
exe2-4File.txt
exe2-4str.txt
请输入文本文件名: exe2-4File.txt
请输入待搜索的字符串文件名: exe2-4str.txt

待搜索的字符串:exe
搜索的结果：各行的文本为
5       1230713("%s);0exe1B文件操作.c

待搜索的字符串:FILE
搜索的结果：各行的文本为

待搜索的字符串:str
搜索的结果：各行的文本为
1       Abstringstract
3       A strustringstracctustrgstracred
10      propstringstracosed. stringstrac

请按任意键继续. . .
*/
