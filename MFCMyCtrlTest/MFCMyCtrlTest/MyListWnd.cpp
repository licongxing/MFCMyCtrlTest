// LabelWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyListWnd.h"

// CMyListWnd

IMPLEMENT_DYNAMIC(CMyListWnd, CWnd)

CMyListWnd::CMyListWnd(CString strfontFamily)
{
	m_strfontFamily = strfontFamily;
	m_iItemHeight = 30;
	m_iDrawOffset = 0;
	m_bTracking= FALSE;
	m_bDrawScroll = FALSE;
	m_bClickScroll = FALSE;
	m_iDrawOffset = 0;
	m_iDrawHeight = 0;
}

CMyListWnd::~CMyListWnd()
{
}


void CMyListWnd::FillFileData()
{
	m_fileList.push_back(_T("1234567.mp4"));
	m_fileList.push_back(_T("1234568.mp4"));
	m_fileList.push_back(_T("1234569.mp4"));
	m_fileList.push_back(_T("1234563.mp4"));
	m_fileList.push_back(_T("1234562.mp4"));
}

void CMyListWnd::AddFile(CString filePath)
{
	// ��ȡ�ļ���С������ʱ�䳤��
	m_fileList.push_back(filePath);
}

void CMyListWnd::DelFile(CString filePath)
{
	std::list<CString>::iterator it = m_fileList.begin();
	for( ; it != m_fileList.end(); )
	{
		if(it->CompareNoCase(filePath) == 0)
		{
			it = m_fileList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void CMyListWnd::RefreshList()
{
	m_Items.clear(); 

	int btnRight = 20; // ���ұ߰�ť���������ұ߿����
	int btnTop = 3;    // ��ť����ÿ���ϱߵľ���
	int btnJianGe = 5;
	int btnWidth = 30,btnHeight = 24; // item ��Ϊ30

	UINT y = 0,j=0;
	std::list<CString>:: iterator it2 = m_fileList.begin();
	for( ; it2 != m_fileList.end() ; it2++,j++)
	{
		y = m_iItemHeight * j;
		CMyListItem item;
		CString filePath = *it2;
		TCHAR c = '\\';
		int index = filePath.ReverseFind(c);
		item.m_strText = filePath.Right(filePath.GetLength()-index-1);
		item.m_strBtn1 = _T("����");
		item.m_strBtn2 = _T("ɾ��");
		item.m_rcRect = RectF( 5, y,  200, m_iItemHeight );
		item.m_rcBtn1 = RectF( m_iWndWidth-btnWidth*2-btnJianGe-btnRight, y+btnTop,  btnWidth, btnHeight ) ;
		item.m_rcBtn2 = RectF( m_iWndWidth-btnWidth -btnRight, y+btnTop,  btnWidth, btnHeight );

		m_Items.push_back(item);
	}
	m_iTotalDrawHeight = m_fileList.size() * m_iItemHeight;
	Invalidate();
}

BOOL CMyListWnd::PointInItem(CPoint point,CMyListItem &item/*out*/,int &btnIndex/*out*/)
{
	int i = 0;
	std::list<CMyListItem>::iterator it = m_Items.begin();

	const PointF p(point.x,point.y);
	btnIndex = 0;
	for(;it != m_Items.end(); it ++,i++)
	{
		UINT y = m_iItemHeight*(i);
		if(it->m_rcBtn1.Contains(p))
		{
			btnIndex = 1;
			item = *it;
			return TRUE;
		}
		else if(it->m_rcBtn2.Contains(p))
		{
			btnIndex = 2;
			item = *it;
			return TRUE;
		}
	}
	return FALSE;
}

// ������Ҫ�Լ���ӣ�����
BEGIN_MESSAGE_MAP(CMyListWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()

	// ��������ض����õ�
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()

	// ���������
	ON_WM_SETCURSOR()

END_MESSAGE_MAP()



// CMyListWnd ��Ϣ�������


/*
��Ӧ�ó���ͨ�����ó�Ա����Create��CreateEx���󴴽�Windows�Ĵ���ʱ����ܵ��������Ա������
OnCreate����Create��CreateEx��Ա��������֮ǰ�����õġ�
���������Ա������ִ������������ĳ�ʼ��������
CREATESTRUCT�ṹ�а��������ڴ������ڵĲ����Ŀ�����
*/
int CMyListWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_iWndWidth = lpCreateStruct->cx;
	m_iWndHeight = lpCreateStruct->cy;
	m_iTotalDrawHeight = m_iWndHeight;
	//m_strfontFamily = _T("����");//_T("΢���ź�");
	FillFileData();
	RefreshList();

	return 0;
}

/*
��CWnd����ı�����Ҫ������ʱ�����磬�����ڴ�С���ı�ʱ������ܾ͵���������������������Ա�Ϊ��ͼ׼����Ч����
������ص�OnEraseBkgnd����ӦWM_ERASEBKGNDʱ�����������Ϣ�������˱�������Ӧ�����ط���ֵ����������Ҫ��һ��������(ʵ���Ͼ�����������Ի�ͼ�����ҷ���TRUE)
*/
BOOL CMyListWnd::OnEraseBkgnd(CDC* pDC)
{
	HDC hMemDC = CreateCompatibleDC( pDC->m_hDC ); 
	
	if(m_iTotalDrawHeight<m_iWndHeight) m_iTotalDrawHeight=m_iWndHeight;

	HBITMAP hMemBitmap = CreateCompatibleBitmap( pDC->m_hDC, m_iWndWidth, m_iTotalDrawHeight);  
	SelectObject(hMemDC, hMemBitmap); 

	Graphics graph( hMemDC );
	//graph.SetSmoothingMode(SmoothingModeHighQuality);
	//graph.SetTextRenderingHint( TextRenderingHintAntiAliasGridFit );
	graph.SetSmoothingMode(SmoothingModeAntiAlias);
	graph.SetTextRenderingHint( TextRenderingHintClearTypeGridFit );


	SolidBrush solidBrushBlack( Color(250,0,0,0) );
	SolidBrush solidBrushBlack2( Color( 200,240,240,240) );
	SolidBrush solidBrushGray( Color( 255,225,225,225) );
	SolidBrush solidBrushWhite( Color(255,255,255,255) );
	SolidBrush solidBrushGrayText( Color( 250, 167, 167, 167 ) );
	//�����������
	FontFamily fontFamily( m_strfontFamily );
	Gdiplus::Font fontRegular( &fontFamily, 13, FontStyleRegular,UnitPixel );
	Gdiplus::Font fontRegular2( &fontFamily, 12, FontStyleRegular,UnitPixel );

	StringFormat sf,sf2;
	sf.SetAlignment(StringAlignmentNear);
	sf.SetLineAlignment( StringAlignmentCenter );

	// ����
	sf2.SetAlignment(StringAlignmentCenter);
	sf2.SetLineAlignment( StringAlignmentCenter );

	graph.FillRectangle( &solidBrushWhite, -1, -1, m_iWndWidth+1, m_iTotalDrawHeight+1 );
	


	// ÿ�и�30
	UINT nCount = m_iTotalDrawHeight/m_iItemHeight;
	for( UINT i = 0; i < nCount ; i++ )
	{
		UINT y = m_iItemHeight*(i);
		if ( i%2 != 0 )
		{
			graph.FillRectangle( &solidBrushBlack2, 0, y, m_iWndWidth, m_iItemHeight );
		}
	}

	m_iDrawHeight = m_Items.size() * m_iItemHeight;

	std::list<CMyListItem>::iterator it = m_Items.begin();
	UINT i = 0;
	int btnRight = 20; // ���ұ߰�ť���������ұ߿����
	int btnTop = 3;    // ��ť����ÿ���ϱߵľ���
	int btnJianGe = 5;
	int btnWidth = 30,btnHeight = 24; // item ��Ϊ30
	for(;it != m_Items.end(); it ++,i++)
	{
		UINT y = m_iItemHeight*(i);
		CString strtemp = it->m_strText;
		graph.DrawString( strtemp, strtemp.GetLength(), &fontRegular, it->m_rcRect, &sf, &solidBrushBlack );
		
		// �Լ��� ���Ե���İ�ť, 
		// ����
		graph.FillRectangle( &solidBrushGray,it->m_rcBtn1);
		graph.DrawString( it->m_strBtn1, it->m_strBtn1.GetLength(), &fontRegular2, it->m_rcBtn1,&sf2, &solidBrushBlack);
		// ɾ��
		graph.FillRectangle( &solidBrushGray, it->m_rcBtn2 );
		graph.DrawString( it->m_strBtn2, it->m_strBtn2.GetLength(), &fontRegular2, it->m_rcBtn2,&sf2, &solidBrushBlack);
	}
	

	int scrollWidth = 15;// �������������
	// ������
	if ( m_iDrawHeight > m_iWndHeight )
	{
		m_bDrawScroll = TRUE;
		SolidBrush solidbrushGray( Color( 150,150,150) );
		Pen penBroder( Color(180,180,180), 1.0 );

		// ������������
		graph.FillRectangle( &solidBrushWhite, m_iWndWidth-scrollWidth, m_iDrawOffset, scrollWidth, m_iWndHeight  ); // ���������ɫ
		graph.DrawRectangle( &penBroder, m_iWndWidth-scrollWidth, m_iDrawOffset+1, scrollWidth-1, m_iWndHeight-2 ); // ���������߿�

		// ����������Сλ��
		double dDate = (double)m_iWndHeight/(double)m_iDrawHeight;
		int nScroll = int(m_iWndHeight*dDate); // ����߶�

		SolidBrush solidbrushScroll( Color( 200,200,200) );
		Pen pen( Color( 0,0,0 ) );
		// ������
		graph.FillRectangle( &solidbrushScroll, m_iWndWidth-scrollWidth, m_iDrawOffset+(INT)(m_iDrawOffset*dDate), scrollWidth, nScroll ); // ��们����ɫ
		int mid = m_iDrawOffset+(INT)(m_iDrawOffset*dDate)+nScroll/2;  
		//graph.DrawLine( &pen, m_iWndWidth-7, mid-4, m_iWndWidth-3, mid-4 );
		//graph.DrawLine( &pen, m_iWndWidth-8, mid, m_iWndWidth-2, mid );
		//graph.DrawLine( &pen, m_iWndWidth-7, mid+4, m_iWndWidth-3, mid+4  );
		graph.DrawRectangle( &penBroder, m_iWndWidth-scrollWidth, m_iDrawOffset+1+(INT)(m_iDrawOffset*dDate), scrollWidth-1, nScroll-2 ); // ������߿�

		// �����������
		m_rectScroll.SetRect( m_iWndWidth-scrollWidth, (int)(m_iDrawOffset*dDate), m_iWndWidth, (int)(m_iDrawOffset*dDate)+nScroll  );
	}
	else 
	{
		m_bDrawScroll = FALSE;
		m_iDrawOffset = 0;
	}


	Pen pen( Color(255,0,0 ),1.0);
	graph.DrawRectangle( &pen, 1, 1, m_iWndWidth-2, m_iTotalDrawHeight-2 );

	DeleteObject(hMemBitmap);  
	//BitBlt( pDC->m_hDC, 0, 0, m_iWndWidth, m_iWndHeight, hMemDC, 0, 0, SRCCOPY);  
	BitBlt( pDC->m_hDC, -1, -1, m_iWndWidth+1, m_iWndHeight, hMemDC, 0, m_iDrawOffset, SRCCOPY ); 
	DeleteDC( hMemDC);
	return TRUE;
}
/*
��Windows��Ӧ�ó��������ػ�Ӧ�ó��򴰿ڵ�һ����ʱ����ܵ��������Ա������
*/
void CMyListWnd::OnPaint()
{
	CWnd::OnPaint();
}

LRESULT CMyListWnd::ButtonPressed(WPARAM w, LPARAM l)
{
	return 0;
}

void CMyListWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ( m_bDrawScroll )
	{
		if( m_rectScroll.PtInRect( point ) )
		{
			SetCapture();
			m_bClickScroll = TRUE;
			m_MousePoint= point;
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CMyListWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if ( m_bClickScroll )
	{
		m_bClickScroll = FALSE;
		ReleaseCapture();
		return CWnd::OnLButtonUp(nFlags, point);;
	}
	else
	{
		// ����������д���жϵ����ĳ���ļ� ֮����߼�
		CMyListItem item;
		int btnIndex = 0;
		BOOL bRet = PointInItem(point,item,btnIndex);
		if(bRet)
		{
			if(btnIndex == 1 )
			{
				// �����ļ�
				//MessageBox(item.m_strText,_T("����"));
				CString strTemp;
				strTemp.Format(_T("%s-����"),item.m_strText);
				AddFile(strTemp);
				RefreshList();
			}
			else if(btnIndex == 2 )
			{
				// ɾ��
				//MessageBox(item.m_strText,_T("ɾ��"));
				DelFile(item.m_strText);
				RefreshList();
			}
		}
	}
	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CMyListWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if(zDelta<=-120)
	{//���¹���
		m_iDrawOffset += m_iItemHeight*3; // һ���Ի���3��
	}
	if(zDelta>=120)
	{//���Ϲ���
		m_iDrawOffset -= m_iItemHeight*3;
	}
	if ( m_iDrawOffset <=0 )
		m_iDrawOffset = 0;
	else if ( m_iDrawOffset > m_iDrawHeight - m_iWndHeight )
	{
		m_iDrawOffset  = m_iDrawHeight - m_iWndHeight;
	}
	Invalidate();
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CMyListWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE | TME_HOVER;//Ҫ��������Ϣ;
		tme.hwndTrack = this->m_hWnd;
		tme.dwHoverTime = 10;// ������˲��������޷�����mouseHover;

		if (::_TrackMouseEvent(&tme)) //MOUSELEAVE|MOUSEHOVER��Ϣ�ɴ˺�������
		{
			m_bTracking = TRUE;   
		}
	}
	if ( m_bClickScroll )
	{
		if ( point.y > m_MousePoint.y )
		{
			//����
			int nMove = point.y-m_MousePoint.y;//����ƶ��˵�����
			float f = (float)m_iTotalDrawHeight/(float)m_iWndHeight; 
			m_iDrawOffset += (int)(nMove * f);
		}
		else if(point.y == m_MousePoint.y)
		{
			return;
		}
		else
		{
			//����
			int nMove = m_MousePoint.y- point.y;//����ƶ��˵�����
			float f = (float)m_iTotalDrawHeight/(float)m_iWndHeight; 
			m_iDrawOffset -= (int)(nMove * f);
		}
		if (m_iDrawOffset <0 )
		{
			m_iDrawOffset = 0;
		}
		else if ( m_iDrawOffset  > m_iTotalDrawHeight - m_iWndHeight )
		{
			m_iDrawOffset = m_iTotalDrawHeight-m_iWndHeight;
		}
		Invalidate();
		m_MousePoint = point;
	}
	else
	{
		// ��ͨ�ƶ�
		CMyListItem item;
		int btnIndex = 0;
		point.y += m_iDrawOffset;
		BOOL bRet = PointInItem(point,item,btnIndex);
		if(bRet)
		{
			HCURSOR hCur  =  LoadCursor( NULL  , IDC_HAND ) ;
			::SetCursor(hCur);
		}
		else
		{
			HCURSOR hCur  =  LoadCursor( NULL  , IDC_ARROW ) ;
			::SetCursor(hCur);
		}
	}
	CWnd::OnMouseMove(nFlags, point);
}

void CMyListWnd::OnMouseLeave()
{
	m_bTracking = FALSE;
	CWnd::OnMouseLeave();
}

void CMyListWnd::OnMouseHover(UINT nFlags, CPoint point)
{
	this->SetFocus();
	

	CWnd::OnMouseHover(nFlags, point);
}

BOOL CMyListWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CMyListItem item;
	int btnIndex = 0;
	CPoint point; 
	GetCursorPos(&point);
	CRect rect;
	GetWindowRect(&rect);

	CPoint point2;
	point2.x = point.x - rect.left ;
	point2.y = point.y - rect.top + m_iDrawOffset;
	BOOL bRet = PointInItem(point2,item,btnIndex);

	if(bRet)
	{
		HCURSOR hCur  =  LoadCursor( NULL  , IDC_HAND ) ;
		::SetCursor(hCur);
	}
	
	return TRUE;
}
