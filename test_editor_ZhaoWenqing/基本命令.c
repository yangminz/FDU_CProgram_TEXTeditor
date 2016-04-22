/*	File: 基本命令.c
	【文本编辑程序】基本命令
	void help(void);			求助函数
	void quit(void);			结束文本编辑程序的函数
	error(void);				告知无效命令的函数
	void errToExit(char *);		出错处理的函数
	TEXT * getENode(void);		获取空闲结点的函数
	void putNode(TEXT *);		存放空闲结点的函数
*/

#include "文本编辑程序.h"

void errToExit(char *errMsg)	/* 出错处理的函数			*/
{
	printf("%s\n", errMsg);		/* 显示出错信息				*/
	printf("按任意键，结束程序...  "); 
	getchar();
	exit(0);					/* 结束整个程序				*/
}
TEXT * getNode(void)			/* 获取空闲结点的函数		*/
{
	TEXT *node;
	if(Empty)
	{
		node = Empty;
		Empty = node->next;
	}
	else
		if( (node = (TEXT *)malloc(sizeof(TEXT))) == NULL)
			errToExit("致命错误：内存分配失败！");
	return(node);
}
void putNode(TEXT *node)		/* 存放空闲结点的函数		*/
{
	node->next = Empty;
	Empty = node;
}
void help(void)					/* 求助函数					*/
{
	printf("====  文本编辑程序的命令  ====\n");
	printf("q \t\t结束程序\n");
	printf("h \t\t显示所有命令及格式(当前命令)\n");
	printf("r file\t\t读入文件file\n");
	printf("w file\t\t另存为文件file\n");
	printf("p \t\t显示所有文本行\n");
	printf("p n\t\t显示第n行文本\n");
	printf("p n,m\t\t显示第n行到m行文本\n");
	printf("f /str/\t\t显示匹配str的文本行\n");
	printf("f /str/g\t显示匹配str的所有文本行\n");
	printf("d n\t\t删除第n行文本\n");
	printf("d n,m\t\t删除第n到m行文本\n");
	printf("d /str/\t\t删除匹配str的文本行\n");
	printf("d /str/g\t删除匹配str的所有文本行\n");
	printf("s /str//\t删除str\n");
	printf("s /str//g\t删除所有行中的str\n");
	printf("s /str/tar/\tstr替换为tar\n");
	printf("s /str/tar/g\t所有的str替换为tar\n");
	printf("i n\t\t在第n行之上添加文本行\n");
	printf("a n\t\t在第n行之下添加文本行\n");
}
void quit(void)					/* 结束文本编辑程序的函数	*/
{
	printf("按任意键，结束程序...  "); 
	getchar();
	exit(0);
}
void error(void)				/* 告知无效命令的函数		*/
{
	printf("无效命令\n");
}
