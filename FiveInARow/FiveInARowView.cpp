
// FiveInARowView.cpp : CFiveInARowView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "FiveInARow.h"
#endif

#include "FiveInARowDoc.h"
#include "FiveInARowView.h"
#include<iostream>
#include<fstream>
#include<time.h>
#include<math.h>
#include<stdlib.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int stopflag=0;

int turn=0;

int difficulty=0;
//撤销缓冲大小
#define BUFF 20
//撤销缓冲
struct point tempsave[BUFF];
int count=0;//撤销计数


extern int mode;//0人人对战，1人机对战，2机机对战
// CFiveInARowView

IMPLEMENT_DYNCREATE(CFiveInARowView, CView)

BEGIN_MESSAGE_MAP(CFiveInARowView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFiveInARowView::OnFilePrintPreview)
//	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_NEW, &CFiveInARowView::OnFileNew)
//	ON_COMMAND(ID_FILE_OPEN, &CFiveInARowView::OnFileOpen)
ON_WM_MOUSEMOVE()
ON_WM_TIMER()
//ON_COMMAND(ID_32772, &CFiveInARowView::OnModeSet)
ON_COMMAND(ID_32772, &CFiveInARowView::OnMode0)
ON_COMMAND(ID_32773, &CFiveInARowView::OnMode1)
ON_COMMAND(ID_32774, &CFiveInARowView::OnMode2)
ON_COMMAND(ID_32776, &CFiveInARowView::OnDifficulty0)
ON_COMMAND(ID_32778, &CFiveInARowView::OnDifficulty2)
ON_COMMAND(ID_32777, &CFiveInARowView::On32777)
ON_COMMAND(ID_32779, &CFiveInARowView::OnChangeFirst)
ON_COMMAND(ID_EDIT_UNDO, &CFiveInARowView::OnEditUndo)
END_MESSAGE_MAP()

// CFiveInARowView 构造/析构

CFiveInARowView::CFiveInARowView()
{
	// TODO: 在此处添加构造代码

}

CFiveInARowView::~CFiveInARowView()
{
}

BOOL CFiveInARowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CFiveInARowView 绘制

void CFiveInARowView::OnDraw(CDC* /*pDC*/)
{
	CFiveInARowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CFiveInARowView 打印


void CFiveInARowView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFiveInARowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CFiveInARowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CFiveInARowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CFiveInARowView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

//void CFiveInARowView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//}


// CFiveInARowView 诊断

#ifdef _DEBUG
void CFiveInARowView::AssertValid() const
{
	CView::AssertValid();
}

void CFiveInARowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFiveInARowDoc* CFiveInARowView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFiveInARowDoc)));
	return (CFiveInARowDoc*)m_pDocument;
}
#endif //_DEBUG


// 全屏刷新函数

