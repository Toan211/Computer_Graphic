
// OPENCV_GUIDoc.cpp : implementation of the COPENCVGUIDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OPENCV_GUI.h"
#endif

#include "OPENCV_GUIDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COPENCVGUIDoc

IMPLEMENT_DYNCREATE(COPENCVGUIDoc, CDocument)

BEGIN_MESSAGE_MAP(COPENCVGUIDoc, CDocument)
END_MESSAGE_MAP()


// COPENCVGUIDoc construction/destruction

COPENCVGUIDoc::COPENCVGUIDoc() noexcept
{
	// TODO: add one-time construction code here

	//lab 6
	m_pBmi = NULL;
	//endl6
}


COPENCVGUIDoc::~COPENCVGUIDoc()
{
	
}

//lab7


CView* COPENCVGUIDoc::GetCurrentActiveView()
{
	POSITION pos = GetFirstViewPosition();
	CView* pView = GetNextView(pos);
	return pView;
}

/*
	Nguyên lý quay góc 90 độ đó là:
		Xác định điểm gốc để quay,
		điểm quay là được tính là điểm trung tâm của tấm ảnh
			==> quay xung quanh tấm ảnh

	Sau đó sử dụng hàm getRotationMatrix2D
		Đối số truyền vào là : 
			điểm quay, giá trị góc quay, và tỉ lệ (để mặc định là 1.0)
	Sau đó lấy kết quả được trả ra
		và gán lại vào biến m_Mat  
		rồi chuyển sang update view để hiện thị kết quả.
	*/
void COPENCVGUIDoc::RotateLeft()
{
	cv::Mat src = m_Mat;
	cv::Mat dst;
	cv::Point2f pt(src.cols / 2., src.rows / 2.); //center
	

	cv::Mat r = getRotationMatrix2D(pt, 90.0, 1.0);
	warpAffine(src, dst, r, cv::Size(src.cols, src.rows));
	m_Mat.release();
	m_Mat = dst.clone();
	dst.release();
	if (GetCurrentActiveView())
	{
		GetCurrentActiveView()->InvalidateRect(NULL);
	}
	
}

void COPENCVGUIDoc::RotateRight()
{
	cv::Mat src = m_Mat;
	cv::Mat dst;
	cv::Point2f pt(src.cols / 2., src.rows / 2.);

	cv::Mat r = getRotationMatrix2D(pt, -90.0, 1.0);
	warpAffine(src, dst, r, cv::Size(src.cols, src.rows));
	m_Mat.release();
	m_Mat = dst.clone();
	dst.release();
	if (GetCurrentActiveView())
	{
		GetCurrentActiveView()->InvalidateRect(NULL);
	}
}

/*
Xử lý cho việc mirror rất đơn giản, chỉ cần gọi hàm cv::flip là xong.
	Các tham số của hàm flip thể hiện ý nghĩa như sau:

		Đối số 1:  src   // dữ liệu ảnh gốc
		Đối số 2:  dst   // dữ liệu ảnh kết quả cùng size với src
		Đối số 3: cờ flip code để chỉ định kiểu flip

	flipCode bằng 0 -> thực hiện flip xung quanh trục x (trục x nằm ngang, nên sẽ hiểu là mirror dọc)
	flipCode bằng  giá trị dương ví dụ như 1 thì sẽ flip ảnh quanh trục y (trục y nằm dọc sẽ hiểu là mirror ngang)
	flipCode bằng  giá trị âm (ví dụ -1) thì sẽ flip theo cả hai chiều
	*/
void  COPENCVGUIDoc::MirrorHorizontal()
{
	cv::Mat src1 = m_Mat;
	cv::Mat src2;
	cv::flip(src1, src2, 1);
	m_Mat = src2;

	if (GetCurrentActiveView())
	{
		GetCurrentActiveView()->InvalidateRect(NULL);
	}
}

	/*
	Về cơ bản việc xử lý độ sáng của ảnh
		sẽ được thông qua hàm convertTo của lớp cv::Mat

	Đối số cuối cùng của hàm này
		là đối số dành cho độ sáng tối,
		và ta truyền giá trị setting trên dialog vào đối số này.
	*/
void COPENCVGUIDoc::AdjustLight(float val)
{
	cv::Mat mat_change;
	m_Mat.convertTo(mat_change, -1, 1, val);
	m_Mat = mat_change;

	if (GetCurrentActiveView())
	{
		GetCurrentActiveView()->InvalidateRect(NULL);
	}
}

//endlab7

BOOL COPENCVGUIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

//lab6
BOOL COPENCVGUIDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	//Start load image by opencv
	cv::String nameStr = CT2A(lpszPathName);
	if (!m_Video.open(nameStr))
		return FALSE;

	//Check image or video
	if (m_Video.get(CV_CAP_PROP_FRAME_COUNT) < 2)
	{
		//::PostMessage(pView->GetSafeHwnd(), WMU_SETFPS, 0, 0);
		m_Mat.release();
		m_Mat = cv::imread(nameStr);
		//lab6 up
		//fix black white error
		ResizeMat(m_Mat);
		//endlab6 up
		SetupBitmapInfo(m_Mat);
	}
	return TRUE;

}
//endl6


// COPENCVGUIDoc serialization

void COPENCVGUIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void COPENCVGUIDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void COPENCVGUIDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void COPENCVGUIDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// COPENCVGUIDoc diagnostics

#ifdef _DEBUG
void COPENCVGUIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COPENCVGUIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COPENCVGUIDoc commands

void COPENCVGUIDoc::SetupBitmapInfo(cv::Mat& mat, const int& bitCount /*=24*/)
{
	if (NULL != m_pBmi)
	{
		delete m_pBmi;
		m_pBmi = NULL;
	}
	m_pBmi = new BITMAPINFO;
	BITMAPINFOHEADER* pHeader = &m_pBmi->bmiHeader;
	pHeader->biSize = sizeof(BITMAPINFOHEADER);
	pHeader->biPlanes = 1;
	pHeader->biCompression = BI_RGB;
	pHeader->biXPelsPerMeter = 100;
	pHeader->biYPelsPerMeter = 100;
	pHeader->biClrUsed = 0;
	pHeader->biClrImportant = 0;
	pHeader->biWidth = m_Mat.cols;
	pHeader->biHeight = -m_Mat.rows;
	pHeader->biBitCount = bitCount;
	m_pBmi->bmiHeader.biSizeImage = 0;
}
