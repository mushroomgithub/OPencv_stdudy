// TestMutiDocView.h : interface of the CTestMutiDocView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTMUTIDOCVIEW_H__38522A3E_75FE_42E8_90C0_D273E7A26FBB__INCLUDED_)
#define AFX_TESTMUTIDOCVIEW_H__38522A3E_75FE_42E8_90C0_D273E7A26FBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestMutiDocView : public CView
{
protected: // create from serialization only
	CTestMutiDocView();
	DECLARE_DYNCREATE(CTestMutiDocView)

// Attributes
public:
	CTestMutiDocDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestMutiDocView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestMutiDocView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestMutiDocView)
	afx_msg void OnFileClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestMutiDocView.cpp
inline CTestMutiDocDoc* CTestMutiDocView::GetDocument()
   { return (CTestMutiDocDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMUTIDOCVIEW_H__38522A3E_75FE_42E8_90C0_D273E7A26FBB__INCLUDED_)
