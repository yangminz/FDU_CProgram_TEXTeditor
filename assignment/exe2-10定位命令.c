/*	File: exe2-10��λ����.c
	���ı��༭���򡿶�λ����:��λ����ʾ��n���ı�
	void gotoLine(void);		��λ�ı��еĺ���
*/

#include "�ı��༭����.h"

/*	---------���º�����"��������.c"��----------------------	*/
void errToExit(char *);		/* ������ĺ���				*/
/* --------------------------------------------------------	*/

void gotoLine(void)			/* ��λ�ı��еĺ���				*/
{
	/* --------�벹����ɶ�λ�ı��й��ܵĳ������----------	*/


	TEXT *node = NULL;

	if(Head == NULL || Head->next == NULL)
	{
		printf("��ʾ�ı��д��󣺱༭�ı�Ϊ��\n");
		return;
	}
	if(numData != 1)
		return;
	if(cmdData[0] < 1 || cmdData[0] > TotalLine)
	{
		printf("��λ�ı��д��󣺵�%d���ı�������\n", cmdData[0]);
		return;
	}
	else
	{
		printf("��λ��%d���ı�\n", cmdData[0]);
		for(ThisLine=1, node=Head;
		node->next && ThisLine < cmdData[0];
		node=node->next, ThisLine++)
		;
		printf("%d\t%s\n", ThisLine, node->next->textline);
	}
	if(node->next == NULL || ThisLine != cmdData[0])
		errToExit("���������������");
}

