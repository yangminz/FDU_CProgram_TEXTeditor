/*	File: exe2-8��������.c
	��ϰ��2-8���ı��༭���򣺲�������
	void insertLine(void);		�ڵ�n�����ϲ����ı��ĺ���
	void addLine(void);			�ڵ�n�����²����ı��ĺ���
*/
/*
	��������ҵ��
		���뺯��insertLine()��addLine()��ȱʧ�����
		ʵ�ֲ����ı���֮ǰ���ж�λ����
*/

#include "exe2-8�ı��༭����.h"
/*	---------���º�����"exe2-8��������.c"��--------------	*/
TEXT * getNode(void);		/* ��ȡ���н��ĺ���			*/
/* --------------------------------------------------------	*/
/* ����������ı��еĺ���									*/
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

/* ��thisNode֮��������ı��еĺ���							*/
void addTextline(TEXT * thisNode)
{
	TEXT *node;
	char textline[LINE];
	int finish=0;
	do
	{
		finish = getLine(textline);
		node = getNode();
		TotalLine++;		/* ���һ�е��к�(������)		*/
		strcpy(node->textline, textline);
		/* ��nodeָ������ı��в嵽thisNode֮��				*/
		/* �������������									*/
		node->next = thisNode->next;
		thisNode->next = node;
		thisNode = thisNode->next;
	}while(finish != CTRLD);
}
void insertLine(void)		/* �ڵ�n�����ϲ����ı��ĺ���	*/
{
	TEXT *thisNode;
	int count = 0;
	if(numData == 0)
	{
		printf("�����������δָ���ı���\n");
		return;
	}
	if( Head != NULL && Head->next != NULL &&
		(cmdData[0] < 1 || cmdData[0] > TotalLine) )
	{
		printf("����ı��д��󣺵�%d���ı�������\n", cmdData[0]);
		return;
	}
	if(Head == NULL || Head->next == NULL)
	{
		printf("�ڿ��ļ�������ı���, ");
		TotalLine = 0;	/* ���һ�е��к�(������)����ֵΪ0	*/
		thisNode = Head;	/* thisNodeָ���0��			*/
	}
	else
	{
		printf("�ڵ�%d����������ı���, ", cmdData[0]);
		/* ----------�벹��������¹��ܵĳ������----------	*/
		/* ��λ����n-1�У���thisNodeָ���n-1��				*/
		for( thisNode = Head; count < cmdData[0]-1;
			thisNode = thisNode->next, count++);	
	
	
	
	
	
	}
	printf("�Կ��Ʒ�<CTRL/D>����\n");
	/* ���ú���addTextline����thisNode֮������µ��ı���	*/
	addTextline(thisNode);
}

void addLine(void)			/* �ڵ�n�����²����ı��ĺ���	*/
{
	TEXT *thisNode;
	int count = 0;
	if(numData == 0)
	{
		printf("�����������δָ���ı���\n");
		return;
	}
	if( Head != NULL && Head->next != NULL &&
		(cmdData[0] < 1 || cmdData[0] > TotalLine) )
	{
		printf("����ı��д��󣺵�%d���ı�������\n", cmdData[0]);
		return;
	}
	if(Head == NULL || Head->next == NULL)
	{
		printf("�ڿ��ļ�������ı���, ");
		TotalLine = 0;	/* ���һ�е��к�(������)����ֵΪ0	*/
		thisNode = Head;	/* thisNodeָ���0��			*/
	}
	else
	{
		printf("�ڵ�%d����������ı���, ", cmdData[0]);
		/* ----------�벹��������¹��ܵĳ������----------	*/
		/* ��λ����n�У���thisNodeָ���n��					*/
		for( thisNode = Head; count < cmdData[0];
			thisNode = thisNode->next, count++);	
	}
	printf("�Կ��Ʒ�<CTRL/D>����\n");
	/* ���ú���addTextline����thisNode֮������µ��ı���	*/
	addTextline(thisNode);
}
