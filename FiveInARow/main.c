//���������
#include"head.h"

int main(void)
{
	int pieces[HEIGHT+2][WIDTH+2];//�����������
	struct point location;//����λ��

	//��ʼ������
	initial(pieces);

	//����
	location=analysis(pieces);

	return 0;
}