/*	File: 读写命令.c
	【文本编辑程序】读写命令
	void readFile(void);		读入文本文件的函数
	void writeFile(void);		输出文本文件的函数
*/

#include "文本编辑程序.h"
/*	---------以下函数在"基本命令.c"中----------------------	*/
TEXT * getNode(void);		/* 获取空闲结点的函数			*/
void putNode(TEXT *);		/* 存放空闲结点的函数			*/
/* --------------------------------------------------------	*/

/* 读入文本文件的文件指针									*/
FILE *filePtr;

void readFile(void)			/* 读入文本文件的函数			*/
{
	TEXT *tail, *node;
	char textline[LINE];
	int n;
	if(numStr == 0)
	{
		printf("读入文件错误：未指定文件名\n");
		return;
	}
	printf("读入文件[%s]\n", cmdStr[0]);
	if((filePtr = fopen(cmdStr[0], "r")) == NULL)
	{
		printf("读入文件错误：打开文件 [%s] 失败\n", cmdStr[0]);
		return;
	}
	if(Head->next != NULL)
	{
		printf("当前正在编辑一个文件，请确认是否读入文件。\n");
		printf("如果还没有存盘，请输入'N'，表示放弃读文件。\n");
		printf("否则，表示确认读文件。请确认:  ");
		gets(textline);
		if(textline[0] == 'N')
			return;
		/* 删除当前文本行链表的所有结点，以读入新的文本文件	*/
		/* 调用putNode函数，将删除的结点存入空闲结点链表	*/
		while(Head->next)
		{
			node = Head->next;
			Head->next = Head->next->next;
			putNode(node);
		}
	}
	TotalLine = 0;		/* 最后一行的行号(总行数)，初值为0	*/
	while(fgets(textline, LINE, filePtr) != NULL)
	{
		node = getNode();
		TotalLine++;		/* 最后一行的行号(总行数)		*/
		n = strlen(textline);
		if(textline[n-1] == '\n')
			textline[n-1] = '\0';
		strcpy(node->textline, textline);
		if(Head->next == NULL)	/* 空链表的后插入语句		*/
			Head->next = tail = node;
		else					/* 非空链表的后插入语句		*/
			tail = tail->next = node;
	}
	tail->next = NULL;		/* 最后一个结点的下一结点指向空	*/
	ThisLine = 1;			/* 当前文本的行号，初值为1		*/
	fclose(filePtr);
}

void writeFile(void)		/* 输出文本文件的函数			*/
{
	TEXT *node;
	char textline[LINE];
	if(numStr == 0)
	{
		printf("另存文件错误：未指定文件名\n");
		return;
	}
	else
	{
		printf("另存为文件[%s]\n", cmdStr[0]);
		if(Head == NULL || Head->next == NULL)
		{
			printf("另存文件错误：编辑文本为空\n");
			return;
		}
		if((filePtr = fopen(cmdStr[0], "r")) != NULL)
		{
			printf("文件[%s]已存在\n", cmdStr[0]);
			printf("请输入'Y'，表示该文件将被复盖\n");
			printf("否则，表示放弃:  ");
			gets(textline);
			if(textline[0] != 'Y')
				return;
		}
		if((filePtr = fopen(cmdStr[0], "w")) == NULL)
		{
			printf("另存文件错误：打开文件 [%s] 失败\n", cmdStr[0]);
			return;
		}
		/* 另存文本文件，以及关闭文件的操作					*/
		for(node=Head->next; node; node=node->next)
			fprintf(filePtr, "%s\n", node->textline);
		fclose(filePtr);
	}
}