int CFiveInARowView::AllDisplay(void)
{
	int i,j;
	CPoint a(0,0);
	CPoint b(0,0);
	for(i=1;i<=HEIGHT;i++)
	{
		for(j=1;j<=WIDTH;j++)
		{
			a.x=MW+PIC*(j-1);
			a.y=MH+PIC*(i-1);
			b.x=MW+PIC*j;
			b.y=MH+PIC*i;
			CBitmap bitmap;	
			if(pieces[i][j]==1)
			{
				if(i==1&&j==1)
				{
					bitmap.LoadBitmap(IDB_BITMAP5);
				}
				else if(i==1&&j==WIDTH)
				{
					bitmap.LoadBitmap(IDB_BITMAP8);
				}
				else if(i==HEIGHT&&j==1)
				{
					bitmap.LoadBitmap(IDB_BITMAP3);
				}
				else if(i==HEIGHT&&j==WIDTH)
				{
					bitmap.LoadBitmap(IDB_BITMAP7);
				}
				else if(i==1)
				{
					bitmap.LoadBitmap(IDB_BITMAP9);
				}
				else if(j==1)
				{
					bitmap.LoadBitmap(IDB_BITMAP4);
				}
				else if(i==HEIGHT)
				{
					bitmap.LoadBitmap(IDB_BITMAP2);
				}
				else if(j==WIDTH)
				{
					bitmap.LoadBitmap(IDB_BITMAP6);
				}
				else
				{
					bitmap.LoadBitmap(IDB_BITMAP1);
				}
			}
			else if(pieces[i][j]==2)
			{
				if(i==1&&j==1)
				{
					bitmap.LoadBitmap(IDB_BITMAP23);
				}
				else if(i==1&&j==WIDTH)
				{
					bitmap.LoadBitmap(IDB_BITMAP26);
				}
				else if(i==HEIGHT&&j==1)
				{
					bitmap.LoadBitmap(IDB_BITMAP22);
				}
				else if(i==HEIGHT&&j==WIDTH)
				{
					bitmap.LoadBitmap(IDB_BITMAP25);
				}
				else if(i==1)
				{
					bitmap.LoadBitmap(IDB_BITMAP27);
				}
				else if(j==1)
				{
					bitmap.LoadBitmap(IDB_BITMAP21);
				}
				else if(i==HEIGHT)
				{
					bitmap.LoadBitmap(IDB_BITMAP20);
				}
				else if(j==WIDTH)
				{
					bitmap.LoadBitmap(IDB_BITMAP24);
				}
				else
				{
					bitmap.LoadBitmap(IDB_BITMAP19);
				}
			}
			else if(pieces[i][j]==0)
			{
				if(i==1&&j==1)
				{
					bitmap.LoadBitmap(IDB_BITMAP14);
				}
				else if(i==1&&j==WIDTH)
				{
					bitmap.LoadBitmap(IDB_BITMAP17);
				}
				else if(i==HEIGHT&&j==1)
				{
					bitmap.LoadBitmap(IDB_BITMAP13);
				}
				else if(i==HEIGHT&&j==WIDTH)
				{
					bitmap.LoadBitmap(IDB_BITMAP16);
				}
				else if(i==1)
				{
					bitmap.LoadBitmap(IDB_BITMAP18);
				}
				else if(j==1)
				{
					bitmap.LoadBitmap(IDB_BITMAP12);
				}
				else if(i==HEIGHT)
				{
					bitmap.LoadBitmap(IDB_BITMAP11);
				}
				else if(j==WIDTH)
				{
					bitmap.LoadBitmap(IDB_BITMAP15);
				}
				else
				{
					bitmap.LoadBitmap(IDB_BITMAP10);
				}
			}
			//显示
			CBrush brush(&bitmap);
			CClientDC dc(this);
			dc.FillRect(CRect(a,b),&brush);
		}
	}
	return 0;
}


void CFiveInARowView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CView::OnPaint()
	AllDisplay();
}


void CFiveInARowView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int i,j;
	if(mode==0||mode==1)
	{
		i=(point.y-MH)/PIC+1;
		j=(point.x-MW)/PIC+1;

		if(point.x>=MW&&point.y>=MH&&point.x<=PIC*WIDTH+MW&&point.y<=PIC*HEIGHT+MH)	 //越界检测
		{
			/*if(player==1)
			{
				//判断这点是否下过棋子
				if(pieces[(point.y-MH)/PIC+1][(point.x-MW)/PIC+1]==0)
				{
					pieces[(point.y-MH)/PIC+1][(point.x-MW)/PIC+1]=1;
					//显示
					Display(point.x,point.y);
					SaveInFile();
					if(WinJudge(i,j)!=0)
						goto end;
					//交换对手
					player=2;
					player_computer1();
				}
				else
				{
					MessageBox("此处无法落子！");
				}

			}
			else if(player==2)
			{
				//判断这点是否下过棋子
				if(pieces[(point.y-MH)/PIC+1][(point.x-MW)/PIC+1]==0)
				{
					pieces[(point.y-MH)/PIC+1][(point.x-MW)/PIC+1]=2;
					//显示
					Display(point.x,point.y);
					SaveInFile();
					if(WinJudge(i,j)!=0)
						goto end;
					//交换对手
					player=1;
					player_computer1();
				}
				else
				{
					MessageBox("此处无法落子！");
				}
			}*/
			click(i,j);
			if(mode==1)
			{
				player_computer1();
			}
		}
	}
	CView::OnLButtonUp(nFlags, point);
}

