
// Registration.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRegistration_App:
// See Registration.cpp for the implementation of this class
//

class CRegistration_App : public CWinApp
{
public:
	CRegistration_App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRegistration_App theApp;
