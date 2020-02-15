#pragma once

#include <list>

class CMyListItem
{
public:
	CMyListItem(){ }
public:
	CString m_strText;

	CString m_strBtn1;
	CString m_strBtn2;
	RectF m_rcRect;
	RectF m_rcBtn1;
	RectF m_rcBtn2;
};

// CMyListWnd

class CMyListWnd : public CWnd
{
	DECLARE_DYNAMIC(CMyListWnd)

public:
	CMyListWnd(CString strfontFamily = _T("宋体"));
	virtual ~CMyListWnd();
public:
	// 初始列表设置
	void FillFileData();
	void AddFile(CString filePath);
	void DelFile(CString filePath);
	void RefreshList();
private:
	// 判断point是否在item的按钮上
	BOOL PointInItem(CPoint point,CMyListItem &item/*out*/,int &btnIndex/*out*/); 

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg LRESULT ButtonPressed(WPARAM w, LPARAM l);

	// 滑动条相关
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );


	DECLARE_MESSAGE_MAP()

private:
	UINT m_iTotalDrawHeight; // 总高度
	UINT m_iDrawHeight; // 画的内容的高度
	int m_iDrawOffset; // 有可能为负数！
	UINT m_iItemHeight; // 画的每一项的高度

	CRect m_rectScroll;
	BOOL m_bDrawScroll;	// 是否画滚动条
	BOOL m_bClickScroll;// 是否按住滑动块
	POINT m_MousePoint;	// 当前鼠标位置
	BOOL m_bTracking; // 是否用的滚轮



	UINT m_iWndWidth;
	UINT m_iWndHeight;
	CString m_strfontFamily;

	std::list<CString> m_fileList;
	std::list<CMyListItem> m_Items;
};


