
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// FiveInARow.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

int pieces[HEIGHT+2][WIDTH+2]={0};
int player1=0;//0��ʾ��
int player2=1;//1��ʾ����
int player=1;
int mode=0;//0���˶�ս��1�˻���ս��2������ս
struct point location;//����λ��
