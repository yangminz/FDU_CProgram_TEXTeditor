/*	File: exe2-6搜索命令.c
	【习题2-6】文本编辑程序：搜索命令
	int substr(char *line, char *sub);	寻找子字符串的函数
	void findStr(void);					搜索字符串的函数
*/

#include "exe2-6文本编辑程序.h"

/*	---------以下函数在"exe2-6基本命令.c"中--------------	*/
void errToExit(char *);		/* 出错处理的函数				*/
/* --------------------------------------------------------	*/


/* 在字符串line中寻找子字符串sub的函数							*/
/* 返回值表示子字符串sub在line中的位置（字符数组下标）			*/
/* 返回值为EOF，表示在字符串line中不存在子字符串sub				*/
/* 主调函数：findStr(), deleteLine(), replaceStr()				*/
int substr(char *line, char *sub)		/* 寻找子字符串的函数	*/
{
	int istr, isub, ichar=0;
	for( ; line[ichar]; ichar++)
	{
		for(istr=ichar, isub=0;
			sub[isub] != '\0' && line[istr] == sub[isub];
			istr++, isub++)
			;
		if(sub[isub] == '\0')
			return(ichar);
	}
	return(EOF);
}


void findStr(void)			/* 搜索字符串的函数				*/
{
	TEXT *node;
	int fail=1;				/* 0:完成操作; 1:无法完成操作	*/
	int i;
	
	if(Head == NULL || Head->next == NULL)
	{
		printf("搜索字符串错误：文本文件为空\n");
		return;
	}

	if(numStr == 0)
	{
		printf("搜索字符串错误：未指定搜索字符串\n");
		return;
	}

	else if(numStr == 2 && cmdStr[1][0] != 'g')
	{
		printf("搜索字符串错误：非法匹配模式: %s\n", cmdStr[1]);
		return;
	}

	else if(numStr == 3 && cmdStr[1][0] == '\0')
	{
		printf("搜索字符串错误：非法匹配模式: /%s/%s/%s\n",
				cmdStr[0], cmdStr[1], cmdStr[2]);
		return;
	}

	else if(numStr == 1)
	{
		/* ----请补齐以下程序,实现搜索命令"f /str/"的功能------	*/
		printf("显示匹配%s的文本行\n", cmdStr[0]);
		node = Head;
		i = 0;

		while( node != NULL )
		{
			if( substr( node->textline, cmdStr[0] ) != -1 )
			{
				printf( "%-8d%s\n", i, node->textline);
				break;
			}
			node = node->next; i++;
		}
		return;
		/* ------------------请补齐以上程序--------------------	*/
	}

	else if(numStr == 2 && cmdStr[1][0] == 'g')
	{
		/* ----请补齐以下程序,实现搜索命令"f /str/g"的功能-----	*/
		printf("显示匹配%s的所有文本行\n", cmdStr[0]);
		
		node = Head;
		i = 0;

		while( node != NULL )
		{
			if( substr( node->textline, cmdStr[0] ) != -1 )
			{
				printf( "%-8d%s\n", i, node->textline);
			}
			node = node->next; i++;
		}
		return;
				/* ------------------请补齐以上程序--------------------	*/
	}

	else
	{
		printf("搜索字符串错误：非法匹配模式: /%s/%s%s\n",
				cmdStr[0], cmdStr[1], cmdStr[2]);
		return;
	}

	if(fail)
		printf("搜索字符串失败：未能匹配指定的字符串%s\n", cmdStr[0]);
}