//windows坐标

int CFiveInARowView::Display(int x, int y)
{
	int i,j;

	CPoint a(0,0);
	CPoint b(0,0);

	j=(x-MW)/PIC+1;
	i=(y-MH)/PIC+1;

	a.x=(j-1)*PIC;
	a.y=(i-1)*PIC;
	b.x=j*PIC;
	b.y=i*PIC;

	CBitmap bitmap;	
	if(pieces[i][j]==1)
	{
		if(i==1&&j==1)
		{
			bitmap.LoadBitmap(IDB_BITMAP5);
		}
		else if(i==1&&j==WIDTH)
		{
			bitmap.LoadBitmap(IDB_BITMAP8);
		}
		else if(i==HEIGHT&&j==1)
		{
			bitmap.LoadBitmap(IDB_BITMAP3);
		}
		else if(i==HEIGHT&&j==WIDTH)
		{
			bitmap.LoadBitmap(IDB_BITMAP7);
		}
		else if(i==1)
		{
			bitmap.LoadBitmap(IDB_BITMAP9);
		}
		else if(j==1)
		{
			bitmap.LoadBitmap(IDB_BITMAP4);
		}
		else if(i==HEIGHT)
		{
			bitmap.LoadBitmap(IDB_BITMAP2);
		}
		else if(j==WIDTH)
		{
			bitmap.LoadBitmap(IDB_BITMAP6);
		}
		else
		{
			bitmap.LoadBitmap(IDB_BITMAP1);
		}
	}
	else if(pieces[i][j]==2)
	{
		if(i==1&&j==1)
		{
			bitmap.LoadBitmap(IDB_BITMAP23);
		}
		else if(i==1&&j==WIDTH)
		{
			bitmap.LoadBitmap(IDB_BITMAP26);
		}
		else if(i==HEIGHT&&j==1)
		{
			bitmap.LoadBitmap(IDB_BITMAP22);
		}
		else if(i==HEIGHT&&j==WIDTH)
		{
			bitmap.LoadBitmap(IDB_BITMAP25);
		}
		else if(i==1)
		{
			bitmap.LoadBitmap(IDB_BITMAP27);
		}
		else if(j==1)
		{
			bitmap.LoadBitmap(IDB_BITMAP21);
		}
		else if(i==HEIGHT)
		{
			bitmap.LoadBitmap(IDB_BITMAP20);
		}
		else if(j==WIDTH)
		{
			bitmap.LoadBitmap(IDB_BITMAP24);
		}
		else
		{
			bitmap.LoadBitmap(IDB_BITMAP19);
		}
	}
	else if(pieces[i][j]==0)
	{
		if(i==1&&j==1)
		{
			bitmap.LoadBitmap(IDB_BITMAP14);
		}
		else if(i==1&&j==WIDTH)
		{
			bitmap.LoadBitmap(IDB_BITMAP17);
		}
		else if(i==HEIGHT&&j==1)
		{
			bitmap.LoadBitmap(IDB_BITMAP13);
		}
		else if(i==HEIGHT&&j==WIDTH)
		{
			bitmap.LoadBitmap(IDB_BITMAP16);
		}
		else if(i==1)
		{
			bitmap.LoadBitmap(IDB_BITMAP18);
		}
		else if(j==1)
		{
			bitmap.LoadBitmap(IDB_BITMAP12);
		}
		else if(i==HEIGHT)
		{
			bitmap.LoadBitmap(IDB_BITMAP11);
		}
		else if(j==WIDTH)
		{
			bitmap.LoadBitmap(IDB_BITMAP15);
		}
		else
		{
			bitmap.LoadBitmap(IDB_BITMAP10);
		}
	}
	//显示
	CBrush brush(&bitmap);
	CClientDC dc(this);
	dc.FillRect(CRect(a,b),&brush);
	return 0;
}

//胜负判断

