/*	File: exe2-6命令行解释.c
	【习题2-6】文本编辑程序：命令行解释函数
*/

#include "exe2-6文本编辑程序.h"

char getCh(void) 			/* 读取字符，返回EOF表示结束	*/
{
	char ch;
	if( (ch = getchar()) == EOF  ||  ch == '\n' )
		return(EOF);
	return(ch);
}
char getData(char ch, short cmdData[ ], int k)
	/* 从字符ch开始读取数字参数	，存入数字参数的数组		*/
	/* k(参数数组下标)为0或1。返回字符参数后续的字符		*/
{
	cmdData[k] = ch - '0';
	while( isdigit(ch = getCh()) )
		cmdData[k] = cmdData[k] * 10 + ch - '0';
	return(ch);
}
char getStr(char ch, char cmdStr[ ][40], int k)
	/* 从字符ch开始读取字符参数	，存入字符参数的数组		*/
	/* k(参数数组下标)为0至2。返回字符参数后续的字符		*/
{
	int n=0;
	cmdStr[k][n] = ch;
	while( (ch = getCh()) != EOF && ch != '/' )
		cmdStr[k][++n] = ch;
	cmdStr[k][++n] = '\0';
	return(ch);
}
char getFile(char ch, char cmdStr[ ][40])
	/* 从字符ch开始读取文件名，存入字符参数的数组			*/
	/* k(参数数组下标)为0。返回字符参数后续的字符			*/
{
	int n=0;
	cmdStr[0][n] = ch;
	while( (ch = getCh()) != EOF && ch != ' ' && ch != '\t' )
		cmdStr[0][++n] = ch;
	cmdStr[0][++n] = '\0';
	return(ch);
}
int getItem(void) 			/* 读取关键字，返回其命令编号	*/
{
	char	ch;
	while( (ch = getCh()) != EOF )
		if((int)isalpha(ch))
			break;
	switch(ch)
	{
		case 'q':	return QUIT;
		case 'h':	return HELP;
		case 'r':	return READ;
		case 'w':	return WRITE;
		case 'p':	return PRINT;
		case 'f':	return FIND;
		case 'd':	return DELETE;
		case 's':	return REPLACE;
		case 'i':	return INSERT;
		case 'a':	return ADD;
		default:	return ERROR;
	}
}
int readCmdLine(void)		/* 命令行参数解释总函数			*/
{							/* 返回命令编号					*/
	char	ch=0;				/* 命令行中逐个读入的字符		*/
	short MenuItem;
	/* 存放命令行解释结果的全局变量	*/
	numData=0; 				/* 数字参数数组的下标，初始为0	*/
	numStr=0; 				/* 字符参数数组的下标，初始为0 	*/
	cmdData[0] = cmdData[1] = 0;
	cmdStr[0][0] = cmdStr[1][0] = cmdStr[2][0] = '\0';

	if( (MenuItem = getItem()) == ERROR )
	{
		while( (ch = getCh()) != EOF )
			;
		return ERROR;
	}
	while( ((ch = getCh()) == ' ') || (ch == '\t') )
		;
	if(MenuItem == QUIT || MenuItem == HELP)
		;											/* 不需要获取参数的命令	*/
	else if(MenuItem == READ || MenuItem == WRITE)
	{
		ch = getFile(ch, cmdStr);						/* 读取文件名		*/
		numStr++;
	}
	else if(isdigit(ch))
	{
		ch = getData(ch, cmdData, numData++);			/* 读取数字参数1	*/
		if(ch == ',' )
			if( isdigit(ch = getCh()) )
				ch = getData(ch, cmdData, numData++);	/* 读取数字参数2	*/
	}
	else if(ch == '/')
	{
		if( (ch = getCh()) == EOF)
			return MenuItem;
		ch = getStr(ch, cmdStr, numStr++);				/* 读取字符参数1	*/

		if( ch == '/' )
		{
		/* ----请补齐以下程序,实现读取字符参数2和参数3的功能---	*/
		/* ------------------(已完成)--------------------------	*/
			ch = getCh();

			if( ch == EOF )
				return MenuItem;
			if( ch == '/' )
			{
				numStr++;
				
				ch = getCh();
				if( ch == EOF )
					return MenuItem;
				ch = getStr(ch, cmdStr, numStr++);
			}
			else
			{
				ch = getStr(ch, cmdStr, numStr++);
				if( ch == '/' )
				{
					if( ch = getCh() == EOF )
						return MenuItem;
					ch = getStr( ch, cmdStr, numStr++);
				}
			}
		/* ------------------请补齐以上程序--------------------	*/
		}
	}
	while( ch != EOF && ch != '\n' )
		ch = getCh();
	return MenuItem;
}
