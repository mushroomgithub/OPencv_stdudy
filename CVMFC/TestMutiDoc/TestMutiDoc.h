// TestMutiDoc.h : main header file for the TESTMUTIDOC application
//

#if !defined(AFX_TESTMUTIDOC_H__B129A240_4FBB_4B43_A734_81F00F831E9E__INCLUDED_)
#define AFX_TESTMUTIDOC_H__B129A240_4FBB_4B43_A734_81F00F831E9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestMutiDocApp:
// See TestMutiDoc.cpp for the implementation of this class
//

class CTestMutiDocApp : public CWinApp
{
public:
	CTestMutiDocApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestMutiDocApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTestMutiDocApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMUTIDOC_H__B129A240_4FBB_4B43_A734_81F00F831E9E__INCLUDED_)
