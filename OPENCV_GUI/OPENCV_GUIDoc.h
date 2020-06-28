
// OPENCV_GUIDoc.h : interface of the COPENCVGUIDoc class
//


#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <opencv2/imgproc/imgproc.hpp>

class COPENCVGUIDoc : public CDocument
{
protected: // create from serialization only
	COPENCVGUIDoc() noexcept;
	DECLARE_DYNCREATE(COPENCVGUIDoc)

// Attributes

	//lab 6
protected:
	cv::VideoCapture m_Video; // Quản lý xem file đọc vào là ảnh hay video
	// Attributes

	//endlab 6
public:
	//lab6 up

	//fix black white image error
	void COPENCVGUIDoc::ResizeMat(cv::Mat& mat)
	{
		int nPadding = 0;
		if (CV_8UC4 != mat.type())
		{
			// padding is not needed for 32bit images
			nPadding = 4 - (mat.cols % 4);
			if (4 == nPadding)
				nPadding = 0;
		}

		cv::Mat matTemp;
		if (nPadding > 0 || !mat.isContinuous())
		{
			// Adding needed columns on the right (max 3px)
			cv::copyMakeBorder(mat, matTemp, 0, 0, 0, nPadding, cv::BORDER_REPLICATE, 0);
			mat = matTemp;
		}
	}
	//endlab6 up

public:
	//lab7
	CView* GetCurrentActiveView();
	void RotateLeft();
	void RotateRight();
	
	void MirrorHorizontal();

	void AdjustLight(float val);

	//endlab7
public:

	//lab 6
	BOOL m_bErase;
	BITMAPINFO* m_pBmi; // Quản lý dữ liệu ảnh xuất ra file
	cv::Mat m_Mat; // Quản lý việc đọc ảnh từ opencv
	//endl 6


// Overrides
public:
	virtual BOOL OnNewDocument();

	//lab 6
	BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//endl6

	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	//lab6
	void SetupBitmapInfo(cv::Mat& mat, const int& bitCount = 24);  // dinh nghia ham setupBitmapInfo


	////endl6
// Implementation
public:
	virtual ~COPENCVGUIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

