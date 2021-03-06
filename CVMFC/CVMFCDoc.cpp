//  CVMFCDoc.cpp : implementation of the CCVMFCDoc class
//

#include "stdafx.h"
 
#include "CVMFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCVMFCDoc

IMPLEMENT_DYNCREATE(CCVMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CCVMFCDoc, CDocument)
	//{{AFX_MSG_MAP(CCVMFCDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCVMFCDoc construction/destruction

CCVMFCDoc::CCVMFCDoc()
{
	// TODO: add one-time construction code here
	pImg=NULL;
 	m_Display=-1;
}

CCVMFCDoc::~CCVMFCDoc()
{
	if (pImg)
		cvReleaseImage(&pImg);
}



/////////////////////////////////////////////////////////////////////////////
// CCVMFCDoc serialization

void CCVMFCDoc::Serialize(CArchive& ar)
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
// CCVMFCDoc diagnostics

#ifdef _DEBUG
void CCVMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCVMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCVMFCDoc commands

BOOL CCVMFCDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	BOOL bl;
    Load(&pImg,lpszPathName);
	if (pImg!=NULL)
		bl=true;
	else
		bl=false;
	return(bl);
}

//---------------------------------------------------------
//---------------------------------------------------------
//  ImageIO
 
BOOL CCVMFCDoc::Load(IplImage** pp,LPCTSTR csFileName)
{
	IplImage* pImg=NULL;

	pImg = cvLoadImage(csFileName,-1);      //  读图像文件(DSCV),-1表示且读入的图像将与它本来颜色信息一样 （颜色通道数目由图像文件决定）
	if (!pImg)
		return(false);
	cvFlip(pImg);                           //  与 DIB 像素结构一致
 	if (*pp) {//如果pp指针开始不为空怎先释放原来图像资源
		cvReleaseImage(pp);
	}
	(*pp)=pImg;
   	m_Display=0;
	return(true);
}

BOOL CCVMFCDoc::Save(LPCTSTR csFileName,IplImage* pImg)
{
	int   bl;

 	cvFlip(pImg);                           //  恢复原 OpenCV 位图结构
  	bl=cvSaveImage(csFileName,pImg);        //  图像存盘
 	return(bl);
}


