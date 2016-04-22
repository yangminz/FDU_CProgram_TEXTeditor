/*	File: ��������.c
	���ı��༭������������
	int substr(char *line, char *sub);	Ѱ�����ַ����ĺ���
	void findStr(void);					�����ַ����ĺ���
*/

#include "�ı��༭����.h"

/*	---------���º�����"��������.c"��----------------------	*/
void errToExit(char *);		/* ������ĺ���				*/
/* --------------------------------------------------------	*/

/* ���ַ���line��Ѱ�����ַ���sub�ĺ���							*/
/* ����ֵ��ʾ���ַ���sub��line�е�λ�ã��ַ������±꣩			*/
/* ����ֵΪEOF����ʾ���ַ���line�в��������ַ���sub				*/
/* ����������findStr(), deleteLine(), replaceStr()				*/
int substr(char *line, char *sub)		/* Ѱ�����ַ����ĺ���	*/
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

void findStr(void)			/* �����ַ����ĺ���				*/
{
	TEXT *node;
	int fail=1;				/* 0:��ɲ���; 1:�޷���ɲ���	*/
	if(Head == NULL || Head->next == NULL)
	{
		printf("�����ַ������󣺱༭�ı�Ϊ��\n");
		return;
	}
	if(numStr == 0)
	{
		printf("�����ַ�������δָ�������ַ���\n");
		return;
	}
	else if(numStr == 2 && cmdStr[1][0] != 'g')
	{
		printf("�����ַ������󣺷Ƿ�ƥ��ģʽ: /%s/%s\n",
				cmdStr[0], cmdStr[1]);
		return;
	}
	else if(numStr == 3 && cmdStr[1][0] == '\0')
	{
		printf("�����ַ������󣺷Ƿ�ƥ��ģʽ: /%s/%s/%s\n",
				cmdStr[0], cmdStr[1], cmdStr[2]);
		return;
	}
	else if(numStr == 1)
	{
		printf("��ʾƥ��\"%s\"���ı���\n", cmdStr[0]);
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
		printf("��ʾƥ��\"%s\"�������ı���\n", cmdStr[0]);
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
		printf("�����ַ������󣺷Ƿ�ƥ��ģʽ: /%s/%s%s\n",
				cmdStr[0], cmdStr[1], cmdStr[2]);
		return;
	}
	if(fail)
		printf("�����ַ���ʧ�ܣ�δ��ƥ��ָ�����ַ���\"%s\"\n", cmdStr[0]);
}
