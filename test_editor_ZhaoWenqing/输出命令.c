/*	File: �������.c
	���ı��༭�����������
	void printLine(void);		����ı��еĺ���
*/

#include "�ı��༭����.h"

/*	---------���º�����"��������.c"��----------------------	*/
void errToExit(char *);		/* ������ĺ���				*/
/* --------------------------------------------------------	*/

void printLine(void)		/* ����ı��еĺ���				*/
{
	TEXT *node;
	int tmpData;
	if(Head == NULL || Head->next == NULL)
	{
		printf("��ʾ�ı��д��󣺱༭�ı�Ϊ��\n");
		return;
	}
	if(numData == 0)
	{
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
		if(	cmdData[0] < 1 || cmdData[0] > TotalLine	||
			cmdData[1] < 1 || cmdData[1] > TotalLine)
		{
			printf("��ʾ�ı��д����޷���ʾ��%d�е���%d��\n", 
					cmdData[0], cmdData[1]);
			return;
		}
		if(	cmdData[0] > cmdData[1] )
		{
			tmpData = cmdData[0];
			cmdData[0] = cmdData[1];
			cmdData[1] = tmpData;
		}
		printf("��ʾ��%d�е���%d���ı�\n", cmdData[0], cmdData[1]);
		for(ThisLine=1, node=Head; node->next && ThisLine < cmdData[0];
			node=node->next, ThisLine++)
			;
		if( !(node->next && ThisLine == cmdData[0]) )
			errToExit("���������������");
		for( ; ThisLine <= cmdData[1]; node=node->next, ThisLine++)
		{
			if(node->next)
				printf("%d\t%s\n", ThisLine, node->next->textline);
			else
				errToExit("���������������");
		}
	}
}
