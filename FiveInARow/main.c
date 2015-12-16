//五子棋程序
#include"head.h"

int main(void)
{
	int pieces[HEIGHT+2][WIDTH+2];//棋盘棋子情况
	struct point location;//棋子位置

	//初始化棋盘
	initial(pieces);

	//分析
	location=analysis(pieces);

	return 0;
}