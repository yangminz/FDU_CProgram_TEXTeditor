/*	File: exe2-7替换命令.c
	【习题2-7】文本编辑程序：替换命令
	void repstr()				在一行内指定位置替换一次字符串的函数
	void replaceStr()			替换（删除）字符串的函数
*/

#include "exe2-7文本编辑程序.h"
/*	---------以下函数在"exe2-7搜索命令.c"中----------------	*/
int substr(char *line, char *sub);	/* 寻找子字符串的函数	*/
/* --------------------------------------------------------	*/

/* 在一行内指定位置替换一次字符串的函数						*/
void repstr(char *textline, int lenText,
			char *str, int lenStr, char *tar, int lenTar)
{
	int k, len=lenStr-lenTar;
	if(len > 0)									/* Str比Tar长				*/
		for(k=lenStr; k<=lenText; k++)
			textline[k-len] = textline[k];		/* str后续的字符左移len位	*/
	else if(len < 0)							/* Tar比Str长				*/
		for(k=lenText; k>=lenStr; k--)
			textline[k-len] = textline[k];		/* str后续的字符右移len位	*/
	for(k=0; k<lenTar; k++)
		textline[k] = tar[k];					/* 复制tar的字符			*/
}

void replaceStr(void)			/* 替换（删除）字符串的函数	*/
{
	int lenStr, lenTar, lenText;
	int ichar, kchar;
	int i;
	int fail=1;				/* 0:完成操作; 1:无法完成操作	*/
	int match=0;			/* 1:完成匹配; 0:未能完成匹配	*/
	TEXT *node;
	
	if(numStr < 2)
	{
		printf("删除/替换字符串错误：未指定替换或者删除的字符串\n");
		return;
	}
	else if(numStr == 3 && cmdStr[1][0] == '\0' &&  cmdStr[2][0] != 'g')
	{
		printf("删除字符串错误：非法匹配模式: /%s/%s/%s\n",
				cmdStr[0], cmdStr[1], cmdStr[2]);
		return;
	}
	else if(numStr == 3 && cmdStr[1][0] != '\0' &&  cmdStr[2][0] != 'g')
	{
		printf("替换字符串错误：非法匹配模式: /%s/%s/%s\n",
				cmdStr[0], cmdStr[1], cmdStr[2]);
		return;
	}
	
	else if(numStr == 2 && cmdStr[1][0] == '\0' ||
			numStr == 3 && cmdStr[1][0] == '\0' &&  cmdStr[2][0] == '\0')
	{
		lenStr = strlen(cmdStr[0]);
		printf("删除字符串\"%s\"\n", cmdStr[0]);
		for(ThisLine=1, node=Head->next; node; node=node->next, ThisLine++)
			if((ichar = substr(node->textline, cmdStr[0])) != EOF)
			{
				for(kchar=0; node->textline[ichar+kchar+lenStr]!='\0'; kchar++)
					node->textline[ichar+kchar] =
					node->textline[ichar+kchar+lenStr];


				node->textline[ichar+kchar] = '\0';
				printf("%d\t%s\n", ThisLine, node->textline);
				fail = 0;
				break;
			}
	}
	
	else if(numStr == 2 && cmdStr[1][0] != '\0')
	{
		lenStr = strlen(cmdStr[0]);
		lenTar = strlen(cmdStr[1]);
		printf("字符串\"%s\"替换为\"%s\"\n", cmdStr[0], cmdStr[1]);
		for(ThisLine=1, node=Head->next; node; node=node->next, ThisLine++)
			if((ichar = substr(node->textline, cmdStr[0])) != EOF)
			{
				lenText = strlen(node->textline);
				repstr(	&(node->textline[ichar]), lenText-ichar,
						cmdStr[0], lenStr, cmdStr[1], lenTar);
				printf("%d\t%s\n", ThisLine, node->textline);
				fail = 0;
				break;
			}
	}
	
	else if(numStr == 3 && cmdStr[1][0] == '\0' &&  cmdStr[2][0] == 'g')
	{
		lenStr = strlen(cmdStr[0]);
		/* --------请补齐完成以下功能的程序语句--------------------	*/
		printf("删除所有的字符串\"%s\"\n", cmdStr[0]);
		for(ThisLine=1,i=1, node=Head->next; node; node=node->next, ThisLine++)
		{
			if((ichar = substr(node->textline, cmdStr[0])) == EOF)
				i++;
		}
		if(ThisLine == i);
		else
		{
			for(ThisLine=1, node=Head->next; node; node=node->next, ThisLine++)
			{
				i = 0;
				while((ichar = substr(node->textline, cmdStr[0])) != EOF)
				{
					for(kchar=0; node->textline[ichar+kchar+lenStr]!='\0'; kchar++)
					{
						node->textline[ichar+kchar] = node->textline[ichar+kchar+lenStr];
					}
					i++; fail = 0;
				}
				node->textline[ strlen(node->textline) - i*lenStr ] = '\0';
				if( i != 0)
					printf("%d\t%s\n", ThisLine, node->textline);
			}
		}
	}
	
	else if(numStr == 3 && cmdStr[1][0] != '\0' &&  cmdStr[2][0] == 'g')
	{
		lenStr = strlen(cmdStr[0]);
		lenTar = strlen(cmdStr[1]);
		/* --------请补齐完成以下功能的程序语句--------------------	*/
		printf("所有的字符串\"%s\"替换为\"%s\"\n", cmdStr[0], cmdStr[1]);
		for(ThisLine=1, node=Head->next; node; node=node->next, ThisLine++)
		{
			match = 0; kchar = 0;
			lenText = strlen(node->textline);

			while( (ichar = substr(node->textline, cmdStr[0])) != EOF )
			{
				lenText -= ichar;
				kchar += ichar;
				repstr(&(node->textline[ichar]), lenText, 
							cmdStr[0], lenStr, cmdStr[1], lenTar);
				lenText -= lenStr;
				kchar += lenTar;
				fail = 0; match = 1;
			}

			if( match == 1 )
				printf("%d\t%s\n", ThisLine, node->textline);
		}
	}

	if(fail)
		printf("删除/替换字符串失败：未能匹配指定的字符串\"%s\"\n", cmdStr[0]);
}
