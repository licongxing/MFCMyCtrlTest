
// MFCMyCtrlTestDlg.h : 头文件
//

#pragma once
#include "MyListWnd.h"
#include <list>

typedef struct CMyWnd
{
	int m_index;
	UINT m_nID;
	CWnd* m_wnd;
}CMyWnd;
// CMFCMyCtrlTestDlg 对话框
class CMFCMyCtrlTestDlg : public CDialogEx
{
// 构造
public:
	CMFCMyCtrlTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCMYCTRLTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


private:
	std::list<CMyWnd> m_listWnd;
	CString m_strfontFamily;
private:
	void ShowOneWnd(int index);
public:
	afx_msg void OnBnClickedBtnShowmylist();
};
