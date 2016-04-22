/*	File: 文本编辑程序.c
	【文本编辑程序】主控程序
	【相关文件】
		文本编辑程序.h
		命令行解释.c
		基本命令.c
		读写命令.c
		搜索命令.c
		输出命令.c
		删除命令.c
		替换命令.c
		插入命令.c
		可运行的文本编辑程序.exe
*/

#include "文本编辑程序.h"

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
		error				/* #define	ERROR	10	*/
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
测试删除命令和读写命令：
r .txt
p
d 12,4
p
w out.txt
Y
r .txt
Y
p 13
q

> r .txt
读入文件[.txt]
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
> d 12,4
删除第4行到第12行文本
4       9 addLine() 向后添加文本行
> p
显示所有文本行
1       0 quit() 结束程序
2
3       1 help() 显示所有命令及格式
4       9 addLine() 向后添加文本行
> w out.txt
另存为文件[out.txt]
文件[out.txt]已存在
请输入'Y'，表示该文件将被复盖
否则，表示放弃:  Y
> r .txt
读入文件[.txt]
当前正在编辑一个文件，请确认是否读入文件。
如果还没有存盘，请输入'N'，表示放弃读文件。
否则，表示确认读文件。请确认:  Y
> p 13
显示第13行文本
13      9 addLine() 向后添加文本行
> q
按任意键，结束程序...
*/

/*
测试删除命令和插入命令：（以下的字符^D是一个控制符）
r .txt
d 1,13
a 4
aaaaa
bb
ccccccc^D
p
i 1
^D
p
q

> r .txt
读入文件[.txt]
> d 1,13
删除第1行到第13行文本
文本被全部删除
> a 4
在空文件中添加文本行, 以控制符<CTRL/D>结束
aaaaa
bb
ccccccc^D
> p
显示所有文本行
1       aaaaa
2       bb
3       ccccccc
> i 1
在第1行向上添加文本行, 以控制符<CTRL/D>结束
^D
> p
显示所有文本行
1
2       aaaaa
3       bb
4       ccccccc
> q
按任意键，结束程序...
*/