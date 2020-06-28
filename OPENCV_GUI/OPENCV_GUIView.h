
// OPENCV_GUIView.h : interface of the COPENCVGUIView class
//

#pragma once


class COPENCVGUIView : public CView
{
protected: // create from serialization only
	COPENCVGUIView() noexcept;
	DECLARE_DYNCREATE(COPENCVGUIView)

// Attributes
public:
	COPENCVGUIDoc* GetDocument() const;

	//lab6
	void RenderImage(COPENCVGUIDoc* pDoc, CDC* pDC);
	//endl6

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~COPENCVGUIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//lab6 up
	CBrush m_brush;
	//endl6 up
// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OPENCV_GUIView.cpp
inline COPENCVGUIDoc* COPENCVGUIView::GetDocument() const
   { return reinterpret_cast<COPENCVGUIDoc*>(m_pDocument); }
#endif

