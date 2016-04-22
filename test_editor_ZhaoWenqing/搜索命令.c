/*	File: 搜索命令.c
	【文本编辑程序】搜索命令
	int substr(char *line, char *sub);	寻找子字符串的函数
	void findStr(void);					搜索字符串的函数
*/

#include "文本编辑程序.h"

/*	---------以下函数在"基本命令.c"中----------------------	*/
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
	if(Head == NULL || Head->next == NULL)
	{
		printf("搜索字符串错误：编辑文本为空\n");
		return;
	}
	if(numStr == 0)
	{
		printf("搜索字符串错误：未指定搜索字符串\n");
		return;
	}
	else if(numStr == 2 && cmdStr[1][0] != 'g')
	{
		printf("搜索字符串错误：非法匹配模式: /%s/%s\n",
				cmdStr[0], cmdStr[1]);
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
		printf("显示匹配\"%s\"的文本行\n", cmdStr[0]);
		for(ThisLine=1, node=Head; node->next; node=node->next, ThisLine++)
		{
			if(substr(node->next->textline, cmdStr[0]) != EOF)
			{
				printf("%d\t%s\n", ThisLine, node->next->textline);
				return;
			}
		}
	}
	else if(numStr == 2 && cmdStr[1][0] == 'g')
	{
		printf("显示匹配\"%s\"的所有文本行\n", cmdStr[0]);
		for(ThisLine=1, node=Head; node->next; node=node->next, ThisLine++)
		{
			if(substr(node->next->textline, cmdStr[0]) != EOF)
			{
				printf("%d\t%s\n", ThisLine, node->next->textline);
				fail = 0;
			}
		}
	}
	else
	{
		printf("搜索字符串错误：非法匹配模式: /%s/%s%s\n",
				cmdStr[0], cmdStr[1], cmdStr[2]);
		return;
	}
	if(fail)
		printf("搜索字符串失败：未能匹配指定的字符串\"%s\"\n", cmdStr[0]);
}
