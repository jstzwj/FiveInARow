
// FiveInARowView.h : CFiveInARowView ��Ľӿ�
//
#pragma once

extern int pieces[HEIGHT+2][WIDTH+2];
extern int player1;//0��ʾ��
extern int player2;//1��ʾ����
extern int player;
extern struct point location;//����λ��
class CFiveInARowView : public CView
{
protected: // �������л�����
	CFiveInARowView();
	DECLARE_DYNCREATE(CFiveInARowView)

// ����
public:
	CFiveInARowDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CFiveInARowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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
	//����ÿһ��λ�õ����ȼ�
	//���룺���������������
	//���أ��������ӵ�λ��
	struct point analysis(const int pieces[][WIDTH+2]);

	//��ʼ����������
	//�������������������
	//�޷���ֵ
	void initial(int pieces[][WIDTH+2]);

	//�ж�ĳ��λ�������
	//������������������飬��ǰλ��
	//���ظõ����ȼ�
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
	int count=0;//��������
};

#ifndef _DEBUG  // FiveInARowView.cpp �еĵ��԰汾
inline CFiveInARowDoc* CFiveInARowView::GetDocument() const
   { return reinterpret_cast<CFiveInARowDoc*>(m_pDocument); }
#endif

