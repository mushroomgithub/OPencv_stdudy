// TestMutiDocDoc.cpp : implementation of the CTestMutiDocDoc class
//

#include "stdafx.h"
#include "TestMutiDoc.h"

#include "TestMutiDocDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestMutiDocDoc

IMPLEMENT_DYNCREATE(CTestMutiDocDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestMutiDocDoc, CDocument)
	//{{AFX_MSG_MAP(CTestMutiDocDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestMutiDocDoc construction/destruction

CTestMutiDocDoc::CTestMutiDocDoc()
{
	// TODO: add one-time construction code here

}

CTestMutiDocDoc::~CTestMutiDocDoc()
{
}

BOOL CTestMutiDocDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestMutiDocDoc serialization

void CTestMutiDocDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CTestMutiDocDoc diagnostics

#ifdef _DEBUG
void CTestMutiDocDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestMutiDocDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestMutiDocDoc commands
