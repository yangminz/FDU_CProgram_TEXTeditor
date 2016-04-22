/*	File: exe2-7�滻����.c
	��ϰ��2-7���ı��༭�����滻����
	void repstr()				��һ����ָ��λ���滻һ���ַ����ĺ���
	void replaceStr()			�滻��ɾ�����ַ����ĺ���
*/

#include "exe2-7�ı��༭����.h"
/*	---------���º�����"exe2-7��������.c"��----------------	*/
int substr(char *line, char *sub);	/* Ѱ�����ַ����ĺ���	*/
/* --------------------------------------------------------	*/

/* ��һ����ָ��λ���滻һ���ַ����ĺ���						*/
void repstr(char *textline, int lenText,
			char *str, int lenStr, char *tar, int lenTar)
{
	int k, len=lenStr-lenTar;
	if(len > 0)									/* Str��Tar��				*/
		for(k=lenStr; k<=lenText; k++)
			textline[k-len] = textline[k];		/* str�������ַ�����lenλ	*/
	else if(len < 0)							/* Tar��Str��				*/
		for(k=lenText; k>=lenStr; k--)
			textline[k-len] = textline[k];		/* str�������ַ�����lenλ	*/
	for(k=0; k<lenTar; k++)
		textline[k] = tar[k];					/* ����tar���ַ�			*/
}

void replaceStr(void)			/* �滻��ɾ�����ַ����ĺ���	*/
{
	int lenStr, lenTar, lenText;
	int ichar, kchar;
	int i;
	int fail=1;				/* 0:��ɲ���; 1:�޷���ɲ���	*/
	int match=0;			/* 1:���ƥ��; 0:δ�����ƥ��	*/
	TEXT *node;
	
	if(numStr < 2)
	{
		printf("ɾ��/�滻�ַ�������δָ���滻����ɾ�����ַ���\n");
		return;
	}
	else if(numStr == 3 && cmdStr[1][0] == '\0' &&  cmdStr[2][0] != 'g')
	{
		printf("ɾ���ַ������󣺷Ƿ�ƥ��ģʽ: /%s/%s/%s\n",
				cmdStr[0], cmdStr[1], cmdStr[2]);
		return;
	}
	else if(numStr == 3 && cmdStr[1][0] != '\0' &&  cmdStr[2][0] != 'g')
	{
		printf("�滻�ַ������󣺷Ƿ�ƥ��ģʽ: /%s/%s/%s\n",
				cmdStr[0], cmdStr[1], cmdStr[2]);
		return;
	}
	
	else if(numStr == 2 && cmdStr[1][0] == '\0' ||
			numStr == 3 && cmdStr[1][0] == '\0' &&  cmdStr[2][0] == '\0')
	{
		lenStr = strlen(cmdStr[0]);
		printf("ɾ���ַ���\"%s\"\n", cmdStr[0]);
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
		printf("�ַ���\"%s\"�滻Ϊ\"%s\"\n", cmdStr[0], cmdStr[1]);
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
		/* --------�벹��������¹��ܵĳ������--------------------	*/
		printf("ɾ�����е��ַ���\"%s\"\n", cmdStr[0]);
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
		/* --------�벹��������¹��ܵĳ������--------------------	*/
		printf("���е��ַ���\"%s\"�滻Ϊ\"%s\"\n", cmdStr[0], cmdStr[1]);
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
		printf("ɾ��/�滻�ַ���ʧ�ܣ�δ��ƥ��ָ�����ַ���\"%s\"\n", cmdStr[0]);
}
