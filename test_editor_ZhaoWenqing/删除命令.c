/*	File: 删除命令.c
	【文本编辑程序】删除命令
	void deleteLine(void);		删除文本行的函数
*/

#include "文本编辑程序.h"
/*	---------以下函数在"基本命令.c"中----------------------	*/
void errToExit(char *);		/* 出错处理的函数				*/
TEXT * getNode(void);		/* 获取空闲结点的函数			*/
void putNode(TEXT *);		/* 存放空闲结点的函数			*/
/* --------------------------------------------------------	*/
/*	---------以下函数在"搜索命令.c"中----------------------	*/
int substr(char *line, char *sub);	/* 寻找子字符串的函数	*/
/* --------------------------------------------------------	*/

void deleteLine(void)		/* 删除文本行的函数				*/
{
	TEXT *node, *deleteNode;
	int deleteLine;			/* 待删除文本的行号				*/
	int fail=1;				/* 0:完成操作; 1:无法完成操作	*/
	int tmpData;
	if(numData == 0 && numStr == 0)
	{
		printf("删除命令错误：未指定删除的文本行或者匹配的字符串\n");
		return;
	}
	else if(numStr == 2 && cmdStr[1][0] != 'g')
	{
		printf("删除命令错误：非法匹配模式: /%s/%s\n", 
				cmdStr[0], cmdStr[1]);
		return;
	}
	else if(numStr == 3)
	{
		printf("删除命令错误：非法匹配模式: /%s/%s/%s\n",
				cmdStr[0], cmdStr[1], cmdStr[2]);
		return;
	}
	else if(numData == 1)
	{
		printf("删除第%d行文本\n", cmdData[0]);
		if(cmdData[0] < 1 || cmdData[0] > TotalLine)
		{
			printf("第%d行文本不存在\n", cmdData[0]);
			return;
		}
		for(ThisLine=1, node=Head; node->next && ThisLine < cmdData[0];
			node=node->next, ThisLine++)
			;
		if(node->next == NULL || ThisLine != cmdData[0])
			errToExit("程序出现致命错误！\n");
		TotalLine--;
		deleteNode = node->next;
		node->next= deleteNode->next;
		putNode(deleteNode);
		deleteLine = ThisLine;
		fail = 0;
	}
	else if(numData == 2)
	{
		if(	cmdData[0] < 1 || cmdData[0] > TotalLine	||
			cmdData[1] < 1 || cmdData[1] > TotalLine)
		{
			printf("删除命令错误：无法删除第%d行到第%d行\n", 
					cmdData[0], cmdData[1]);
			return;
		}
		if(	cmdData[0] > cmdData[1] )
		{
			tmpData = cmdData[0];
			cmdData[0] = cmdData[1];
			cmdData[1] = tmpData;
		}
		printf("删除第%d行到第%d行文本\n", cmdData[0], cmdData[1]);
		for(deleteLine=1, node=Head; node->next && deleteLine < cmdData[0];
			node=node->next, deleteLine++)
			;
		if( !(node->next && deleteLine == cmdData[0]) )
			errToExit("程序出现致命错误！\n");
		for(ThisLine=deleteLine; deleteLine <= cmdData[1];
			deleteLine++, TotalLine--)
		{
			if(node->next)
			{
				deleteNode = node->next;
				node->next= deleteNode->next;
				putNode(deleteNode);
			}
			else
				errToExit("程序出现致命错误！");
		}
		deleteLine = ThisLine;
		fail = 0;
	}
	else if(numStr == 1)
	{
		printf("删除匹配\"%s\"的文本行\n", cmdStr[0]);
		for(ThisLine=1, node=Head; node->next;
			node=node->next, ThisLine++)
			if(substr(node->next->textline, cmdStr[0]) != EOF)
				break;
		if(node->next)
		{
			TotalLine--;
			deleteNode = node->next;
			node->next= deleteNode->next;
			putNode(deleteNode);
			deleteLine = ThisLine;
			fail = 0;
		}
	}
	else if(numStr == 2 && cmdStr[1][0] == 'g')
	{
		printf("删除匹配\"%s\"的所有文本行\n", cmdStr[0]);
		for(ThisLine=1, node=Head; node && node->next; )
		{
			if(substr(node->next->textline, cmdStr[0]) == EOF)
			{
				node = node->next;
				ThisLine++;
				continue;
			}
			if(node->next == NULL)
				errToExit("程序出现致命错误！");
			TotalLine--;
			deleteNode = node->next;
			node->next= deleteNode->next;
			putNode(deleteNode);
			deleteNode = node; 
			deleteLine = ThisLine;
			fail = 0;
		}
		node = deleteNode;
	}
	if(fail)
	{
		printf("删除命令失败：未能匹配指定的字符串\"%s\"\n", cmdStr[0]);
		return;
	}

	/* 显示删除操作后的当前行文本			*/
	if(TotalLine == 0)
	{
		printf("文本被全部删除\n");
		Head->next = NULL;
		ThisLine = 0;
	}
	else
	{
		if(node->next)
			printf("%d\t%s\n", deleteLine, node->next->textline);
		else
			printf("%d\t%s\n", --deleteLine, node->textline);
	}
}
