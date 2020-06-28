
// OPENCV_GUIView.cpp : implementation of the COPENCVGUIView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OPENCV_GUI.h"
#endif

#include "OPENCV_GUIDoc.h"
#include "OPENCV_GUIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COPENCVGUIView

IMPLEMENT_DYNCREATE(COPENCVGUIView, CView)

BEGIN_MESSAGE_MAP(COPENCVGUIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COPENCVGUIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// COPENCVGUIView construction/destruction

COPENCVGUIView::COPENCVGUIView() noexcept
{
	// TODO: add construction code here

}

COPENCVGUIView::~COPENCVGUIView()
{
    //lab6 up
    if (NULL != m_brush.GetSafeHandle())
        m_brush.DeleteObject();
    //endlab 6 up 
}

BOOL COPENCVGUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COPENCVGUIView drawing

// void COPENCVGUIView::OnDraw(CDC* /*pDC*/) trc khi làm lab 6, pDC còn trong cmt
void COPENCVGUIView::OnDraw(CDC* pDC)
{
	COPENCVGUIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
    //lab 6
    RenderImage(pDoc, pDC);  // gọi hàm RenderImage tại đây
    //endlab 6

	// TODO: add draw code for native data here
}


// COPENCVGUIView printing


void COPENCVGUIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COPENCVGUIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COPENCVGUIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COPENCVGUIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void COPENCVGUIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COPENCVGUIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COPENCVGUIView diagnostics

#ifdef _DEBUG
void COPENCVGUIView::AssertValid() const
{
	CView::AssertValid();
}

void COPENCVGUIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COPENCVGUIDoc* COPENCVGUIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COPENCVGUIDoc)));
	return (COPENCVGUIDoc*)m_pDocument;
}
#endif //_DEBUG


// COPENCVGUIView message handlers
//lab6
void COPENCVGUIView::RenderImage(COPENCVGUIDoc* pDoc, CDC* pDC)
{
    if (pDoc)
    {
        //......................block 1.............. 
                //khối xử lý thiết lập môi trường bitmap cho view, để hiện thị được hình ảnh cho view//

        CRect rectClient;
        GetClientRect(&rectClient);

        CDC memDC;
        memDC.CreateCompatibleDC(pDC);

        CBitmap bmpMem;
        bmpMem.CreateCompatibleBitmap(pDC, rectClient.Width(), rectClient.Height());

        CBitmap* pOldBitmap = memDC.SelectObject(&bmpMem);
       

        //lab6 up
        // Create grid background for document
        if (NULL == m_brush.GetSafeHandle())
        {
            m_brush.CreateHatchBrush(HS_DIAGCROSS, RGB(190, 190, 190));
        }
        CBrush* pOldBrush = memDC.SelectObject(&m_brush);
        memDC.PatBlt(0, 0, rectClient.right, rectClient.bottom, PATCOPY);
        //endlab6 up
        
        /////////////////////////////////////////////////////////


        //......................block 2..............
                    //lấy liệu hình ảnh đọc được từ opencv thông qua biến : pDoc->m_Mat

        //Insert image into document
        const int cx = rectClient.right;                // view client area width;
        const int cy = rectClient.bottom;                // view client area height;

        const int bx = pDoc->m_Mat.cols;                // source bitmap width;
        const int by = pDoc->m_Mat.rows;                // source bitmap height;

        const int vx = (int)((double)bx);// virtual document width;
        const int vy = (int)((double)by);// virtual document height;

        int xSrc = 0;
        int ySrc = 0;
        int nSrcWidth = bx;
        int nSrcHeight = by;
        int xDst = 0;
        int yDst = 0;
        int nDstWidth = vx;
        int nDstHeight = vy;
        /////////////////////////////////////////////////////

        //..............................block3....................
                       //thực hiện việc đẩy dữ liệu trong m_Mat vào môi trường đồ họa của MFC thông qua hàm StretchDIBits

        memDC.SetStretchBltMode(COLORONCOLOR);
        StretchDIBits(memDC.m_hDC, xDst, yDst, nDstWidth, nDstHeight,
            0, 0, nSrcWidth, nSrcHeight, pDoc->m_Mat.data,
            pDoc->m_pBmi, DIB_RGB_COLORS, SRCCOPY);

        pDC->BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &memDC, 0, 0, SRCCOPY);
        memDC.SelectObject(pOldBitmap);
        bmpMem.DeleteObject();
        /////////////////////////////////////////////////////////////////
    }
}
//endlab6