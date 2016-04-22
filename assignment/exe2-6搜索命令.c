/*	File: exe2-6��������.c
	��ϰ��2-6���ı��༭������������
	int substr(char *line, char *sub);	Ѱ�����ַ����ĺ���
	void findStr(void);					�����ַ����ĺ���
*/

#include "exe2-6�ı��༭����.h"

/*	---------���º�����"exe2-6��������.c"��--------------	*/
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
	int i;
	
	if(Head == NULL || Head->next == NULL)
	{
		printf("�����ַ��������ı��ļ�Ϊ��\n");
		return;
	}

	if(numStr == 0)
	{
		printf("�����ַ�������δָ�������ַ���\n");
		return;
	}

	else if(numStr == 2 && cmdStr[1][0] != 'g')
	{
		printf("�����ַ������󣺷Ƿ�ƥ��ģʽ: %s\n", cmdStr[1]);
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
		/* ----�벹�����³���,ʵ����������"f /str/"�Ĺ���------	*/
		printf("��ʾƥ��%s���ı���\n", cmdStr[0]);
		node = Head;
		i = 0;

		while( node != NULL )
		{
			if( substr( node->textline, cmdStr[0] ) != -1 )
			{
				printf( "%-8d%s\n", i, node->textline);
				break;
			}
			node = node->next; i++;
		}
		return;
		/* ------------------�벹�����ϳ���--------------------	*/
	}

	else if(numStr == 2 && cmdStr[1][0] == 'g')
	{
		/* ----�벹�����³���,ʵ����������"f /str/g"�Ĺ���-----	*/
		printf("��ʾƥ��%s�������ı���\n", cmdStr[0]);
		
		node = Head;
		i = 0;

		while( node != NULL )
		{
			if( substr( node->textline, cmdStr[0] ) != -1 )
			{
				printf( "%-8d%s\n", i, node->textline);
			}
			node = node->next; i++;
		}
		return;
				/* ------------------�벹�����ϳ���--------------------	*/
	}

	else
	{
		printf("�����ַ������󣺷Ƿ�ƥ��ģʽ: /%s/%s%s\n",
				cmdStr[0], cmdStr[1], cmdStr[2]);
		return;
	}

	if(fail)
		printf("�����ַ���ʧ�ܣ�δ��ƥ��ָ�����ַ���%s\n", cmdStr[0]);
}
