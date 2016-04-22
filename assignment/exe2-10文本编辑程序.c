/*	File: exe2-10文本编辑程序.c
	【文本编辑程序】主控程序
	【相关文件】
		文本编辑程序.h
		基本命令.c
		读写命令.c
		搜索命令.c
		输出命令.c
		删除命令.c
		替换命令.c
		插入命令.c
		exe2-10命令行解释.c
		exe2-10插入命令.c
		可运行的exe2-10文本编辑程序.exe
	【编程要求】本文件需要补齐1处程序
*/

#include "文本编辑程序.h"
#define	GOTO	11

/*	---------以下函数在"命令行解释.c"中--------------------	*/
int readCmdLine(void);		/* 命令行参数解释函数			*/
/* --------------------------------------------------------	*/

/*	---------以下函数在"基本命令.c"中----------------------	*/
void help(void);			/* 求助函数						*/
void quit(void);			/* 结束文本编辑程序的函数		*/
void error(void);			/* 告知无效命令的函数			*/
void errToExit(char *);		/* 出错处理的函数				*/
TEXT * getNode(void);		/* 获取空闲结点的函数			*/
void putNode(TEXT *);		/* 存放空闲结点的函数			*/
/* --------------------------------------------------------	*/

/*	---------以下函数在"读写命令.c"中----------------------	*/
void readFile(void);		/* 读入文本文件的函数			*/
void writeFile(void);		/* 输出文本文件的函数			*/
/* --------------------------------------------------------	*/

/*	---------以下函数在"搜索命令.c"中----------------------	*/
int substr(char *line, char *sub);	/* 寻找子字符串的函数	*/
void findStr(void);			/* 搜索字符串的函数				*/
/* --------------------------------------------------------	*/

/*	---------以下函数在"输出命令.c"中----------------------	*/
void printLine(void);		/* 输出文本行的函数				*/
/* --------------------------------------------------------	*/

/*	---------以下函数在"删除命令.c"中----------------------	*/
void deleteLine(void);		/* 删除文本行的函数				*/
/* --------------------------------------------------------	*/

/*	---------以下函数在"替换命令.c"中----------------------	*/
void replaceStr(void);		/* 替换（删除）字符串的函数		*/
/* --------------------------------------------------------	*/

/*	---------以下函数在"插入命令.c"中----------------------	*/
void insertLine(void);		/* 在第n行以上插入文本的函数	*/
void addLine(void);			/* 在第n行以下插入文本的函数	*/
/* --------------------------------------------------------	*/

/*	---------以下函数在"定位命令.c"中----------------------	*/
void gotoLine(void);		/* 命令文本行的函数				*/
/* --------------------------------------------------------	*/

void main()
{
	void (*MenuFp[])(void) =
	{
		quit,				/* #define	QUIT	0	*/
		help,				/* #define	HELP	1	*/
		readFile,			/* #define	READ	2	*/
		writeFile,			/* #define	WRITE	3	*/
		printLine,			/* #define	PRINT	4	*/
		findStr,			/* #define	FIND	5	*/
		deleteLine,			/* #define	DELETE	6	*/
		replaceStr,			/* #define	REPLACE	7	*/
		insertLine,			/* #define	INSERT	8	*/
		addLine,			/* #define	ADD		9	*/
		error,				/* #define	ERROR	10	*/
		/* ----请补齐定义定位命令函数的程序语句----	*/
		gotoLine,

	};
	short MenuItem=ERROR;

	/* 全局变量初始化										*/
	Empty = NULL;		/* 空闲结点链表初始为空				*/
	Head = getNode();	/* 为文本行结点链表设置哨兵			*/
	Head->next = NULL;	/* 存放文本行的链表初始为空			*/


	while(MenuItem != QUIT)
	{
		printf("> ");
		MenuItem = readCmdLine();
		(*MenuFp[MenuItem])();		
	}
	system("pause");
}

/*
测试定位命令：
r exe2-10.txt
p
g 4
g 13
q

> r exe2-10.txt
读入文件[exe2-10.txt]
> p
显示所有文本行
1       0 quit() 结束程序
2
3       1 help() 显示所有命令及格式
4       2 readFile() 读入文件
5       3 writeFile() 另存文件
6       4 printLine() 显示文本行
7       5 findText() 搜索字符串
8
9
10      6 deleteLine() 删除文本行
11      7 replaceText() 替换和删除字符串
12      8 insertLine() 向前添加文本行
13      9 addLine() 向后添加文本行
> g 4
定位第4行文本
4       2 readFile() 读入文件
> g 13
定位第13行文本
13      9 addLine() 向后添加文本行
> q
按任意键，结束程序...
*/