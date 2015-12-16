
// stdafx.cpp : 只包括标准包含文件的源文件
// FiveInARow.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

int pieces[HEIGHT+2][WIDTH+2]={0};
int player1=0;//0表示人
int player2=1;//1表示电脑
int player=1;
int mode=0;//0人人对战，1人机对战，2机机对战
struct point location;//棋子位置
