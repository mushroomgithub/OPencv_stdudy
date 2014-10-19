// TestMutiDocView.cpp : implementation of the CTestMutiDocView class
//

#include "stdafx.h"
#include "TestMutiDoc.h"

#include "TestMutiDocDoc.h"
#include "TestMutiDocView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestMutiDocView

IMPLEMENT_DYNCREATE(CTestMutiDocView, CView)

BEGIN_MESSAGE_MAP(CTestMutiDocView, CView)
	//{{AFX_MSG_MAP(CTestMutiDocView)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestMutiDocView construction/destruction

CTestMutiDocView::CTestMutiDocView()
{
	// TODO: add construction code here

}

CTestMutiDocView::~CTestMutiDocView()
{
}

BOOL CTestMutiDocView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestMutiDocView drawing

void CTestMutiDocView::OnDraw(CDC* pDC)
{
	CTestMutiDocDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestMutiDocView printing

BOOL CTestMutiDocView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestMutiDocView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestMutiDocView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestMutiDocView diagnostics

#ifdef _DEBUG
void CTestMutiDocView::AssertValid() const
{
	CView::AssertValid();
}

void CTestMutiDocView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestMutiDocDoc* CTestMutiDocView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestMutiDocDoc)));
	return (CTestMutiDocDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestMutiDocView message handlers

void CTestMutiDocView::OnFileClose() 
{
	// TODO: Add your command handler code here
	
}
