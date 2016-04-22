/*	File: ��д����.c
	���ı��༭���򡿶�д����
	void readFile(void);		�����ı��ļ��ĺ���
	void writeFile(void);		����ı��ļ��ĺ���
*/

#include "�ı��༭����.h"
/*	---------���º�����"��������.c"��----------------------	*/
TEXT * getNode(void);		/* ��ȡ���н��ĺ���			*/
void putNode(TEXT *);		/* ��ſ��н��ĺ���			*/
/* --------------------------------------------------------	*/

/* �����ı��ļ����ļ�ָ��									*/
FILE *filePtr;

void readFile(void)			/* �����ı��ļ��ĺ���			*/
{
	TEXT *tail, *node;
	char textline[LINE];
	int n;
	if(numStr == 0)
	{
		printf("�����ļ�����δָ���ļ���\n");
		return;
	}
	printf("�����ļ�[%s]\n", cmdStr[0]);
	if((filePtr = fopen(cmdStr[0], "r")) == NULL)
	{
		printf("�����ļ����󣺴��ļ� [%s] ʧ��\n", cmdStr[0]);
		return;
	}
	if(Head->next != NULL)
	{
		printf("��ǰ���ڱ༭һ���ļ�����ȷ���Ƿ�����ļ���\n");
		printf("�����û�д��̣�������'N'����ʾ�������ļ���\n");
		printf("���򣬱�ʾȷ�϶��ļ�����ȷ��:  ");
		gets(textline);
		if(textline[0] == 'N')
			return;
		/* ɾ����ǰ�ı�����������н�㣬�Զ����µ��ı��ļ�	*/
		/* ����putNode��������ɾ���Ľ�������н������	*/
		while(Head->next)
		{
			node = Head->next;
			Head->next = Head->next->next;
			putNode(node);
		}
	}
	TotalLine = 0;		/* ���һ�е��к�(������)����ֵΪ0	*/
	while(fgets(textline, LINE, filePtr) != NULL)
	{
		node = getNode();
		TotalLine++;		/* ���һ�е��к�(������)		*/
		n = strlen(textline);
		if(textline[n-1] == '\n')
			textline[n-1] = '\0';
		strcpy(node->textline, textline);
		if(Head->next == NULL)	/* ������ĺ�������		*/
			Head->next = tail = node;
		else					/* �ǿ�����ĺ�������		*/
			tail = tail->next = node;
	}
	tail->next = NULL;		/* ���һ��������һ���ָ���	*/
	ThisLine = 1;			/* ��ǰ�ı����кţ���ֵΪ1		*/
	fclose(filePtr);
}

void writeFile(void)		/* ����ı��ļ��ĺ���			*/
{
	TEXT *node;
	char textline[LINE];
	if(numStr == 0)
	{
		printf("����ļ�����δָ���ļ���\n");
		return;
	}
	else
	{
		printf("���Ϊ�ļ�[%s]\n", cmdStr[0]);
		if(Head == NULL || Head->next == NULL)
		{
			printf("����ļ����󣺱༭�ı�Ϊ��\n");
			return;
		}
		if((filePtr = fopen(cmdStr[0], "r")) != NULL)
		{
			printf("�ļ�[%s]�Ѵ���\n", cmdStr[0]);
			printf("������'Y'����ʾ���ļ���������\n");
			printf("���򣬱�ʾ����:  ");
			gets(textline);
			if(textline[0] != 'Y')
				return;
		}
		if((filePtr = fopen(cmdStr[0], "w")) == NULL)
		{
			printf("����ļ����󣺴��ļ� [%s] ʧ��\n", cmdStr[0]);
			return;
		}
		/* ����ı��ļ����Լ��ر��ļ��Ĳ���					*/
		for(node=Head->next; node; node=node->next)
			fprintf(filePtr, "%s\n", node->textline);
		fclose(filePtr);
	}
}
