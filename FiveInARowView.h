
// FiveInARowView.h : CFiveInARowView 类的接口
//
#pragma once

extern int pieces[HEIGHT+2][WIDTH+2];
extern int player1;//0表示人
extern int player2;//1表示电脑
extern int player;
extern struct point location;//棋子位置
class CFiveInARowView : public CView
{
protected: // 仅从序列化创建
	CFiveInARowView();
	DECLARE_DYNCREATE(CFiveInARowView)

// 特性
public:
	CFiveInARowDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CFiveInARowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	int AllDisplay(void);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	int Display(int x, int y);
	int WinJudge(int i, int j);
	/*
	//分析每一个位置的优先级
	//读入：棋盘棋子情况数组
	//返回：电脑落子的位置
	struct point analysis(const int pieces[][WIDTH+2]);

	//初始化棋盘数组
	//读入棋盘棋子情况数组
	//无返回值
	void initial(int pieces[][WIDTH+2]);

	//判断某空位四周情况
	//读入棋盘棋子情况数组，当前位置
	//返回该点优先级
	int situation(const int pieces[][WIDTH+2],int height,int width);
	*/
	struct point analysis(int pieces[][WIDTH+2]);
	int situation(int pieces[][WIDTH+2],int height,int width);
	void initial(int pieces[][WIDTH+2]);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int player_computer1(void);
	int SaveInFile(void);
	int ReadFromFile(void);
	afx_msg void OnFileNew();
//	afx_msg void OnFileOpen();
	int player_computer2(void);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	int click(int i, int j);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnModeSet();
	afx_msg void OnMode0();
	afx_msg void OnMode1();
	afx_msg void OnMode2();
	struct point analysis2(const int pieces[][WIDTH+2]);
	struct point analysis3(int pieces[][WIDTH+2]);
	int analysis_2(int pieces[][WIDTH+2]);
	afx_msg void OnDifficulty0();
	afx_msg void OnDifficulty2();
	afx_msg void On32777();
	afx_msg void OnChangeFirst();
	afx_msg void OnEditUndo();
private:
	int count=0;//撤销计数
};

#ifndef _DEBUG  // FiveInARowView.cpp 中的调试版本
inline CFiveInARowDoc* CFiveInARowView::GetDocument() const
   { return reinterpret_cast<CFiveInARowDoc*>(m_pDocument); }
#endif

