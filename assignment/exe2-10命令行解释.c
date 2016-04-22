/*	File: exe2-10�����н���.c
	���ı��༭���������н��ͺ���
	�����Ҫ�󡿱��ļ���Ҫ����1������
*/

#include "�ı��༭����.h"
#define	GOTO	11

char getCh(void) 			/* ��ȡ�ַ�������EOF��ʾ����	*/
{
	char ch;
	if( (ch = getchar()) == EOF  ||  ch == '\n' )
		return(EOF);
	return(ch);
}

char getData(char ch, short cmdData[ ], int k)
	/* ���ַ�ch��ʼ��ȡ���ֲ���	���������ֲ���������		*/
	/* k(���������±�)Ϊ0��1�������ַ������������ַ�		*/
{
	cmdData[k] = ch - '0';
	while( isdigit(ch = getCh()) )
		cmdData[k] = cmdData[k] * 10 + ch - '0';
	return(ch);
}
char getStr(char ch, char cmdStr[ ][40], int k)
	/* ���ַ�ch��ʼ��ȡ�ַ�����	�������ַ�����������		*/
	/* k(���������±�)Ϊ0��2�������ַ������������ַ�		*/
{
	int n=0;
	cmdStr[k][n] = ch;
	while( (ch = getCh()) != EOF && ch != '/' )
		cmdStr[k][++n] = ch;
	cmdStr[k][++n] = '\0';
	return(ch);
}
char getFile(char ch, char cmdStr[ ][40])
	/* ���ַ�ch��ʼ��ȡ�ļ����������ַ�����������			*/
	/* k(���������±�)Ϊ0�������ַ������������ַ�			*/
{
	int n=0;
	cmdStr[0][n] = ch;
	while( (ch = getCh()) != EOF && ch != ' ' && ch != '\t' )
		cmdStr[0][++n] = ch;
	cmdStr[0][++n] = '\0';
	return(ch);
}

int getItem(void) 			/* ��ȡ�ؼ��֣�������������	*/
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
		/* ----�벹�뷵�ض�λ�����ŵĳ������----	*/
		case 'g':	return GOTO;


		default:	return ERROR;
	}
}
int readCmdLine(void)		/* �����в��������ܺ���			*/
{							/* ����������					*/
	char	ch;				/* �����������������ַ�		*/
	short MenuItem;
	short	sign=-1;
	
	/* ��������н��ͽ����ȫ�ֱ���	*/
	numData=0; 				/* ���ֲ���������±꣬��ʼΪ0	*/
	numStr=0; 				/* �ַ�����������±꣬��ʼΪ0 	*/
	cmdData[0] = cmdData[1] = 0;
	cmdStr[0][0] = cmdStr[1][0] = cmdStr[2][0] = '\0';

	if( (MenuItem = getItem()) == ERROR )
		;
	while( ((ch = getCh()) == ' ') || (ch == '\t') )
		;
	if(ch == EOF)
		return MenuItem;
	if(MenuItem == QUIT || MenuItem == HELP)
		;											/* ����Ҫ��ȡ����������	*/
	else if(MenuItem == READ || MenuItem == WRITE)
	{
		ch = getFile(ch, cmdStr);						/* ��ȡ�ļ���		*/
		numStr++;
	}
	else if(isdigit(ch))
	{
		ch = getData(ch, cmdData, numData++);			/* ��ȡ���ֲ���1	*/
		if(ch == ',' )
		{
			if( isdigit(ch = getCh()) )
				ch = getData(ch, cmdData, numData++);	/* ��ȡ���ֲ���2	*/
			else if( ch == '-' )
			{
				sign = -1;
				if( isdigit(ch = getCh()) )
					ch = getData(ch, cmdData, numData++);
				cmdData[1] *= sign;
			}
		}
	}
	else if( ch == '-' )
	{
		sign = -1;
		if( isdigit(ch = getCh()) )						/* ��ȡ���ֲ���1	*/
			ch = getData(ch, cmdData, numData++);
		cmdData[0] *= sign;
		if(ch == ',' )
		{
			if( isdigit(ch = getCh()) )
				ch = getData(ch, cmdData, numData++);	/* ��ȡ���ֲ���2	*/
			else if( ch == '-' )
			{
				sign = -1;
				if( isdigit(ch = getCh()) )
					ch = getData(ch, cmdData, numData++);
				cmdData[1] *= sign;
			}
		}
	}
	else if(ch == '/')
	{
		if( (ch = getCh()) == EOF)
			return MenuItem;
		ch = getStr(ch, cmdStr, numStr++);				/* ��ȡ�ַ�����1	*/
		if( ch == '/' )
		{
			if( (ch = getCh()) == EOF)
				return MenuItem;
			if( ch != '/')
			{
				ch = getStr(ch, cmdStr, numStr++);		/* ��ȡ�ַ�����2	*/
				if(ch == EOF)
					return MenuItem;
			}
			else /* if( ch == '/')	*/
				cmdStr[++numStr][0] = '\0';
			if( (ch = getCh()) == EOF)
				return MenuItem;
			ch = getStr(ch, cmdStr, numStr++);			/* ��ȡ�ַ�����3	*/
		}
	}
	while( ch != EOF && ch != '\n' )
		ch = getCh();
	return MenuItem;
}
