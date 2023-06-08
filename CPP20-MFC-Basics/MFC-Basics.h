
// MFC-Basics.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasicsApp:
// See MFC-Basics.cpp for the implementation of this class
//

class CMFCBasicsApp : public CWinApp
{
public:
	CMFCBasicsApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasicsApp theApp;
