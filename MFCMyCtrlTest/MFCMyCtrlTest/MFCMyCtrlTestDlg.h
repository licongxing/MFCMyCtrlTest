
// MFCMyCtrlTestDlg.h : ͷ�ļ�
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
// CMFCMyCtrlTestDlg �Ի���
class CMFCMyCtrlTestDlg : public CDialogEx
{
// ����
public:
	CMFCMyCtrlTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCMYCTRLTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
