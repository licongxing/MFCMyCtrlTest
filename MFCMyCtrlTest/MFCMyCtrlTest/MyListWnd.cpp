// LabelWnd.cpp : 实现文件
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
	// 获取文件大小，播放时间长短
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

	int btnRight = 20; // 最右边按钮距离容器右边框距离
	int btnTop = 3;    // 按钮距离每行上边的距离
	int btnJianGe = 5;
	int btnWidth = 30,btnHeight = 24; // item 高为30

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
		item.m_strBtn1 = _T("复制");
		item.m_strBtn2 = _T("删除");
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

// 这里需要自己添加！！！
BEGIN_MESSAGE_MAP(CMyListWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()

	// 滚动条相关都有用到
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()

	// 设置鼠标手
	ON_WM_SETCURSOR()

END_MESSAGE_MAP()



// CMyListWnd 消息处理程序


/*
当应用程序通过调用成员函数Create或CreateEx请求创建Windows的窗口时，框架调用这个成员函数。
OnCreate是在Create或CreateEx成员函数返回之前被调用的。
重载这个成员函数以执行派生类所需的初始化工作。
CREATESTRUCT结构中包含了用于创建窗口的参数的拷贝。
*/
int CMyListWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_iWndWidth = lpCreateStruct->cx;
	m_iWndHeight = lpCreateStruct->cy;
	m_iTotalDrawHeight = m_iWndHeight;
	//m_strfontFamily = _T("宋体");//_T("微软雅黑");
	FillFileData();
	RefreshList();

	return 0;
}

/*
当CWnd对象的背景需要被擦除时（例如，当窗口大小被改变时），框架就调用这个函数。它被调用以便为绘图准备无效区域。
如果重载的OnEraseBkgnd在响应WM_ERASEBKGND时处理了这个消息并擦除了背景，则应当返回非零值，表明不需要进一步擦除。(实际上就是在这里可以绘图，并且返回TRUE)
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
	//设置字体相关
	FontFamily fontFamily( m_strfontFamily );
	Gdiplus::Font fontRegular( &fontFamily, 13, FontStyleRegular,UnitPixel );
	Gdiplus::Font fontRegular2( &fontFamily, 12, FontStyleRegular,UnitPixel );

	StringFormat sf,sf2;
	sf.SetAlignment(StringAlignmentNear);
	sf.SetLineAlignment( StringAlignmentCenter );

	// 居中
	sf2.SetAlignment(StringAlignmentCenter);
	sf2.SetLineAlignment( StringAlignmentCenter );

	graph.FillRectangle( &solidBrushWhite, -1, -1, m_iWndWidth+1, m_iTotalDrawHeight+1 );
	


	// 每行高30
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
	int btnRight = 20; // 最右边按钮距离容器右边框距离
	int btnTop = 3;    // 按钮距离每行上边的距离
	int btnJianGe = 5;
	int btnWidth = 30,btnHeight = 24; // item 高为30
	for(;it != m_Items.end(); it ++,i++)
	{
		UINT y = m_iItemHeight*(i);
		CString strtemp = it->m_strText;
		graph.DrawString( strtemp, strtemp.GetLength(), &fontRegular, it->m_rcRect, &sf, &solidBrushBlack );
		
		// 自己画 可以点击的按钮, 
		// 复制
		graph.FillRectangle( &solidBrushGray,it->m_rcBtn1);
		graph.DrawString( it->m_strBtn1, it->m_strBtn1.GetLength(), &fontRegular2, it->m_rcBtn1,&sf2, &solidBrushBlack);
		// 删除
		graph.FillRectangle( &solidBrushGray, it->m_rcBtn2 );
		graph.DrawString( it->m_strBtn2, it->m_strBtn2.GetLength(), &fontRegular2, it->m_rcBtn2,&sf2, &solidBrushBlack);
	}
	

	int scrollWidth = 15;// 滚动条背景宽度
	// 滑动条
	if ( m_iDrawHeight > m_iWndHeight )
	{
		m_bDrawScroll = TRUE;
		SolidBrush solidbrushGray( Color( 150,150,150) );
		Pen penBroder( Color(180,180,180), 1.0 );

		// 画滚动条背景
		graph.FillRectangle( &solidBrushWhite, m_iWndWidth-scrollWidth, m_iDrawOffset, scrollWidth, m_iWndHeight  ); // 填滑动条背景色
		graph.DrawRectangle( &penBroder, m_iWndWidth-scrollWidth, m_iDrawOffset+1, scrollWidth-1, m_iWndHeight-2 ); // 画滑动条边框

		// 计算滚动块大小位置
		double dDate = (double)m_iWndHeight/(double)m_iDrawHeight;
		int nScroll = int(m_iWndHeight*dDate); // 滑块高度

		SolidBrush solidbrushScroll( Color( 200,200,200) );
		Pen pen( Color( 0,0,0 ) );
		// 画滑块
		graph.FillRectangle( &solidbrushScroll, m_iWndWidth-scrollWidth, m_iDrawOffset+(INT)(m_iDrawOffset*dDate), scrollWidth, nScroll ); // 填充滑块颜色
		int mid = m_iDrawOffset+(INT)(m_iDrawOffset*dDate)+nScroll/2;  
		//graph.DrawLine( &pen, m_iWndWidth-7, mid-4, m_iWndWidth-3, mid-4 );
		//graph.DrawLine( &pen, m_iWndWidth-8, mid, m_iWndWidth-2, mid );
		//graph.DrawLine( &pen, m_iWndWidth-7, mid+4, m_iWndWidth-3, mid+4  );
		graph.DrawRectangle( &penBroder, m_iWndWidth-scrollWidth, m_iDrawOffset+1+(INT)(m_iDrawOffset*dDate), scrollWidth-1, nScroll-2 ); // 画滑块边框

		// 滑块矩形设置
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
当Windows或应用程序请求重画应用程序窗口的一部分时，框架调用这个成员函数。
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
		// 可以在这里写，判断点击到某个文件 之后的逻辑
		CMyListItem item;
		int btnIndex = 0;
		BOOL bRet = PointInItem(point,item,btnIndex);
		if(bRet)
		{
			if(btnIndex == 1 )
			{
				// 复制文件
				//MessageBox(item.m_strText,_T("复制"));
				CString strTemp;
				strTemp.Format(_T("%s-副本"),item.m_strText);
				AddFile(strTemp);
				RefreshList();
			}
			else if(btnIndex == 2 )
			{
				// 删除
				//MessageBox(item.m_strText,_T("删除"));
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
	{//向下滚动
		m_iDrawOffset += m_iItemHeight*3; // 一次性滑动3个
	}
	if(zDelta>=120)
	{//向上滚动
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
		tme.dwFlags = TME_LEAVE | TME_HOVER;//要触发的消息;
		tme.hwndTrack = this->m_hWnd;
		tme.dwHoverTime = 10;// 若不设此参数，则无法触发mouseHover;

		if (::_TrackMouseEvent(&tme)) //MOUSELEAVE|MOUSEHOVER消息由此函数触发
		{
			m_bTracking = TRUE;   
		}
	}
	if ( m_bClickScroll )
	{
		if ( point.y > m_MousePoint.y )
		{
			//向下
			int nMove = point.y-m_MousePoint.y;//鼠标移动了的像素
			float f = (float)m_iTotalDrawHeight/(float)m_iWndHeight; 
			m_iDrawOffset += (int)(nMove * f);
		}
		else if(point.y == m_MousePoint.y)
		{
			return;
		}
		else
		{
			//向上
			int nMove = m_MousePoint.y- point.y;//鼠标移动了的像素
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
		// 普通移动
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