int CFiveInARowView::WinJudge(int i, int j)
{
	int m;
	int color;
	int len=0;
	color=pieces[i][j];//暂存颜色
	//横的方向判断胜负
	len=0;
	for(m=0;pieces[i][j+m]==color;m++)
	{
	}
	len+=m-1;
	for(m=0;pieces[i][j+m]==color;m--)
	{
	}
	len+=-m-1;
	len++;
	if(len>=5)
	{
		if(player==1)
		{
			stopflag=1;
			MessageBox("黑棋获胜！");
			return 1;
		}
		else if(player==2)
		{
			stopflag=1;
			MessageBox("白棋获胜！");
			return 2;
		}
	}
	//纵向判断胜负
	len=0;
	for(m=0;pieces[i+m][j]==color;m++)
	{
	}		
	len+=m-1;
	for(m=0;pieces[i+m][j]==color;m--)
	{
	}
	len+=-m-1;
	len++;
	if(len>=5)
	{
		if(player==1)
		{
			stopflag=1;
			MessageBox("黑棋获胜！");
			return 1;
		}
		else if(player==2)
		{
			stopflag=1;
			MessageBox("白棋获胜！");
			return 2;
		}
	}
	//主对角线胜负判断
	len=0;
	for(m=0;pieces[i+m][j+m]==color;m++)
	{
	}
	len+=m-1;
	for(m=0;pieces[i+m][j+m]==color;m--)
	{	
	}
	len+=-m-1;
	len++;
	if(len>=5)
	{
		if(player==1)
		{
			stopflag=1;
			MessageBox("黑棋获胜！");
			return 1;
		}
		else if(player==2)
		{
			stopflag=1;
			MessageBox("白棋获胜！");
			return 2;
		}
	}
	//副对角线胜负判断
	len=0;
	for(m=0;pieces[i+m][j-m]==color;m++)
	{
	}	
	len+=m-1;
	for(m=0;pieces[i+m][j-m]==color;m--)
	{
	}
	len+=-m-1;
	len++;
	if(len>=5)
	{
		if(player==1)
		{
			stopflag=1;
			MessageBox("黑棋获胜！");
			return 1;
		}
		else if(player==2)
		{
			stopflag=1;
			MessageBox("白棋获胜！");
			return 2;
		}
	}
	return 0;
}


struct point CFiveInARowView::analysis(int pieces[][WIDTH+2])
{
	int priority[HEIGHT+2][WIDTH+2];//每个位置优先级量化
	int height,width;
	int temp;
	int x,y;
	struct point result;

	for(height=0;height<HEIGHT+2;height++)
	{
		for(width=0;width<WIDTH+2;width++)
		{
			//当该位置已经有棋子或已经到达边界时
			if(pieces[height][width]!=0)
			{
				priority[height][width]=-1;//把此位置赋值为-1
			}

			//该位置可以落子
			else
			{
				priority[height][width]=0;

				//判断四周情况
				priority[height][width]=situation(pieces,height,width);
			}
		}
	}
	temp=-1;
	for(height=1;height<HEIGHT+1;height++)
	{
		for(width=1;width<WIDTH+1;width++)
		{
			if(priority[height][width]>temp)
			{
				temp=priority[height][width];
				y=height;
				x=width;
			}
		}
	}
	if(turn!=0)
	{
	result.x=x;
	result.y=y;
	return result;
	}
	else
	{
	result.x=WIDTH/2;
	result.y=HEIGHT/2;
	return result;
	}
}


