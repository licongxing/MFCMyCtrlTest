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
	CMyListWnd(CString strfontFamily = _T("����"));
	virtual ~CMyListWnd();
public:
	// ��ʼ�б�����
	void FillFileData();
	void AddFile(CString filePath);
	void DelFile(CString filePath);
	void RefreshList();
private:
	// �ж�point�Ƿ���item�İ�ť��
	BOOL PointInItem(CPoint point,CMyListItem &item/*out*/,int &btnIndex/*out*/); 

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg LRESULT ButtonPressed(WPARAM w, LPARAM l);

	// ���������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );


	DECLARE_MESSAGE_MAP()

private:
	UINT m_iTotalDrawHeight; // �ܸ߶�
	UINT m_iDrawHeight; // �������ݵĸ߶�
	int m_iDrawOffset; // �п���Ϊ������
	UINT m_iItemHeight; // ����ÿһ��ĸ߶�

	CRect m_rectScroll;
	BOOL m_bDrawScroll;	// �Ƿ񻭹�����
	BOOL m_bClickScroll;// �Ƿ�ס������
	POINT m_MousePoint;	// ��ǰ���λ��
	BOOL m_bTracking; // �Ƿ��õĹ���



	UINT m_iWndWidth;
	UINT m_iWndHeight;
	CString m_strfontFamily;

	std::list<CString> m_fileList;
	std::list<CMyListItem> m_Items;
};


