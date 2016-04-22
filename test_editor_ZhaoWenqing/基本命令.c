/*	File: ��������.c
	���ı��༭���򡿻�������
	void help(void);			��������
	void quit(void);			�����ı��༭����ĺ���
	error(void);				��֪��Ч����ĺ���
	void errToExit(char *);		������ĺ���
	TEXT * getENode(void);		��ȡ���н��ĺ���
	void putNode(TEXT *);		��ſ��н��ĺ���
*/

#include "�ı��༭����.h"

void errToExit(char *errMsg)	/* ������ĺ���			*/
{
	printf("%s\n", errMsg);		/* ��ʾ������Ϣ				*/
	printf("�����������������...  "); 
	getchar();
	exit(0);					/* ������������				*/
}
TEXT * getNode(void)			/* ��ȡ���н��ĺ���		*/
{
	TEXT *node;
	if(Empty)
	{
		node = Empty;
		Empty = node->next;
	}
	else
		if( (node = (TEXT *)malloc(sizeof(TEXT))) == NULL)
			errToExit("���������ڴ����ʧ�ܣ�");
	return(node);
}
void putNode(TEXT *node)		/* ��ſ��н��ĺ���		*/
{
	node->next = Empty;
	Empty = node;
}
void help(void)					/* ��������					*/
{
	printf("====  �ı��༭���������  ====\n");
	printf("q \t\t��������\n");
	printf("h \t\t��ʾ���������ʽ(��ǰ����)\n");
	printf("r file\t\t�����ļ�file\n");
	printf("w file\t\t���Ϊ�ļ�file\n");
	printf("p \t\t��ʾ�����ı���\n");
	printf("p n\t\t��ʾ��n���ı�\n");
	printf("p n,m\t\t��ʾ��n�е�m���ı�\n");
	printf("f /str/\t\t��ʾƥ��str���ı���\n");
	printf("f /str/g\t��ʾƥ��str�������ı���\n");
	printf("d n\t\tɾ����n���ı�\n");
	printf("d n,m\t\tɾ����n��m���ı�\n");
	printf("d /str/\t\tɾ��ƥ��str���ı���\n");
	printf("d /str/g\tɾ��ƥ��str�������ı���\n");
	printf("s /str//\tɾ��str\n");
	printf("s /str//g\tɾ���������е�str\n");
	printf("s /str/tar/\tstr�滻Ϊtar\n");
	printf("s /str/tar/g\t���е�str�滻Ϊtar\n");
	printf("i n\t\t�ڵ�n��֮������ı���\n");
	printf("a n\t\t�ڵ�n��֮������ı���\n");
}
void quit(void)					/* �����ı��༭����ĺ���	*/
{
	printf("�����������������...  "); 
	getchar();
	exit(0);
}
void error(void)				/* ��֪��Ч����ĺ���		*/
{
	printf("��Ч����\n");
}