int CFiveInARowView::situation(int pieces[][WIDTH+2],int height,int width)
{
	int y,x;
	int priority=0;//初始优先级为0
	int quality;//棋子属性
	int num;
	int i;

	for(y=-1;y<=1;y++)
	{
		for(x=-1;x<=1;x++)
		{
			if(((pieces[height+y][width+x]==0)||(pieces[height+y][width+x]==3))||(x==0&&y==0))
			{
				continue;
			}
			else
			{
				num=1;
				quality=pieces[height+y][width+x];//该点的属性

				for(i=2;;i++)
				{
					if(quality==pieces[height+y*i][width+x*i])
					{
						num++;
					}
					else if(pieces[height+y*i][width+x*i]==0)
					{
						if(quality==COMPUTER)//quality为1时，是电脑
						{
							switch(num)
							{
							case 1:priority+=2;break;//o
							case 2:priority+=6*8;break;//oo
							case 3:priority+=14*8*8;break;//ooo
							case 4:priority+=14*8*8*8;break;//oooo
							case 5:priority+=20*8*8*8*8;break;//ooooo
							case 6:priority+=20*8*8*8*8;break;
							case 7:priority+=20*8*8*8*8;break;
							}
						}
						else
						{
							switch(num)
							{
							case 1:priority+=2;break;//x
							case 2:priority+=4*8;break;//xx
							case 3:priority+=14*8*8;break;//xxx
							case 4:priority+=14*8*8*8;break;//xxxx
							case 5:priority+=18*8*8*8*8;break;//xxxxx
							case 6:priority+=20*8*8*8*8;break;
							case 7:priority+=20*8*8*8*8;break;
							}
						}
						break;
					}
					else
					{
						if(quality==COMPUTER)//quality为1时，是电脑
						{
							switch(num)
							{
							case 1:priority+=1;break;//xo
							case 2:priority+=5*8;break;//xoo
							case 3:priority+=9*8*8;break;//xooo
							case 4:priority+=15*8*8;break;//xoooo
							case 5:priority+=19*8*8*8*8;break;//xooooo
							case 6:priority+=20*8*8*8*8;break;
							case 7:priority+=20*8*8*8*8;break;
							}
						}
						else
						{
							switch(num)
							{
							case 1:priority+=1;break;//ox
							case 2:priority+=3*8;break;//oxx
							case 3:priority+=7*8*8;break;//oxxx
							case 4:priority+=15*8*8;break;//oxxxx
							case 5:priority+=17*8*8*8*8;break;//oxxxxx
							case 6:priority+=20*8*8*8*8;break;
							case 7:priority+=20*8*8*8*8;break;
							}
						}
						break;
					}
				}
			}
		}
	}
	return priority;
	return 0;
}


void CFiveInARowView::initial(int pieces[][WIDTH+2])
{
	int y,x;
	int i;
	player=1;
	//边框初始化为3
	for(x=0;x<WIDTH+2;x++)
	{
		pieces[0][x]=pieces[HEIGHT+1][x]=3;
	}
	for(y=0;y<HEIGHT+2;y++)
	{
		pieces[y][0]=pieces[y][WIDTH+1]=3;
	}

	//除边框其他为0
	for(y=1;y<HEIGHT+1;y++)
	{
		for(x=1;x<WIDTH+1;x++)
		{
			pieces[y][x]=0;
		}
	}
	//初始化tempsave
	for(i=0;i<BUFF;i++)
	{
	tempsave[i].x=0;
	tempsave[i].y=0;
	tempsave[i].color=0;
	}
	count=0;
	stopflag=0;
	turn=0;
	AllDisplay();
}


int CFiveInARowView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	initial(pieces);
	ReadFromFile();
	return 0;
}


int CFiveInARowView::player_computer1(void)
{
	if(player1==1&&player==1)
	{
		//难度控制
		if(difficulty==0)
		{
			location=analysis(pieces);
		}
		else if(difficulty==1)
		{
			location=analysis3(pieces);
		}
		else if(difficulty==2)
		{
			location=analysis3(pieces);
		}
		if(click(location.y,location.x)!=0)
		{
			initial(pieces);
		}
	}
	else if(player2==1&&player==2)
	{
		//难度控制
		if(difficulty==0)
		{
			location=analysis(pieces);
		}
		else if(difficulty==1)
		{
			location=analysis3(pieces);
		}
		else if(difficulty==2)
		{
			location=analysis3(pieces);
		}
		if(click(location.y,location.x)!=0)
		{
			initial(pieces);
		}
	}
	return 0;
}


int CFiveInARowView::SaveInFile(void)
{
	int i,j;
	ofstream outfile("save.txt");
	if(outfile.is_open())
	{
		outfile<<turn<<' '<<difficulty<<' '<<mode<<' '<<count<<'\n';
		for(int i=0;i<BUFF;i++)
		{
			outfile<<tempsave[i].x<<' '<<tempsave[i].y<<' '<<tempsave[i].color<<'\n';
		}

		for(i=1;i<=HEIGHT;i++)
		{
			for(j=1;j<=WIDTH;j++)
			{
				outfile<<pieces[i][j]<<' ';
			}
			outfile<<'\n';
		}
	}
	return 0;
}


