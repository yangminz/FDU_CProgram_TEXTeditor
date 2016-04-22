/*	File: exe2-8ɾ������key.c
	��ϰ��2-8���ı��༭����ɾ������
	void deleteLine(void);		ɾ���ı��еĺ���
*/
/*
	��������ҵ��
		���뺯��deleteLine()��ȱʧ����䣬ʵ�����¹��ܣ�
		d n,m			ɾ����n�е�m���ı�
*/

#include "exe2-8�ı��༭����.h"
/*	---------���º�����"exe2-8��������.c"��--------------	*/
void errToExit(char *);		/* ������ĺ���				*/
TEXT * getNode(void);		/* ��ȡ���н��ĺ���			*/
void putNode(TEXT *);		/* ��ſ��н��ĺ���			*/
/* --------------------------------------------------------	*/
/*	---------���º�����"exe2-8��������.c"��--------------	*/
int substr(char *line, char *sub);	/* Ѱ�����ַ����ĺ���	*/
/* --------------------------------------------------------	*/

void deleteLine(void)		/* ɾ���ı��еĺ���				*/
{
	TEXT *node, *deleteNode;
	int deleteLine;			/* ��ɾ���ı����к�				*/
	int fail=1;				/* 0:��ɲ���; 1:�޷���ɲ���	*/
	int tmpData;

	if(numData == 0 && numStr == 0)
	{
		printf("ɾ���������δָ��ɾ�����ı��л���ƥ����ַ���\n");
		return;
	}
	else if(numStr == 2 && cmdStr[1][0] != 'g')
	{
		printf("ɾ��������󣺷Ƿ�ƥ��ģʽ: /%s/%s\n", 
				cmdStr[0], cmdStr[1]);
		return;
	}
	else if(numStr == 3)
	{
		printf("ɾ��������󣺷Ƿ�ƥ��ģʽ: /%s/%s/%s\n",
				cmdStr[0], cmdStr[1], cmdStr[2]);
		return;
	}

	else if(numData == 1)
	{
		printf("ɾ����%d���ı�\n", cmdData[0]);
		if(cmdData[0] < 1 || cmdData[0] > TotalLine)
		{
			printf("��%d���ı�������\n", cmdData[0]);
			return;
		}
		for(ThisLine=1, node=Head; node->next && ThisLine < cmdData[0];
			node=node->next, ThisLine++)
			;
		if(node->next == NULL || ThisLine != cmdData[0])
			errToExit("���������������\n");
		TotalLine--;
		deleteNode = node->next;
		node->next= deleteNode->next;
		putNode(deleteNode);
		deleteLine = ThisLine;
		fail = 0;
	}

	else if(numData == 2)
	{
		if(	cmdData[0] < 1 || cmdData[0] > TotalLine	||
			cmdData[1] < 1 || cmdData[1] > TotalLine)
		{
			printf("ɾ����������޷�ɾ����%d�е���%d��\n", 
					cmdData[0], cmdData[1]);
			return;
		}
		if(	cmdData[0] > cmdData[1] )
		{
			tmpData = cmdData[0];
			cmdData[0] = cmdData[1];
			cmdData[1] = tmpData;
		}
		printf("ɾ����%d�е���%d���ı�\n", cmdData[0], cmdData[1]);
		/* --------�벹��������¹��ܵĳ������----------------	*/
		for(ThisLine=1, node=Head; node->next && ThisLine < cmdData[0];
			node=node->next, ThisLine++)
			;
		if(node->next == NULL || ThisLine != cmdData[0])
			errToExit("���������������\n");
		deleteLine = ThisLine;
		for(; ThisLine <= cmdData[1];TotalLine--, ThisLine++)
		{
			
			deleteNode = node->next;
			node->next= deleteNode->next;
			putNode(deleteNode);
			
		}
		fail = 0;
	}

	else if(numStr == 1)
	{
		printf("ɾ��ƥ��\"%s\"���ı���\n", cmdStr[0]);
		for(ThisLine=1, node=Head; node->next;
			node=node->next, ThisLine++)
			if(substr(node->next->textline, cmdStr[0]) != EOF)
				break;
		if(node->next)
		{
			TotalLine--;
			deleteNode = node->next;
			node->next= deleteNode->next;
			putNode(deleteNode);
			deleteLine = ThisLine;
			fail = 0;
		}
	}
	else if(numStr == 2 && cmdStr[1][0] == 'g')
	{
		printf("ɾ��ƥ��\"%s\"�������ı���\n", cmdStr[0]);
		for(ThisLine=1, node=Head; node && node->next; )
		{
			if(substr(node->next->textline, cmdStr[0]) == EOF)
			{
				node = node->next;
				ThisLine++;
				continue;
			}
			if(node->next == NULL)
				errToExit("���������������");
			TotalLine--;
			deleteNode = node->next;
			node->next= deleteNode->next;
			putNode(deleteNode);
			deleteNode = node; 
			deleteLine = ThisLine;
			fail = 0;
		}
		node = deleteNode;
	}
	if(fail)
	{
		printf("ɾ������ʧ�ܣ�δ��ƥ��ָ�����ַ���\"%s\"\n", cmdStr[0]);
		return;
	}

	/* ��ʾɾ��������ĵ�ǰ���ı�			*/
	if(TotalLine == 0)
	{
		printf("�ı���ȫ��ɾ��\n");
		Head->next = NULL;
		ThisLine = 0;
	}
	else
	{
		if(node->next)
			printf("%d\t%s\n", deleteLine, node->next->textline);
		else
			printf("%d\t%s\n", --deleteLine, node->textline);
	}
}
