
// OPENCV_GUI.h : main header file for the OPENCV_GUI application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// OPENCVGUI_App:
// See OPENCV_GUI.cpp for the implementation of this class
//

class OPENCVGUI_App : public CWinAppEx
{
public:
	OPENCVGUI_App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern OPENCVGUI_App theApp;