int CFiveInARowView::ReadFromFile(void)
{
	int i,j;
	ifstream infile("save.txt");
	if(infile.is_open())
	{
		infile>>turn>>difficulty>>mode>>count;
		for(int i=0;i<BUFF;i++)
		{
			infile>>tempsave[i].x>>tempsave[i].y>>tempsave[i].color;
		}
		for(i=1;i<=HEIGHT;i++)
		{
			for(j=1;j<=WIDTH;j++)
			{
				infile>>pieces[i][j];
			}
		}
	}
	return 0;
}


void CFiveInARowView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	initial(pieces);
	SaveInFile();
	AllDisplay();
}


int CFiveInARowView::player_computer2(void)
{
	if(player1==0&&player==1)
	{
		location=analysis(pieces);
		if(click(location.y,location.x)!=0)
		{
			initial(pieces);
		}
	}
	else if(player2==0&&player==2)
	{
		location=analysis(pieces);
		if(click(location.y,location.x)!=0)
		{
			initial(pieces);
		}
	}
	return 0;
}


void CFiveInARowView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

		
	CView::OnMouseMove(nFlags, point);
}


int CFiveInARowView::click(int i, int j)
{
	int temp=0;
	//判断这点是否下过棋子
	if(pieces[i][j]==0)
	{
		if(player==1)
		{
			pieces[i][j]=1;
			//回合数++
			turn++;
		}
		else if(player==2)
		{
			pieces[i][j]=2;
		}
		//自动保存
		for(int m=1;m<BUFF;m++)
		{
			tempsave[m-1]=tempsave[m];
		}
		tempsave[BUFF-1].x=j;
		tempsave[BUFF-1].y=i;
		tempsave[BUFF-1].color=pieces[i][j];
		//显示
		Display((j-1)*PIC+MW,(i-1)*PIC+MH);
		//保存
		SaveInFile();
		//胜负检测
		temp=WinJudge(i,j);
		//交换对手
		if(player==1)
			player=2;
		else if(player==2)
			player=1;
	}
	else
	{
		MessageBox("此处无法落子！");
	}
	if(temp!=0)
	{
		initial(pieces);
		return temp;
	}
	return 0;
}


void CFiveInARowView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(stopflag==0&&mode==2)
	{
		player_computer1();
		player_computer2();
	}
	if(stopflag==0&&mode==1)
	{
		player_computer1();
	}
	AllDisplay();
	CView::OnTimer(nIDEvent);
}



void CFiveInARowView::OnMode0()
{
	// TODO: 在此添加命令处理程序代码
	mode=0;
}


void CFiveInARowView::OnMode1()
{
	// TODO: 在此添加命令处理程序代码
	mode=1;
	SetTimer(1,1000,NULL);
}


void CFiveInARowView::OnMode2()
{
	// TODO: 在此添加命令处理程序代码
	mode=2;
	SetTimer(2,1000,NULL);
}

//学习算法
struct point CFiveInARowView::analysis2(const int pieces[][WIDTH+2])
{
	//int store[HEIGHT+2][WIDTH+2]={0};
	int temp[HEIGHT+WIDTH]={0};
	int i,j;
	int m,n;
	struct point start,end;
	int color;
	int len=0;
	struct point location;
	color=player;//暂存颜色
	//复制数组
	/*for(i=0;i<HEIGHT+2;i++)
	{
		for(j=0;j<WIDTH+2;j++)
		{
				store[i][j]=piece[i][j];
		}
	}*/

	//计算权重
	for(i=0;i<HEIGHT+2;i++)
	{
		for(j=0;j<WIDTH+2;j++)
		{
			if(pieces[i][j]==player)
			{
				//横向计算

				//纵向计算

				//主对角线计算

				//副对角线计算

				//综合计算
			}
		}
	}
	return location;
}


struct point CFiveInARowView::analysis3(int pieces[][WIDTH+2])
{
	int priority[HEIGHT+2][WIDTH+2];//每个位置优先级量化
	int height,width,m_height,m_width;
	int temp,temp_com,temp_hum;
	int x,y;
	struct point result;

