/*	File: 插入命令.c
	【文本编辑程序】插入命令
	void insertLine(void);		在第n行以上插入文本的函数
	void addLine(void);			在第n行以下插入文本的函数
*/

#include "文本编辑程序.h"
/*	---------以下函数在"基本命令.c"中----------------------	*/
TEXT * getNode(void);		/* 获取空闲结点的函数			*/
/* --------------------------------------------------------	*/

/* 读入新添加文本行的函数									*/
#define CTRLD	4
int getLine(char *textline)
{
	int len=0, finish=0;
	while((textline[len]=getchar()) != '\n' && textline[len] != CTRLD)
		len++;
	if(textline[len] == CTRLD)
	{
		finish = CTRLD;
		while( getchar() != '\n' )
			;
	}
	textline[len] = '\0';
	return finish;
}

/* 在thisNode之后添加新文本行的函数							*/
void addTextline(TEXT * thisNode)
{
	TEXT *node;
	char textline[LINE];
	int finish=0;
	do
	{
		finish = getLine(textline);
		node = getNode();
		TotalLine++;		/* 最后一行的行号(总行数)		*/
		strcpy(node->textline, textline);
		/* 将node指向的新文本行插到thisNode之后				*/
		/* 保持链表的链接									*/
		node->next = thisNode->next;
		thisNode->next = node;
		thisNode = thisNode->next;
	}while(finish != CTRLD);
}
void insertLine(void)		/* 在第n行以上插入文本的函数	*/
{
	TEXT *thisNode;
	if(numData == 0)
	{
		printf("插入命令错误：未指定文本行\n");
		return;
	}
	if( Head != NULL && Head->next != NULL &&
		(cmdData[0] < 1 || cmdData[0] > TotalLine) )
	{
		printf("添加文本行错误：第%d行文本不存在\n", cmdData[0]);
		return;
	}
	if(Head == NULL || Head->next == NULL)
	{
		printf("在空文件中添加文本行, ");
		TotalLine = 0;	/* 最后一行的行号(总行数)，初值为0	*/
		thisNode = Head;	/* thisNode指向第0行			*/
	}
	else
	{
		printf("在第%d行向上添加文本行, ", cmdData[0]);
		/* 定位到第n-1行，由thisNode指向第n-1行				*/
		for(ThisLine=1, thisNode=Head;
			thisNode->next && ThisLine < cmdData[0];
			thisNode=thisNode->next, ThisLine++)
			;
	}
	printf("以控制符<CTRL/D>结束\n");
	/* 调用函数addTextline，在thisNode之后添加新的文本行	*/
	addTextline(thisNode);
}

void addLine(void)			/* 在第n行以下插入文本的函数	*/
{
	TEXT *thisNode;
	if(numData == 0)
	{
		printf("插入命令错误：未指定文本行\n");
		return;
	}
	if( Head != NULL && Head->next != NULL &&
		(cmdData[0] < 1 || cmdData[0] > TotalLine) )
	{
		printf("添加文本行错误：第%d行文本不存在\n", cmdData[0]);
		return;
	}
	if(Head == NULL || Head->next == NULL)
	{
		printf("在空文件中添加文本行, ");
		TotalLine = 0;	/* 最后一行的行号(总行数)，初值为0	*/
		thisNode = Head;	/* thisNode指向第0行			*/
	}
	else
	{
		printf("在第%d行向下添加文本行, ", cmdData[0]);
		/* 定位到第n行，由thisNode指向第n行					*/
		for(ThisLine=1, thisNode=Head;
			thisNode->next && ThisLine < cmdData[0];
			thisNode=thisNode->next, ThisLine++)
			;
		thisNode = thisNode->next;
	}
	printf("以控制符<CTRL/D>结束\n");
	/* 调用函数addTextline，在thisNode之后添加新的文本行	*/
	addTextline(thisNode);
}
