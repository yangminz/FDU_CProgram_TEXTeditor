/*	File: exe2-4�ַ�������.c
	��ϰ��2-4�����ļ��ĸ����ı�text������(Ѱ��)�ַ���str��
	����ҵҪ�󡿶����ı��ļ����������³����й涨�Ľṹ���壬
				��������˳�����д洢�ı��С�
				������������ַ����ļ�����ÿһ���ַ�����
				���Ѵ洢���ı������������ַ�����
				�������ƥ����ı��е���Ļ��
				��д����ȱʧ�ĳ���
	��ʾ�����򡿿����е�exe2-4�ַ�������.exe
	��ʾ���ı��ļ���exe2-4File.txt
	��ʾ���ַ����ļ���exe2-4str.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* ���д���ı��Ľṹ����	*/
#define LINE 80
#define TEXT struct text
TEXT
{
	char textline[LINE];
	TEXT *next;
};

/* �����ı��ļ��ĺ���	*/

TEXT *readFile(FILE *fp)
{
	char buf[LINE];
	TEXT *head=NULL, *tail=NULL, *node;

	while(fgets(buf, LINE, fp))
	{
		if((node = (TEXT*)malloc(sizeof(TEXT))) == NULL)
			exit(0);
		strcpy(node->textline, buf);
		if(tail == NULL)
		{
			node->next = tail; 			/* ������ĺ������� 	*/
			head = tail = node;
		}
		else
		{
			node->next = tail->next;	/* �ǿ�����ĺ������� */
			tail = tail->next = node;
		}
	}
	return head;
}

/* �����ַ����ĺ���	*/
int search( char *text, char *str )
{
	/* ��д����ȱʧ�ĳ���	*/
	char *ptext,*pstr;
	short k;
	for(k = 0; *text; text++, k++)
	{
		for(ptext = text, pstr = str; 
			*pstr != '\0' && *ptext == *pstr;
			ptext++, pstr++)
			;
		if((*pstr == '\0')||(*pstr == '\n'))
			return(k);
	}
	return (EOF);
}

/* �����������ĺ���	*/
void findStr(TEXT *head)
{
	TEXT *node;
	FILE *strFp;
	char strFile[20], buf[LINE];
	int n;

	printf("��������������ַ����ļ���: ");
	scanf("%s", strFile);
	if((strFp = fopen(strFile, "r")) == NULL)
		exit(0);

	while(fgets(buf, LINE, strFp))
	{
		/* ��д����ȱʧ�ĳ���	*/
		node=head;
		n = 1;

		printf("\n���������ַ���:%s",buf);
		printf("�����Ľ�������е��ı�Ϊ\n");
		while(node!=NULL)
		{
			if(search(node->textline, buf) != -1)
			{
				printf("%-8d%s", n, node->textline);
			}
			node=node->next; n++;
		}
	}
}

int main()
{
	FILE *inFp;
	TEXT *head=NULL;
	char inFile[20];

	printf("�������ı��ļ���: ");
	scanf("%s", inFile);
	if((inFp = fopen(inFile, "r")) == NULL)
	{
		printf("�޷����ļ�\n", inFile);
		system("pause");
		exit(0);
	}

	head = readFile(inFp);
	findStr(head);

	system("pause");
}
/*
exe2-4File.txt
exe2-4str.txt
�������ı��ļ���: exe2-4File.txt
��������������ַ����ļ���: exe2-4str.txt

���������ַ���:exe
�����Ľ�������е��ı�Ϊ
5       1230713("%s);0exe1B�ļ�����.c

���������ַ���:FILE
�����Ľ�������е��ı�Ϊ

���������ַ���:str
�����Ľ�������е��ı�Ϊ
1       Abstringstract
3       A strustringstracctustrgstracred
10      propstringstracosed. stringstrac

�밴���������. . .
*/
