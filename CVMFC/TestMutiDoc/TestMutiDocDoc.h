// TestMutiDocDoc.h : interface of the CTestMutiDocDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTMUTIDOCDOC_H__4E806726_8EC8_46DF_8E6E_A4D6ADDE53F0__INCLUDED_)
#define AFX_TESTMUTIDOCDOC_H__4E806726_8EC8_46DF_8E6E_A4D6ADDE53F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestMutiDocDoc : public CDocument
{
protected: // create from serialization only
	CTestMutiDocDoc();
	DECLARE_DYNCREATE(CTestMutiDocDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestMutiDocDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestMutiDocDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestMutiDocDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMUTIDOCDOC_H__4E806726_8EC8_46DF_8E6E_A4D6ADDE53F0__INCLUDED_)
