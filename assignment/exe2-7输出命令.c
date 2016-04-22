/*	File: exe2-7输出命令.c
	【习题2-7】文本编辑程序：输出命令
	void printLine(void);		输出文本行的函数
*/

#include "exe2-7文本编辑程序.h"

/*	---------以下函数在"exe2-7基本命令.c"中--------------	*/
void errToExit(char *);		/* 出错处理的函数				*/
/* --------------------------------------------------------	*/

void printLine(void)		/* 输出文本行的函数				*/
{
	TEXT *node;
	if(Head == NULL || Head->next == NULL)
	{
		printf("显示文本行错误：编辑文本为空\n");
		return;
	}
	if(numData == 0)
	{
		/* --------请补齐完成以下功能的程序语句--(已完成)------	*/
		printf("显示所有文本行\n");
		for(ThisLine=0, node=Head; node->next; node=node->next)
		{
			printf("%d\t%s\n", ++ThisLine, node->next->textline);
		}
	}
	else if(numData == 1)
	{
		if(cmdData[0] < 1 || cmdData[0] > TotalLine)
		{
			printf("显示文本行错误：第%d行文本不存在\n", cmdData[0]);
			return;
		}
		/* --------请补齐完成以下功能的程序语句--(已完成)------	*/
		printf("显示第%d行文本\n", cmdData[0]);
		for(ThisLine=1, node=Head;
			node->next && ThisLine < cmdData[0];
			node=node->next, ThisLine++)
			;
		if(node->next == NULL || ThisLine != cmdData[0])
			errToExit("程序出现致命错误！");
		printf("%d\t%s\n", ThisLine, node->next->textline);
	}
	else if(numData == 2)
	{
		if(	cmdData[0] > cmdData[1] ||
			cmdData[0] < 1 || cmdData[0] > TotalLine	||
			cmdData[1] < 1 || cmdData[1] > TotalLine)
		{
			printf("显示文本行错误：无法显示第%d行到第%d行\n", 
					cmdData[0], cmdData[1]);
			return;
		}
		/* --------请补齐完成以下功能的程序语句--(已完成)------	*/
		printf("显示第%d行到第%d行文本\n", cmdData[0], cmdData[1]);
		node = Head; ThisLine = 0;
		while( node != NULL )
		{
			if( cmdData[0] <= ThisLine && ThisLine <= cmdData[1] )
			{
				printf("%d\t%s\n", ThisLine, node->textline);
			}
			ThisLine ++; node = node -> next;
		}
	}
}
