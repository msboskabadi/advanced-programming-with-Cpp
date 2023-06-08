// SimpleSocket.h : main header file for the SimpleSocket application
//

#if !defined(AFX_SimpleSocket_H__4CADC9C8_6763_11D7_ADFE_EC624CEC9037__INCLUDED_)
#define AFX_SimpleSocket_H__4CADC9C8_6763_11D7_ADFE_EC624CEC9037__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// SimpleSocketApp:
// See SimpleSocket.cpp for the implementation of this class
//

class SimpleSocketApp : public CWinApp
{
public:
	SimpleSocketApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SimpleSocketApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(SimpleSocketApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SimpleSocket_H__4CADC9C8_6763_11D7_ADFE_EC624CEC9037__INCLUDED_)