	srand((unsigned)time(NULL));
	for(m_height=0;m_height<HEIGHT+2;m_height++)
	{
		for(m_width=0;m_width<WIDTH+2;m_width++)
		{
			if(pieces[m_height][m_width]==0)
			{
				pieces[m_height][m_width]=COMPUTER;
				temp_com=analysis_2(pieces);
				pieces[m_height][m_width]=HUMAN;
				temp_hum=analysis_2(pieces);
				pieces[m_height][m_width]=0;
			}
			else
			{
				temp_com=temp_hum=-1;
			}
			priority[m_height][m_width]=(temp_com>temp_hum?temp_com:temp_hum);
		}
	}
	//int flag=1,count;
	int count=0;
	temp=-1;
	for(height=1;height<HEIGHT+1;height++)
	{
		for(width=1;width<WIDTH+1;width++)
		{
			if(priority[height][width]>temp)
			{
			//	if(priority[height][width]>temp)
			//		flag=0;
			//	temp=priority[height][width];
			//	if(flag==1)
			//	{
			//		count++;
			//	}
			//	flag=1;
				count=1;
				temp=priority[height][width];
			}
			else if(priority[height][width]==temp)
			{
				count++;
			}
		}
	}

	count=rand()%count+1;
	for(height=1;height<HEIGHT+1;height++)
	{
		for(width=1;width<WIDTH+1;width++)
		{
			if(priority[height][width]==temp)
				count--;
			if(count<=0)
				break;
		}
		if(count<=0)
			break;
	}
	/*while(1)
	{
		static int count=0;
		height=rand()%HEIGHT;
		width=rand()%WIDTH;
		if(priority[height][width]==temp)
		break;
		if(count>=500)
		{
			height=
		}
		count++;
	}*/
	y=height;
	x=width;
	result.x=x;
	result.y=y;
	return result;
}


int CFiveInARowView::analysis_2(int pieces[][WIDTH+2])
{
	int priority[HEIGHT+2][WIDTH+2];//每个位置优先级量化
	int height,width;
	int temp;
	int x,y;
	struct point result;

	for(height=0;height<HEIGHT+2;height++)
	{
		for(width=0;width<WIDTH+2;width++)
		{
			//当该位置已经有棋子或已经到达边界时
			if(pieces[height][width]!=0&&pieces[height][width]!=3)
			{
				priority[height][width]=-1;//把此位置赋值为-1
			}

			//该位置可以落子
			else
			{
				priority[height][width]=0;

				//判断四周情况
				priority[height][width]=situation(pieces,height,width);
			}
		}
	}
	temp=0;
	for(height=0;height<HEIGHT+2;height++)
	{
		for(width=0;width<WIDTH+2;width++)
		{

				temp+=priority[height][width];

		}
	}
	return temp;
}


void CFiveInARowView::OnDifficulty0()
{
	// TODO: 在此添加命令处理程序代码
	//初级难度
	difficulty=0;
}

void CFiveInARowView::On32777()
{
	// TODO: 在此添加命令处理程序代码
	//中级难度
	difficulty=1;
}

void CFiveInARowView::OnDifficulty2()
{
	// TODO: 在此添加命令处理程序代码
	//高级难度
	difficulty=2;
}

void CFiveInARowView::OnChangeFirst()
{
	// TODO: 在此添加命令处理程序代码
	int temp;
	temp=player1;
	player1=player2;
	player2=temp;
	player=1;
	initial(pieces);
}


void CFiveInARowView::OnEditUndo()
{
	// TODO: 在此添加命令处理程序代码
	if(count<=10)
	{
		pieces[tempsave[BUFF-1].y][tempsave[BUFF-1].x]=0;
		pieces[tempsave[BUFF-2].y][tempsave[BUFF-2].x]=0;
		for(int i=BUFF-3;i>=0;i--)
		{
			tempsave[i+2]=tempsave[i];
		}
		count++;
		AllDisplay();
	}
	else
	{
		MessageBox("本局已经无法撤销！");
	}
}
