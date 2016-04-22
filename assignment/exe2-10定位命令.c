/*	File: exe2-10定位命令.c
	【文本编辑程序】定位命令:定位并显示第n行文本
	void gotoLine(void);		定位文本行的函数
*/

#include "文本编辑程序.h"

/*	---------以下函数在"基本命令.c"中----------------------	*/
void errToExit(char *);		/* 出错处理的函数				*/
/* --------------------------------------------------------	*/

void gotoLine(void)			/* 定位文本行的函数				*/
{
	/* --------请补齐完成定位文本行功能的程序语句----------	*/


	TEXT *node = NULL;

	if(Head == NULL || Head->next == NULL)
	{
		printf("显示文本行错误：编辑文本为空\n");
		return;
	}
	if(numData != 1)
		return;
	if(cmdData[0] < 1 || cmdData[0] > TotalLine)
	{
		printf("定位文本行错误：第%d行文本不存在\n", cmdData[0]);
		return;
	}
	else
	{
		printf("定位第%d行文本\n", cmdData[0]);
		for(ThisLine=1, node=Head;
		node->next && ThisLine < cmdData[0];
		node=node->next, ThisLine++)
		;
		printf("%d\t%s\n", ThisLine, node->next->textline);
	}
	if(node->next == NULL || ThisLine != cmdData[0])
		errToExit("程序出现致命错误！");
}

