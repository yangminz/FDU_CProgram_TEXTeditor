/*	File: exe2-7�������.c
	��ϰ��2-7���ı��༭�����������
	void printLine(void);		����ı��еĺ���
*/

#include "exe2-7�ı��༭����.h"

/*	---------���º�����"exe2-7��������.c"��--------------	*/
void errToExit(char *);		/* ������ĺ���				*/
/* --------------------------------------------------------	*/

void printLine(void)		/* ����ı��еĺ���				*/
{
	TEXT *node;
	if(Head == NULL || Head->next == NULL)
	{
		printf("��ʾ�ı��д��󣺱༭�ı�Ϊ��\n");
		return;
	}
	if(numData == 0)
	{
		/* --------�벹��������¹��ܵĳ������--(�����)------	*/
		printf("��ʾ�����ı���\n");
		for(ThisLine=0, node=Head; node->next; node=node->next)
		{
			printf("%d\t%s\n", ++ThisLine, node->next->textline);
		}
	}
	else if(numData == 1)
	{
		if(cmdData[0] < 1 || cmdData[0] > TotalLine)
		{
			printf("��ʾ�ı��д��󣺵�%d���ı�������\n", cmdData[0]);
			return;
		}
		/* --------�벹��������¹��ܵĳ������--(�����)------	*/
		printf("��ʾ��%d���ı�\n", cmdData[0]);
		for(ThisLine=1, node=Head;
			node->next && ThisLine < cmdData[0];
			node=node->next, ThisLine++)
			;
		if(node->next == NULL || ThisLine != cmdData[0])
			errToExit("���������������");
		printf("%d\t%s\n", ThisLine, node->next->textline);
	}
	else if(numData == 2)
	{
		if(	cmdData[0] > cmdData[1] ||
			cmdData[0] < 1 || cmdData[0] > TotalLine	||
			cmdData[1] < 1 || cmdData[1] > TotalLine)
		{
			printf("��ʾ�ı��д����޷���ʾ��%d�е���%d��\n", 
					cmdData[0], cmdData[1]);
			return;
		}
		/* --------�벹��������¹��ܵĳ������--(�����)------	*/
		printf("��ʾ��%d�е���%d���ı�\n", cmdData[0], cmdData[1]);
		node = Head; ThisLine = 0;
		while( node != NULL )
		{
			if( cmdData[0] <= ThisLine && ThisLine <= cmdData[1] )
			{
				printf("%d\t%s\n", ThisLine, node->textline);
			}
			ThisLine ++; node = node -> next;
		}
	}
}
