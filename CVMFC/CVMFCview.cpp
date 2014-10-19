// CVMFCView.cpp : implementation of the CCVMFCView class
//

#include "stdafx.h"
 
#include "CVMFCDoc.h"
#include "CVMFCView.h"
#include <opencv2/legacy/legacy.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef min
#define min(a,b)  (((a)<(b))?(a):(b))
#endif

/////////////////////////////////////////////////////////////////////////////
// CCVMFCView

IMPLEMENT_DYNCREATE(CCVMFCView, CScrollView)

BEGIN_MESSAGE_MAP(CCVMFCView, CScrollView)
	//{{AFX_MSG_MAP(CCVMFCView)
	ON_WM_TIMER()
	ON_WM_SIZE()
	//�ļ��Ӳ˵�
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
 	ON_UPDATE_COMMAND_UI(ID_REFRESH, OnUpdateRefresh)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateFileClose)
	ON_UPDATE_COMMAND_UI(ID_CONSERVATION_IMAGE, OnUpdateConservationImage)
	ON_UPDATE_COMMAND_UI(ID_COLOR_IMAGE_REFRESH, OnUpdateColorImageRefresh)
 	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateAppExit)
  	ON_COMMAND(ID_REFRESH, OnRefresh)//�ָ�ͼ��
	ON_COMMAND(ID_CONSERVATION_IMAGE, OnConservationImage)//���浱ǰλͼ
	ON_COMMAND(ID_COLOR_IMAGE_REFRESH, OnColorImageRefresh)//�ָ�ԭʼͼ��
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)//��ǰ�������
	//�㴦���Ӳ˵�
	ON_UPDATE_COMMAND_UI(ID_COLOR_TO_GRAY, OnUpdateColorToGray)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_INVERT, OnUpdateImageInvert)
	ON_UPDATE_COMMAND_UI(ID_FLIP_V, OnUpdateFlipV)
	ON_UPDATE_COMMAND_UI(ID_FLIP_H, OnUpdateFlipH)
	ON_UPDATE_COMMAND_UI(ID_FLIP, OnUpdateFlip)
	ON_UPDATE_COMMAND_UI(ID_ROTATION_30, OnUpdateRotation30)
	ON_UPDATE_COMMAND_UI(ID_WARP_AFFINE, OnUpdateWarpAffine)
	ON_UPDATE_COMMAND_UI(ID_WARP_PERSPECT, OnUpdateWarpPerspect)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_ADJUST, OnUpdateImageAdjust)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_HISTOGRAM, OnUpdateImageHistogram)
	ON_UPDATE_COMMAND_UI(ID_HIST_EQUALIZE, OnUpdateHistEqualize)
	ON_COMMAND(ID_COLOR_TO_GRAY, OnColorToGray)//��ɫ��ҽ�
	ON_COMMAND(ID_IMAGE_INVERT, OnImageInvert)//ͼ����
	ON_COMMAND(ID_FLIP_V, OnFlipV)//��ֱ����
	ON_COMMAND(ID_FLIP_H, OnFlipH)//ˮƽ����
	ON_COMMAND(ID_FLIP, OnFlip)//180����ת
	ON_COMMAND(ID_ROTATION_30, OnRotation30)//30����ת
	ON_COMMAND(ID_WARP_AFFINE, OnWarpAffine)//����任
	ON_COMMAND(ID_WARP_PERSPECT, OnWarpPerspect)//͸�ӱ任
	ON_COMMAND(ID_IMAGE_ADJUST, OnImageAdjust)//���ȱ任
	ON_COMMAND(ID_IMAGE_HISTOGRAM, OnImageHistogram)//�ҽ�ͼ��ֱ��ͼ
	ON_COMMAND(ID_HIST_EQUALIZE, OnHistEqualize)//ֱ��ͼ���⻯
	//�������Ӳ˵�
	ON_UPDATE_COMMAND_UI(ID_BLUR_SMOOTH, OnUpdateBlurSmooth)
	ON_UPDATE_COMMAND_UI(ID_GAUSS_SMOOTH, OnUpdateGaussSmooth)
	ON_UPDATE_COMMAND_UI(ID_MEDIAN_SMOOTH, OnUpdateMedianSmooth)
	ON_UPDATE_COMMAND_UI(ID_SOBEL, OnUpdateSobel)
	ON_UPDATE_COMMAND_UI(ID_LAPLACE, OnUpdateLaplace)
	ON_COMMAND(ID_BLUR_SMOOTH, OnBlurSmooth)//������˵����µ�����ƽ��
	ON_COMMAND(ID_GAUSS_SMOOTH, OnGaussSmooth)//������˵����µ�Gauss�˲�
	ON_COMMAND(ID_MEDIAN_SMOOTH, OnMedianSmooth)//�������µ���ֵ�˲�
	ON_COMMAND(ID_SOBEL, OnSobel)//�������µ�Sobel��Ե���
	ON_COMMAND(ID_LAPLACE, OnLaplace)//�������µ�Laplace��Ե���
	//��ֵ���Ӳ˵�
	ON_UPDATE_COMMAND_UI(ID_THRESHOLDING_1, OnUpdateThresholding1)
	ON_UPDATE_COMMAND_UI(ID_THRESHOLDING_2, OnUpdateThresholding2)
	ON_UPDATE_COMMAND_UI(ID_ADAPTIVE_THRESHOLD, OnUpdateAdaptiveThreshold)
	ON_UPDATE_COMMAND_UI(ID_BASIC_GLOBAL_THRESHOLD, OnUpdateBasicGlobalThreshold)
	ON_COMMAND(ID_THRESHOLDING_1, OnThresholding1)//ѡ����ֵ
	ON_COMMAND(ID_THRESHOLDING_2, OnThresholding2)//ѡ����ֵ��ESC��
	ON_COMMAND(ID_ADAPTIVE_THRESHOLD, OnAdaptiveThreshold)//����Ӧ��ֵ��
	ON_COMMAND(ID_BASIC_GLOBAL_THRESHOLD, OnBasicGlobalThreshold)//����ȫ����ֵ��
	//��ֵͼ�����Ӳ˵�
	ON_UPDATE_COMMAND_UI(ID_MIN_AREA_RECT_2, OnUpdateMinAreaRect2)
	ON_UPDATE_COMMAND_UI(ID_AREA_RECT, OnUpdateAreaRect)
	ON_UPDATE_COMMAND_UI(ID_MIN_AREA_RECT, OnUpdateMinAreaRect)
	ON_UPDATE_COMMAND_UI(ID_APPROX_POLY, OnUpdateApproxPoly)
	ON_UPDATE_COMMAND_UI(ID_CONVEX_HULL_2, OnUpdateConvexHull2)
	ON_UPDATE_COMMAND_UI(ID_CONVEX_HULL, OnUpdateConvexHull)
	ON_UPDATE_COMMAND_UI(ID_AREA_CONVEX_HULL, OnUpdateAreaConvexHull)
	ON_UPDATE_COMMAND_UI(ID_CONVEXITY_DEFECTS, OnUpdateConvexityDefects)
	ON_UPDATE_COMMAND_UI(ID_CONTOUR_TRACK, OnUpdateContourTrack)
	ON_UPDATE_COMMAND_UI(ID_DISTANCE, OnUpdateDistance)
	ON_COMMAND(ID_MIN_AREA_RECT_2, OnMinAreaRect2)//�㼯��С����ESC��
	ON_COMMAND(ID_AREA_RECT, OnAreaRect)//��Ӿ��Σ�����
	ON_COMMAND(ID_MIN_AREA_RECT, OnMinAreaRect)//��С������Σ�����
	ON_COMMAND(ID_APPROX_POLY, OnApproxPoly)//����αƽ�������
	ON_COMMAND(ID_CONVEX_HULL_2, OnConvexHull2)//�㼯͹����ESC��
	ON_COMMAND(ID_CONVEX_HULL, OnConvexHull)//�㼯͹�����¼�������
	ON_COMMAND(ID_AREA_CONVEX_HULL, OnAreaConvexHull)//����͹��������
	ON_COMMAND(ID_CONVEXITY_DEFECTS, OnConvexityDefects)//���򰼲����
	ON_COMMAND(ID_CONTOUR_TRACK, OnContourTrack)//�ֻ����
	ON_COMMAND(ID_DISTANCE, OnDistance)//����任
	//��̬ѧ�����Ӳ˵�
	ON_UPDATE_COMMAND_UI(ID_EROSION, OnUpdateErosion)
	ON_UPDATE_COMMAND_UI(ID_DILATION, OnUpdateDilation)
	ON_UPDATE_COMMAND_UI(ID_OPENNING, OnUpdateOpenning)
	ON_UPDATE_COMMAND_UI(ID_CLOSING, OnUpdateClosing)
	ON_UPDATE_COMMAND_UI(ID_GRADS, OnUpdateGrads)
	ON_UPDATE_COMMAND_UI(ID_GRAY_TOPHAT, OnUpdateGrayTophat)
	ON_UPDATE_COMMAND_UI(ID_GRAY_BLACKHAT, OnUpdateGrayBlackhat)
	ON_COMMAND(ID_EROSION, OnErosion)//��ʴ
	ON_COMMAND(ID_DILATION, OnDilation)//����
	ON_COMMAND(ID_OPENNING, OnOpenning)//������
	ON_COMMAND(ID_CLOSING, OnClosing)//������
	ON_COMMAND(ID_GRADS, OnGrads)//��̬ѧ�ݶ�
	ON_COMMAND(ID_GRAY_TOPHAT, OnGrayTophat)//��ñ�任
	ON_COMMAND(ID_GRAY_BLACKHAT, OnGrayBlackhat)//���ȼ��
	//��ɫͼ�����Ӳ˵�
	ON_UPDATE_COMMAND_UI(ID_IMAGE_RGB, OnUpdateImageRgb)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_HSV, OnUpdateImageHsv)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_LAB, OnUpdateImageLab)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_RGB_C, OnUpdateImageRgbC)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_XYZ, OnUpdateImageXyz)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_YCRCB, OnUpdateImageYcrcb)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_LUV, OnUpdateImageLuv)
	ON_UPDATE_COMMAND_UI(ID_2D_HISTOGRAM, OnUpdate2dHistogram)
	ON_UPDATE_COMMAND_UI(ID_BLUR_SMOOTH_C, OnUpdateBlurSmoothC)
	ON_UPDATE_COMMAND_UI(ID_GAUSS_SMOOTH_C, OnUpdateGaussSmoothC)
	ON_UPDATE_COMMAND_UI(ID_MEDIAN_SMOOTH_C, OnUpdateMedianSmoothC)
	ON_UPDATE_COMMAND_UI(ID_SOBEL_C, OnUpdateSobelC)
	ON_UPDATE_COMMAND_UI(ID_LAPLACE_C, OnUpdateLaplaceC)
	ON_COMMAND(ID_IMAGE_RGB, OnImageRgb)//RGB����
	ON_COMMAND(ID_IMAGE_HSV, OnImageHsv)//HSV����
	ON_COMMAND(ID_IMAGE_LAB, OnImageLab)//Lab����
	ON_COMMAND(ID_IMAGE_RGB_C, OnImageRgbC)//RGB������C��
	ON_COMMAND(ID_IMAGE_XYZ, OnImageXyz)//XYZ����
	ON_COMMAND(ID_IMAGE_YCRCB, OnImageYcrcb)//YCrCb����
	ON_COMMAND(ID_IMAGE_LUV, OnImageLuv)//Luv����
	ON_COMMAND(ID_2D_HISTOGRAM, On2dHistogram)//��άֱ��ͼ
	ON_COMMAND(ID_BLUR_SMOOTH_C, OnBlurSmoothC)//��ɫͼ����˵��µ�����ƽ��
	ON_COMMAND(ID_GAUSS_SMOOTH_C, OnGaussSmoothC)	//��ɫͼ����˵��µ� Gauss �˲�   
	ON_COMMAND(ID_MEDIAN_SMOOTH_C, OnMedianSmoothC)//��ɫͼ�����µ���ֵ�˲�
	ON_COMMAND(ID_SOBEL_C, OnSobelC)//��ɫͼ�����µ�Sobel��Ե���
	ON_COMMAND(ID_LAPLACE_C, OnLaplaceC)//��ɫͼ�����µ�Laplace��Ե���
	//�ۺϴ������Ӳ˵�
	ON_UPDATE_COMMAND_UI(ID_IMAGE_SHRINK, OnUpdateImageShrink)
	ON_UPDATE_COMMAND_UI(ID_RADIAL_GRADS, OnUpdateRadialGrads)
	ON_UPDATE_COMMAND_UI(ID_CANNY_BORDDETEC, OnUpdateCannyBorddetec)
	ON_UPDATE_COMMAND_UI(ID_HOUGH_LINES, OnUpdateHoughLines)
	ON_UPDATE_COMMAND_UI(ID_HOUGH_CIRCLE, OnUpdateHoughCircle)
	ON_UPDATE_COMMAND_UI(ID_SQUARES_TEST, OnUpdateSquaresTest)
	ON_UPDATE_COMMAND_UI(ID_FLOOD_FILL, OnUpdateFloodFill)
	ON_UPDATE_COMMAND_UI(ID_PYR_SEGMENTATION, OnUpdatePyrSegmentation)
	ON_UPDATE_COMMAND_UI(ID_FIT_ELLIPSE, OnUpdateFitEllipse)
	ON_UPDATE_COMMAND_UI(ID_SNAKE, OnUpdateSnake)//
	ON_UPDATE_COMMAND_UI(ID_WATERSHED, OnUpdateWatershed)
	ON_UPDATE_COMMAND_UI(ID_CORNERS_TEST, OnUpdateCornersTest)
	ON_UPDATE_COMMAND_UI(ID_CLUSTERS, OnUpdateClusters)
	ON_UPDATE_COMMAND_UI(ID_SEQ_PARTITION, OnUpdateSeqPartition)
	ON_UPDATE_COMMAND_UI(ID_ROTATION_TRACK, OnUpdateRotationTrack)
	ON_UPDATE_COMMAND_UI(ID_FACE_DETECT, OnUpdateFaceDetect)
	ON_COMMAND(ID_IMAGE_SHRINK, OnImageShrink)//ͼ����С
	ON_COMMAND(ID_RADIAL_GRADS, OnRadialGrads)//�����ݶ�
	ON_COMMAND(ID_CANNY_BORDDETEC, OnCannyBorddetec)//Canny�㷨
	ON_COMMAND(ID_HOUGH_LINES, OnHoughLines)//Hough�任��ֱ�ߣ�
	ON_COMMAND(ID_HOUGH_CIRCLE, OnHoughCircle)//Hough�任��Բ��
	ON_COMMAND(ID_SQUARES_TEST, OnSquaresTest)//ƽ���ı��μ��
	ON_COMMAND(ID_FLOOD_FILL, OnFloodFill)//��ͨ������䣨ESC��
	ON_COMMAND(ID_PYR_SEGMENTATION, OnPyrSegmentation)//��������ͼ��ָ�
	ON_COMMAND(ID_FIT_ELLIPSE, OnFitEllipse)//��Բ�������
	ON_COMMAND(ID_SNAKE, OnSnake)//Snakeԭ��
	ON_COMMAND(ID_WATERSHED, OnWatershed)//��ˮ��ԭ��ESC��
	ON_COMMAND(ID_CORNERS_TEST, OnCornersTest)//�ǵ���
	ON_COMMAND(ID_CLUSTERS, OnClusters)//�㼯���ࣨESC)
	ON_COMMAND(ID_SEQ_PARTITION, OnSeqPartition)//�ָ��ά�㼯��ESC��
	ON_COMMAND(ID_ROTATION_TRACK, OnRotationTrack)//��ת����٣�ESC��
	ON_COMMAND(ID_FACE_DETECT, OnFaceDetect)//�������
	//��̬����Ӳ˵�
	ON_UPDATE_COMMAND_UI(ID_DYNAMIC_BORDER_TEST, OnUpdateDynamicBorderTest)
	ON_UPDATE_COMMAND_UI(ID_OPTICAL_FLOW_TRACK, OnUpdateOpticalFlowTrack)
	ON_UPDATE_COMMAND_UI(IF_FOREGROUND_DETECT, OnUpdateForegroundDetect)
	ON_UPDATE_COMMAND_UI(ID_MOTION_DETECT, OnUpdateMotionDetect)
	ON_UPDATE_COMMAND_UI(ID_CAM_SHIFT_DEMO, OnUpdateCamShiftDemo)
	ON_UPDATE_COMMAND_UI(ID_FACE_DETECT_2, OnUpdateFaceDetect2)
	ON_COMMAND(ID_DYNAMIC_BORDER_TEST, OnDynamicBorderTest)//��̬��Ե��⣨ESC)
	ON_COMMAND(ID_OPTICAL_FLOW_TRACK, OnOpticalFlowTrack)//L_K�㷨�������٣�ESC��
	ON_COMMAND(IF_FOREGROUND_DETECT, OnForegroundDetect)//������ģ���
	ON_COMMAND(ID_MOTION_DETECT, OnMotionDetect)//�˶�Ŀ���⣨ESC��
	ON_COMMAND(ID_CAM_SHIFT_DEMO, OnCamShiftDemo)//��ɫĿ����٣�ESC��
	ON_COMMAND(ID_FACE_DETECT_2, OnFaceDetect2)//����������ESC)
	//��Ƶ�ɼ������Ӳ˵�
	ON_UPDATE_COMMAND_UI(ID_START_CAPTURE, OnUpdateStartCapture)
	ON_UPDATE_COMMAND_UI(ID_OPEN_AVI_FILE, OnUpdateOpenAviFile)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CONTINUE, OnUpdateViewContinue)
	ON_UPDATE_COMMAND_UI(ID_CAPTURE_IMAGE, OnUpdateCaptureImage)
	ON_UPDATE_COMMAND_UI(ID_AVERAGE_IMAGE, OnUpdateAverageImage)
	ON_UPDATE_COMMAND_UI(ID_CAP_ABORT, OnUpdateCapAbort)
	ON_UPDATE_COMMAND_UI(ID_SET_PARAMETER, OnUpdateSetParameter)
	ON_COMMAND(ID_START_CAPTURE, OnStartCapture)//��������ͷ
	ON_COMMAND(ID_OPEN_AVI_FILE, OnOpenAviFile)//��AVI�ļ�
	ON_COMMAND(ID_VIEW_CONTINUE, OnViewContinue)//��Ƶ�ⶳ
	ON_COMMAND(ID_CAPTURE_IMAGE, OnCaptureImage)//��Ƶ����
	ON_COMMAND(ID_AVERAGE_IMAGE, OnAverageImage)//��ͼ��ƽ��
	ON_COMMAND(ID_CAP_ABORT, OnCapAbort)//�ر���Ƶ
	ON_COMMAND(ID_SET_PARAMETER, OnSetParameter)//ѡ������ֱ���
	//ͼ�μ������Ӳ˵�
	ON_UPDATE_COMMAND_UI(ID_DRAWING, OnUpdateDrawing)
	ON_UPDATE_COMMAND_UI(ID_DELAUNAY, OnUpdateDelaunay)
	ON_UPDATE_COMMAND_UI(ID_LOG_POLAR, OnUpdateLogPolar)
	ON_UPDATE_COMMAND_UI(ID_DFT, OnUpdateDft)
	ON_COMMAND(ID_DRAWING, OnDrawing)//����ͼ��
	ON_COMMAND(ID_DELAUNAY, OnDelaunay)//����Delaunayͼ��
	ON_COMMAND(ID_LOG_POLAR, OnLogPolar)//������任
	ON_COMMAND(ID_DFT, OnDft)//DFT
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCVMFCView construction/destruction

CFile fCapture;
CFileException eCapture;
char pbuf[20];
int  captSetFlag=0;
 
CCVMFCView::CCVMFCView()
{
	// TODO: add construction code here
	saveImg    = NULL;
	workImg    = NULL;
  
	m_lpBmi    = 0;

	m_CaptFlag = 0;
	m_dibFlag  = 0;
 	m_ImageType= 0;
  
	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	if(fCapture.Open( "CaptSetup.txt", CFile::modeRead, &eCapture ) )
	{
		fCapture.Read( pbuf, 20 );          //  ȡ���ֱ�����������
 		sscanf(pbuf,"%d  %d",&frameSetW,&frameSetH);
		/*CString str;
		str.Format("%d %d",frameSetW,frameSetH);
		MessageBox(str);*/
		fCapture.Close();
	}
}

CCVMFCView::~CCVMFCView()
{
	if (m_CaptFlag)//��Ƶ�ڲ���
		AbortCapture(workImg);              //  �ر���Ƶ

 	if (saveImg)
		cvReleaseImage(&saveImg);           //  �ͷ�λͼ
 	if (workImg) 
		cvReleaseImage(&workImg);
 
	if (m_lpBmi)
		free(m_lpBmi);                      //  �ͷ�λͼ��Ϣ

	if (captSetFlag==1) {//���÷ֱ��ʲ���ʱ����captSetFlagΪ1,������ʱ����ò���Ϊ1����ʾ֮ǰ������Ƶǰ���ù��ֱ��ʣ��򽫷ֱ��ʲ���д���ļ���Ȼ�󽫱�־����Ϊ0
		if(fCapture.Open( "CaptSetup.txt", CFile::modeCreate | 
			CFile::modeWrite, &eCapture ) )
		{
			sprintf(pbuf,"%d  %d",frameSetW,frameSetH);
			fCapture.Write( pbuf, 20 );     //  �ֱ����������ݴ���
			fCapture.Close();
		}
		captSetFlag=0;
	}
}

BOOL CCVMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCVMFCView drawing

void CCVMFCView::OnDraw(CDC* pDC)
{
	CCVMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	if (pDoc->pImg!=NULL)	{	            //  �д�������ͼ�񣬼��Ӵ��̶���ͼ��
		if (pDoc->m_Display==0) {           //  ��δ��ʾ//m_Display��ʼ��Ϊ-1�����Ӵ��̼���ͼ��֮�󣬻�δ��ʾʱ���øò���Ϊ0,
 			imageClone(pDoc->pImg,&saveImg);         //  ���Ƶ�����λͼ
			m_dibFlag=imageClone(saveImg,&workImg);  //  ���Ƶ�����λͼ��m_dibFlag��λͼ�ṹ�����ı��ʾ�����ڼ���ˢ��λͼ�ṹ

			m_ImageType=imageType(workImg);//�ж�ͼ���Ƿ��Ƕ�ֵͼ������
			m_SaveFlag=m_ImageType;
			pDoc->m_Display=1;//λͼ��Ҫ��ʾ��־
		}
	}
 
	if (m_dibFlag) {                        //  DIB �ṹ�ı�
 		if (m_lpBmi)
			free(m_lpBmi);
		m_lpBmi=CtreateMapInfo(workImg,m_dibFlag);//��ȡ�µ�λͼ��Ϣ��ŵ�ַ
		m_dibFlag=0;//����µ�λͼ��Ϣ�����øñ�־Ϊ0,��ʾ��λͼ�ṹ���»�ã�û�з����ı�

		CSize  sizeTotal;
 		sizeTotal = CSize(workImg->width,workImg->height);
		SetScrollSizes(MM_TEXT,sizeTotal);  //  ���ù�����
	}

	char *pBits;
	if (m_CaptFlag==1) //��ʾ����Ƶ��������ô�ʱ��λͼ�����׵�ַ
		pBits=m_Frame->imageData;
	else if (workImg) //����ǹ���λͼ�ڼ䣬���ù���λͼ���ص��׵�ַ
		pBits=workImg->imageData;

	if (workImg) {                          //  ˢ�´��ڻ��棬��ʾͼ��
		StretchDIBits(pDC->m_hDC,
			    0,0,workImg->width,workImg->height,
				0,0,workImg->width,workImg->height,
				pBits,m_lpBmi,DIB_RGB_COLORS,SRCCOPY);
	}
}

void CCVMFCView::OnInitialUpdate()//��ʼ���ĵ��ʹ��ڴ���֮�󣬵�һ��ִ�еĺ���ʽOnInitialUpdate()���������Կ��Խ����ù������ߴ���ڴ˴�
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CCVMFCView diagnostics

#ifdef _DEBUG
void CCVMFCView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCVMFCView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CCVMFCDoc* CCVMFCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCVMFCDoc)));
	return (CCVMFCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCVMFCView message handlers

//---------------------------------------------------------
//  ͼ��ָ���洢

void CCVMFCView::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_ImageType!=-3);
}

void CCVMFCView::OnUpdateRefresh(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateConservationImage(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateFileClose(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateColorImageRefresh(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateAppExit(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_ImageType!=-3);
}

void CCVMFCView::OnRefresh() 
{
	m_dibFlag=imageClone(saveImg,&workImg);
	m_ImageType=m_SaveFlag;
  	Invalidate();
}

void CCVMFCView::OnConservationImage() 
{
 	imageClone(workImg,&saveImg);
	m_SaveFlag=m_ImageType;
}

void CCVMFCView::OnColorImageRefresh() 
{
	CCVMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_Display=0;//��ʾ�ָ�ԭʼͼ���־
	Invalidate();
}

void CCVMFCView::OnFileSaveAs() 
{
    CString csBMP="BMP Files(*.BMP)|*.BMP|";
	CString csJPG="JPEG Files(*.JPG)|*.JPG|";
	CString csTIF="TIF Files(*.TIF)|*.TIF|";
	CString csPNG="PNG Files(*.PNG)|*.PNG|";
	CString csDIB="DIB Files(*.DIB)|*.DIB|";
	CString csPBM="PBM Files(*.PBM)|*.PBM|";
	CString csPGM="PGM Files(*.PGM)|*.PGM|";
	CString csPPM="PPM Files(*.PPM)|*.PPM|";
	CString csSR ="SR  Files(*.SR) |*.SR|";
	CString csRAS="RAS Files(*.RAS)|*.RAS||";

    CString csFilter=csBMP+csJPG+csTIF+csPNG+csDIB
					 +csPBM+csPGM+csPPM+csSR+csRAS;

	CString name[]={"","bmp","jpg","tif","png","dib",
		               "pbm","pgm","ppm","sr", "ras",""};

	CString strFileName;
	CString strExtension;
 
	CFileDialog FileDlg(false,NULL,NULL,OFN_HIDEREADONLY,csFilter);
	                                        //  �ļ����̶Ի���
	if (FileDlg.DoModal()==IDOK ) {         //  ѡ�����ļ���
 		strFileName = FileDlg.m_ofn.lpstrFile;
		if (FileDlg.m_ofn.nFileExtension == 0) {  //  ���ļ���׺
			strExtension = name[FileDlg.m_ofn.nFilterIndex];
			strFileName = strFileName + '.' + strExtension;
			                                //  ���ļ���׺
		}

		CCVMFCDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->Save(strFileName,workImg);   //  ��ǰ�������
	}
}

void CCVMFCView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	
	if (workImg) {                          //  ˢ�´��ڻ���
 		CSize  sizeTotal;
 		sizeTotal = CSize(workImg->width,workImg->height);
		SetScrollSizes(MM_TEXT, sizeTotal);   //  ���ù�����
	}
}

//---------------------------------------------------------
//  ��Ƶ�ɼ�

void CCVMFCView::OnUpdateStartCapture(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag==0)&&(m_ImageType!=-3));//��ʼδ������Ƶʱ��ʹ�ܿ�������ͷ�Ӳ˵�
}

void CCVMFCView::OnUpdateOpenAviFile(CCmdUI* pCmdUI) //��ʼδ������Ƶʱ��ʹ�ܴ�AVI��Ƶ�ļ��Ӳ˵�
{
    pCmdUI->Enable((m_CaptFlag==0)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateCaptureImage(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_CaptFlag==1); //��ʾ��Ƶ��ǰ���ڳ�ʼ����״̬��ʹ�ܶ����Ӳ˵�
}

void CCVMFCView::OnUpdateAverageImage(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_CaptFlag==1);//ʹ�ܶ�ͼ��ƽ���Ӳ˵�
}

void CCVMFCView::OnUpdateViewContinue(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_CaptFlag==2);//��ʾ��Ƶ���ڶ���״̬ʱ���ⶳ�˵������
}

void CCVMFCView::OnUpdateCapAbort(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag)&&(m_ImageType!=-3));//��Ƶ������ʹ�ܹر���Ƶ�Ӳ˵�
}
 
void CCVMFCView::OnUpdateSetParameter(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag==0)&&(m_ImageType!=-3));//��Ƶδ����ʱ�����û�������Ƶ�ֱ��ʲ���
}

//---------------------------------------------------------
//
//  m_CaptFlag  ��Ƶ״̬��־  0 -- �رգ� 1 -- ������ 2 -- ���� 
//
 
void CCVMFCView::OnStartCapture()           //  ������Ƶ
{
	BOOL  bl;

 	if (workImg) {//�����ǰ�й���λͼ���ڹ�����������汳�������ǵ�ǰworkingλͼָ�뻹û�ͷţ���ֻ��ʹ��ָ����ɫ��դ���»�����ָ����������
 		CCVMFCDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		cvReleaseImage(&pDoc->pImg);
		pDoc->m_Display=0;

		CClientDC dc(this);
		dc.PatBlt(0,0,1024,768,WHITENESS);  //  �������
	}

	bl=StartCapture();                      //  ������Ƶ
	if (!bl) {//bl=falseʱ��ʾû��ö�ٵ�����ͷ�豸��������û�а�װ����ͷ
 		AfxMessageBox("����û�а�װ����ͷ��");
		return;
	}
	else if (bl==-1) {//-1��ʾö�ٵ�������ͷ�豸�����Ǵ�����ͷʱʧ��
		if (frameSetW>640) {
			frameSetW=640;     frameSetH=480;
			bl=StartCapture();
			if (bl==-1) {
				AfxMessageBox("�޷�������ͷ");
				return;
			}
		}
	}

	if (workImg) {
		cvReleaseImage(&workImg);
	}
	workImg =cvCreateImage(cvSize(frameW,frameH), IPL_DEPTH_8U, 3);
	if (saveImg) {
		cvReleaseImage(&saveImg);
	}
	m_dibFlag=1;
   	
 	SetTimer(ID_TIMER,67,NULL);             //  ÿ����� 1000/67=15 ��
	m_CaptFlag=1;                           //  ��Ƶ״̬��־��ʼ��
}

void CCVMFCView::OnOpenAviFile() 
{
	BOOL  bl;

	CString csFilter="AVI Files(*.AVI)|*.AVI||";
	CString strFileName;
  
	CFileDialog FileDlg(true,NULL,NULL,OFN_HIDEREADONLY,csFilter);
	                                        //  �ļ����̶Ի���
	if (FileDlg.DoModal()==IDOK ) {         //  ѡ�����ļ���
 		strFileName = FileDlg.m_ofn.lpstrFile;
		if (FileDlg.m_ofn.nFileExtension == 0) {  //  ���ļ���׺
			strFileName = strFileName + ".avi";
			                                //  ���ļ���׺
		}
	}

	if (workImg) {
 		CCVMFCDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (pDoc->pImg) {
			cvReleaseImage(&pDoc->pImg);
		}
		pDoc->m_Display=0;

		CClientDC dc(this);
		dc.PatBlt(0,0,1024,768,WHITENESS);  //  �������
	}

	bl=OpenAviFile(strFileName);            //  ����Ƶ�ļ�
	if (!bl) {
		AfxMessageBox("�޷�����Ƶ�ļ�");
		return;
	}

	if (workImg) {
		cvReleaseImage(&workImg);
	}
	workImg =cvCreateImage(cvSize(frameW,frameH), IPL_DEPTH_8U, 3);
	if (saveImg) {
		cvReleaseImage(&saveImg);
	}
	m_dibFlag=1;
   	
	SetTimer(ID_TIMER,67,NULL);             //  ÿ����� 15 ��
	m_CaptFlag=1;                           //  ��Ƶ״̬��־��ʼ��
}

void CCVMFCView::OnCaptureImage()           //  ��Ƶ����
{
	BOOL bl=LoadImageFrame(workImg,1);      //  ������Ƶͼ��
	if (bl) {
 		imageClone(workImg,&saveImg);       //  ����Ϊ����ͼ��

		KillTimer(ID_TIMER);                //  �ض�ʱ��
		m_ImageType=m_SaveFlag=workImg->nChannels;
		m_CaptFlag = 2;                     //  �޸���Ƶ״̬��־
		Invalidate(false);
	}
}

void CCVMFCView::OnAverageImage() //����Ϊ��ͼ��ƽ����ʽ��Ҳ������λͼ���黺����Buffer��Ŀ���ڶ�ʱ����ʼ������ʱ����OnTimer�н��ж�ͼ�������ƽ������
{
	StartAverage();
}

void CCVMFCView::OnViewContinue()           //  ��Ƶ�ⶳ
{
	SetTimer(ID_TIMER,67,NULL);             //  ÿ����� 15 ��
	m_CaptFlag=1;                           //  �ָ���Ƶ״̬
}

void CCVMFCView::OnCapAbort()               //  �ر���Ƶ
{
	CCVMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	IplImage *p;

	AbortCapture(workImg);                  //  �ر���Ƶ
	if (saveImg) 
		p=saveImg;                 //  ���ж���ͼ��
	else 
		p=workImg;
 	imageClone(p,&pDoc->pImg);              //  ����Ϊԭʼͼ��
  
	KillTimer(ID_TIMER);                    //  �ض�ʱ��
	pDoc->m_Display=0;
	m_CaptFlag=0;                           //  ����Ƶ״̬��־
	Invalidate(false);
}

void CCVMFCView::OnSetParameter() 
{
	BOOL  bl;

	bl=SetParameter();
	if (bl==0) {
 		AfxMessageBox("����û�а�װ����ͷ��");
	}
	else {
		if ((frameSetW != frameW) ||
			(frameSetH != frameH)) {
			captSetFlag=1;//��ʾ�����˷ֱ���
		}
	}
}

void CCVMFCView::OnTimer(UINT nIDEvent)     //  ��ʱ����Ӧ
{
	int  bl=LoadImageFrame(workImg,0);      //  ������Ƶͼ��

	if (bl==0) {
 		OnCapAbort();                       //  �ر���Ƶ
	}
	else if (bl==1) { //������Ƶ�����Ӳ˵�����OnDraw��ˢ��
  		Invalidate(false);                  //  ˢ�»���
	}
	else if (bl==2) {
		KillTimer(ID_TIMER);                //  �ض�ʱ��

		AverageImage(workImg);              //  ȡ��ƽ��ֵ
 		imageClone(workImg,&saveImg);       //  ����Ϊ����ͼ��

		m_ImageType=m_SaveFlag=workImg->nChannels;
		m_CaptFlag = 2;                     //  �޸���Ƶ״̬��־
		Invalidate(false);
	}
 
	CScrollView::OnTimer(nIDEvent);
}

//---------------------------------------------------------
//  OpenCVͼ����

//---------------------------------------------------------
//  �㴦��

void CCVMFCView::OnUpdateColorToGray(CCmdUI* pCmdUI) //��ɫ��ҽ�
{
    pCmdUI->Enable((m_CaptFlag==0)&&(m_ImageType>1));
}

void CCVMFCView::OnUpdateImageInvert(CCmdUI* pCmdUI) //ͼ����
{
    pCmdUI->Enable((m_CaptFlag!=1)&&
		(m_ImageType)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateFlipV(CCmdUI* pCmdUI) //��ֱ����
{
    pCmdUI->Enable((m_CaptFlag!=1)&&
		(m_ImageType)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateFlipH(CCmdUI* pCmdUI) //ˮƽ����
{
    pCmdUI->Enable((m_CaptFlag!=1)&&
		(m_ImageType)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateFlip(CCmdUI* pCmdUI) //180����ת
{
    pCmdUI->Enable((m_CaptFlag!=1)&&
		(m_ImageType)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateRotation30(CCmdUI* pCmdUI) //30����ת
{
    pCmdUI->Enable((m_CaptFlag!=1)&&
		(m_ImageType)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateWarpAffine(CCmdUI* pCmdUI) //����任
{
    pCmdUI->Enable((m_CaptFlag!=1)&&
		(m_ImageType)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateWarpPerspect(CCmdUI* pCmdUI) //͸�ӱ任
{
    pCmdUI->Enable((m_CaptFlag!=1)&&
		(m_ImageType)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateImageAdjust(CCmdUI* pCmdUI) //���ȱ任
{
	pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnUpdateImageHistogram(CCmdUI* pCmdUI) //�ҽ�ͼ��ֱ��ͼ
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnUpdateHistEqualize(CCmdUI* pCmdUI) //ֱ��ͼ���⻯
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnColorToGray()            //  ͼ���ɫ��ҽ�   
{
	IplImage* pImage;
	IplImage* pImg8u = NULL;
 
	pImage = workImg;                       //  ������ͼ����

    //  ��������λͼ
 	pImg8u = cvCreateImage(cvGetSize(pImage),IPL_DEPTH_8U,1);

 	cvCvtColor(pImage,pImg8u,CV_BGR2GRAY);  //  ��ɫ��ҽ�

	m_dibFlag=imageReplace(pImg8u,&workImg);  //  ���������
 
 	imageClone(workImg,&saveImg);           //  ���浱ǰλͼ�����ڻָ�λͼ
     
	m_SaveFlag=m_ImageType=1;               //  ���ûҽ�λͼ��־
	Invalidate();
}

void CCVMFCView::OnImageInvert()            //  ͼ����
{
	cvNot(workImg,workImg);                 //  ���ط��࣬����workingλͼ��ÿһ�����ص�ÿһλ��λȡ����Ȼ���ڽ������ֵ��working��ʵ��ͼ��ķ���
 	Invalidate();
}

void CCVMFCView::OnFlipV() 
{
 	cvFlip(workImg);                        //  ��ֱ���� cvFlip(in,0,0) 
	Invalidate();
}

void CCVMFCView::OnFlipH() 
{
 	cvFlip(workImg,0,1);                    //  ˮƽ����
 	Invalidate();
}

void CCVMFCView::OnFlip() 
{
  	cvFlip(workImg,0,-1);                   //  180 ����ת
 	Invalidate();
}

void CCVMFCView::OnRotation30()             //  30 ����ת
{   //  ���ݡ�����OpenCV�ļ�����Ӿ�����ʵ�֡����� 6-7 �ı�

 	int angle = 30;                         //  ��ת 30 ��
	int opt = 0;                            //  1: ������   0: ����ת
	double factor;                          //  ��������
    IplImage *pImage;
    IplImage *pImgRotation = NULL;

	pImage = workImg;
	pImgRotation = cvCloneImage(workImg);

	angle=-angle;//��ת����ת

	//  ���� M ����
	float m[6];
	//      Matrix m looks like:
	//      [ m0  m1  m2 ] ----> [ a11  a12  b1 ]
	//      [ m3  m4  m5 ] ----> [ a21  a22  b2 ]

	CvMat M = cvMat(2,3,CV_32F,m);//����һ��32λ����������ɵ�2*3�ľ���
	int w = workImg->width;
	int h = workImg->height;

	if (opt) //����
		factor = (cos(angle*CV_PI/180.)+1.0)*2;
	else //������ת
		factor = 1;

	m[0] = (float)(factor*cos(-angle*CV_PI/180.));
	m[1] = (float)(factor*sin(-angle*CV_PI/180.));
	m[3] = -m[1];
	m[4] =  m[0];
	//  ����ת��������ͼ������
	m[2] = w*0.5f;
	m[5] = h*0.5f;

//---------------------------------------------------------
	//  dst(x,y) = A * src(x,y) + b
	cvZero(pImgRotation);//��ʼ��
	cvGetQuadrangleSubPix(pImage,pImgRotation,&M);
//---------------------------------------------------------

	cvNamedWindow("Rotation Image");
 	cvFlip(pImgRotation);//��ֱ����
	cvShowImage("Rotation Image",pImgRotation);

    cvReleaseImage( &pImgRotation );
    cvWaitKey(0);

    cvDestroyWindow("Rotation Image");
}

void CCVMFCView::OnWarpAffine()             //  ����任
{                         //  ���ݡ�ѧϰOpenCV���� 6-2 �ı�
	CvPoint2D32f srcTri[3], dstTri[3];
	CvMat* rot_mat  = cvCreateMat(2,3,CV_32FC1);
	CvMat* warp_mat = cvCreateMat(2,3,CV_32FC1);
	IplImage *src=0, *dst=0;

	src = cvCloneImage(workImg);
	cvFlip(src);
	dst = cvCloneImage(src);
	dst->origin = src->origin;
	cvZero(dst);

	//COMPUTE WARP MATRIX
	srcTri[0].x = 0;                          //src Top left
	srcTri[0].y = 0;
	srcTri[1].x = (float) src->width - 1;     //src Top right
	srcTri[1].y = 0;
	srcTri[2].x = 0;                          //src Bottom left
	srcTri[2].y = (float) src->height - 1;
	//- - - - - - - - - - - - - - -//
	dstTri[0].x = (float)(src->width*0.0);    //dst Top left
	dstTri[0].y = (float)(src->height*0.33);
	dstTri[1].x = (float)(src->width*0.85);   //dst Top right
	dstTri[1].y = (float)(src->height*0.25);
	dstTri[2].x = (float)(src->width*0.15);   //dst Bottom left
	dstTri[2].y = (float)(src->height*0.7);
	cvGetAffineTransform(srcTri,dstTri,warp_mat);
	cvWarpAffine(src,dst,warp_mat);
	cvCopy(dst,src);

	//COMPUTE ROTATION MATRIX
	CvPoint2D32f center = cvPoint2D32f(src->width/2,src->height/2);
	double angle = -50.0;
	double scale = 0.6;
	cv2DRotationMatrix(center,angle,scale,rot_mat);
	cvWarpAffine(src,dst,rot_mat);

	//DO THE TRANSFORM:
	cvNamedWindow( "Affine_Transform", 1 );
    cvShowImage( "Affine_Transform", dst );

	m_ImageType=-3;
    cvWaitKey();

    cvDestroyWindow( "Affine_Transform" );
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseMat(&rot_mat);
	cvReleaseMat(&warp_mat);

	m_ImageType=imageType(workImg);
}

void CCVMFCView::OnWarpPerspect()           //  ͸�ӱ任
{                         //  ���ݡ�ѧϰOpenCV���� 6-3 �ı�
	CvPoint2D32f srcQuad[4], dstQuad[4];
	CvMat* warp_matrix = cvCreateMat(3,3,CV_32FC1);
	IplImage *src=0, *dst=0;

	src = cvCloneImage(workImg);
	cvFlip(src);
	dst = cvCloneImage(src);
	dst->origin = src->origin;
	cvZero(dst);

	srcQuad[0].x = 0;                         //src Top left
	srcQuad[0].y = 0;
	srcQuad[1].x = (float) src->width - 1;    //src Top right
	srcQuad[1].y = 0;
	srcQuad[2].x = 0;                         //src Bottom left
	srcQuad[2].y = (float) src->height - 1;
	srcQuad[3].x = (float) src->width - 1;    //src Bot right
	srcQuad[3].y = (float) src->height - 1;
      //- - - - - - - - - - - - - -//
	dstQuad[0].x = (float)(src->width*0.05);  //dst Top left
	dstQuad[0].y = (float)(src->height*0.33);
	dstQuad[1].x = (float)(src->width*0.9);   //dst Top right
	dstQuad[1].y = (float)(src->height*0.25);
	dstQuad[2].x = (float)(src->width*0.2);   //dst Bottom left
	dstQuad[2].y = (float)(src->height*0.7);      
	dstQuad[3].x = (float)(src->width*0.8);   //dst Bot right
	dstQuad[3].y = (float)(src->height*0.9);

	cvGetPerspectiveTransform(srcQuad,dstQuad,warp_matrix);
	cvWarpPerspective(src,dst,warp_matrix);

	cvNamedWindow( "Perspective_Warp", 1 );
    cvShowImage( "Perspective_Warp", dst );

	m_ImageType=-3;
    cvWaitKey();

    cvDestroyWindow( "Perspective_Warp" );
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseMat(&warp_matrix);

	m_ImageType=imageType(workImg);
}

//-------------------------------------
//  ���ȱ任
//  ���ݡ�OpenCV�̳�(����ƪ)���� 5-10 �ı�

/*
  src and dst are grayscale, 8-bit images;
  Default input value: 
           [low, high] = [0,1];  X-Direction
           [bottom, top] = [0,1]; Y-Direction
           gamma ;
  if adjust successfully, return 0, otherwise, return non-zero.
*/
int ImageAdjust(IplImage* src, IplImage* dst, 
    	double low, double high,   // X����low and high are the intensities of src
    	double bottom, double top, // Y����mapped to bottom and top of dst
    	double gamma )
{
	if(low<0 && low>1 && high <0 && high>1&&
		bottom<0 && bottom>1 && top<0 && top>1 && low>high)
        return -1;
    double low2 = low*255;
    double high2 = high*255;
    double bottom2 = bottom*255;
    double top2 = top*255;
    double err_in = high2 - low2;
    double err_out = top2 - bottom2;

    int x,y;
    double val;

    // intensity transform
    for( y = 0; y < src->height; y++)
    {
        for (x = 0; x < src->width; x++)
        {
            val = ((uchar*)(src->imageData + src->widthStep*y))[x]; 
            val = pow((val - low2)/err_in, gamma) * err_out + bottom2;
            if(val>255) val=255; if(val<0) val=0; // Make sure src is in the range [low,high]
            ((uchar*)(dst->imageData + dst->widthStep*y))[x] = (uchar) val;
        }
    }
    return 0;
}

void CCVMFCView::OnImageAdjust()            //  ���ȱ任
{
    IplImage *src = 0, *dst = 0;
    
//    if( argc != 2 || (src=cvLoadImage(argv[1], 0)) == NULL)  // force to gray image
//        return -1;
    
	src = workImg;

//    cvNamedWindow( "src", 1 );
    cvNamedWindow( "result", 1 );
    
    // Image adjust
    dst = cvCloneImage(src);
    // ������� [0,0.5] �� [0.5,1], gamma=1
	if( ImageAdjust( src, dst, 0, 0.5, 0.5, 1, 1)!=0) return;
    
//    cvShowImage( "src", src );
	cvFlip(dst);
    cvShowImage( "result", dst );
    cvWaitKey(0);

//    cvDestroyWindow("src");
    cvDestroyWindow("result");
//    cvReleaseImage( &src );
//    cvReleaseImage( &dst );

	cvFlip(dst);
	m_dibFlag=imageReplace(dst,&workImg);
  	
	Invalidate();
}

void CCVMFCView::OnImageHistogram()         //  �ҽ�ͼ��ֱ��ͼ
{                //  ���ݡ�OpenCV�̳�(����ƪ)���� 5-11 �ı�

    IplImage *src;
    IplImage *histimg = 0;
    CvHistogram *hist = 0;
    
    int hdims = 256;     // ����HIST�ĸ�����Խ��Խ��ȷ
    float hranges_arr[] = {0,255};
    float* hranges = hranges_arr;
    int bin_w;  
    float max_val;
    int i;
    
	src = workImg;
    
    cvNamedWindow( "Histogram", 0 );
     
    hist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 );  // ����ֱ��ͼ
    histimg = cvCreateImage( cvSize(320,200), 8, 3 );
    cvZero( histimg );
    cvCalcHist( &src, hist, 0, 0 ); // ����ֱ��ͼ
    cvGetMinMaxHistValue( hist, 0, &max_val, 0, 0 );  // ֻ�����ֵ
	cvConvertScale( hist->bins, hist->bins, 
		max_val ? 255. / max_val : 0., 0 ); // ���� bin ������ [0,255] 
    cvZero( histimg );
    bin_w = histimg->width / hdims;  // hdims: ���ĸ������� bin_w Ϊ���Ŀ��
    
    // ��ֱ��ͼ
    for( i = 0; i < hdims; i++ )
    {
        double val = ( cvGetReal1D(hist->bins,i)*histimg->height/255 );
        CvScalar color = CV_RGB(255,255,0); //(hsv2rgb(i*180.f/hdims);
        cvRectangle( histimg, cvPoint(i*bin_w,histimg->height),
            cvPoint((i+1)*bin_w,(int)(histimg->height - val)),
            color, 1, 8, 0 );
    }
    
    cvShowImage( "Histogram", histimg );

    cvReleaseImage( &histimg );
    cvReleaseHist ( &hist );
    cvWaitKey(0);

    cvDestroyWindow("Histogram");
}

//-------------------------------------
//  ֱ��ͼ���⻯
//  ���ݡ�OpenCV�̳�(����ƪ)���� 5-13 �ı�

#define HDIM    256    // bin of HIST, default = 256

void CCVMFCView::OnHistEqualize()           //  ֱ��ͼ���⻯
{

    IplImage *src = 0, *dst = 0;
    CvHistogram *hist = 0;
    
    int n = HDIM;     
    double nn[HDIM];
    uchar T[HDIM];
    CvMat *T_mat;
    
    int x;
    int sum = 0; // sum of pixels of the source image ͼ�������ص���ܺ�
    double val = 0;
    
//    if( argc != 2 || (src=cvLoadImage(argv[1], 0)) == NULL)  // force to gray image
//        return -1;

	src = workImg;
    
//    cvNamedWindow( "source", 1 );
    cvNamedWindow( "result", 1 );
    
    // ����ֱ��ͼ
    hist = cvCreateHist( 1, &n, CV_HIST_ARRAY, 0, 1 );  
    cvCalcHist( &src, hist, 0, 0 ); 
    
    // Create Accumulative Distribute Function of histgram
    val = 0;
    for ( x = 0; x < n; x++)
    {
        val = val + cvGetReal1D (hist->bins, x);
        nn[x] = val;
    }

    // ��һ��ֱ��ͼ
    sum = src->height * src->width;
    for( x = 0; x < n; x++ )
    {
        T[x] = (uchar) (255 * nn[x] / sum); // range is [0,255]
    }

    // Using look-up table to perform intensity transform for source image 
    dst = cvCloneImage( src );
    T_mat = cvCreateMatHeader( 1, 256, CV_8UC1 );
    cvSetData( T_mat, T, 0 );    
    // ֱ�ӵ����ڲ�������� look-up-table �Ĺ���
    cvLUT( src, dst, T_mat ); 

//    cvShowImage( "source", src );
	cvFlip(dst);
    cvShowImage( "result", dst );

    cvReleaseHist ( &hist );
    cvWaitKey(0);

//    cvDestroyWindow("source");
    cvDestroyWindow("result");
//    cvReleaseImage( &src );
//    cvReleaseImage( &dst );

	cvFlip(dst);
	m_dibFlag=imageReplace(dst,&workImg);
  	
	Invalidate();
}

//---------------------------------------------------------
//  ������

void CCVMFCView::OnUpdateBlurSmooth(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnUpdateGaussSmooth(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnUpdateMedianSmooth(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnUpdateSobel(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnUpdateLaplace(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnBlurSmooth()             //  ����ƽ��
{
	IplImage* in;
 
	in = workImg;
 
	IplImage* out = cvCreateImage(cvGetSize(in),
		IPL_DEPTH_8U,workImg->nChannels); 

	cvSmooth(in,out,CV_BLUR,3,workImg->nChannels);  //  ��ƽ��

	m_dibFlag=imageReplace(out,&workImg); 

	Invalidate();
}

void CCVMFCView::OnGaussSmooth()            //  Gauss �˲�  c
{                         //  ���ݡ�ѧϰOpenCV���� 2-4 �ı�
	IplImage* in;
 
	in = workImg;
 
	IplImage* out = cvCreateImage(cvGetSize(in),
		IPL_DEPTH_8U,workImg->nChannels);   //  ��������λͼ

	cvSmooth(in,out,CV_GAUSSIAN,3,workImg->nChannels);  //  Gauss ƽ��

	m_dibFlag=imageReplace(out,&workImg);   //  ���������

	Invalidate();
}

void CCVMFCView::OnMedianSmooth()           //  ��ֵ�˲�
{
	IplImage* in;
 
	in = workImg;
 
	IplImage* out = cvCreateImage(cvGetSize(in),
		IPL_DEPTH_8U,workImg->nChannels); 

	cvSmooth(in,out,CV_MEDIAN,3,workImg->nChannels);  //  ��ֵ�˲�

	m_dibFlag=imageReplace(out,&workImg);

	Invalidate();
}

void CCVMFCView::OnSobel()                  //  Sobel ��Ե���
{   //  ���ݡ�����OpenCV�ļ�����Ӿ�����ʵ�֡����� 6-1 �ı�

	IplImage* pImage;
	IplImage* pImgSobel = NULL;
	IplImage* pImgPlanes[3] = {0,0,0};
	int   i;
 
	pImage = workImg;
 
	pImgSobel= cvCreateImage(cvGetSize(pImage),
						IPL_DEPTH_16S,1);   //  ��������λͼ

	if (workImg->nChannels==1) {            //  ��ͨ��ͼ����
		cvSobel(pImage,pImgSobel,1,1,3);
		cvConvertScaleAbs(pImgSobel,pImage, 1, 0 );
	}
	else {                                  //  ��ͨ��ͼ����
		for (i=0;i<3;i++) {
			pImgPlanes[i] = cvCreateImage(cvGetSize(pImage),
						IPL_DEPTH_8U,1);    //  ��������λͼ
		}
 
		cvCvtPixToPlane(pImage,pImgPlanes[0],
				pImgPlanes[1],pImgPlanes[2],0);  //  ȡ��������

		for (i=0;i<3;i++) {                 //  ��������������
			cvSobel(pImgPlanes[i],pImgSobel,1,1,3);
			cvConvertScaleAbs(pImgSobel,pImgPlanes[i], 1, 0 );
		}

		cvCvtPlaneToPix(pImgPlanes[0],pImgPlanes[1],
				pImgPlanes[2],0,pImage);    //  �ɷ�����װ�ɲ�ɫͼ��

		for (i=0;i<3;i++) {
			cvReleaseImage(&pImgPlanes[i]);  //  �ͷŷ���λͼ
		}
	}
	cvReleaseImage(&pImgSobel);             //  �ͷŹ���λͼ

	Invalidate();
}

void CCVMFCView::OnLaplace()                //  Laplace ��Ե���
{                                           //  ����ṹͬ Sobel
	IplImage* pImage;
	IplImage* pImgLaplace = NULL;
	IplImage* pImgPlanes[3] = {0,0,0};
	int   i;
 
	pImage = workImg;
 
	pImgLaplace= cvCreateImage(cvGetSize(pImage),
						IPL_DEPTH_16S,1);

	if (workImg->nChannels==1) {
		cvLaplace(pImage,pImgLaplace,3);
		cvConvertScaleAbs(pImgLaplace,pImage, 1, 0 );
	}
	else {
		for (i=0;i<3;i++) {
			pImgPlanes[i] = cvCreateImage(cvGetSize(pImage),
						IPL_DEPTH_8U,1);
		}
 
		cvCvtPixToPlane(pImage,pImgPlanes[0],
				pImgPlanes[1],pImgPlanes[2],0);

		for (i=0;i<3;i++) {
			cvLaplace(pImgPlanes[i],pImgLaplace,3);
			cvConvertScaleAbs(pImgLaplace,pImgPlanes[i], 1, 0 );
		}

		cvCvtPlaneToPix(pImgPlanes[0],pImgPlanes[1],
				pImgPlanes[2],0,pImage);

		for (i=0;i<3;i++) {
			cvReleaseImage(&pImgPlanes[i]);
		}
	}
	cvReleaseImage(&pImgLaplace);

	Invalidate();
}

//---------------------------------------------------------
//  ��ֵͼ����

void CCVMFCView::OnUpdateThresholding1(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnUpdateThresholding2(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnUpdateBasicGlobalThreshold(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnUpdateAdaptiveThreshold(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnUpdateContourTrack(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==-1));
}


void CCVMFCView::OnUpdateDistance(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==-1));
}

void CCVMFCView::OnUpdateConvexHull(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==0));
}

void CCVMFCView::OnUpdateConvexHull2(CCmdUI* pCmdUI) 
{   
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==0));
}

void CCVMFCView::OnUpdateAreaConvexHull(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==-1));
}

void CCVMFCView::OnUpdateConvexityDefects(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==-1));
}

void CCVMFCView::OnUpdateMinAreaRect2(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==0));
}

void CCVMFCView::OnUpdateAreaRect(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==-1));
}

void CCVMFCView::OnUpdateMinAreaRect(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==-1));
}

void CCVMFCView::OnUpdateApproxPoly(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==-1));
}
 
char *threWin="Threshold Window";
IplImage *threImage0 = 0;
IplImage *threImage  = 0;
int  Threshold       = 128;

void onThreChange(int pos)
{
	cvThreshold(threImage,threImage0,Threshold,
				255,CV_THRESH_BINARY);
	cvShowImage( threWin, threImage0 );
}

void CCVMFCView::OnThresholding1() 
{
  	threImage  = cvCloneImage(workImg);
	cvFlip(threImage);
   	threImage0 = cvCloneImage(threImage);
  
    cvNamedWindow(threWin, 0);
	cvResizeWindow(threWin, 300, 320);

    cvCreateTrackbar( "Thresh", threWin, &Threshold, 255, onThreChange );
	onThreChange(0);
 	
	cvWaitKey(0);

	cvReleaseImage(&threImage);
    cvDestroyWindow(threWin);

	cvFlip(threImage0);
	m_dibFlag=imageReplace(threImage0,&workImg);
  	
	m_ImageType=-1;
	Invalidate();
}
 
void onThreChange2(int pos)
{
	cvThreshold(threImage,threImage0,Threshold,
				255,CV_THRESH_BINARY);
}

void CCVMFCView::OnThresholding2() 
{
	int   flag=0,thre=0;

  	threImage  = cvCloneImage(workImg);
	cvFlip(threImage);
   	threImage0 = cvCloneImage(threImage);
  
    cvNamedWindow(threWin, 0);
	cvResizeWindow(threWin, 300, 320);

    cvCreateTrackbar( "Thresh", threWin, &Threshold, 255, onThreChange2 );
	cvShowImage( threWin, threImage );
	onThreChange2(0);
 	
	m_ImageType=-3;
	for (;;) {
		if (cvWaitKey(40)==27) break;

 		if (flag==0) {
			free(m_lpBmi);
			m_lpBmi=CtreateMapInfo(workImg,1);
			flag=1;
		}
		if (Threshold != thre) {
			cvCopy(threImage0,workImg);
 			cvFlip(workImg);

			CClientDC dc(this);
			StretchDIBits(dc.m_hDC,         //  ˢ����ͼ����
				0,0,workImg->width,workImg->height,  
				0,0,workImg->width,workImg->height,
				workImg->imageData,m_lpBmi,DIB_RGB_COLORS,SRCCOPY);
			thre = Threshold;
		}
	}

	cvReleaseImage(&threImage);
	cvReleaseImage(&threImage0);
    cvDestroyWindow(threWin);
   	
	m_ImageType=-1;
	Invalidate();
}

void CCVMFCView::OnBasicGlobalThreshold()   //  ����ȫ����ֵ����ֵ��
{
	int  pg[256],i,thre;

	for (i=0;i<256;i++) pg[i]=0;
	for (i=0;i<workImg->imageSize;i++)      //  ֱ��ͼͳ��
		pg[(BYTE)workImg->imageData[i]]++;

	thre=BasicGlobalThreshold(pg,0,256);    //  ȷ����ֵ

	cvThreshold(workImg,workImg,thre,255,CV_THRESH_BINARY);  //  ��ֵ��

	m_ImageType=-1;
 	Invalidate();
}

void CCVMFCView::OnAdaptiveThreshold()      //  ����Ӧ��ֵ
{
 	cvAdaptiveThreshold(workImg,workImg,255,
			CV_ADAPTIVE_THRESH_GAUSSIAN_C,
			CV_THRESH_BINARY_INV,3,5);

	m_ImageType=-1;
 	Invalidate();
}

//-------------------------------------
//  �㼯��С����
//  ���� OpenCV ϵͳ�������ʵ�� minarea.c �ı�
 
void CCVMFCView::OnMinAreaRect2() 
{
    IplImage* img = cvCreateImage( cvSize( 500, 500 ), 8, 3 );
 
    cvNamedWindow( "rect & circle", 1 );
        
	m_ImageType=-3;
    for(;;)
    {
        char key;
        int i, count = rand()%100 + 1;
        CvPoint pt0, pt;
        CvBox2D box;
        CvPoint2D32f box_vtx[4];
        CvPoint2D32f center;
        CvPoint icenter;
        float radius;

        CvPoint* points = (CvPoint*)malloc( count * sizeof(points[0]));
        CvMat pointMat = cvMat( 1, count, CV_32SC2, points );

        for( i = 0; i < count; i++ )
        {
            pt0.x = rand() % (img->width/2) + img->width/4;
            pt0.y = rand() % (img->height/2) + img->height/4;
            points[i] = pt0;
        }
        box = cvMinAreaRect2( &pointMat, 0 );
        cvMinEnclosingCircle( &pointMat, &center, &radius );

        cvBoxPoints( box, box_vtx );
        cvZero( img );
        for( i = 0; i < count; i++ )
        {
            pt0 = points[i];

            cvCircle( img, pt0, 2, CV_RGB( 255, 0, 0 ), CV_FILLED, CV_AA, 0 );
        }

        pt0.x = cvRound(box_vtx[3].x);
        pt0.y = cvRound(box_vtx[3].y);
        for( i = 0; i < 4; i++ )
        {
            pt.x = cvRound(box_vtx[i].x);
            pt.y = cvRound(box_vtx[i].y);
            cvLine(img, pt0, pt, CV_RGB(0, 255, 0), 1, CV_AA, 0);
            pt0 = pt;
        }
        icenter.x = cvRound(center.x);
        icenter.y = cvRound(center.y);
        cvCircle( img, icenter, cvRound(radius), CV_RGB(255, 255, 0), 1, CV_AA, 0 );

        cvShowImage( "rect & circle", img );

        key = (char) cvWaitKey(0);
        if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
            break;

        free( points );
	}
    
    cvDestroyWindow( "rect & circle" );

	m_ImageType=0;
}
//-------------------------------------
//  ��������ͼ��ָ�
//  ���ݡ�OpenCV�̳�(����ƪ)���� 5-9 �ı�
//  OpenCV ϵͳ�������ʵ�� pyramid_segmentation.c

IplImage*  images[2] = { 0, 0 }, *images0 = 0, *images1 = 0;
CvSize size;

int  w0, h0 , i;
int  threshold1, threshold2;
int  l,level = 4;
int sthreshold1, sthreshold2;
int  l_comp;
int block_size = 1000;
float  parameter;
double threshold;
double rezult, min_rezult;
int filter = CV_GAUSSIAN_5x5;
CvConnectedComp *cur_comp, min_comp;
CvSeq *comp;
//CvMemStorage *storage;

CvPoint pt1, pt2;

int n;

void CCVMFCView::OnAreaRect()               //  ��Ӿ��� (����ͨ)
{
	IplImage *image  = 0;
	IplImage *image2 = 0;

 	image = cvCloneImage( workImg );        //  ��������λͼ
	cvFlip(image);

 	image2=cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,3);
	cvCvtColor(image,image2,CV_GRAY2BGR);

	cvThreshold(image,image,128,255,CV_THRESH_BINARY);  //  ��ֵ��

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;

	cvFindContours(image,storage,&contours,sizeof(CvContour),
			CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);   //  ��������

	CvSeq* contourn = contours;
	for (int n=0; contourn != 0; contourn = contourn->h_next,n++) {
	}                                       //  ���߽���
	if ((!contours)||(n>1)) {
		cvReleaseMemStorage(&storage);
  		cvReleaseImage(&image2);
 		AfxMessageBox("��ѡ����ͨ����");
		return;
	}
 	int  length = contours->total;
	if (length<10) {
		cvReleaseMemStorage(&storage);
  		cvReleaseImage(&image2);
		return;
	}
 
	CvPoint* point = new CvPoint[length];
	CvSeqReader  reader;
	CvPoint pt = cvPoint(0,0);
 
	cvStartReadSeq(contours, &reader);      //  ȡ���߽��
	for (int i = 0; i < length; i++) {
		CV_READ_SEQ_ELEM(pt, reader);
		point[i]=pt;
	}

    CvRect  rect;
	CvPoint pt1,pt2;
    
    rect = cvBoundingRect( contours, 0 );   //  ������Ӿ���

 	pt1.x =rect.x;
	pt1.y =rect.y;
 	pt2.x =rect.x + rect.width -1;
	pt2.y =rect.y + rect.height-1;

	pt.x  =(pt1.x+pt2.x+1)/2;
	pt.y  =(pt1.y+pt2.y+1)/2;

 	cvCircle(image2, pt,  2, CV_RGB( 0, 255, 0 ), CV_FILLED );
	cvRectangle(image2,cvPoint(pt1.x,pt1.y),
			 cvPoint(pt2.x,pt2.y),CV_RGB(0,255,0),1,8,0);

	for ( i = 0; i < length; i++) {          //  ����ԭ���߽�
		int j = (i+1)%length;
		cvLine(image2,point[i],point[j],CV_RGB(255,0,0),1,8,0);
	}
 	
	cvReleaseMemStorage(&storage);          //  �ͷ���Դ
	delete [] point;
 	cvReleaseImage(&image);

	cvFlip(image2);
	m_dibFlag=imageReplace(image2,&workImg);
  	
	m_ImageType=-2;
	Invalidate();
}

void CCVMFCView::OnMinAreaRect()            //  ��С������� (����ͨ)
{
	IplImage *image  = 0;
	IplImage *image2 = 0;

 	image = cvCloneImage( workImg );        //  ��������λͼ
	cvFlip(image);

 	image2=cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,3);
	cvCvtColor(image,image2,CV_GRAY2BGR);

	cvThreshold(image,image,128,255,CV_THRESH_BINARY);  //  ��ֵ��

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;

	cvFindContours(image,storage,&contours,sizeof(CvContour),
			CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);   //  ��������

	CvSeq* contourn = contours;
	for (int n=0; contourn != 0; contourn = contourn->h_next,n++) {
	}                                       //  ���߽���
	if ((!contours)||(n>1)) {
		cvReleaseMemStorage(&storage);
  		cvReleaseImage(&image2);
 		AfxMessageBox("��ѡ����ͨ����");
		return;
	}
 	int  length = contours->total;
	if (length<10) {
		cvReleaseMemStorage(&storage);
  		cvReleaseImage(&image2);
		return;
	}
 
	CvPoint* point = new CvPoint[length];
	CvSeqReader  reader;
	CvPoint pt = cvPoint(0,0);
 
	cvStartReadSeq(contours, &reader);      //  ȡ���߽��
	for (int i = 0; i < length; i++) {
		CV_READ_SEQ_ELEM(pt, reader);
		point[i]=pt;
	}

    CvBox2D box2d;
	CvPoint pt1,pt2,pt3,pt4;
	double  dx,dy,alpha,beta,r,x0,y0,x1,y1,x2,y2;
  
    box2d = cvMinAreaRect2( contours, 0 );  //  ������С�������

	x0 = box2d.center.x;                    //  ����λ��
	y0 = box2d.center.y;
	alpha = -box2d.angle*CV_PI/180;         //  �Ƕ�ת���ɻ���
 	dx = box2d.size.height/2;               //  ���֮��(���ߡ���һ����)
 	dy = box2d.size.width/2;                //  �߶�֮��
    
	pt = cvPoint((int) (x0+0.5),(int) (y0+0.5));  //  ��������
	beta  = atan(dy/dx);
	r  = sqrt(dx*dx+dy*dy);
	x1 = r*cos(alpha+beta);
	y1 = r*sin(alpha+beta);
	x2 = r*cos(alpha-beta);
	y2 = r*sin(alpha-beta);

	pt1.x =(int) ( x0 + x1 + 0.5 );         //  �����ĸ��ǵ�����
	pt1.y =(int) ( y0 + y1 + 0.5 );
	pt2.x =(int) ( x0 + x2 + 0.5 );
	pt2.y =(int) ( y0 + y2 + 0.5 );
	pt3.x =(int) ( x0 - x1 + 0.5 );
	pt3.y =(int) ( y0 - y1 + 0.5 );
	pt4.x =(int) ( x0 - x2 + 0.5 );
	pt4.y =(int) ( y0 - y2 + 0.5 );
 
	cvCircle(image2, pt,  2, CV_RGB( 0, 255, 0 ), CV_FILLED );
	cvLine(image2,pt1,pt2,CV_RGB(0,255,0),1,8,0);
	cvLine(image2,pt2,pt3,CV_RGB(0,255,0),1,8,0);
	cvLine(image2,pt3,pt4,CV_RGB(0,255,0),1,8,0);
	cvLine(image2,pt4,pt1,CV_RGB(0,255,0),1,8,0);
 
	for (i = 0; i < length; i++) {          //  ����ԭ���߽�
		int j = (i+1)%length;
		cvLine(image2,point[i],point[j],CV_RGB(255,0,0),1,8,0);
	}
 	
	cvReleaseMemStorage(&storage);          //  �ͷ���Դ
	delete [] point;
 	cvReleaseImage(&image);

	cvFlip(image2);
	m_dibFlag=imageReplace(image2,&workImg);
  	
	m_ImageType=-2;
	Invalidate();
}

void CCVMFCView::OnApproxPoly()             //  ����αƽ� (����ͨ)
{
	IplImage *image  = 0;
	IplImage *image2 = 0;

 	image = cvCloneImage( workImg );        //  ��������λͼ
	cvFlip(image);

 	image2=cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,3);
	cvCvtColor(image,image2,CV_GRAY2BGR);

	cvThreshold(image,image,128,255,CV_THRESH_BINARY);  //  ��ֵ��

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;

	cvFindContours(image,storage,&contours,sizeof(CvContour),
			CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);   //  ��������

	CvSeq* contourn = contours;
	for (int n=0; contourn != 0; contourn = contourn->h_next,n++) {
	}                                       //  ���߽���
	if ((!contours)||(n>1)) {
		cvReleaseMemStorage(&storage);
  		cvReleaseImage(&image2);
 		AfxMessageBox("��ѡ����ͨ����");
		return;
	}

	int  length = contours->total;
	if (length<100) {
		cvReleaseMemStorage(&storage);
  		cvReleaseImage(&image2);
		return;
	}
 
	CvPoint* point = new CvPoint[length];
	CvSeqReader  reader;
	CvPoint pt = cvPoint(0,0);
	CvSeq* contour2 = contours;

	cvStartReadSeq(contour2, &reader);      //  ȡ���߽��
	for (int i = 0; i < length; i++) {
		CV_READ_SEQ_ELEM(pt, reader);
		point[i]=pt;
	}

	for (i = 0; i < length; i++) {          //  ����ԭ���߽�
		int j = (i+1)%length;
		cvLine(image2,point[i],point[j],CV_RGB(255,0,0),1,8,0);
	}
	
    contour2 = cvApproxPoly( contours, sizeof(CvContour), storage,
                    CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.001, 0 );

	length = contour2->total;
	cvStartReadSeq(contour2, &reader);      //  ȡ���߽��
	for (i = 0; i < length; i++) {
		CV_READ_SEQ_ELEM(pt, reader);
		point[i]=pt;
	}

	for (i = 0; i < length; i++) {          //  ���Ʊƽ��߽�
		int j = (i+1)%length;
		cvLine(image2,point[i],point[j],CV_RGB(0,255,0),1,8,0);
	}
 	
	cvReleaseMemStorage(&storage);
 	delete [] point;
 	cvReleaseImage(&image);

	cvFlip(image2);
	m_dibFlag=imageReplace(image2,&workImg);
  	
	m_ImageType=-2;
	Invalidate();
}

//-------------------------------------
//  �㼯͹��
//  ���ݡ�OpenCV�̳�(����ƪ)���� 5-18 �ı�
//  OpenCV ϵͳ�������ʵ�� convexhull.c
//  ������������е��������벿��
 
void CCVMFCView::OnConvexHull2() 
{
    cvNamedWindow( "hull", 1 );
    IplImage* img = cvCreateImage( cvSize( 500, 500 ), 8, 3 );

    CvMemStorage* storage = cvCreateMemStorage();

	m_ImageType=-3;
	for(;;)
	{
        int i, count = rand()%100 + 1, hullcount;
        CvPoint pt0;

        CvSeq* ptseq = cvCreateSeq( CV_SEQ_KIND_GENERIC|CV_32SC2, sizeof(CvContour),
                                     sizeof(CvPoint), storage );
        CvSeq* hull;

        for( i = 0; i < count; i++ )
        {
            pt0.x = rand() % (img->width/2) + img->width/4;
            pt0.y = rand() % (img->height/2) + img->height/4;
            cvSeqPush( ptseq, &pt0 );
        }
        hull = cvConvexHull2( ptseq, 0, CV_CLOCKWISE, 0 );
        hullcount = hull->total;

        cvZero( img );
        for( i = 0; i < count; i++ )
        {
            pt0 = *CV_GET_SEQ_ELEM( CvPoint, ptseq, i );
            cvCircle( img, pt0, 3, CV_RGB( 255, 0, 0 ), CV_FILLED );
        }

        pt0 = **CV_GET_SEQ_ELEM( CvPoint*, hull, hullcount - 1 );

        for( i = 0; i < hullcount; i++ )
        {
            CvPoint pt = **CV_GET_SEQ_ELEM( CvPoint*, hull, i );
            cvLine( img, pt0, pt, CV_RGB( 0, 255, 0 ));
            pt0 = pt;
        }
 
        cvShowImage( "hull", img );

        int key = cvWaitKey(0);
        if( key == 27 ) // 'ESC'
            break;
	}

    cvClearMemStorage( storage );
    cvDestroyWindow("hull");

	m_ImageType=0;
}

void CCVMFCView::OnConvexHull()             //  �㼯͹�� (�¼�����)
{
    IplImage* img = cvCreateImage( cvSize( 500, 500 ), 8, 3 );

    CvMemStorage* storage = cvCreateMemStorage();

    int i, count = rand()%100 + 1, hullcount;
    CvPoint pt0;

    CvSeq* ptseq = cvCreateSeq( CV_SEQ_KIND_GENERIC|CV_32SC2, sizeof(CvContour),
                                     sizeof(CvPoint), storage );
    CvSeq* hull;

    for( i = 0; i < count; i++ )
    {
        pt0.x = rand() % (img->width/2) + img->width/4;
        pt0.y = rand() % (img->height/2) + img->height/4;
        cvSeqPush( ptseq, &pt0 );
    }
    hull = cvConvexHull2( ptseq, 0, CV_CLOCKWISE, 0 );
    hullcount = hull->total;

    cvZero( img );
    for( i = 0; i < count; i++ )
    {
        pt0 = *CV_GET_SEQ_ELEM( CvPoint, ptseq, i );
        cvCircle( img, pt0, 3, CV_RGB( 255, 0, 0 ), CV_FILLED );
    }

    pt0 = **CV_GET_SEQ_ELEM( CvPoint*, hull, hullcount - 1 );

    for( i = 0; i < hullcount; i++ )
    {
        CvPoint pt = **CV_GET_SEQ_ELEM( CvPoint*, hull, i );
        cvLine( img, pt0, pt, CV_RGB( 0, 255, 0 ));
        pt0 = pt;
    }

	cvClearMemStorage( storage );

	cvFlip(img);                            //  ��ֱ����
	m_dibFlag=imageReplace(img,&workImg);   //  ���������
 
	m_ImageType=0;
 	Invalidate();
}

void CCVMFCView::OnAreaConvexHull()         //  ����͹�� (����ͨ)
{
	IplImage *image  = 0;
	IplImage *image2 = 0;

 	image = cvCloneImage( workImg );        //  ��������λͼ
//	cvFlip(image);

 	image2=cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,3);
	cvCvtColor(image,image2,CV_GRAY2BGR);

	cvThreshold(image,image,128,255,CV_THRESH_BINARY);  //  ��ֵ��

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;

	cvFindContours(image,storage,&contours,sizeof(CvContour),
			CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);   //  ��������

	CvSeq* contourn = contours;
	for (int n=0; contourn != 0; contourn = contourn->h_next,n++) {
	}                                       //  ���߽���
	if ((!contours)||(n>1)) {
		cvReleaseMemStorage(&storage);
  		cvReleaseImage(&image2);
 		AfxMessageBox("��ѡ����ͨ����");
		return;
	}
 	int  length = contours->total;
	if (length<100) {
		cvReleaseMemStorage(&storage);
  		cvReleaseImage(&image2);
		return;
	}
 
	CvPoint* point = new CvPoint[length];
	CvSeqReader  reader;
	CvPoint pt = cvPoint(0,0);
	CvSeq* contour2 = contours;

    CvSeq* hull;
	int    hullcount;
    CvPoint pt0;

    hull = cvConvexHull2( contour2, 0, CV_CLOCKWISE, 0 );  //  ����͹��
    hullcount = hull->total;

    pt0 = **CV_GET_SEQ_ELEM( CvPoint*, hull, hullcount - 1 );
    for(int i = 0; i < hullcount; i++ ) {                  //  ����͹��
        CvPoint pt = **CV_GET_SEQ_ELEM( CvPoint*, hull, i );
        cvLine( image2, pt0, pt, CV_RGB( 0, 255, 0 ), 2);
        pt0 = pt;
    }

	cvStartReadSeq(contour2, &reader);      //  ȡ���߽��
	for (i = 0; i < length; i++) {
		CV_READ_SEQ_ELEM(pt, reader);
		point[i]=pt;
	}

	for (i = 0; i < length; i++) {          //  ����ԭ���߽�
		int j = (i+1)%length;
		cvLine(image2,point[i],point[j],CV_RGB(255,0,0),1,8,0);
	}
 	
	cvReleaseMemStorage(&storage);
	delete [] point;
 	cvReleaseImage(&image);

//	cvFlip(image2);
	m_dibFlag=imageReplace(image2,&workImg);
  	
	m_ImageType=-2;
	Invalidate();
}

void CCVMFCView::OnConvexityDefects()       //  ���ɰ��� (����ͨ)
{
	IplImage *image  = 0;
	IplImage *image2 = 0;
	int  n, i, j, k, length, hullcount, defectcount;
 
 	image = cvCloneImage( workImg );        //  ��������λͼ
	cvFlip(image);

 	image2=cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,3);
	cvCvtColor(image,image2,CV_GRAY2BGR);

	cvThreshold(image,image,128,255,CV_THRESH_BINARY);  //  ��ֵ��

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;

	cvFindContours(image,storage,&contours,sizeof(CvContour),
			CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);   //  ��������

	CvSeq* contourn = contours;
	for ( n=0; contourn != 0; contourn = contourn->h_next,n++) {
	}                                       //  ���߽���
	if ((!contours)||(n>1)) {
		cvReleaseMemStorage(&storage);
  		cvReleaseImage(&image2);
 		AfxMessageBox("��ѡ����ͨ����");
		return;
	}
 	length = contours->total;
	if (length<100) {
		cvReleaseMemStorage(&storage);
  		cvReleaseImage(&image2);
		return;
	}
 
	CvSeqReader  reader;
	CvPoint* point = new CvPoint[length];
	CvSeq* contour2 = contours;

	cvStartReadSeq(contour2, &reader);      //  ȡ���߽��
	for ( i = 0; i < length; i++) {
 		CV_READ_SEQ_ELEM(point[i], reader);
	}
  	
    CvSeq* hull = 0;
  
    hull = cvConvexHull2( contour2, 0, CV_COUNTER_CLOCKWISE, 0 );  //  ����͹��
    hullcount = hull->total;

    CvSeq* defects = 0;
 
	defects = cvConvexityDefects( contour2, hull, 0);  //  ���ɰ���
    defectcount = defects->total;
 	CvConvexityDefect* defectArray = 
		new CvConvexityDefect[defectcount];

	CvPoint pts,pte;

	cvStartReadSeq( defects, &reader, 0);
    for( i = 0, j = 0, k = 1; i < defectcount; i++ ) {
        CV_READ_SEQ_ELEM( defectArray[i], reader );
		if (defectArray[i].depth>1) {       //  ��ȴ��� 1
			pts = *defectArray[i].start;    //  �������
			pte = *defectArray[i].end;      //  �����յ�

			while((point[j%length].x != pts.x)||
				(point[j%length].y != pts.y)) j++;  //  �߽���Ѱ�Ұ������
 			do {
 				cvLine( image2, point[j%length], point[(j+1)%length],
					CV_RGB( VgaDefPal[k].rgbRed ,   //  ���Ӱ����ڱ߽�
					VgaDefPal[k].rgbGreen , VgaDefPal[k].rgbBlue ), 2);
				j++;
			}
			while((point[j%length].x != pte.x)||    //  �߽���Ѱ�Ұ����յ�
				(point[j%length].y != pte.y));

			cvLine( image2, pts, pte,       //  ���Ӱ�������յ�
				CV_RGB( VgaDefPal[k].rgbRed , 
				VgaDefPal[k].rgbGreen , VgaDefPal[k].rgbBlue ), 2);
			k = NextColor( 1, k, 4 );       //  �޸���ɫֵ
		}
	}
  	
	cvReleaseMemStorage(&storage);
 	delete [] point;
 	delete [] defectArray;
 	cvReleaseImage(&image);

	cvFlip(image2);
	m_dibFlag=imageReplace(image2,&workImg);
  	
	m_ImageType=-2;
	Invalidate();
}

void CCVMFCView::OnContourTrack()           //  ��������
{   //  ���ݡ�����OpenCV�ļ�����Ӿ�����ʵ�֡����� 5-3 �ı�

 	int  mode = CV_RETR_CCOMP;
	int  contours_num = 0,color;
	CvScalar external_color;
	CvScalar hole_color;
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contour = 0;
	IplImage* pImg;
	IplImage* pContourImg = NULL;
	CvFont  font;
	char  ch[20];

 	cvFlip(workImg);
 	pImg = workImg;
	pContourImg = cvCreateImage(cvGetSize(pImg),IPL_DEPTH_8U,3);
	cvZero(pContourImg);

	mode = CV_RETR_LIST;
//---------------------------------------------------------
	contours_num=cvFindContours(pImg,storage,&contour,  //  ��������
		sizeof(CvContour),mode,CV_CHAIN_APPROX_NONE);
//---------------------------------------------------------

	color=2;
	for (int n=0; contour != 0; contour = contour->h_next,n++) {
//		external_color = CV_RGB(rand()&255,rand()&255,rand()&255);
//		hole_color = CV_RGB(rand()&255,rand()&255,rand()&255);
		external_color = CV_RGB(VgaDefPal[color].rgbRed,
			VgaDefPal[color].rgbGreen,VgaDefPal[color].rgbBlue);
		color=NextColor(2,color,4);         //  1 or 4
		hole_color = CV_RGB(192,192,192);
		cvDrawContours(pContourImg,contour,
				external_color,hole_color,1,1,8);
	}

	cvReleaseMemStorage(&storage);

	m_dibFlag=imageReplace(pContourImg,&workImg);  //  ���������

	if ((n>2)&&(workImg->width>200)&&(workImg->height>150)) {
		cvInitFont(&font,CV_FONT_HERSHEY_COMPLEX,0.4,0.4,0,1,CV_AA);
		sprintf(ch,"%d",contours_num);
		cvPutText(workImg,"contours_num",cvPoint(30,40),&font,CV_RGB(255,255,255));
		cvPutText(workImg,ch,cvPoint(30,60),&font,CV_RGB(255,255,255));
	}

 	cvFlip(workImg);
 
	m_ImageType=-2;
 	Invalidate();
}

/*
void CCVMFCView::OnDistance()               //  ����任
{                //  ���ݡ�OpenCV�̳�(����ƪ)���� 5-16 �ı�

	IplImage* pImg;
	IplImage* dist = NULL;
	IplImage* dist32s = NULL;
   
	pImg = workImg;
	dist = cvCreateImage(cvGetSize(pImg),IPL_DEPTH_32F,1);
	dist32s = cvCreateImage(cvGetSize(pImg),IPL_DEPTH_32S,1);

    cvDistTransform(pImg,dist,CV_DIST_L2,5,NULL);

	cvConvertScale(dist,dist,5000.0,0);
	cvPow(dist,dist,0.5);
 
	cvConvertScale(dist,dist32s,1.0,0.5);
//	cvAndS(dist32s,cvScalarAll(255),dist32s,0);
 	cvConvertScale(dist32s,pImg,1,0);
 
	cvReleaseImage(&dist);
	cvReleaseImage(&dist32s);
  
	m_ImageType=1;
 	Invalidate();
}
*/

void CCVMFCView::OnDistance()               //  ����任
{                                           //  �ò�ͬ��ɫ�����
	IplImage* pImg;
	IplImage* dist = NULL;
	IplImage* dist32s = NULL;
    
	pImg = workImg;                         //  ����λͼ����

	dist = cvCreateImage(cvGetSize(pImg),IPL_DEPTH_32F,1);
	dist32s = cvCreateImage(cvGetSize(pImg),IPL_DEPTH_32S,1);

//---------------------------------------------------------
//  ����任
    cvDistTransform(pImg,dist,CV_DIST_L2,5,NULL);

	cvConvertScale(dist,dist32s,1.0,0);     //  ת��Ϊ����

//---------------------------------------------------------
//  ����ֵת������ɫ���
	int   i,j,k,*pi,*tab,startColor,max;
	BYTE  *pb;

	pi=(int*)  (dist32s->imageData);
	for (i=0,max=0;i<dist->imageSize/4;i++,pi++) {
		if (abs(*pi)>max) max=(abs(*pi));   //  Ѱ��������
	}
	max++;

	tab =(int*) malloc(max*sizeof(int));
	startColor=1;
	tab[0]=255;                             //  �����ð�ɫ
	tab[1]=startColor;
	for (i=2;i<max;i++) {                   //  ������ɫ���ת����
		tab[i]=NextColor(startColor,tab[i-1],4);    //  1 or 4
	}

	k=min(pImg->width,dist32s->width);
	for (i=0;i<pImg->height;i++) {
		pb=(BYTE*) (pImg->imageData+i*pImg->widthStep);
		pi=(int*)  (dist32s->imageData+i*dist32s->widthStep);
		for (j=0;j<k;j++) pb[j]=tab[pi[j]];  //  ���ת��
	}
	free(tab);
//---------------------------------------------------------

	cvReleaseImage(&dist);
	cvReleaseImage(&dist32s);
  
	m_dibFlag  = 2;                         //  ���� VGA Ĭ�ϵ�ɫ��
	m_ImageType=-2;                         //  Ĭ�ϵ�ɫ��
 	Invalidate();
}

//---------------------------------------------------------
//  ��̬ѧ����

void CCVMFCView::OnUpdateErosion(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(abs(m_ImageType)==1));
}

void CCVMFCView::OnUpdateDilation(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(abs(m_ImageType)==1));
}

void CCVMFCView::OnUpdateOpenning(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(abs(m_ImageType)==1));
}

void CCVMFCView::OnUpdateClosing(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(abs(m_ImageType)==1));
}

void CCVMFCView::OnUpdateGrads(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(abs(m_ImageType)==1));
}

void CCVMFCView::OnUpdateGrayTophat(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnUpdateGrayBlackhat(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

//  ��ֵ���ֵ��̬ѧ����
void CCVMFCView::OnErosion()                //  ��ʴ
{
  	cvErode(workImg,workImg,0,1);
 	Invalidate();
}

void CCVMFCView::OnDilation()               //  ����
{
  	cvDilate(workImg,workImg,0,1);
 	Invalidate();
}

void CCVMFCView::OnOpenning()               //  ������
{
   	cvErode(workImg,workImg,0,1);
  	cvDilate(workImg,workImg,0,1);
  	Invalidate();
}

void CCVMFCView::OnClosing()                //  ������
{
  	cvDilate(workImg,workImg,0,1);
  	cvErode(workImg,workImg,0,1);
  	Invalidate();
}
  
void CCVMFCView::OnGrads()                  //  ��̬ѧ�ݶ�
{
	IplImage* in;
	IplImage* temp = NULL;
	IplImage* out  = NULL;
 
	in = workImg;

	temp = cvCreateImage(cvGetSize(in),
		IPL_DEPTH_8U,workImg->nChannels);
	out  = cvCreateImage(cvGetSize(in),
		IPL_DEPTH_8U,workImg->nChannels);

	cvMorphologyEx(in,out,temp,0,CV_MOP_GRADIENT,1);
/*	
	temp=cvCloneImage(in);   //  �˶γ������������ȼ�
	cvDilate(workImg,workImg,0,1);
  	cvErode(temp,temp,0,1);
	cvSub(workImg,temp,out,0);
*/
	m_dibFlag=imageReplace(out,&workImg);
   
	cvReleaseImage(&temp);
 
	Invalidate();
}

//  ����ֵ��̬ѧ����
void CCVMFCView::OnGrayTophat()             //  ��ñ�任
{
	IplImage* in;
	IplImage* temp = NULL;
	IplImage* out  = NULL;
 
	in = workImg;

	temp = cvCreateImage(cvGetSize(in),
		IPL_DEPTH_8U,workImg->nChannels);
	out  = cvCreateImage(cvGetSize(in),
		IPL_DEPTH_8U,workImg->nChannels);

	cvMorphologyEx(in,out,temp,0,CV_MOP_TOPHAT,1);
/*
	temp=cvCloneImage(in);   //  �˶γ������������ȼ�
   	cvErode(temp, temp,0,1);
  	cvDilate(temp,temp,0,1);
	cvSub(workImg,temp,out,0);
*/
	m_dibFlag=imageReplace(out,&workImg);
    
	cvReleaseImage(&temp);
 
	Invalidate();
}

void CCVMFCView::OnGrayBlackhat()           //  ���ȼ�� (�ڶ�ñ�任)
{
	IplImage* in;
	IplImage* temp = NULL;
	IplImage* out  = NULL;
 
	in = workImg;

	temp = cvCreateImage(cvGetSize(in),
		IPL_DEPTH_8U,workImg->nChannels);
	out  = cvCreateImage(cvGetSize(in),
		IPL_DEPTH_8U,workImg->nChannels);

	cvMorphologyEx(in,out,temp,0,CV_MOP_BLACKHAT,1);
/*	
	temp=cvCloneImage(in);   //  �˶γ������������ȼ�
	cvDilate(temp,temp,0,1);
  	cvErode(temp,temp,0,1);
	cvSub(temp,workImg,out,0);
*/
	m_dibFlag=imageReplace(out,&workImg);
	cvNot(workImg,workImg);
   
	cvReleaseImage(&temp);
 
	Invalidate();
}

//---------------------------------------------------------
//  �ۺϴ���

void CCVMFCView::OnUpdateImageShrink(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag==0)&&
		(m_ImageType)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateRadialGrads(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType>2));
}

void CCVMFCView::OnUpdateCannyBorddetec(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag==0)&&
		(m_ImageType)&&(m_ImageType>0));
}
 
void CCVMFCView::OnUpdateHoughLines(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag==0)&&
		(m_ImageType)&&(m_ImageType>0));
}

void CCVMFCView::OnUpdateHoughCircle(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag==0)&&
		(m_ImageType)&&(m_ImageType>0));
}

void CCVMFCView::OnUpdateSquaresTest(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag==0)&&
		(m_ImageType)&&(m_ImageType>0));
}

void CCVMFCView::OnUpdateFloodFill(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdatePyrSegmentation(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateFitEllipse(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType>0));
}

void CCVMFCView::OnUpdateSnake(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==1));
}

void CCVMFCView::OnUpdateWatershed(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateCornersTest(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType>0));
}

void CCVMFCView::OnUpdateClusters(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==0));
}

void CCVMFCView::OnUpdateSeqPartition(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==0));
}

void CCVMFCView::OnUpdateRotationTrack(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==0));
}

void CCVMFCView::OnUpdateFaceDetect(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

//-------------------------------------
//  ͼ������
//  ���ݡ�ѧϰOpenCV���� 2-5 �ı�

IplImage* doPyrDown(IplImage* in, int filter=IPL_GAUSSIAN_5x5)
{                                           //  λͼ��Сһ��
	if (in->width%2) in->width++;//��ʾλͼ�Ŀ��ż��
	IplImage* out = cvCreateImage(cvSize(in->width/2,
			in->height/2),in->depth,in->nChannels);
	cvPyrDown(in,out);                      //  λͼ��С
	return(out);
}

void CCVMFCView::OnImageShrink()            //  ͼ������
{
	IplImage* in;
	IplImage* out = 0;
 
	in = workImg;
	if ((in->nChannels==3)&&                //  ������ż�������ɫͼ��
			((in->width%2)||(in->height%2))) {
		out = cvCreateImage(cvSize((in->width+1)/2,
			(in->height+1)/2),in->depth,in->nChannels);
		ImageDwindle(in,out,2,in->nChannels);
	}
	else 
 		out = doPyrDown(in);                //  ͼ����С

	if (out)
		m_dibFlag=imageReplace(out,&workImg);   //  ���������
	Invalidate();
}

void CCVMFCView::OnRadialGrads()            //  �����ݶȱ任 
{   //  ���ݡ�����OpenCV�ļ�����Ӿ�����ʵ�֡����� 1-1 �ı�

	CvPoint center;
	double  scale = -3;
	IplImage* image;
 
	image = workImg;

	center = cvPoint(image->width/2,image->height/2);

	for (int i=0; i<image->height; i++) {
		for (int j=0; j<image->width; j++) {
			double dx=(double)(j-center.x)/center.x;
			double dy=(double)(i-center.y)/center.y;
			double weight=exp((dx*dx+dy*dy)*scale);
			uchar *ptr = &CV_IMAGE_ELEM(image,uchar,i,j*3);
			ptr[0]=cvRound(ptr[0]*weight);
			ptr[1]=cvRound(ptr[1]*weight);
			ptr[2]=cvRound(ptr[2]*weight);
		}
	}
 
	Invalidate();
}

void CCVMFCView::OnCannyBorddetec()         //  Canny ��Ե���
{                         //  ���ݡ�ѧϰOpenCV���� 2-6 �ı�
    //  ���幤��λͼ
	IplImage* pImg8u = NULL;
	IplImage* pImg8uSmooth = NULL;
	IplImage* pImgCanny = NULL;
 
	//**  ���������ͼ��  **                //  �޸Ĳ��� 1

	if (workImg->nChannels==3) {
 		pImg8u=cvCreateImage(cvGetSize(workImg),IPL_DEPTH_8U,1);
		cvCvtColor(workImg,pImg8u,CV_BGR2GRAY);
		imageReplace(pImg8u,&workImg);
	}
 	pImg8u = workImg;

    //  ��������λͼ
	pImg8uSmooth=cvCreateImage(cvGetSize(pImg8u),IPL_DEPTH_8U,1);
	pImgCanny   =cvCreateImage(cvGetSize(pImg8u),IPL_DEPTH_8U,1);

	//  ͼ����
 	cvSmooth(pImg8u,pImg8uSmooth,CV_GAUSSIAN,3,0,0);
	cvCanny(pImg8uSmooth,pImgCanny,100,200,3);

 	//  �ͷ�λͼ
	cvReleaseImage(&pImg8uSmooth);
  
	//**  ���������  **                  //  �޸Ĳ��� 2
	m_dibFlag=imageReplace(pImgCanny,&workImg);
  	
	//**  ���ñ�־��ˢ�´���  **            //  �޸Ĳ��� 3
	m_ImageType=1;
	Invalidate();
}

//-------------------------------------
//  Hough �任 (ֱ��)
//  ���� OpenCV ϵͳ�������ʵ�� houghlines.c �ı�

void CCVMFCView::OnHoughLines() 
{
    IplImage* src = 0;
    IplImage* dst = 0;
    IplImage* color_dst = 0;
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* lines = 0;
    int i;

	if (workImg->nChannels==3) {
 		src = cvCreateImage(cvGetSize(workImg), IPL_DEPTH_8U, 1);
		cvCvtColor(workImg, src, CV_BGR2GRAY);
	}
	else {
        src = cvCloneImage( workImg );
	}
	cvFlip(src);
     
    dst = cvCreateImage( cvGetSize(src), 8, 1 );
    color_dst = cvCreateImage( cvGetSize(src), 8, 3 );
    
    cvCanny( src, dst, 50, 200, 3 );
    cvCvtColor( dst, color_dst, CV_GRAY2BGR );

    lines = cvHoughLines2( dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, 50, 50, 10 );
    for( i = 0; i < lines->total; i++ )
    {
        CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
        cvLine( color_dst, line[0], line[1], CV_RGB(255,0,0), 3, CV_AA, 0 );
    }

    cvNamedWindow( "Hough", 1 );
    cvShowImage( "Hough", color_dst );

    cvWaitKey(0);

    cvReleaseMemStorage(&storage );
    cvReleaseImage( &src );
    cvReleaseImage( &dst );
    cvReleaseImage( &color_dst );
    cvDestroyWindow( "Hough" );
}

//-------------------------------------
//  Hough �任 (Բ)
//  ���ݡ�����OpenCV�ļ�����Ӿ�����ʵ�֡�����6-6 �ı�

void CCVMFCView::OnHoughCircle() 
{
    IplImage* pImage = NULL;
    IplImage* pImg8U = NULL;
    CvMemStorage* storage = NULL;
    CvSeq* circles = NULL;

	if (workImg->nChannels==3) {
        pImage = cvCloneImage( workImg );
	}
	else {
 		pImage = cvCreateImage(cvGetSize(workImg), IPL_DEPTH_8U, 3);
		cvCvtColor(workImg, pImage, CV_GRAY2BGR);
	}
	cvFlip(pImage);
     
    pImg8U = cvCreateImage( cvGetSize(pImage), 8, 1 );
	cvCvtColor(pImage, pImg8U, CV_BGR2GRAY);
    cvSmooth( pImg8U, pImg8U, CV_GAUSSIAN, 7, 7 );
 
	storage = cvCreateMemStorage(0);

    circles = cvHoughCircles( pImg8U, storage, CV_HOUGH_GRADIENT,
					2, pImg8U->height/10, 100, 55 );

    int i;
    for( i = 0; i < circles->total; i++ )
    {
        float* p = (float*)cvGetSeqElem(circles,i);
        cvCircle( pImage, cvPoint(cvRound(p[0]), cvRound(p[1])), 
					cvRound(p[2]),CV_RGB(255,0,0), 1, CV_AA, 0 );
    }

    cvReleaseMemStorage( &storage );
    cvReleaseImage( &pImg8U );

	cvFlip(pImage);
	m_dibFlag=imageReplace( pImage, &workImg);
  	
	m_ImageType=-2;
	Invalidate();
}

//-------------------------------------
//  ƽ���ı��μ��
//  ���� OpenCV ϵͳ�������ʵ�� squares.c �ı�

int thresh = 50;
IplImage* img = 0;
IplImage* img0 = 0;
CvMemStorage* storage = 0;
const char* wndname = "Square Detection Demo";

// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2 
double angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 )
{
    double dx1 = pt1->x - pt0->x;
    double dy1 = pt1->y - pt0->y;
    double dx2 = pt2->x - pt0->x;
    double dy2 = pt2->y - pt0->y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
CvSeq* findSquares4( IplImage* img, CvMemStorage* storage )
{
    CvSeq* contours;
    int i, c, l, N = 11;
    CvSize sz = cvSize( img->width & -2, img->height & -2 );
    IplImage* timg = cvCloneImage( img ); // make a copy of input image
    IplImage* gray = cvCreateImage( sz, 8, 1 ); 
    IplImage* pyr = cvCreateImage( cvSize(sz.width/2, sz.height/2), 8, 3 );
    IplImage* tgray;
    CvSeq* result;
    double s, t;
    // create empty sequence that will contain points -
    // 4 points per square (the square's vertices)
    CvSeq* squares = cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), storage );
    
    // select the maximum ROI in the image
    // with the width and height divisible by 2
    cvSetImageROI( timg, cvRect( 0, 0, sz.width, sz.height ));
    
    // down-scale and upscale the image to filter out the noise
    cvPyrDown( timg, pyr, 7 );
    cvPyrUp( pyr, timg, 7 );
    tgray = cvCreateImage( sz, 8, 1 );
    
    // find squares in every color plane of the image
    for( c = 0; c < 3; c++ )
    {
        // extract the c-th color plane
        cvSetImageCOI( timg, c+1 );
        cvCopy( timg, tgray, 0 );
        
        // try several threshold levels
        for( l = 0; l < N; l++ )
        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading   
            if( l == 0 )
            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging) 
                cvCanny( tgray, gray, 0, thresh, 5 );
                // dilate canny output to remove potential
                // holes between edge segments 
                cvDilate( gray, gray, 0, 1 );
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                cvThreshold( tgray, gray, (l+1)*255/N, 255, CV_THRESH_BINARY );
            }
            
            // find contours and store them all as a list
            cvFindContours( gray, storage, &contours, sizeof(CvContour),
                CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
            
            // test each contour
            while( contours )
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                result = cvApproxPoly( contours, sizeof(CvContour), storage,
                    CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0 );
                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if( result->total == 4 &&
                    fabs(cvContourArea(result,CV_WHOLE_SEQ)) > 1000 &&
                    cvCheckContourConvexity(result) )
                {
                    s = 0;
                    
                    for( i = 0; i < 5; i++ )
                    {
                        // find minimum angle between joint
                        // edges (maximum of cosine)
                        if( i >= 2 )
                        {
                            t = fabs(angle(
                            (CvPoint*)cvGetSeqElem( result, i ),
                            (CvPoint*)cvGetSeqElem( result, i-2 ),
                            (CvPoint*)cvGetSeqElem( result, i-1 )));
                            s = s > t ? s : t;
                        }
                    }
                    
                    // if cosines of all angles are small
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence 
                    if( s < 0.3 )
                        for( i = 0; i < 4; i++ )
                            cvSeqPush( squares,
                                (CvPoint*)cvGetSeqElem( result, i ));
                }
                
                // take the next contour
                contours = contours->h_next;
            }
        }
    }
    
    // release all the temporary images
    cvReleaseImage( &gray );
    cvReleaseImage( &pyr );
    cvReleaseImage( &tgray );
    cvReleaseImage( &timg );
    
    return squares;
}

// the function draws all the squares in the image
void drawSquares( IplImage* img, CvSeq* squares )
{
    CvSeqReader reader;
    IplImage* cpy = cvCloneImage( img );
    int i;
    
    // initialize reader of the sequence
    cvStartReadSeq( squares, &reader, 0 );
    
    // read 4 sequence elements at a time (all vertices of a square)
    for( i = 0; i < squares->total; i += 4 )
    {
        CvPoint pt[4], *rect = pt;
        int count = 4;
        
        // read 4 vertices
        CV_READ_SEQ_ELEM( pt[0], reader );
        CV_READ_SEQ_ELEM( pt[1], reader );
        CV_READ_SEQ_ELEM( pt[2], reader );
        CV_READ_SEQ_ELEM( pt[3], reader );
        
        // draw the square as a closed polyline 
        cvPolyLine( cpy, &rect, &count, 1, 1, CV_RGB(0,255,0), 3, CV_AA, 0 );
    }
    
    // show the resultant image
    cvShowImage( wndname, cpy );
    cvReleaseImage( &cpy );
}

void CCVMFCView::OnSquaresTest()            //  ƽ���ı��μ��
{
    storage = cvCreateMemStorage(0);

	if (workImg->nChannels==1) {
 		img0 = cvCreateImage(cvGetSize(workImg), IPL_DEPTH_8U, 3);
		cvCvtColor(workImg, img0, CV_GRAY2BGR);
	}
	else {
        img0 = cvCloneImage( workImg );
	}
	cvFlip(img0);
    img = cvCloneImage( img0 );
        
    // create window and a trackbar (slider) with parent "image" and set callback
    // (the slider regulates upper threshold, passed to Canny edge detector) 
    cvNamedWindow( wndname, 1 );
        
    // find and draw the squares
    drawSquares( img, findSquares4( img, storage ) );
        
    // wait for key.
    // Also the function cvWaitKey takes care of event processing
    int c = cvWaitKey(0);
    // release both images
    cvReleaseImage( &img );
    cvReleaseImage( &img0 );
    // clear memory storage - reset free space position
    
    cvDestroyWindow( wndname );
}

//-------------------------------------
//  �������
//  ���ݡ�OpenCV�̳�(����ƪ)���� 5-7 �ı�
//  OpenCV ϵͳ�������ʵ�� ffilldemo.c

IplImage* color_img0;
IplImage* mask;
IplImage* color_img;
IplImage* gray_img0 = NULL;
IplImage* gray_img = NULL;
int ffill_case = 1;
int lo_diff = 20, up_diff = 20;
int connectivity = 4;
int is_color = 1;
int is_mask = 0;
int new_mask_val = 255;

void on_mousef( int event, int x, int y, int flags, void* param )
{
    if( !color_img )
        return;

    switch( event )
    {
    case CV_EVENT_LBUTTONDOWN:
        {
            CvPoint seed = cvPoint(x,y);
            int lo = ffill_case == 0 ? 0 : lo_diff;
            int up = ffill_case == 0 ? 0 : up_diff;
            int flags = connectivity + (new_mask_val << 8) +
                        (ffill_case == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
            int b = rand() & 255, g = rand() & 255, r = rand() & 255;
            CvConnectedComp comp;

            if( is_mask )
                cvThreshold( mask, mask, 1, 128, CV_THRESH_BINARY );
            
            if( is_color )
            {
                CvScalar color = CV_RGB( r, g, b );
                cvFloodFill( color_img, seed, color, CV_RGB( lo, lo, lo ),
                             CV_RGB( up, up, up ), &comp, flags, is_mask ? mask : NULL );
                cvShowImage( "image", color_img );
            }
            else
            {
                CvScalar brightness = cvRealScalar((r*2 + g*7 + b + 5)/10);
                cvFloodFill( gray_img, seed, brightness, cvRealScalar(lo),
                             cvRealScalar(up), &comp, flags, is_mask ? mask : NULL );
                cvShowImage( "image", gray_img );
            }

            printf("%g pixels were repainted\n", comp.area );

            if( is_mask )
                cvShowImage( "mask", mask );
        }
        break;
    }
}

void CCVMFCView::OnFloodFill() 
{
//    char* filename = argc >= 2 ? argv[1] : (char*)"fruits.jpg";

//    if( (color_img0 = cvLoadImage(filename,1)) == 0 )
//        return 0;

	color_img0 = cvCloneImage(workImg);
	cvFlip(color_img0);

/*
    printf( "Hot keys: \n"
            "\tESC - quit the program\n"
            "\tc - switch color/grayscale mode\n"
            "\tm - switch mask mode\n"
            "\tr - restore the original image\n"
            "\ts - use null-range floodfill\n"
            "\tf - use gradient floodfill with fixed(absolute) range\n"
            "\tg - use gradient floodfill with floating(relative) range\n"
            "\t4 - use 4-connectivity mode\n"
            "\t8 - use 8-connectivity mode\n" );
*/ 
	
    color_img = cvCloneImage( color_img0 );
    gray_img0 = cvCreateImage( cvSize(color_img->width, color_img->height), 8, 1 );
    cvCvtColor( color_img, gray_img0, CV_BGR2GRAY );
    gray_img = cvCloneImage( gray_img0 );
    mask = cvCreateImage( cvSize(color_img->width + 2, color_img->height + 2), 8, 1 );

    cvNamedWindow( "image", 0 );
    cvCreateTrackbar( "lo_diff", "image", &lo_diff, 255, NULL );
    cvCreateTrackbar( "up_diff", "image", &up_diff, 255, NULL );

    cvSetMouseCallback( "image", on_mousef, 0 );

	m_ImageType=-3;
    for(;;)
    {
        int c;
        
        if( is_color )
            cvShowImage( "image", color_img );
        else
            cvShowImage( "image", gray_img );

        c = cvWaitKey(0);
        switch( (char) c )
        {
        case '\x1b':
            printf("Exiting ...\n");
            goto exit_main;
        case 'c':
            if( is_color )
            {
                printf("Grayscale mode is set\n");
                cvCvtColor( color_img, gray_img, CV_BGR2GRAY );
                is_color = 0;
            }
            else
            {
                printf("Color mode is set\n");
                cvCopy( color_img0, color_img, NULL );
                cvZero( mask );
                is_color = 1;
            }
            break;
        case 'm':
            if( is_mask )
            {
                cvDestroyWindow( "mask" );
                is_mask = 0;
            }
            else
            {
                cvNamedWindow( "mask", 0 );
                cvZero( mask );
                cvShowImage( "mask", mask );
                is_mask = 1;
            }
            break;
        case 'r':
            printf("Original image is restored\n");
            cvCopy( color_img0, color_img, NULL );
            cvCopy( gray_img0, gray_img, NULL );
            cvZero( mask );
            break;
        case 's':
            printf("Simple floodfill mode is set\n");
            ffill_case = 0;
            break;
        case 'f':
            printf("Fixed Range floodfill mode is set\n");
            ffill_case = 1;
            break;
        case 'g':
            printf("Gradient (floating range) floodfill mode is set\n");
            ffill_case = 2;
            break;
        case '4':
            printf("4-connectivity mode is set\n");
            connectivity = 4;
            break;
        case '8':
            printf("8-connectivity mode is set\n");
            connectivity = 8;
            break;
        }
    }

exit_main:

    cvDestroyWindow( "image" );
	if (is_mask)
		cvDestroyWindow( "mask" );
    cvReleaseImage( &gray_img );
    cvReleaseImage( &gray_img0 );
    cvReleaseImage( &color_img );
    cvReleaseImage( &color_img0 );
    cvReleaseImage( &mask );

	m_ImageType=imageType(workImg);
}


void ON_SEGMENT(int a)
{   
    cvPyrSegmentation(images0, images1, storage, &comp, 
                      level, threshold1+1, threshold2+1);

    /*l_comp = comp->total;

    i = 0;
    min_comp.value = cvScalarAll(0);
    while(i<l_comp)
    {
        cur_comp = (CvConnectedComp*)cvGetSeqElem ( comp, i );
        if(fabs(255- min_comp.value.val[0])>
           fabs(255- cur_comp->value.val[0]) &&
           fabs(min_comp.value.val[1])>
           fabs(cur_comp->value.val[1]) &&
           fabs(min_comp.value.val[2])>
           fabs(cur_comp->value.val[2]) )
           min_comp = *cur_comp;
        i++;
    }*/
    cvShowImage("Segmentation", images1);
}

void CCVMFCView::OnPyrSegmentation() 
{
//    char* filename = argc == 2 ? argv[1] : (char*)"fruits.jpg";
//        if( (images[0] = cvLoadImage( filename, 1)) == 0 )
//        return -1;

//    cvNamedWindow("Source", 1);
//    cvShowImage("Source", images[0]);

	images[0] = cvCloneImage(workImg);
	cvFlip(images[0]);
 
    cvNamedWindow("Segmentation", 1);

    storage = cvCreateMemStorage ( block_size );

    images[0]->width &= -(1<<level);
    images[0]->height &= -(1<<level);

    images0 = cvCloneImage( images[0] );
    images1 = cvCloneImage( images[0] );
    // �Բ�ɫͼ����зָ�
    l = 1;
    threshold1 =255;
    threshold2 =30;

    ON_SEGMENT(1);

	sthreshold1 = cvCreateTrackbar("Threshold1", "Segmentation", 
						&threshold1, 255, ON_SEGMENT);
	sthreshold2 = cvCreateTrackbar("Threshold2", "Segmentation",   
						&threshold2, 255,ON_SEGMENT);

    cvShowImage("Segmentation", images1);

    cvWaitKey(0);

    cvReleaseMemStorage(&storage );
    cvReleaseImage(&images[0]);
    cvReleaseImage(&images0);
    cvReleaseImage(&images1);

    cvDestroyWindow("Segmentation");
//    cvDestroyWindow("Source");
}

//-------------------------------------
//  ��Բ�������
//  ���ݡ�OpenCV�̳�(����ƪ)���� 5-17 �ı�
//  OpenCV ϵͳ�������ʵ�� fitellipse.c

int slider_pos = 110;

IplImage *image02 = 0, *image03 = 0, *image04 = 0;

// Define trackbar callback functon. This function find contours,
// draw it and approximate it by ellipses.
void process_image(int h)
{
    CvMemStorage* stor;
    CvSeq* cont;
    CvBox2D32f* box;
    CvPoint* PointArray;
    CvPoint2D32f* PointArray2D32f;
    
    // ������̬�ṹ����
    stor = cvCreateMemStorage(0);
    cont = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint) , stor);
    
    // ��ֵ��ͼ��.
    cvThreshold( image03, image02, slider_pos, 255, CV_THRESH_BINARY );
    
    // Ѱ����������.
    cvFindContours( image02, stor, &cont, sizeof(CvContour), 
                    CV_RETR_LIST, CV_CHAIN_APPROX_NONE, cvPoint(0,0));
    
    // Clear images. IPL use.
    cvZero(image02);
    cvZero(image04);
    
    // ��ѭ��������������������Բ���.
    for(;cont;cont = cont->h_next)
    {   
        int i; // Indicator of cycle.
        int count = cont->total; // This is number point in contour
        CvPoint center;
        CvSize size;
        
        // Number point must be more than or equal to 6 (for cvFitEllipse_32f).        
        if( count < 6 )
            continue;
        
        // Alloc memory for contour point set.    
        PointArray = (CvPoint*)malloc( count*sizeof(CvPoint) );
        PointArray2D32f= (CvPoint2D32f*)malloc( count*sizeof(CvPoint2D32f) );
        
        // Alloc memory for ellipse data.
        box = (CvBox2D32f*)malloc(sizeof(CvBox2D32f));
        
        // Get contour point set.
        cvCvtSeqToArray(cont, PointArray, CV_WHOLE_SEQ);
        
        // Convert CvPoint set to CvBox2D32f set.
        for(i=0; i<count; i++)
        {
            PointArray2D32f[i].x = (float)PointArray[i].x;
            PointArray2D32f[i].y = (float)PointArray[i].y;
        }
        
        //��ϵ�ǰ����.
        cvFitEllipse(PointArray2D32f, count, box);
        
        // ���Ƶ�ǰ����.
        cvDrawContours(image04,cont,CV_RGB(255,255,255),
					CV_RGB(255,255,255),0,1,8,cvPoint(0,0));
        
        // Convert ellipse data from float to integer representation.
        center.x = cvRound(box->center.x);
        center.y = cvRound(box->center.y);
        size.width = cvRound(box->size.width*0.5);
        size.height = cvRound(box->size.height*0.5);
        box->angle = -box->angle;
        
        // Draw ellipse.
        cvEllipse(image04, center, size,
                  box->angle, 0, 360,
                  CV_RGB(0,0,255), 1, CV_AA, 0);
        
        // Free memory.          
        free(PointArray);
        free(PointArray2D32f);
        free(box);
    }
    
    // Show image. HighGUI use.
	cvFlip(image04);
    cvShowImage( "Result", image04 );
}

void CCVMFCView::OnFitEllipse()             //  ��Բ�������
{
//  const char* filename = argc == 2 ? argv[1] : (char*)"stuff.jpg";
    
    //  ����ͼ��ǿ��Ϊ�Ҷ�ͼ��
//  if( (image03 = cvLoadImage(filename, 0)) == 0 )
//      return -1;

	if (workImg->nChannels==1) image03=workImg;
	else {
 		image03=cvCreateImage(cvGetSize(workImg),IPL_DEPTH_8U,1);
		cvCvtColor(workImg,image03,CV_BGR2GRAY);
		imageReplace(image03,&workImg);
		m_dibFlag=1;                        //  workImg ���͸ı����־
	}

    // Create the destination images
    image02 = cvCloneImage( image03 );
    image04 = cvCloneImage( image03 );

    // Create windows.
//  cvNamedWindow("Source", 1);
    cvNamedWindow("Result", 1);

    // Show the image.
//  cvShowImage("Source", image03);

    // Create toolbars. HighGUI use.
    cvCreateTrackbar( "Threshold", "Result", &slider_pos, 255, process_image );

    process_image(0);

    // Wait for a key stroke; the same function arranges events processing                
	m_ImageType=-3;
    cvWaitKey(0);

    cvReleaseImage(&image02);
//  cvReleaseImage(&image03);

//  cvDestroyWindow("Source");
    cvDestroyWindow("Result");

	cvFlip(image04);
	m_dibFlag=imageReplace(image04,&workImg);
  	
	m_ImageType=-1;
	Invalidate();
}

//-------------------------------------
//  Snake �㷨 
//  ���ݡ�����OpenCV�ļ�����Ӿ�����ʵ�֡� 13.7 �ڳ���ı�

char *theWin="Snake Window";
IplImage *image0 = 0;
IplImage *image1 = 0;
IplImage *image  = 0;
IplImage *image2 = 0;

int  Thresholdness = 80;
int  ialpha = 20;
int  ibeta  = 20;
int  igamma = 20;
   
void onChange(int pos)
{
	cvCopy(image0,image);                   //  �ָ�ԭʼͼ��
	cvCopy(image1,image2);

	cvThreshold(image,image,Thresholdness,255,CV_THRESH_BINARY);  //  ��ֵ��

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;

	cvFindContours(image,storage,&contours,sizeof(CvContour),
			CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);   //  ��������

	if (!contours) return;
 	int  length = contours->total;
	if (length<10) return;
 
	CvPoint* point = new CvPoint[length];
	CvSeqReader  reader;
	CvPoint pt = cvPoint(0,0);
	CvSeq* contour2 = contours;

	cvStartReadSeq(contour2, &reader);      //  ȡ���߽��
	for (int i = 0; i < length; i++) {
		CV_READ_SEQ_ELEM(pt, reader);
		point[i]=pt;
	}
	cvReleaseMemStorage(&storage);

	for (i = 0; i < length; i++) {          //  ����ԭ���߽�
		int j = (i+1)%length;
		cvLine(image2,point[i],point[j],CV_RGB(255,0,0),1,8,0);
	}

	float alpha = ialpha/100.0f;
	float beta  = ibeta /100.0f;
	float gamma = igamma/100.0f;
	CvTermCriteria criteria;
	criteria.type = CV_TERMCRIT_ITER;
	criteria.max_iter = 1000;
	criteria.epsilon = 0.1;
    CvSize win;

    win.height = win.width = 3;
	
	cvSnakeImage(image, point, length, &alpha, &beta,
			&gamma, CV_VALUE, win, criteria, 0);  //  �����±߽�

	for (i = 0; i < length; i++) {          //  �����±߽�
		int j = (i+1)%length;
		cvLine(image2,point[i],point[j],CV_RGB(0,255,0),1,8,0);
	}

	delete [] point;
 
	cvShowImage( theWin, image2 );
}

void CCVMFCView::OnSnake()                  //  Snake ԭ��
{
	int  flag=0,thre=0;

  	image0 = cvCloneImage( workImg );       //  ��������λͼ
	cvFlip(image0);
 	image =cvCreateImage(cvGetSize(image0),IPL_DEPTH_8U,1);
 	image1=cvCreateImage(cvGetSize(image0),IPL_DEPTH_8U,3);
	cvCvtColor(image0,image1,CV_GRAY2BGR);
 	image2=cvCreateImage(cvGetSize(image0),IPL_DEPTH_8U,3);
 
    cvNamedWindow(theWin, 0);
	cvResizeWindow(theWin, 400, 600);

    cvCreateTrackbar( "Thresh", theWin, &Thresholdness, 255, onChange );
    cvCreateTrackbar( "Alpha", theWin, &ialpha, 255, onChange );
    cvCreateTrackbar( "Beta", theWin, &ibeta, 255, onChange );
    cvCreateTrackbar( "Gamma", theWin, &igamma, 255, onChange );

	onChange(0);

	m_ImageType=-3;
	for (;;) {
		if (cvWaitKey(40)==27) break;

		if (flag==0) {
  			imageClone(image2,&workImg);
 			free(m_lpBmi);
			m_lpBmi=CtreateMapInfo(workImg,m_dibFlag);
			flag=1;
		}
		if (Threshold != thre) {
  			cvCopy(image2,workImg);
			cvFlip(workImg);

			CClientDC dc(this);
			StretchDIBits(dc.m_hDC,0,0,workImg->width,workImg->height,  //  ˢ��������
				0,0,workImg->width,workImg->height,
				workImg->imageData,m_lpBmi,DIB_RGB_COLORS,SRCCOPY);
			thre = Thresholdness;
		}
	}

 	cvReleaseImage(&image);
 	cvReleaseImage(&image0);
 	cvReleaseImage(&image1);
    cvDestroyWindow(theWin);

	cvFlip(image2);
	m_dibFlag=imageReplace(image2,&workImg);
  	
	Invalidate();
}
 
//-------------------------------------
//  ��ˮ���㷨ԭ��
//  ���� OpenCV ϵͳ�������ʵ�� watershed.cpp �ı�

IplImage* marker_mask = 0;
IplImage* markers = 0;
//IplImage* img0 = 0, *img = 0, *img_gray = 0, *wshed = 0;
IplImage  *img_gray = 0, *wshed = 0;
CvPoint prev_pt = {-1,-1};

void on_mouse( int event, int x, int y, int flags, void* param )
{
    if( !img )
        return;

    if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
        prev_pt = cvPoint(-1,-1);
    else if( event == CV_EVENT_LBUTTONDOWN )
        prev_pt = cvPoint(x,y);
    else if( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) )
    {
        CvPoint pt = cvPoint(x,y);
        if( prev_pt.x < 0 )
            prev_pt = pt;
        cvLine( marker_mask, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
        cvLine( img, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
        prev_pt = pt;
        cvShowImage( "image", img );
    }
}

void CCVMFCView::OnWatershed()              //  ��ˮ��ԭ��
{
	int   flag=0;
    CvRNG rng = cvRNG(-1);

	img0 = cvCloneImage( workImg );         //  ��������λͼ
	cvFlip(img0);

    cvNamedWindow( "image", 1 );
//  cvNamedWindow( "watershed transform", 1 );

    img = cvCloneImage( img0 );
    img_gray = cvCloneImage( img0 );
    wshed = cvCloneImage( img0 );
    marker_mask = cvCreateImage( cvGetSize(img), 8, 1 );
    markers = cvCreateImage( cvGetSize(img), IPL_DEPTH_32S, 1 );
    cvCvtColor( img, marker_mask, CV_BGR2GRAY );
    cvCvtColor( marker_mask, img_gray, CV_GRAY2BGR );

    cvZero( marker_mask );
    cvZero( wshed );
    cvShowImage( "image", img );
//  cvShowImage( "watershed transform", wshed );
    cvSetMouseCallback( "image", on_mouse, 0 );

	m_ImageType=-3;
    for(;;)
    {
        int c = cvWaitKey(0);

        if( c == 27 ) {
			if (!flag) {                    //  δ�ӱ��
  				wshed = cvCloneImage( img0 );
			}
            break;
		}

        if( c == 'r' )
        {
            cvZero( marker_mask );
            cvCopy( img0, img );
            cvShowImage( "image", img );
        }

        if( c == 'w' || c == '\r' )
        {
			CvMemStorage* storage = cvCreateMemStorage(0);
			CvSeq* contours = 0;
			CvMat* color_tab;
			int i, j, comp_count = 0;
			//cvSaveImage( "wshed_mask.png", marker_mask );
			//marker_mask = cvLoadImage( "wshed_mask.png", 0 );
			cvFindContours( marker_mask, storage, &contours, sizeof(CvContour),
							CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

			CvSeq* contourn = contours;
			for (int n=0; contourn != 0; contourn = contourn->h_next,n++) {
			}                               //  ���߽���
			if (n) {                        //  ������ǲŽ��д���             
				cvZero( markers );
				for( ; contours != 0; contours = contours->h_next, comp_count++ )
				{
					cvDrawContours( markers, contours, cvScalarAll(comp_count+1),
                            cvScalarAll(comp_count+1), -1, -1, 8, cvPoint(0,0) );
				}

				color_tab = cvCreateMat( 1, comp_count, CV_8UC3 );
				for( i = 0; i < comp_count; i++ )
				{
					uchar* ptr = color_tab->data.ptr + i*3;
					ptr[0] = (uchar)(cvRandInt(&rng)%180 + 50);
					ptr[1] = (uchar)(cvRandInt(&rng)%180 + 50);
					ptr[2] = (uchar)(cvRandInt(&rng)%180 + 50);
				}

				{
					double t = (double)cvGetTickCount();
					cvWatershed( img0, markers );  //  ��ˮ���㷨����
					t = (double)cvGetTickCount() - t;
//					printf( "exec time = %gms\n", t/(cvGetTickFrequency()*1000.) );
				}

				// paint the watershed image
				for( i = 0; i < markers->height; i++ ) {
					for( j = 0; j < markers->width; j++ )
					{
						int idx = CV_IMAGE_ELEM( markers, int, i, j );
						uchar* dst = &CV_IMAGE_ELEM( wshed, uchar, i, j*3 );
						if( idx == -1 )
							dst[0] = dst[1] = dst[2] = (uchar)255;
						else if( idx <= 0 || idx > comp_count )
							dst[0] = dst[1] = dst[2] = (uchar)0; // should not get here
						else
						{
							uchar* ptr = color_tab->data.ptr + (idx-1)*3;
							dst[0] = ptr[0]; dst[1] = ptr[1]; dst[2] = ptr[2];
						}
					}
				}

				cvAddWeighted( wshed, 0.5, img_gray, 0.5, 0, wshed );  //  ͼ��ϳ�
//				cvShowImage( "watershed transform", wshed );
				cvReleaseMemStorage( &storage );
				cvReleaseMat( &color_tab );
			}
			else {                          //  δ�ӱ��
  				wshed = cvCloneImage( img0 );
			}
			cvCopy(wshed,workImg);
			cvFlip(workImg);

			CClientDC dc(this);
			StretchDIBits(dc.m_hDC,         //  ˢ��������
				0,0,workImg->width,workImg->height,
				0,0,workImg->width,workImg->height,
				workImg->imageData,m_lpBmi,DIB_RGB_COLORS,SRCCOPY);
			flag=1;
		}
	}

	cvDestroyWindow( "image" );
	cvReleaseImage(&img0);
 	cvReleaseImage(&img);
 	cvReleaseImage(&img_gray);
 	cvReleaseImage(&marker_mask);
 	cvReleaseImage(&markers);
 
	cvFlip(wshed);
	m_dibFlag=imageReplace(wshed,&workImg);
  	
	Invalidate();
}

//-------------------------------------
//  �ǵ��� 
//  ���ݡ�����OpenCV�ļ�����Ӿ�����ʵ�֡� ���� 12-1 �ı�

#define max_corners 200;                    //  �޶������ǵ���

IplImage* srcImage  = 0;                    //  �������Դͼ��
IplImage* ImageShow = 0;                    //  �洢��ʾ���ǵ��ͼ��
IplImage* grayImage = 0;                    //  ԭʼͼ��ת���ɵĻҽ�ͼ��
IplImage* corners1  = 0;                    //  ��ʱͼ��
IplImage* corners2  = 0;                    //  ��ʱͼ��

int cornerCount0 = max_corners;
int cornerCount;                            //  ʵ�ʲ�ýǵ���
int qualityLevel = 0;                       //  ��С��������
int minDistance  = 15;                      //  �ǵ���С����
CvScalar color = CV_RGB(255,0,0);           //  ��ͼ��ɫ
CvPoint2D32f corners[200];                  //  �ǵ�����
CvRect ROI_rect;                            //  ���Է�Χ
char   chek_area_state = 0;                 //  ���״̬
 
void re_find_corners(int)                   //  ��������Ӧ����
{
	int   i,x,y,xl,yu,xr,yd,k;
	int   radius = 5;
	int   thickness = 1;
	double quality_level = (double) qualityLevel / 100 + 0.02;
	double min_distance  = (double) minDistance;

	cornerCount=cornerCount0;               //  �������ǵ���
	cvGoodFeaturesToTrack(grayImage,        //  �ǵ���
					corners1,corners2,corners,&cornerCount,
					quality_level,min_distance,NULL);

	if (cornerCount>0) {                    //  �⵽�ǵ�
		xl=ROI_rect.x;     yu=ROI_rect.y;   //  ���ó�ʼ���Է�Χ
		xr=ROI_rect.x+ROI_rect.width;
		yd=ROI_rect.y+ROI_rect.height;
		cvCopy(srcImage,ImageShow);         //  �ָ�Դͼ��
		for (i=0,k=0;i<cornerCount;i++) {
 			x=(int)corners[i].x;
			y=(int)corners[i].y;
			if ((xl<x)&&(x<xr)&&(yu<y)&&(y<yd)) {  //  ��Χ���
				corners[k].x=corners[i].x;  //  ���淶Χ�ڽǵ�
				corners[k].y=corners[i].y;
				k++;
			}
		}
 		cornerCount=k;                      //  ��Χ�ڽǵ���
		cvCopy(srcImage,ImageShow);
		for (i=0;i<cornerCount;i++) {
 			x=(int)corners[i].x;
			y=(int)corners[i].y;
 			cvCircle(ImageShow,cvPoint(x,y),   //  �ǵ㴦��Ȧ
				radius,color,thickness,CV_AA,0);
		}
		cvRectangle(ImageShow,cvPoint(xl,yu),cvPoint(xr,yd),
			CV_RGB(0,255,0),thickness,CV_AA,0);  //  ������
		cvShowImage("image", ImageShow);    //  ��ʾ��Ȧͼ��
	}
}

void on_mouse2(int event,int x,int y,int flags,void* param)
{                                           //  �����Ӧ����
	int  thickness = 1;
	CvPoint point1,point2;

	if (event == CV_EVENT_LBUTTONDOWN) {    //  ����������
		ROI_rect.x = x;                     //  ��¼��ⴰ��һ������
		ROI_rect.y = y;
		chek_area_state = 1;                //  ����״̬��־
	}
	else if (chek_area_state && event == CV_EVENT_MOUSEMOVE) {  //  ����ƶ�
 		cvCopy(srcImage,ImageShow);         //  �ָ�ԭʼͼ��
		point1 = cvPoint(ROI_rect.x, ROI_rect.y);
		point2 = cvPoint(x,y);              //  ��ǰ����
		cvRectangle(ImageShow,point1,point2,CV_RGB(0,255,0),
				thickness,CV_AA,0);         //  ������
		cvShowImage("image", ImageShow);    //  ��ʾ�����
		cvWaitKey(20);                      //  ��ʱ
	}
	else if (chek_area_state && event == CV_EVENT_LBUTTONUP) {  //  ������̧��
		ROI_rect.width  = abs(x - ROI_rect.x);  //  ��¼��ⴰ�ڶԽ�����
		ROI_rect.height = abs(y - ROI_rect.y);

   		re_find_corners(0);                 //  �ǵ���
		chek_area_state = 0;                //  �ָ�״̬��־
		cvWaitKey(20); 
	}
}

void CCVMFCView::OnCornersTest()            //  �ǵ���
{
	if (workImg->nChannels>1) {             //  ԭͼΪ���ɫͼ��
		srcImage = cvCloneImage(workImg);
	}
	else {                                  //  ԭͼΪ�ҽ�ͼ��
 		srcImage = cvCreateImage(cvGetSize(workImg),IPL_DEPTH_8U,3);
		cvCvtColor(workImg,srcImage,CV_GRAY2BGR);
	}
 	cvFlip(srcImage);

 	grayImage = cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_8U,1);
	cvCvtColor(srcImage,grayImage,CV_BGR2GRAY);  //  ת��Ϊ�ҽ�ͼ��
	ImageShow = cvCloneImage(srcImage);

	ROI_rect.x =0;
	ROI_rect.y =0;
	ROI_rect.width  = grayImage->width;
	ROI_rect.height = grayImage->height;
  
	corners1 = cvCreateImage(cvGetSize(grayImage),IPL_DEPTH_32F,1);
	corners2 = cvCreateImage(cvGetSize(grayImage),IPL_DEPTH_32F,1);

	cvNamedWindow("image",0);               //  ������ʾ����
	cvResizeWindow("image",325,350);        //  �ı䴰�ڳߴ�

	cvCreateTrackbar("minDistance", "image",  //  ���þ��뻬����
		&minDistance, 200,re_find_corners);
	cvCreateTrackbar("qualityLevel","image",  //  ��������������
		&qualityLevel,100,re_find_corners);
  
	re_find_corners(0);                     //  �ǵ���

	cvSetMouseCallback("image",on_mouse2,0);  //  ���������Ӧ����

	cvWaitKey(0);                           //  �ȴ�������

	cvDestroyWindow( "image" );             //  �رմ���
 
	cvReleaseImage(&srcImage);              //  �ͷ�ͼ��洢��Ԫ
	cvReleaseImage(&grayImage);
	cvReleaseImage(&corners1);
	cvReleaseImage(&corners2);

	cvFlip(ImageShow);
	m_dibFlag=imageReplace(ImageShow,&workImg);  //  ��������
  	
	m_ImageType=-2;
	Invalidate();
}

//-------------------------------------
//  �㼯����
//  ���ݡ�OpenCV�̳�(����ƪ)���� 4-6 �ı�
//  OpenCV ϵͳ�������ʵ�� kmeans.c

void CCVMFCView::OnClusters()               //  �㼯����
{
    #define MAX_CLUSTERS 5
    CvScalar color_tab[MAX_CLUSTERS];
    IplImage* img = cvCreateImage( cvSize( 500, 500 ), 8, 3 );
    CvRNG rng = cvRNG(-1);
    CvPoint ipt;

    color_tab[0] = CV_RGB(255,0,0);
    color_tab[1] = CV_RGB(0,255,0);
    color_tab[2] = CV_RGB(100,100,255);
    color_tab[3] = CV_RGB(255,0,255);
    color_tab[4] = CV_RGB(255,255,0);

    cvNamedWindow( "clusters", 1 );
        
	m_ImageType=-3;
    for(;;)
    {
        char key;
        int k, cluster_count = cvRandInt(&rng)%MAX_CLUSTERS + 1;
        int i, sample_count = cvRandInt(&rng)%1000 + 1;
        CvMat* points = cvCreateMat( sample_count, 1, CV_32FC2 );
        CvMat* clusters = cvCreateMat( sample_count, 1, CV_32SC1 );
        
        /* generate random sample from multigaussian distribution */
        for( k = 0; k < cluster_count; k++ )
        {
            CvPoint center;
            CvMat point_chunk;
            center.x = cvRandInt(&rng)%img->width;
            center.y = cvRandInt(&rng)%img->height;
            cvGetRows( points, &point_chunk, k*sample_count/cluster_count,
                       k == cluster_count - 1 ? sample_count :
                       (k+1)*sample_count/cluster_count, 1 );
                        
            cvRandArr( &rng, &point_chunk, CV_RAND_NORMAL,
                       cvScalar(center.x,center.y,0,0),
                       cvScalar(img->width*0.1,img->height*0.1,0,0));
        }

        /* shuffle samples */
        for( i = 0; i < sample_count/2; i++ )
        {
            CvPoint2D32f* pt1 = (CvPoint2D32f*)points->data.fl + cvRandInt(&rng)%sample_count;
            CvPoint2D32f* pt2 = (CvPoint2D32f*)points->data.fl + cvRandInt(&rng)%sample_count;
            CvPoint2D32f temp;
            CV_SWAP( *pt1, *pt2, temp );
        }

        cvKMeans2( points, cluster_count, clusters,
                   cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0 ));

        cvZero( img );

        for( i = 0; i < sample_count; i++ )
        {
            int cluster_idx = clusters->data.i[i];
            ipt.x = (int)points->data.fl[i*2];
            ipt.y = (int)points->data.fl[i*2+1];
            cvCircle( img, ipt, 2, color_tab[cluster_idx], CV_FILLED, CV_AA, 0 );
        }

        cvReleaseMat( &points );
        cvReleaseMat( &clusters );

        cvShowImage( "clusters", img );

        key = (char) cvWaitKey(0);
        if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
            break;
    }
    
    cvDestroyWindow( "clusters" );

	m_ImageType=0;
}

//-------------------------------------
//  �ָ��ά�㼯
//  ���ݡ�OpenCV�̳�(����ƪ)���� 4-7 �ı�

CvSeq* point_seq = 0;
IplImage* canvas = 0;
CvScalar* colors = 0;
int pos = 10;

int is_equal( const void* _a, const void* _b, void* userdata )
{
    CvPoint a = *(const CvPoint*)_a;
    CvPoint b = *(const CvPoint*)_b;
    double threshold = *(double*)userdata;
    return (double)(a.x - b.x)*(a.x - b.x) + (double)(a.y - b.y)*(a.y - b.y) <= threshold;
}

void on_trackSP( int pos )
{
    CvSeq* labels = 0;
    double threshold = pos*pos;
    int i, class_count = cvSeqPartition( point_seq, 0, &labels, is_equal, &threshold );
    printf("%4d classes\n", class_count );
    cvZero( canvas );

    for( i = 0; i < labels->total; i++ )
    {
        CvPoint pt = *(CvPoint*)cvGetSeqElem( point_seq, i );
        CvScalar color = colors[*(int*)cvGetSeqElem( labels, i )];
        cvCircle( canvas, pt, 1, color, -1 );
    }

    cvShowImage( "points", canvas );
}

void CCVMFCView::OnSeqPartition() 
{
    CvMemStorage* storage = cvCreateMemStorage(0);
    point_seq = cvCreateSeq( CV_32SC2, sizeof(CvSeq), sizeof(CvPoint), storage );
    CvRNG rng = cvRNG(0xffffffff);

    int width = 500, height = 500;
    int i, count = 1000;
    canvas = cvCreateImage( cvSize(width,height), 8, 3 );

    colors = (CvScalar*)cvAlloc( count*sizeof(colors[0]) );
    for( i = 0; i < count; i++ )
    {
        CvPoint pt;
        int icolor;
        pt.x = cvRandInt( &rng ) % width;
        pt.y = cvRandInt( &rng ) % height;
        cvSeqPush( point_seq, &pt );
        icolor = cvRandInt( &rng ) | 0x00404040;
        colors[i] = CV_RGB(icolor & 255, (icolor >> 8)&255, (icolor >> 16)&255);
    }

    cvNamedWindow( "points", 1 );
    cvCreateTrackbar( "threshold", "points", &pos, 50, on_trackSP );
    on_trackSP( pos );

	m_ImageType=-3;
    cvWaitKey(0);

    cvDestroyWindow( "points" );
	cvReleaseMemStorage( &storage );
    cvReleaseImage( &canvas );

	m_ImageType=0;
}

//-------------------------------------
//  ��ת�����
//  ���� OpenCV ϵͳ�������ʵ�� kalman.c �ı�

void CCVMFCView::OnRotationTrack() 
{
    const float A[] = { 1, 1, 0, 1 };
    
    IplImage* img = cvCreateImage( cvSize(500,500), 8, 3 );
    CvKalman* kalman = cvCreateKalman( 2, 1, 0 );
    CvMat* state = cvCreateMat( 2, 1, CV_32FC1 ); /* (phi, delta_phi) */
    CvMat* process_noise = cvCreateMat( 2, 1, CV_32FC1 );
    CvMat* measurement = cvCreateMat( 1, 1, CV_32FC1 );
    CvRNG rng = cvRNG(-1);
    char code = -1;

    cvZero( measurement );
    cvNamedWindow( "Kalman", 1 );

	m_ImageType=-3;
    for(;;)
    {
        cvRandArr( &rng, state, CV_RAND_NORMAL, cvRealScalar(0), cvRealScalar(0.1) );
        
        memcpy( kalman->transition_matrix->data.fl, A, sizeof(A));
        cvSetIdentity( kalman->measurement_matrix, cvRealScalar(1) );
        cvSetIdentity( kalman->process_noise_cov, cvRealScalar(1e-5) );
        cvSetIdentity( kalman->measurement_noise_cov, cvRealScalar(1e-1) );
        cvSetIdentity( kalman->error_cov_post, cvRealScalar(1));
        cvRandArr( &rng, kalman->state_post, CV_RAND_NORMAL, cvRealScalar(0), cvRealScalar(0.1) );
        
        for(;;)
        {
            #define calc_point(angle)                                      \
                cvPoint( cvRound(img->width/2 + img->width/3*cos(angle)),  \
                         cvRound(img->height/2 - img->width/3*sin(angle))) 

            float state_angle = state->data.fl[0];
            CvPoint state_pt = calc_point(state_angle);
            
            const CvMat* prediction = cvKalmanPredict( kalman, 0 );
            float predict_angle = prediction->data.fl[0];
            CvPoint predict_pt = calc_point(predict_angle);
            float measurement_angle;
            CvPoint measurement_pt;

            cvRandArr( &rng, measurement, CV_RAND_NORMAL, cvRealScalar(0),
                       cvRealScalar(sqrt(kalman->measurement_noise_cov->data.fl[0])) );

            /* generate measurement */
            cvMatMulAdd( kalman->measurement_matrix, state, measurement, measurement );

            measurement_angle = measurement->data.fl[0];
            measurement_pt = calc_point(measurement_angle);
            
            /* plot points */
            #define draw_cross( center, color, d )                                 \
                cvLine( img, cvPoint( center.x - d, center.y - d ),                \
                             cvPoint( center.x + d, center.y + d ), color, 1, CV_AA, 0); \
                cvLine( img, cvPoint( center.x + d, center.y - d ),                \
                             cvPoint( center.x - d, center.y + d ), color, 1, CV_AA, 0 )

            cvZero( img );
            draw_cross( state_pt, CV_RGB(255,255,255), 3 );
            draw_cross( measurement_pt, CV_RGB(255,0,0), 3 );
            draw_cross( predict_pt, CV_RGB(0,255,0), 3 );
            cvLine( img, state_pt, measurement_pt, CV_RGB(255,0,0), 3, CV_AA, 0 );
            cvLine( img, state_pt, predict_pt, CV_RGB(255,255,0), 3, CV_AA, 0 );
            
            cvKalmanCorrect( kalman, measurement );

            cvRandArr( &rng, process_noise, CV_RAND_NORMAL, cvRealScalar(0),
                       cvRealScalar(sqrt(kalman->process_noise_cov->data.fl[0])));
            cvMatMulAdd( kalman->transition_matrix, state, process_noise, state );

            cvShowImage( "Kalman", img );
            code = (char) cvWaitKey( 100 );
            
            if( code > 0 )
                break;
        }
        if( code == 27 || code == 'q' || code == 'Q' )
            break;
    }
    
    cvDestroyWindow("Kalman");

	m_ImageType=0;
}

//-------------------------------------
//  �������
//  ���� OpenCV ϵͳ�������ʵ�� facedetect.c �ı�

CvMemStorage* storage1 = 0;
CvHaarClassifierCascade* cascade = 0;

void detect_and_draw( IplImage* img ,int flag)
{
    static CvScalar colors[] = 
    {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}}
    };

    double scale = 1.3;
    IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );
    IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
                         cvRound (img->height/scale)),
                     8, 1 );
    int i;

    cvCvtColor( img, gray, CV_BGR2GRAY );
    cvResize( gray, small_img, CV_INTER_LINEAR );
    cvEqualizeHist( small_img, small_img );
    cvClearMemStorage( storage1 );

    if( cascade )
    {
        double t = (double)cvGetTickCount();
        CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage1,
                                            1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
                                            cvSize(30, 30) );
        t = (double)cvGetTickCount() - t;
        printf( "detection time = %gms\n", t/((double)cvGetTickFrequency()*1000.) );
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
            CvPoint center;
            int radius;
            center.x = cvRound((r->x + r->width*0.5)*scale);
            center.y = cvRound((r->y + r->height*0.5)*scale);
            radius = cvRound((r->width + r->height)*0.25*scale);
            cvCircle( img, center, radius, colors[i%8], 3, 8, 0 );
        }
    }

	if (flag==1)
		cvShowImage( "result", img );
    cvReleaseImage( &gray );
    cvReleaseImage( &small_img );
}

void CCVMFCView::OnFaceDetect()             //  �������
{
	char cascade_name[] = "image\\haarcascade_frontalface_alt2.xml";
  
    cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
    
    storage1 = cvCreateMemStorage(0);
    
	cvFlip(workImg);                        //  �ָ�ԭʼͼ��
    detect_and_draw( workImg , 0);          //  �������

	cvReleaseMemStorage(&storage1);
	cvReleaseHaarClassifierCascade( &cascade );
	cvFlip(workImg);                        //  ����ʾ��Ҫ������

	Invalidate();
}

//---------------------------------------------------------
//  ��Ƶ����

void CCVMFCView::OnUpdateDynamicBorderTest(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag==0)&&(m_ImageType!=-3));
}
 
void CCVMFCView::OnUpdateOpticalFlowTrack(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag==0)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateMotionDetect(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag==0)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateCamShiftDemo(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag==0)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateForegroundDetect(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag==0)&&(m_ImageType!=-3));
}

void CCVMFCView::OnUpdateFaceDetect2(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag==0)&&(m_ImageType!=-3));
}

//-------------------------------------
//  ��̬��Ե���
//  ���� OpenCV ϵͳ�������ʵ�� laplace.cpp �ı�

void CCVMFCView::OnDynamicBorderTest()      //  ��̬��Ե���
{
    IplImage* laplace = 0;
    IplImage* colorlaplace = 0;
    IplImage* planes[3] = { 0, 0, 0 };
    CvCapture* capture = 0;
    
    capture = cvCaptureFromCAM(0);
 
    if( !capture )
    {
 		AfxMessageBox("����û�а�װ����ͷ��");
        return;
    }

	m_CaptFlag=3;                           //  ������Ƶ״̬��־

    cvNamedWindow( "Laplacian", 0 );
 
	m_ImageType=-3;
    for(;;)
    {
        IplImage* frame = 0;
        int i;

        frame = cvQueryFrame( capture );
        if( !frame )
            break;

        if( !laplace )
        {
            for( i = 0; i < 3; i++ )
                planes[i] = cvCreateImage( cvSize(frame->width,frame->height), 8, 1 );
            laplace = cvCreateImage( cvSize(frame->width,frame->height), IPL_DEPTH_16S, 1 );
            colorlaplace = cvCreateImage( cvSize(frame->width,frame->height), 8, 3 );
        }

        cvCvtPixToPlane( frame, planes[0], planes[1], planes[2], 0 );
        for( i = 0; i < 3; i++ )
        {
            cvLaplace( planes[i], laplace, 3 );
            cvConvertScaleAbs( laplace, planes[i], 1, 0 );
        }
        cvCvtPlaneToPix( planes[0], planes[1], planes[2], 0, colorlaplace );
        colorlaplace->origin = frame->origin;

        cvShowImage("Laplacian", colorlaplace );

        if( cvWaitKey(10) >= 0 )
            break;
    }

    cvReleaseCapture( &capture );
    cvDestroyWindow("Laplacian");

	m_CaptFlag=0;
	m_ImageType=0;
}

//-------------------------------------
//  L_K �㷨��������
//  ���� OpenCV ϵͳ�������ʵ�� lkdemo.cpp �ı�

//IplImage *image = 0, *grey = 0, *prev_grey = 0, *pyramid = 0, *prev_pyramid = 0, *swap_temp;
IplImage *grey = 0, *prev_grey = 0, *pyramid = 0, *prev_pyramid = 0, *swap_temp;

int win_size = 10;
const int MAX_COUNT = 500;
CvPoint2D32f* points[2] = {0,0}, *swap_points;
char* status = 0;
int count = 0;
int need_to_init = 0;
int night_mode = 0;
int flags = 0;
int add_remove_pt = 0;
CvPoint pt;

void on_mouse3( int event, int x, int y, int flags, void* param )
{
    if( !image )
        return;

    if( image->origin )
        y = image->height - y;

    if( event == CV_EVENT_LBUTTONDOWN )
    {
        pt = cvPoint(x,y);
        add_remove_pt = 1;
    }
}

void CCVMFCView::OnOpticalFlowTrack()       //  L_K �㷨��������
{
    CvCapture* capture = 0;
    
    capture = cvCaptureFromCAM(0);
 
    if( !capture )
    {
 		AfxMessageBox("����û�а�װ����ͷ��");
        return;
    }

	m_CaptFlag=3;                           //  ������Ƶ״̬��־

	if( image )
		cvReleaseImage( &image );

    /* print a welcome message, and the OpenCV version */
/*
    printf ("Welcome to lkdemo, using OpenCV version %s (%d.%d.%d)\n",
	    CV_VERSION,
	    CV_MAJOR_VERSION, CV_MINOR_VERSION, CV_SUBMINOR_VERSION);

    printf( "Hot keys: \n"
            "\tESC - quit the program\n"
            "\tr - auto-initialize tracking\n"
            "\tc - delete all the points\n"
            "\tn - switch the \"night\" mode on/off\n"
            "To add/remove a feature point click it\n" );
*/
    cvNamedWindow( "LkDemo", 0 );
    cvSetMouseCallback( "LkDemo", on_mouse3, 0 );

	m_ImageType=-3;
    for(;;)
    {
        IplImage* frame = 0;
        int i, k, c;

        frame = cvQueryFrame( capture );
        if( !frame )
            break;

        if( !image )
        {
            /* allocate all the buffers */
            image = cvCreateImage( cvGetSize(frame), 8, 3 );
            image->origin = frame->origin;
            grey = cvCreateImage( cvGetSize(frame), 8, 1 );
            prev_grey = cvCreateImage( cvGetSize(frame), 8, 1 );
            pyramid = cvCreateImage( cvGetSize(frame), 8, 1 );
            prev_pyramid = cvCreateImage( cvGetSize(frame), 8, 1 );
            points[0] = (CvPoint2D32f*)cvAlloc(MAX_COUNT*sizeof(points[0][0]));
            points[1] = (CvPoint2D32f*)cvAlloc(MAX_COUNT*sizeof(points[0][0]));
            status = (char*)cvAlloc(MAX_COUNT);
            flags = 0;
        }

        cvCopy( frame, image, 0 );
        cvCvtColor( image, grey, CV_BGR2GRAY );

        if( night_mode )
            cvZero( image );
        
        if( need_to_init )
        {
            /* automatic initialization */
            IplImage* eig = cvCreateImage( cvGetSize(grey), 32, 1 );
            IplImage* temp = cvCreateImage( cvGetSize(grey), 32, 1 );
            double quality = 0.01;
            double min_distance = 10;

            count = MAX_COUNT;
            cvGoodFeaturesToTrack( grey, eig, temp, points[1], &count,
                                   quality, min_distance, 0, 3, 0, 0.04 );
            cvFindCornerSubPix( grey, points[1], count,
                cvSize(win_size,win_size), cvSize(-1,-1),
                cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
            cvReleaseImage( &eig );
            cvReleaseImage( &temp );

            add_remove_pt = 0;
        }
        else if( count > 0 )
        {
            cvCalcOpticalFlowPyrLK( prev_grey, grey, prev_pyramid, pyramid,
                points[0], points[1], count, cvSize(win_size,win_size), 3, status, 0,
                cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03), flags );
            flags |= CV_LKFLOW_PYR_A_READY;
            for( i = k = 0; i < count; i++ )
            {
                if( add_remove_pt )
                {
                    double dx = pt.x - points[1][i].x;
                    double dy = pt.y - points[1][i].y;

                    if( dx*dx + dy*dy <= 25 )
                    {
                        add_remove_pt = 0;
                        continue;
                    }
                }
                
                if( !status[i] )
                    continue;
                
                points[1][k++] = points[1][i];
                cvCircle( image, cvPointFrom32f(points[1][i]), 3, CV_RGB(0,255,0), -1, 8,0);
            }
            count = k;
        }

        if( add_remove_pt && count < MAX_COUNT )
        {
            points[1][count++] = cvPointTo32f(pt);
            cvFindCornerSubPix( grey, points[1] + count - 1, 1,
                cvSize(win_size,win_size), cvSize(-1,-1),
                cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
            add_remove_pt = 0;
        }

        CV_SWAP( prev_grey, grey, swap_temp );
        CV_SWAP( prev_pyramid, pyramid, swap_temp );
        CV_SWAP( points[0], points[1], swap_points );
        need_to_init = 0;
        cvShowImage( "LkDemo", image );

        c = cvWaitKey(10);
        if( (char)c == 27 )
            break;
        switch( (char) c )
        {
        case 'r':
            need_to_init = 1;
            break;
        case 'c':
            count = 0;
            break;
        case 'n':
            night_mode ^= 1;
            break;
        default:
            ;
        }
    }

    cvReleaseCapture( &capture );
    cvDestroyWindow("LkDemo");

	m_CaptFlag=0;
	m_ImageType=0;
}

//-------------------------------------
//  ������ģ����˶�����
//  ���ݡ�ѧϰOpenCV���� 5-20 �ı�

#include "highgui.h"

void CCVMFCView::OnForegroundDetect()       //  ������ģ����˶�����
{
	//����IplImageָ��
	IplImage* pFrame = NULL; 
	IplImage* pFrImg = NULL;
	IplImage* pBkImg = NULL;

	CvMat* pFrameMat = NULL;
	CvMat* pFrMat = NULL;
	CvMat* pBkMat = NULL;
  
	CvCapture* pCapture = NULL;
  
	int nFrmNum = 0;
 
    pCapture = cvCaptureFromCAM(0);

    if( !pCapture )
    {
 		AfxMessageBox("����û�а�װ����ͷ��");
        return;
    }

	m_CaptFlag=3;                           //  ������Ƶ״̬��־

	//��������
	cvNamedWindow("video", 0);
	cvNamedWindow("background",0);
	cvNamedWindow("foreground",0);

	cvResizeWindow("video",320,240);
	cvResizeWindow("background",320,240);
	cvResizeWindow("foreground",320,240);

	//ʹ������������
	cvMoveWindow("video", 30, 0);
	cvMoveWindow("background", 360, 0);
	cvMoveWindow("foreground", 690, 0);

  
	m_ImageType=-3;
	//��֡��ȡ��Ƶ
  	while(pFrame = cvQueryFrame( pCapture ))
    {
      	nFrmNum++;
      
      	//����ǵ�һ֡����Ҫ�����ڴ棬����ʼ��
      	if(nFrmNum == 1)
		{
	  		pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),
  									IPL_DEPTH_8U,1);
	  		pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  
									IPL_DEPTH_8U,1);
			pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
	  		pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
	  		pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);

	  		//ת���ɵ�ͨ��ͼ���ٴ���
	  		cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);
	  		cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);

	  		cvConvert(pFrImg, pFrameMat);
	  		cvConvert(pFrImg, pFrMat);
	  		cvConvert(pFrImg, pBkMat);
		}
      	else
		{
	  		cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
	  		cvConvert(pFrImg, pFrameMat);
	  		//������˹�˲�����ƽ��ͼ��
	  		//cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0, 0);
	  
	  		//��ǰ֡������ͼ���
	  		cvAbsDiff(pFrameMat, pBkMat, pFrMat);

	  		//��ֵ��ǰ��ͼ
	  		cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);
			pFrImg->origin=pFrame->origin;

	  		//������̬ѧ�˲���ȥ������  
	 		//cvErode(pFrImg, pFrImg, 0, 1);
	  		//cvDilate(pFrImg, pFrImg, 0, 1);

	  		//���±���
	  		cvRunningAvg(pFrameMat, pBkMat, 0.003, 0);
	  		//������ת��Ϊͼ���ʽ��������ʾ
	  		cvConvert(pBkMat, pBkImg);
			pBkImg->origin=pFrame->origin;

	  		//��ʾͼ��
	  		cvShowImage("video", pFrame);
	  		cvShowImage("background", pBkImg);
	  		cvShowImage("foreground", pFrImg);

	  		//����а����¼���������ѭ��
	  		//�˵ȴ�ҲΪcvShowImage�����ṩʱ�������ʾ
	  		//�ȴ�ʱ����Ը���CPU�ٶȵ���
	  		if( cvWaitKey(2) >= 0 )
	    		break;
		}  // end of if-else
    } // end of while-loop

  	//���ٴ���
  	cvDestroyWindow("video");
  	cvDestroyWindow("background");
  	cvDestroyWindow("foreground");

  	//�ͷ�ͼ��;���
  	cvReleaseImage(&pFrImg);
  	cvReleaseImage(&pBkImg);

  	cvReleaseMat(&pFrameMat);
  	cvReleaseMat(&pFrMat);
  	cvReleaseMat(&pBkMat);

  	cvReleaseCapture(&pCapture);

	m_CaptFlag=0;
	m_ImageType=0;
}

//-------------------------------------
//  �˶�Ŀ�����
//  ���ݡ�OpenCV�̳�(����ƪ)���� 5-21 �ı�
//  OpenCV ϵͳ�������ʵ�� motempl.c

// various tracking parameters (in seconds)
const double MHI_DURATION = 1;
const double MAX_TIME_DELTA = 0.5;
const double MIN_TIME_DELTA = 0.05;
// number of cyclic frame buffer used for motion detection
// (should, probably, depend on FPS)
const int N = 4;

// ring image buffer
IplImage **buf = 0;
int last = 0;

// temporary images
IplImage *mhi = 0; // MHI
IplImage *orient = 0; // orientation
//IplImage *mask = 0; // valid orientation mask
IplImage *segmask = 0; // motion segmentation map
//CvMemStorage* storage = 0; // temporary storage

// parameters:
//  img - input video frame
//  dst - resultant motion picture
//  args - optional parameters
void  update_mhi( IplImage* img, IplImage* dst, int diff_threshold )
{
    double timestamp = (double)clock()/CLOCKS_PER_SEC; // get current time in seconds
    CvSize size = cvSize(img->width,img->height); // get current frame size
    int i, idx1 = last, idx2;
    IplImage* silh;
    CvSeq* seq;
    CvRect comp_rect;
    double count;
    double angle;
    CvPoint center;
    double magnitude;          
    CvScalar color;

    // allocate images at the beginning or
    // reallocate them if the frame size is changed
    if( !mhi || mhi->width != size.width || mhi->height != size.height ) {
        if( buf == 0 ) {
            buf = (IplImage**)malloc(N*sizeof(buf[0]));
            memset( buf, 0, N*sizeof(buf[0]));
        }
        
        for( i = 0; i < N; i++ ) {
            cvReleaseImage( &buf[i] );
            buf[i] = cvCreateImage( size, IPL_DEPTH_8U, 1 );
            cvZero( buf[i] );
        }
        cvReleaseImage( &mhi );
        cvReleaseImage( &orient );
        cvReleaseImage( &segmask );
        cvReleaseImage( &mask );
        
        mhi = cvCreateImage( size, IPL_DEPTH_32F, 1 );
        cvZero( mhi ); // clear MHI at the beginning
        orient = cvCreateImage( size, IPL_DEPTH_32F, 1 );
        segmask = cvCreateImage( size, IPL_DEPTH_32F, 1 );
        mask = cvCreateImage( size, IPL_DEPTH_8U, 1 );
    }

    cvCvtColor( img, buf[last], CV_BGR2GRAY ); // convert frame to grayscale

    idx2 = (last + 1) % N; // index of (last - (N-1))th frame
    last = idx2;

    silh = buf[idx2];
    cvAbsDiff( buf[idx1], buf[idx2], silh ); // get difference between frames
    
    cvThreshold( silh, silh, diff_threshold, 1, CV_THRESH_BINARY ); // and threshold it
    cvUpdateMotionHistory( silh, mhi, timestamp, MHI_DURATION ); // update MHI

    // convert MHI to blue 8u image
    cvCvtScale( mhi, mask, 255./MHI_DURATION,
                (MHI_DURATION - timestamp)*255./MHI_DURATION );
    cvZero( dst );
    cvCvtPlaneToPix( mask, 0, 0, 0, dst );

    // calculate motion gradient orientation and valid orientation mask
    cvCalcMotionGradient( mhi, mask, orient, MAX_TIME_DELTA, MIN_TIME_DELTA, 3 );
    
    if( !storage )
        storage = cvCreateMemStorage(0);
    else
        cvClearMemStorage(storage);
    
    // segment motion: get sequence of motion components
    // segmask is marked motion components map. It is not used further
    seq = cvSegmentMotion( mhi, segmask, storage, timestamp, MAX_TIME_DELTA );

    // iterate through the motion components,
    // One more iteration (i == -1) corresponds to the whole image (global motion)
    for( i = -1; i < seq->total; i++ ) {

        if( i < 0 ) { // case of the whole image
            comp_rect = cvRect( 0, 0, size.width, size.height );
            color = CV_RGB(255,255,255);
            magnitude = 100;
        }
        else { // i-th motion component
            comp_rect = ((CvConnectedComp*)cvGetSeqElem( seq, i ))->rect;
            if( comp_rect.width + comp_rect.height < 100 ) // reject very small components
                continue;
            color = CV_RGB(255,0,0);
            magnitude = 30;
        }

        // select component ROI
        cvSetImageROI( silh, comp_rect );
        cvSetImageROI( mhi, comp_rect );
        cvSetImageROI( orient, comp_rect );
        cvSetImageROI( mask, comp_rect );

        // calculate orientation
        angle = cvCalcGlobalOrientation( orient, mask, mhi, timestamp, MHI_DURATION);
        angle = 360.0 - angle;  // adjust for images with top-left origin

        count = cvNorm( silh, 0, CV_L1, 0 ); // calculate number of points within silhouette ROI

        cvResetImageROI( mhi );
        cvResetImageROI( orient );
        cvResetImageROI( mask );
        cvResetImageROI( silh );

        // check for the case of little motion
        if( count < comp_rect.width*comp_rect.height * 0.05 )
            continue;

        // draw a clock with arrow indicating the direction
        center = cvPoint( (comp_rect.x + comp_rect.width/2),
                          (comp_rect.y + comp_rect.height/2) );

        cvCircle( dst, center, cvRound(magnitude*1.2), color, 3, CV_AA, 0 );
        cvLine( dst, center, cvPoint( cvRound( center.x + magnitude*cos(angle*CV_PI/180)),
                cvRound( center.y - magnitude*sin(angle*CV_PI/180))), color, 3, CV_AA, 0 );
    }
}

void CCVMFCView::OnMotionDetect()           //  �˶�Ŀ�����
{
    IplImage* motion = 0;
    CvCapture* capture = 0;
    
    capture = cvCaptureFromCAM(0);
 
    if( !capture )
    {
 		AfxMessageBox("����û�а�װ����ͷ��");
        return;
    }

	m_CaptFlag=3;                           //  ������Ƶ״̬��־

    cvNamedWindow( "Motion", 1 );
        
	m_ImageType=-3;
    for(;;)
    {
        IplImage* image;
        if( !cvGrabFrame( capture ))
            break;
        image = cvRetrieveFrame( capture );

        if( image )
        {
            if( !motion )
            {
                motion = cvCreateImage( cvSize(image->width,image->height), 8, 3 );
                cvZero( motion );
                motion->origin = image->origin;
            }
        }

        update_mhi( image, motion, 30 );
        cvShowImage( "Motion", motion );

        if( cvWaitKey(10) >= 0 )
            break;
    }
    cvReleaseCapture( &capture );
    cvDestroyWindow( "Motion" );
 
	m_CaptFlag=0;
	m_ImageType=0;
}

//-------------------------------------
//  ��ɫĿ�����
//  ���ݡ�OpenCV�̳�(����ƪ)���� 5-22 �ı�
//  OpenCV ϵͳ�������ʵ�� camshiftdemo.c

//IplImage *image = 0, *hsv = 0, *hue = 0, *mask = 0, *backproject = 0, *histimg = 0;
IplImage *hsv = 0, *hue = 0, *backproject = 0, *histimg = 0;
CvHistogram *hist = 0;

int backproject_mode = 0;
int select_object = 0;
int track_object = 0;
int show_hist = 1;
CvPoint origin;
CvRect selection;
CvRect track_window;
CvBox2D track_box;
CvConnectedComp track_comp;
int hdims = 16;
float hranges_arr[] = {0,180};
float* hranges = hranges_arr;
int vmin = 10, vmax = 256, smin = 30;

void on_mouse4( int event, int x, int y, int flags, void* param )
{
    if( !image )
        return;

    if( image->origin )
        y = image->height - y;

    if( select_object )
    {
        selection.x = MIN(x,origin.x);
        selection.y = MIN(y,origin.y);
        selection.width = selection.x + CV_IABS(x - origin.x);
        selection.height = selection.y + CV_IABS(y - origin.y);
        
        selection.x = MAX( selection.x, 0 );
        selection.y = MAX( selection.y, 0 );
        selection.width = MIN( selection.width, image->width );
        selection.height = MIN( selection.height, image->height );
        selection.width -= selection.x;
        selection.height -= selection.y;
    }

    switch( event )
    {
    case CV_EVENT_LBUTTONDOWN:
        origin = cvPoint(x,y);
        selection = cvRect(x,y,0,0);
        select_object = 1;
        break;
    case CV_EVENT_LBUTTONUP:
        select_object = 0;
        if( selection.width > 0 && selection.height > 0 )
            track_object = -1;
        break;
    }
}

CvScalar hsv2rgb( float hue )
{
    int rgb[3], p, sector;
    static const int sector_data[][3]=
        {{0,2,1}, {1,2,0}, {1,0,2}, {2,0,1}, {2,1,0}, {0,1,2}};
    hue *= 0.033333333333333333333333333333333f;
    sector = cvFloor(hue);
    p = cvRound(255*(hue - sector));
    p ^= sector & 1 ? 255 : 0;

    rgb[sector_data[sector][0]] = 255;
    rgb[sector_data[sector][1]] = 0;
    rgb[sector_data[sector][2]] = p;

    return cvScalar(rgb[2], rgb[1], rgb[0],0);
}

void CCVMFCView::OnCamShiftDemo() 
{
    CvCapture* capture = 0;
    
    capture = cvCaptureFromCAM(0);
 
    if( !capture )
    {
 		AfxMessageBox("����û�а�װ����ͷ��");
        return;
    }

	m_CaptFlag=3;                           //  ������Ƶ״̬��־

	if( image )
		cvReleaseImage( &image );
	if( mask )
		cvReleaseImage( &mask );
/*
    printf( "Hot keys: \n"
        "\tESC - quit the program\n"
        "\tc - stop the tracking\n"
        "\tb - switch to/from backprojection view\n"
        "\th - show/hide object histogram\n"
        "To initialize tracking, select the object with mouse\n" );
*/
    cvNamedWindow( "Histogram", 1 );
    cvNamedWindow( "CamShiftDemo", 1 );
    cvSetMouseCallback( "CamShiftDemo", on_mouse4, 0 );
    cvCreateTrackbar( "Vmin", "CamShiftDemo", &vmin, 256, 0 );
    cvCreateTrackbar( "Vmax", "CamShiftDemo", &vmax, 256, 0 );
    cvCreateTrackbar( "Smin", "CamShiftDemo", &smin, 256, 0 );

	m_ImageType=-3;
    for(;;)
    {
        IplImage* frame = 0;
        int i, bin_w, c;

        frame = cvQueryFrame( capture );
        if( !frame )
            break;

        if( !image )
        {
            /* allocate all the buffers */
            image = cvCreateImage( cvGetSize(frame), 8, 3 );
            image->origin = frame->origin;
            hsv = cvCreateImage( cvGetSize(frame), 8, 3 );
            hue = cvCreateImage( cvGetSize(frame), 8, 1 );
            mask = cvCreateImage( cvGetSize(frame), 8, 1 );
            backproject = cvCreateImage( cvGetSize(frame), 8, 1 );
            hist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 );
            histimg = cvCreateImage( cvSize(320,200), 8, 3 );
            cvZero( histimg );
        }

        cvCopy( frame, image, 0 );
        cvCvtColor( image, hsv, CV_BGR2HSV );

        if( track_object )
        {
            int _vmin = vmin, _vmax = vmax;

            cvInRangeS( hsv, cvScalar(0,smin,MIN(_vmin,_vmax),0),
                        cvScalar(180,256,MAX(_vmin,_vmax),0), mask );
            cvSplit( hsv, hue, 0, 0, 0 );

            if( track_object < 0 )
            {
                float max_val = 0.f;
                cvSetImageROI( hue, selection );
                cvSetImageROI( mask, selection );
                cvCalcHist( &hue, hist, 0, mask );
                cvGetMinMaxHistValue( hist, 0, &max_val, 0, 0 );
                cvConvertScale( hist->bins, hist->bins, max_val ? 255. / max_val : 0., 0 );
                cvResetImageROI( hue );
                cvResetImageROI( mask );
                track_window = selection;
                track_object = 1;

                cvZero( histimg );
                bin_w = histimg->width / hdims;
                for( i = 0; i < hdims; i++ )
                {
                    int val = cvRound( cvGetReal1D(hist->bins,i)*histimg->height/255 );
                    CvScalar color = hsv2rgb(i*180.f/hdims);
                    cvRectangle( histimg, cvPoint(i*bin_w,histimg->height),
                                 cvPoint((i+1)*bin_w,histimg->height - val),
                                 color, -1, 8, 0 );
                }
            }

            cvCalcBackProject( &hue, backproject, hist );
            cvAnd( backproject, mask, backproject, 0 );
            cvCamShift( backproject, track_window,
                        cvTermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ),
                        &track_comp, &track_box );
            track_window = track_comp.rect;
            
            if( backproject_mode )
                cvCvtColor( backproject, image, CV_GRAY2BGR );
            if( image->origin )
                track_box.angle = -track_box.angle;
            cvEllipseBox( image, track_box, CV_RGB(255,0,0), 3, CV_AA, 0 );
        }
        
        if( select_object && selection.width > 0 && selection.height > 0 )
        {
            cvSetImageROI( image, selection );
            cvXorS( image, cvScalarAll(255), image, 0 );
            cvResetImageROI( image );
        }

        cvShowImage( "CamShiftDemo", image );
        cvShowImage( "Histogram", histimg );

        c = cvWaitKey(10);
        if( (char) c == 27 )
            break;
        switch( (char) c )
        {
        case 'b':
            backproject_mode ^= 1;
            break;
        case 'c':
            track_object = 0;
            cvZero( histimg );
            break;
        case 'h':
            show_hist ^= 1;
            if( !show_hist )
                cvDestroyWindow( "Histogram" );
            else
                cvNamedWindow( "Histogram", 1 );
            break;
        default:
            ;
        }
    }

    if( show_hist )
        cvDestroyWindow( "Histogram" );
    cvReleaseCapture( &capture );
    cvDestroyWindow("CamShiftDemo");
 
	m_CaptFlag=0;
	m_ImageType=0;
}

//-------------------------------------
//  ��������
//  ���� OpenCV ϵͳ�������ʵ�� facedetect.c �ı�

void CCVMFCView::OnFaceDetect2()            //  ��������
{
    CvCapture* capture = 0;
    IplImage *frame, *frame_copy = 0;
	char cascade_name[] = "image\\haarcascade_frontalface_alt.xml";

    capture = cvCaptureFromCAM(0);
 
    if( !capture )
    {
 		AfxMessageBox("����û�а�װ����ͷ��");
        return;
    }

	m_CaptFlag=3;                           //  ������Ƶ״̬��־

    cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
    
    storage1 = cvCreateMemStorage(0);
    
    cvNamedWindow( "result", 1 );

	m_ImageType=-3;
    for(;;)
    {
        if( !cvGrabFrame( capture ))
            break;
        frame = cvRetrieveFrame( capture );
        if( !frame )
            break;
        if( !frame_copy )
            frame_copy = cvCreateImage( cvSize(frame->width,frame->height),
                                    IPL_DEPTH_8U, frame->nChannels );
        if( frame->origin == IPL_ORIGIN_TL )
            cvCopy( frame, frame_copy, 0 );
        else
            cvFlip( frame, frame_copy, 0 );
           
        detect_and_draw( frame_copy , 1);

        if( cvWaitKey( 10 ) >= 0 )
            break;
    }

    cvReleaseImage( &frame_copy );
    cvReleaseCapture( &capture );
    
	cvReleaseMemStorage(&storage1);
	cvReleaseHaarClassifierCascade( &cascade );
    cvDestroyWindow("result");
 
	m_CaptFlag=0;
	m_ImageType=0;
}

//---------------------------------------------------------
//  ��ɫͼ����

void CCVMFCView::OnUpdateImageRgb(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateImageRgbC(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateImageHsv(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateImageLab(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateImageXyz(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateImageYcrcb(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateImageLuv(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdate2dHistogram(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateBlurSmoothC(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateGaussSmoothC(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateMedianSmoothC(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateSobelC(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateLaplaceC(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnImageRgb() 
{
	IplImage* pImage    = NULL; 
	IplImage* pRedImg   = NULL; 
	IplImage* pGreenImg = NULL;
	IplImage* pBlueImg  = NULL;
 	IplImage* pMaskImg  = NULL; 
	int   wid,hei,top;
 
	pImage = cvCloneImage( workImg );
	cvFlip(pImage);

	pRedImg   = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	pGreenImg = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	pBlueImg  = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);

    cvCvtPixToPlane( pImage, pBlueImg, pGreenImg, pRedImg, 0 );

	cvNamedWindow("Red Image", 0);
	cvNamedWindow("Green Image", 0);
	cvNamedWindow("Blue Image", 0);
 
	if (pImage->width>320) wid=320;
	else wid=pImage->width;
	hei = wid*pImage->height/pImage->width;
	cvResizeWindow("Red Image",wid,hei);
	cvResizeWindow("Green Image",wid,hei);
	cvResizeWindow("Blue Image",wid,hei);

	top = 695 - hei;
	cvMoveWindow("Red Image", 15, top);
	cvMoveWindow("Green Image", 345, top);
	cvMoveWindow("Blue Image", 675, top);

	cvShowImage("Red Image", pRedImg);
 	cvShowImage("Green Image", pGreenImg);
 	cvShowImage("Blue Image", pBlueImg);

	m_ImageType=-3;
	cvWaitKey(0);

  	cvDestroyWindow("Red Image");
  	cvDestroyWindow("Green Image");
  	cvDestroyWindow("Blue Image");
  	cvReleaseImage(&pImage);
  	cvReleaseImage(&pRedImg);
  	cvReleaseImage(&pGreenImg);
  	cvReleaseImage(&pBlueImg);

	m_ImageType=3;
}

void CCVMFCView::OnImageHsv() 
{
	IplImage* pImage  = NULL; 
	IplImage* pHueImg = NULL; 
	IplImage* pSatImg = NULL;
	IplImage* pValImg = NULL;
 	IplImage* pMaskImg  = NULL; 
	int   wid,hei,top,i,j,k,bplc,bplh;
	BYTE  *buf,*bufc,*bufh;

	pImage = cvCloneImage( workImg );
	cvFlip(pImage);

	pHueImg = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	pSatImg = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	pValImg = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);

	cvCvtColor( pImage, pImage ,CV_BGR2HSV );  //  ģʽת��
    cvCvtPixToPlane( pImage, pHueImg, pSatImg, pValImg, 0 );  //  ����������

	pMaskImg = cvCreateImage(cvSize(256, 1),IPL_DEPTH_8U,3);
	buf=(BYTE*) pMaskImg->imageData;
	memset(buf,232,pMaskImg->imageSize);    //  ���û�ɫֵ
	for (i=0;i<=180;i++) {                  //  181 ��ɫ��ģʽ
		buf[3*i]=(BYTE) i;                  //  hue
//		buf[3*i+1]=255;                     //  Saturation
//		buf[3*i+2]=255;                     //  Value
	}
	cvCvtColor( pMaskImg, pMaskImg ,CV_HSV2BGR );  //  ת������ʾ�� BGR ����

	bufh =(BYTE*) pHueImg->imageData;       //  �ҽ�ɫ��ͼ
	bplh = pHueImg->widthStep;
	bufc =(BYTE*) pImage->imageData;        //  ��ɫɫ��ͼ
	bplc = pImage->widthStep;
	for (i=0;i<pHueImg->height;i++) {
		for (j=0,k=0;j<pHueImg->width;j++,k+=3) {
			memcpy(&bufc[k],&buf[3*bufh[j]],3);  //  �����ת��
		}
		bufc+=bplc;     bufh+=bplh;         //  ָ����һ��
	}

	cvNamedWindow("Hue Image", 0);
	cvNamedWindow("Saturation Image", 0);
	cvNamedWindow("Value Image", 0);

	if (pImage->width>320) wid=320;
	else wid=pImage->width;
	hei = wid*pImage->height/pImage->width;
	cvResizeWindow("Hue Image",wid,hei);
	cvResizeWindow("Saturation Image",wid,hei);
	cvResizeWindow("Value Image",wid,hei);

	top = 695 - hei;
	cvMoveWindow("Hue Image", 15, top);
	cvMoveWindow("Saturation Image", 345, top);
	cvMoveWindow("Value Image", 675, top);

//	cvShowImage("Hue Image", pHueImg);      //  �ҽ�ɫ��ͼ
	cvShowImage("Hue Image", pImage);       //  ��ɫɫ��ͼ
	cvShowImage("Saturation Image", pSatImg);
	cvShowImage("Value Image", pValImg);

	m_ImageType=-3;
	cvWaitKey(0);

  	cvDestroyWindow("Hue Image");
  	cvDestroyWindow("Saturation Image");
  	cvDestroyWindow("Value Image");
  	cvReleaseImage(&pImage);
   	cvReleaseImage(&pHueImg);
  	cvReleaseImage(&pSatImg);
  	cvReleaseImage(&pValImg);
  	cvReleaseImage(&pMaskImg);

	m_ImageType=3;
}

void CCVMFCView::OnImageLab() 
{
	IplImage* pImage  = NULL; 
	IplImage* pLImg   = NULL; 
	IplImage* paImg   = NULL;
	IplImage* pbImg   = NULL;
	int   wid,hei,top;

	pImage = cvCloneImage( workImg );
	cvFlip(pImage);

	pLImg   = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	paImg   = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	pbImg   = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);

	cvCvtColor( pImage, pImage ,CV_BGR2Lab );

    cvCvtPixToPlane( pImage, pLImg, paImg, pbImg, 0 );

	cvNamedWindow("L Image", 0);
	cvNamedWindow("a Image", 0);
	cvNamedWindow("b Image", 0);
 
	if (pImage->width>320) wid=320;
	else wid=pImage->width;
	hei = wid*pImage->height/pImage->width;
	cvResizeWindow("L Image",wid,hei);
	cvResizeWindow("a Image",wid,hei);
	cvResizeWindow("b Image",wid,hei);

	top = 695 - hei;
	cvMoveWindow("L Image", 15, top);
	cvMoveWindow("a Image", 345, top);
	cvMoveWindow("b Image", 675, top);

	cvShowImage("L Image", pLImg);
	cvShowImage("a Image", paImg);
	cvShowImage("b Image", pbImg);

	m_ImageType=-3;
	cvWaitKey(0);

  	cvDestroyWindow("L Image");
  	cvDestroyWindow("a Image");
  	cvDestroyWindow("b Image");
  	cvReleaseImage(&pImage);
   	cvReleaseImage(&pLImg);
  	cvReleaseImage(&paImg);
  	cvReleaseImage(&pbImg);

	m_ImageType=3;
}

void CCVMFCView::OnImageRgbC() 
{
	IplImage* pImage    = NULL; 
	IplImage* pRedImg   = NULL; 
	IplImage* pGreenImg = NULL;
	IplImage* pBlueImg  = NULL;
 	IplImage* pMaskImg  = NULL; 
	int   wid,hei,top,i,j,k,bplc,bplh;
	BYTE  *buf,*bufc,*bufh;

	pImage = cvCloneImage( workImg );
	cvFlip(pImage);

	pRedImg   = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	pGreenImg = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	pBlueImg  = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);

    cvCvtPixToPlane( pImage, pBlueImg, pGreenImg, pRedImg, 0 );

	cvNamedWindow("Red Image", 0);
	cvNamedWindow("Green Image",0);
	cvNamedWindow("Blue Image",0);
 
	if (pImage->width>320) wid=320;
	else wid=pImage->width;
	hei = wid*pImage->height/pImage->width;
	cvResizeWindow("Red Image",wid,hei);
	cvResizeWindow("Green Image",wid,hei);
	cvResizeWindow("Blue Image",wid,hei);

	top = 695 - hei;
	cvMoveWindow("Red Image", 15, top);
	cvMoveWindow("Green Image", 345, top);
	cvMoveWindow("Blue Image", 675, top);

	pMaskImg = cvCreateImage(cvSize(256, 1),IPL_DEPTH_8U,3);
	buf=(BYTE*) pMaskImg->imageData;
	memset(buf,0,pMaskImg->imageSize);
	for (i=0;i<256;i++) {  
		buf[3*i+2]=(BYTE) i;                //  �����
	}
	bufc =(BYTE*) pImage->imageData;
	bplc = pImage->widthStep;
	bufh =(BYTE*) pRedImg->imageData;
	bplh = pRedImg->widthStep;
	for (i=0;i<pRedImg->height;i++) {
		for (j=0,k=0;j<pRedImg->width;j++,k+=3) {
			memcpy(&bufc[k],&buf[3*bufh[j]],3);  //  �����ת��
		}
		bufc+=bplc;     bufh+=bplh;         //  ָ����һ��
	}
	cvShowImage("Red Image", pImage);

	memset(buf,0,pMaskImg->imageSize);
	for (i=0;i<256;i++) {  
		buf[3*i+1]=(BYTE) i;                //  �̷���
	}
	bufc =(BYTE*) pImage->imageData;
	bplc = pImage->widthStep;
	bufh =(BYTE*) pGreenImg->imageData;
	bplh = pRedImg->widthStep;
	for (i=0;i<pRedImg->height;i++) {
		for (j=0,k=0;j<pRedImg->width;j++,k+=3) {
			memcpy(&bufc[k],&buf[3*bufh[j]],3); 
		}
		bufc+=bplc;     bufh+=bplh; 
	}
	cvShowImage("Green Image", pImage);

	memset(buf,0,pMaskImg->imageSize);
	for (i=0;i<256;i++) {  
		buf[3*i]=(BYTE) i;                  //  ������
	}
	bufc =(BYTE*) pImage->imageData;
	bplc = pImage->widthStep;
	bufh =(BYTE*) pBlueImg->imageData;
	bplh = pRedImg->widthStep;
	for (i=0;i<pRedImg->height;i++) {
		for (j=0,k=0;j<pRedImg->width;j++,k+=3) {
			memcpy(&bufc[k],&buf[3*bufh[j]],3); 
		}
		bufc+=bplc;     bufh+=bplh; 
	}
	cvShowImage("Blue Image", pImage);

	m_ImageType=-3;
	cvWaitKey(0);

  	cvDestroyWindow("Red Image");
  	cvDestroyWindow("Green Image");
  	cvDestroyWindow("Blue Image");
  	cvReleaseImage(&pImage);
  	cvReleaseImage(&pRedImg);
  	cvReleaseImage(&pGreenImg);
  	cvReleaseImage(&pBlueImg);
  	cvReleaseImage(&pMaskImg);

	m_ImageType=3;
}

void CCVMFCView::OnImageXyz() 
{
	IplImage* pImage  = NULL; 
 	IplImage* pXImg   = NULL; 
	IplImage* pYImg   = NULL;
	IplImage* pZImg   = NULL;
	int   wid,hei,top;

	pImage = cvCloneImage( workImg );
	cvFlip(pImage);

 	pXImg   = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	pYImg   = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	pZImg   = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);

	cvCvtColor( pImage, pImage ,CV_BGR2XYZ );

    cvCvtPixToPlane( pImage, pXImg, pYImg, pZImg, 0 );

	cvNamedWindow("X Image", 0);
	cvNamedWindow("Y Image", 0);
	cvNamedWindow("Z Image", 0);
 
	if (pImage->width>320) wid=320;
	else wid=pImage->width;
	hei = wid*pImage->height/pImage->width;
	cvResizeWindow("X Image",wid,hei);
	cvResizeWindow("Y Image",wid,hei);
	cvResizeWindow("Z Image",wid,hei);

	top = 695 - hei;
	cvMoveWindow("X Image", 15, top);
	cvMoveWindow("Y Image", 345, top);
	cvMoveWindow("Z Image", 675, top);

	cvShowImage("X Image", pXImg);
	cvShowImage("Y Image", pYImg);
	cvShowImage("Z Image", pZImg);

	m_ImageType=-3;
	cvWaitKey(0);

  	cvDestroyWindow("X Image");
  	cvDestroyWindow("Y Image");
  	cvDestroyWindow("Z Image");
  	cvReleaseImage(&pImage);
   	cvReleaseImage(&pXImg);
  	cvReleaseImage(&pYImg);
  	cvReleaseImage(&pZImg);

	m_ImageType=3;
}

void CCVMFCView::OnImageYcrcb() 
{
	IplImage* pImage = NULL; 
 	IplImage* pYImg  = NULL; 
	IplImage* pCrImg = NULL;
	IplImage* pCbImg = NULL;
	int   wid,hei,top;

	pImage = cvCloneImage( workImg );
	cvFlip(pImage);

	pYImg     = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	pCrImg    = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	pCbImg    = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);

	cvCvtColor( pImage, pImage ,CV_BGR2YCrCb );

    cvCvtPixToPlane( pImage, pYImg, pCrImg, pCbImg, 0 );

	cvNamedWindow("Y Image", 0);
	cvNamedWindow("Cr Image", 0);
	cvNamedWindow("Cb Image", 0);
 
	if (pImage->width>320) wid=320;
	else wid=pImage->width;
	hei = wid*pImage->height/pImage->width;
	cvResizeWindow("Y Image",wid,hei);
	cvResizeWindow("Cr Image",wid,hei);
	cvResizeWindow("Cb Image",wid,hei);

	top = 695 - hei;
	cvMoveWindow("Y Image", 15, top);
	cvMoveWindow("Cr Image", 345, top);
	cvMoveWindow("Cb Image", 675, top);

	cvShowImage("Y Image", pYImg);
	cvShowImage("Cr Image", pCrImg);
	cvShowImage("Cb Image", pCbImg);

	m_ImageType=-3;
	cvWaitKey(0);

  	cvDestroyWindow("Y Image");
  	cvDestroyWindow("Cr Image");
  	cvDestroyWindow("Cb Image");
  	cvReleaseImage(&pImage);
  	cvReleaseImage(&pYImg);
  	cvReleaseImage(&pCrImg);
  	cvReleaseImage(&pCbImg);

	m_ImageType=3;
}

void CCVMFCView::OnImageLuv() 
{
	IplImage* pImage  = NULL; 
	IplImage* pLImg   = NULL; 
	IplImage* puImg   = NULL;
	IplImage* pvImg   = NULL;
	int   wid,hei,top;

	pImage = cvCloneImage( workImg );
	cvFlip(pImage);

	pLImg   = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	puImg   = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);
	pvImg   = cvCreateImage(cvSize(pImage->width, pImage->height),
  						IPL_DEPTH_8U,1);

	cvCvtColor( pImage, pImage ,CV_BGR2Lab );

    cvCvtPixToPlane( pImage, pLImg, puImg, pvImg, 0 );

	cvNamedWindow("L Image", 0);
	cvNamedWindow("u Image", 0);
	cvNamedWindow("v Image", 0);
 
	if (pImage->width>320) wid=320;
	else wid=pImage->width;
	hei = wid*pImage->height/pImage->width;
	cvResizeWindow("L Image",wid,hei);
	cvResizeWindow("u Image",wid,hei);
	cvResizeWindow("v Image",wid,hei);

	top = 695 - hei;
	cvMoveWindow("L Image", 15, top);
	cvMoveWindow("u Image", 345, top);
	cvMoveWindow("v Image", 675, top);

	cvShowImage("L Image", pLImg);
	cvShowImage("u Image", puImg);
	cvShowImage("v Image", pvImg);

	m_ImageType=-3;
	cvWaitKey(0);

  	cvDestroyWindow("L Image");
  	cvDestroyWindow("u Image");
  	cvDestroyWindow("v Image");
  	cvReleaseImage(&pImage);
   	cvReleaseImage(&pLImg);
  	cvReleaseImage(&puImg);
  	cvReleaseImage(&pvImg);

	m_ImageType=3;
}

//-------------------------------------
//  ��ɫͼ���άֱ��ͼ
//  ���ݡ�OpenCV�̳�(����ƪ)���� 5-12 �ı�

void CCVMFCView::On2dHistogram() 
{
    IplImage* src = cvCloneImage( workImg );
 
    IplImage* h_plane = cvCreateImage( cvGetSize(src), 8, 1 );
    IplImage* s_plane = cvCreateImage( cvGetSize(src), 8, 1 );
    IplImage* v_plane = cvCreateImage( cvGetSize(src), 8, 1 );
    IplImage* planes[] = { h_plane, s_plane };
    IplImage* planev[] = { h_plane, v_plane };
    IplImage* plane3[] = { s_plane, v_plane };

    int h_bins = 180, s_bins = 128, v_bins = 128;
    int hist_size[] = {h_bins, s_bins};
    int hist_size3[] = {s_bins, v_bins};
    float h_ranges[] = { 0, 180 }; /* hue varies from 0 (~0��red) to 180 (~360��red again) */
    float s_ranges[] = { 0, 255 }; /* saturation varies from 0 (black-gray-white) to 255 (pure spectrum color) */
    float v_ranges[] = { 0, 255 }; /* value varies from 0 (black-gray-white) to 255 (pure spectrum color) */
    float* ranges[] = { h_ranges, s_ranges };
    float* rangev[] = { h_ranges, v_ranges };
    float* range3[] = { s_ranges, v_ranges };
    IplImage* hist_img = cvCreateImage( cvSize(h_bins,s_bins), 8, 3 );
    CvHistogram* hist;
    int   h, s, v, intensity;
	RGBQUAD pal[256];
	char  *buf;
    int   k, bpl,factor;

	factor = src->imageSize/3/(512*512/4);  //  ȷ����������
	if (factor==0) factor=1;

	GrayColorTransfor(pal);                 //  ����α��ɫ��ɫ��

    cvCvtColor( src, src, CV_BGR2HSV );
    cvCvtPixToPlane( src, h_plane, s_plane, v_plane, 0 );
    hist = cvCreateHist( 2, hist_size, CV_HIST_ARRAY, ranges, 1 );

    cvCalcHist( planes, hist, 0, 0 );
 
	buf=hist_img->imageData;
	bpl=hist_img->widthStep;
    for( s = 0; s < s_bins; s++ )
    {
		for( h = 0, k = 0; h < h_bins; h++, k += 3 )
        {
			intensity =(int) (cvQueryHistValue_2D( hist, h, s )/factor);
			if (intensity>255) intensity=255;
			memcpy(&buf[k],&pal[intensity],3);  //  �����ת��
        }
		buf+=bpl;
    }
    cvNamedWindow( "H-S", 1 );
	cvMoveWindow("H-S", 820, 160);
	cvFlip(hist_img);
    cvShowImage( "H-S", hist_img );

    cvCalcHist( planev, hist, 0, 0 );
 
	buf=hist_img->imageData;
	bpl=hist_img->widthStep;
    for( v = 0; v < v_bins; v++ )
    {
		for( h = 0, k = 0; h < h_bins; h++, k += 3 )
        {
 			intensity =(int) (cvQueryHistValue_2D( hist, h, v )/factor);
			if (intensity>255) intensity=255;
			memcpy(&buf[k],&pal[intensity],3);
        }
		buf+=bpl;
    }
    cvNamedWindow( "H-V", 1 );
 	cvMoveWindow("H-V", 820, 325);
	cvFlip(hist_img);
    cvShowImage( "H-V", hist_img );

  	cvReleaseImage(&hist_img);
  	cvReleaseHist(&hist);
	hist_img=cvCreateImage( cvSize(s_bins,v_bins), 8, 3 );
    hist = cvCreateHist( 2, hist_size3, CV_HIST_ARRAY, range3, 1 );

    cvCalcHist( plane3, hist, 0, 0 );
 
	buf=hist_img->imageData;
	bpl=hist_img->widthStep;
    for( v = 0; v < v_bins; v++ )
    {
		for( s = 0, k = 0; s < s_bins; s++, k += 3 )
        {
 			intensity =(int) (cvQueryHistValue_2D( hist, s, v )/factor);
			if (intensity>255) intensity=255;
			memcpy(&buf[k],&pal[intensity],3);
        }
		buf+=bpl;
    }
    cvNamedWindow( "S-V", 1 );
 	cvMoveWindow("S-V", 820, 490);
	cvFlip(hist_img);
    cvShowImage( "S-V", hist_img );

	m_ImageType=-3;
    cvWaitKey(0);
  	cvDestroyWindow("H-S");
  	cvDestroyWindow("H-V");
  	cvDestroyWindow("S-V");
  	cvReleaseImage(&src);
  	cvReleaseImage(&h_plane);
  	cvReleaseImage(&s_plane);
  	cvReleaseImage(&v_plane);
  	cvReleaseImage(&hist_img);
  	cvReleaseHist(&hist);

	m_ImageType=3;
}

void CCVMFCView::OnBlurSmoothC() 
{
	OnBlurSmooth();
}

void CCVMFCView::OnGaussSmoothC() 
{
	OnGaussSmooth();
}

void CCVMFCView::OnMedianSmoothC() 
{
	OnMedianSmooth();
}

void CCVMFCView::OnSobelC() 
{
	OnSobel();
}

void CCVMFCView::OnLaplaceC() 
{
	OnLaplace();
}

//---------------------------------------------------------
//  ����

void CCVMFCView::OnUpdateDrawing(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==0));
}

void CCVMFCView::OnUpdateDelaunay(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==0));
}

void CCVMFCView::OnUpdateLogPolar(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType==3));
}

void CCVMFCView::OnUpdateDft(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CaptFlag!=1)&&(m_ImageType>0));
}

//-------------------------------------
//  ����ͼ��
//  ���� OpenCV ϵͳ�������ʵ�� drawing.c �ı�

#define NUMBER 100
#define DELAY 5
char wndnamed[] = "Drawing Demo";

CvScalar random_color(CvRNG* rng)
{
    int icolor = cvRandInt(rng);
    return CV_RGB(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

void CCVMFCView::OnDrawing() 
{
    int line_type = CV_AA; // change it to 8 to see non-antialiased graphics���Ǿ��ͼ�Σ�
    int i;
    CvPoint pt1,pt2;
    double angle;
    CvSize sz;
    CvPoint  ptt[6];
    CvPoint* pt[2];
    int  arr[2];
    CvFont font;
    CvRNG rng;
    int width = 1000, height = 700;
    int width3 = width*3, height3 = height*3;
    CvSize text_size;
    int ymin = 0;
    // Load the source image
    IplImage* image = cvCreateImage( cvSize(width,height), 8, 3 );
    IplImage* image2;

    // Create a window
    cvNamedWindow(wndnamed, 1 );
    cvZero( image );//��ʼ�����ͼ��������齫ͼ������е�ֵÿ��������Ϊ0
    cvShowImage(wndnamed,image);//��ʱ��ʾ��ͼ����Ǻ�ɫͼ��

    rng = cvRNG((unsigned)-1);//����һ���������������
    pt[0] = &(ptt[0]);
    pt[1] = &(ptt[3]);

    arr[0] = 3;
    arr[1] = 3;

	m_ImageType=-3;//����Ϊ-3��������ʲô
    for (i = 0; i< NUMBER; i++)
    {
        pt1.x=cvRandInt(&rng) % width3 - width;
        pt1.y=cvRandInt(&rng) % height3 - height;
        pt2.x=cvRandInt(&rng) % width3 - width;
        pt2.y=cvRandInt(&rng) % height3 - height;

        cvLine( image, pt1, pt2, random_color(&rng), cvRandInt(&rng)%10, line_type, 0 );//��ͼ��image�ϻ�һ����
        cvShowImage(wndnamed,image);
        cvWaitKey(DELAY);
    }

    for (i = 0; i< NUMBER; i++)
    {
        pt1.x=cvRandInt(&rng) % width3 - width;
        pt1.y=cvRandInt(&rng) % height3 - height;
        pt2.x=cvRandInt(&rng) % width3 - width;
        pt2.y=cvRandInt(&rng) % height3 - height;

        cvRectangle( image,pt1, pt2, random_color(&rng), cvRandInt(&rng)%10-1, line_type, 0 );
        cvShowImage(wndnamed,image);
        cvWaitKey(DELAY);
    }

    for (i = 0; i< NUMBER; i++)
    {
        pt1.x=cvRandInt(&rng) % width3 - width;
        pt1.y=cvRandInt(&rng) % height3 - height;
        sz.width =cvRandInt(&rng)%200;
        sz.height=cvRandInt(&rng)%200;
        angle = (cvRandInt(&rng)%1000)*0.180;

        cvEllipse( image, pt1, sz, angle, angle - 100, angle + 200,
                   random_color(&rng), cvRandInt(&rng)%10-1, line_type, 0 );
        cvShowImage(wndnamed,image);
        cvWaitKey(DELAY);
    }

    for (i = 0; i< NUMBER; i++)
    {
        pt[0][0].x=cvRandInt(&rng) % width3 - width;
        pt[0][0].y=cvRandInt(&rng) % height3 - height;
        pt[0][1].x=cvRandInt(&rng) % width3 - width;
        pt[0][1].y=cvRandInt(&rng) % height3 - height;
        pt[0][2].x=cvRandInt(&rng) % width3 - width;
        pt[0][2].y=cvRandInt(&rng) % height3 - height;
        pt[1][0].x=cvRandInt(&rng) % width3 - width;
        pt[1][0].y=cvRandInt(&rng) % height3 - height;
        pt[1][1].x=cvRandInt(&rng) % width3 - width;
        pt[1][1].y=cvRandInt(&rng) % height3 - height;
        pt[1][2].x=cvRandInt(&rng) % width3 - width;
        pt[1][2].y=cvRandInt(&rng) % height3 - height;

        cvPolyLine( image, pt, arr, 2, 1, random_color(&rng), cvRandInt(&rng)%10, line_type, 0 );
        cvShowImage(wndnamed,image);
        cvWaitKey(DELAY);
    }

    for (i = 0; i< NUMBER; i++)
    {
        pt[0][0].x=cvRandInt(&rng) % width3 - width;
        pt[0][0].y=cvRandInt(&rng) % height3 - height;
        pt[0][1].x=cvRandInt(&rng) % width3 - width;
        pt[0][1].y=cvRandInt(&rng) % height3 - height;
        pt[0][2].x=cvRandInt(&rng) % width3 - width;
        pt[0][2].y=cvRandInt(&rng) % height3 - height;
        pt[1][0].x=cvRandInt(&rng) % width3 - width;
        pt[1][0].y=cvRandInt(&rng) % height3 - height;
        pt[1][1].x=cvRandInt(&rng) % width3 - width;
        pt[1][1].y=cvRandInt(&rng) % height3 - height;
        pt[1][2].x=cvRandInt(&rng) % width3 - width;
        pt[1][2].y=cvRandInt(&rng) % height3 - height;

        cvFillPoly( image, pt, arr, 2, random_color(&rng), line_type, 0 );
        cvShowImage(wndnamed,image);
        cvWaitKey(DELAY);
    }

    for (i = 0; i< NUMBER; i++)
    {
        pt1.x=cvRandInt(&rng) % width3 - width;
        pt1.y=cvRandInt(&rng) % height3 - height;

        cvCircle( image, pt1, cvRandInt(&rng)%300, random_color(&rng),
                  cvRandInt(&rng)%10-1, line_type, 0 );
        cvShowImage(wndnamed,image);
        cvWaitKey(DELAY);
    }

    for (i = 1; i< NUMBER; i++)
    {
        pt1.x=cvRandInt(&rng) % width3 - width;
        pt1.y=cvRandInt(&rng) % height3 - height;

        cvInitFont( &font, cvRandInt(&rng) % 8,
                    (cvRandInt(&rng)%100)*0.05+0.1, (cvRandInt(&rng)%100)*0.05+0.1, 
                    (cvRandInt(&rng)%5)*0.1, cvRound(cvRandInt(&rng)%10), line_type );

        cvPutText( image, "Testing text rendering!", pt1, &font, random_color(&rng));
        cvShowImage(wndnamed,image);
        cvWaitKey(DELAY);
    }

    cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX, 3, 3, 0.0, 5, line_type );

    cvGetTextSize( "OpenCV forever!", &font, &text_size, &ymin );

    pt1.x = (width - text_size.width)/2;
    pt1.y = (height + text_size.height)/2;
    image2 = cvCloneImage(image);

    for( i = 0; i < 255; i++ )
    {
        cvSubS( image2, cvScalarAll(i), image, 0 );
        cvPutText( image, "OpenCV forever!", pt1, &font, CV_RGB(255,i,i));
        cvShowImage(wndnamed,image);
        cvWaitKey(DELAY);
    }

    // Wait for a key stroke; the same function arranges events processing
    cvWaitKey(0);
    cvReleaseImage(&image);
    cvReleaseImage(&image2);
    cvDestroyWindow(wndnamed);

	m_ImageType=0;
}

//-------------------------------------
//  ���� Delaunay ͼ��
//  ���� OpenCV ϵͳ�������ʵ�� delaunay.c �ı�

CvSubdiv2D* init_delaunay( CvMemStorage* storage,
                           CvRect rect )
{
    CvSubdiv2D* subdiv;

    subdiv = cvCreateSubdiv2D( CV_SEQ_KIND_SUBDIV2D, sizeof(*subdiv),
                               sizeof(CvSubdiv2DPoint),
                               sizeof(CvQuadEdge2D),
                               storage );
    cvInitSubdivDelaunay2D( subdiv, rect );

    return subdiv;
}


void draw_subdiv_point( IplImage* img, CvPoint2D32f fp, CvScalar color )
{
    cvCircle( img, cvPoint(cvRound(fp.x), cvRound(fp.y)), 3, color, CV_FILLED, 8, 0 );
}


void draw_subdiv_edge( IplImage* img, CvSubdiv2DEdge edge, CvScalar color )
{
    CvSubdiv2DPoint* org_pt;
    CvSubdiv2DPoint* dst_pt;
    CvPoint2D32f org;
    CvPoint2D32f dst;
    CvPoint iorg, idst;

    org_pt = cvSubdiv2DEdgeOrg(edge);
    dst_pt = cvSubdiv2DEdgeDst(edge);

    if( org_pt && dst_pt )
    {
        org = org_pt->pt;
        dst = dst_pt->pt;

        iorg = cvPoint( cvRound( org.x ), cvRound( org.y ));
        idst = cvPoint( cvRound( dst.x ), cvRound( dst.y ));

        cvLine( img, iorg, idst, color, 1, CV_AA, 0 );
    }
}


void draw_subdiv( IplImage* img, CvSubdiv2D* subdiv,
                  CvScalar delaunay_color, CvScalar voronoi_color )
{
    CvSeqReader  reader;
    int i, total = subdiv->edges->total;
    int elem_size = subdiv->edges->elem_size;

    cvStartReadSeq( (CvSeq*)(subdiv->edges), &reader, 0 );

    for( i = 0; i < total; i++ )
    {
        CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);

        if( CV_IS_SET_ELEM( edge ))
        {
            draw_subdiv_edge( img, (CvSubdiv2DEdge)edge + 1, voronoi_color );
            draw_subdiv_edge( img, (CvSubdiv2DEdge)edge, delaunay_color );
        }

        CV_NEXT_SEQ_ELEM( elem_size, reader );
    }
}


void locate_point( CvSubdiv2D* subdiv, CvPoint2D32f fp, IplImage* img,
                   CvScalar active_color )
{
    CvSubdiv2DEdge e;
    CvSubdiv2DEdge e0 = 0;
    CvSubdiv2DPoint* p = 0;

    cvSubdiv2DLocate( subdiv, fp, &e0, &p );

    if( e0 )
    {
        e = e0;
        do
        {
            draw_subdiv_edge( img, e, active_color );
            e = cvSubdiv2DGetEdge(e,CV_NEXT_AROUND_LEFT);
        }
        while( e != e0 );
    }

    draw_subdiv_point( img, fp, active_color );
}


void draw_subdiv_facet( IplImage* img, CvSubdiv2DEdge edge )
{
    CvSubdiv2DEdge t = edge;
    int i, count = 0;
    CvPoint* buf = 0;

    // count number of edges in facet
    do
    {
        count++;
        t = cvSubdiv2DGetEdge( t, CV_NEXT_AROUND_LEFT );
    } while (t != edge );

    buf = (CvPoint*)malloc( count * sizeof(buf[0]));

    // gather points
    t = edge;
    for( i = 0; i < count; i++ )
    {
        CvSubdiv2DPoint* pt = cvSubdiv2DEdgeOrg( t );
        if( !pt ) break;
        buf[i] = cvPoint( cvRound(pt->pt.x), cvRound(pt->pt.y));
        t = cvSubdiv2DGetEdge( t, CV_NEXT_AROUND_LEFT );
    }

    if( i == count )
    {
        CvSubdiv2DPoint* pt = cvSubdiv2DEdgeDst( cvSubdiv2DRotateEdge( edge, 1 ));
        cvFillConvexPoly( img, buf, count, CV_RGB(rand()&255,rand()&255,rand()&255), CV_AA, 0 );
        cvPolyLine( img, &buf, &count, 1, 1, CV_RGB(0,0,0), 1, CV_AA, 0);
        draw_subdiv_point( img, pt->pt, CV_RGB(0,0,0));
    }
    free( buf );
}

void paint_voronoi( CvSubdiv2D* subdiv, IplImage* img )
{
    CvSeqReader  reader;
    int i, total = subdiv->edges->total;
    int elem_size = subdiv->edges->elem_size;

    cvCalcSubdivVoronoi2D( subdiv );

    cvStartReadSeq( (CvSeq*)(subdiv->edges), &reader, 0 );

    for( i = 0; i < total; i++ )
    {
        CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);

        if( CV_IS_SET_ELEM( edge ))
        {
            CvSubdiv2DEdge e = (CvSubdiv2DEdge)edge;
            // left
            draw_subdiv_facet( img, cvSubdiv2DRotateEdge( e, 1 ));

            // right
            draw_subdiv_facet( img, cvSubdiv2DRotateEdge( e, 3 ));
        }

        CV_NEXT_SEQ_ELEM( elem_size, reader );
    }
}

void CCVMFCView::OnDelaunay() 
{
    char win[] = "Delaunay";
    int i;
    CvRect rect = { 0, 0, 600, 600 };
    CvMemStorage* storage;
    CvSubdiv2D* subdiv;
    IplImage* img;
    CvScalar active_facet_color, delaunay_color, voronoi_color, bkgnd_color;

    active_facet_color = CV_RGB( 255, 0, 0 );
    delaunay_color  = CV_RGB( 0,0,0);
    voronoi_color = CV_RGB(0, 180, 0);
    bkgnd_color = CV_RGB(255,255,255);

    img = cvCreateImage( cvSize(rect.width,rect.height), 8, 3 );
    cvSet( img, bkgnd_color, 0 );

    cvNamedWindow( win, 1 );

    storage = cvCreateMemStorage(0);
    subdiv = init_delaunay( storage, rect );

    printf("Delaunay triangulation will be build now interactively.\n"
           "To stop the process, press any key\n\n");

	m_ImageType=-3;
    for( i = 0; i < 200; i++ )
    {
        CvPoint2D32f fp = cvPoint2D32f( (float)(rand()%(rect.width-10)+5),
                                        (float)(rand()%(rect.height-10)+5));

        locate_point( subdiv, fp, img, active_facet_color );
        cvShowImage( win, img );

        if( cvWaitKey( 100 ) >= 0 )
            break;

        cvSubdivDelaunay2DInsert( subdiv, fp );
        cvCalcSubdivVoronoi2D( subdiv );
        cvSet( img, bkgnd_color, 0 );
        draw_subdiv( img, subdiv, delaunay_color, voronoi_color );
        cvShowImage( win, img );

        if( cvWaitKey( 100 ) >= 0 )
            break;
    }

    cvSet( img, bkgnd_color, 0 );
    paint_voronoi( subdiv, img );
    cvShowImage( win, img );

    cvWaitKey(0);

    cvReleaseMemStorage( &storage );
    cvReleaseImage(&img);
    cvDestroyWindow( win );

	m_ImageType=0;
}

//-------------------------------------
//  ������任
//  ���ݡ�OpenCV�̳�(����ƪ)���� 5-4 �ı�

void CCVMFCView::OnLogPolar() 
{
    IplImage* src = 0;

	src = cvCloneImage( workImg );
	cvFlip(src);
 
    IplImage* dst = cvCreateImage( cvSize(src->width/2,src->height/2), 8, 3 );
    IplImage* src2 = cvCreateImage( cvGetSize(src), 8, 3 );
    cvLogPolar( src, dst, cvPoint2D32f(src->width/2,src->height/2), 40, 
		CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS );
    cvLogPolar( dst, src2, cvPoint2D32f(src->width/2,src->height/2), 40, 
		CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS+CV_WARP_INVERSE_MAP );
    cvNamedWindow( "log-polar", 1 );
    cvShowImage( "log-polar", dst );
    cvNamedWindow( "inverse log-polar", 1 );
    cvShowImage( "inverse log-polar", src2 );

    cvWaitKey();
    cvDestroyWindow( "log-polar" );
    cvDestroyWindow( "inverse log-polar" );
    cvReleaseImage(&src);
    cvReleaseImage(&dst);
    cvReleaseImage(&src2);
}

//-------------------------------------
//  DFT
//  ���ݡ�OpenCV�̳�(����ƪ)���� 4-2 �ı�
//  OpenCV ϵͳ�������ʵ�� dft.c

// Rearrange the quadrants of Fourier image so that the origin is at
// the image center
// src & dst arrays of equal size & type
void cvShiftDFT(CvArr * src_arr, CvArr * dst_arr )
{
    CvMat * tmp;
    CvMat q1stub, q2stub;
    CvMat q3stub, q4stub;
    CvMat d1stub, d2stub;
    CvMat d3stub, d4stub;
    CvMat * q1, * q2, * q3, * q4;
    CvMat * d1, * d2, * d3, * d4;

    CvSize size = cvGetSize(src_arr);
    CvSize dst_size = cvGetSize(dst_arr);
    int cx, cy;

    if(dst_size.width != size.width || 
       dst_size.height != size.height){
        cvError( CV_StsUnmatchedSizes, "cvShiftDFT", "Source and Destination arrays must have equal sizes", __FILE__, __LINE__ );   
    }

    if(src_arr==dst_arr){
        tmp = cvCreateMat(size.height/2, size.width/2, cvGetElemType(src_arr));
    }
    
    cx = size.width/2;
    cy = size.height/2; // image center

    q1 = cvGetSubRect( src_arr, &q1stub, cvRect(0,0,cx, cy) );
    q2 = cvGetSubRect( src_arr, &q2stub, cvRect(cx,0,cx,cy) );
    q3 = cvGetSubRect( src_arr, &q3stub, cvRect(cx,cy,cx,cy) );
    q4 = cvGetSubRect( src_arr, &q4stub, cvRect(0,cy,cx,cy) );
    d1 = cvGetSubRect( src_arr, &d1stub, cvRect(0,0,cx,cy) );
    d2 = cvGetSubRect( src_arr, &d2stub, cvRect(cx,0,cx,cy) );
    d3 = cvGetSubRect( src_arr, &d3stub, cvRect(cx,cy,cx,cy) );
    d4 = cvGetSubRect( src_arr, &d4stub, cvRect(0,cy,cx,cy) );

    if(src_arr!=dst_arr){
        if( !CV_ARE_TYPES_EQ( q1, d1 )){
            cvError( CV_StsUnmatchedFormats, "cvShiftDFT", "Source and Destination arrays must have the same format", __FILE__, __LINE__ ); 
        }
        cvCopy(q3, d1, 0);
        cvCopy(q4, d2, 0);
        cvCopy(q1, d3, 0);
        cvCopy(q2, d4, 0);
    }
    else{
        cvCopy(q3, tmp, 0);
        cvCopy(q1, q3, 0);
        cvCopy(tmp, q1, 0);
        cvCopy(q4, tmp, 0);
        cvCopy(q2, q4, 0);
        cvCopy(tmp, q2, 0);
    }
}

void CCVMFCView::OnDft() 
{
//    const char* filename = "image\\lena.jpg";
    IplImage * im;

    IplImage * realInput;
    IplImage * imaginaryInput;
    IplImage * complexInput;
    int dft_M, dft_N;
    CvMat* dft_A, tmp;
    IplImage * image_Re;
    IplImage * image_Im;
    double m, M;

	if (workImg->nChannels==3) {
 		im = cvCreateImage(cvGetSize(workImg), IPL_DEPTH_8U, 1);
		cvCvtColor(workImg, im, CV_BGR2GRAY);
	}
	else {
        im = cvCloneImage( workImg );
	}
	cvFlip(im);

    realInput = cvCreateImage( cvGetSize(im), IPL_DEPTH_64F, 1);
    imaginaryInput = cvCreateImage( cvGetSize(im), IPL_DEPTH_64F, 1);
    complexInput = cvCreateImage( cvGetSize(im), IPL_DEPTH_64F, 2);

    cvScale(im, realInput, 1.0, 0.0);
    cvZero(imaginaryInput);
    cvMerge(realInput, imaginaryInput, NULL, NULL, complexInput);

    dft_M = cvGetOptimalDFTSize( im->height - 1 );
    dft_N = cvGetOptimalDFTSize( im->width - 1 );

    dft_A = cvCreateMat( dft_M, dft_N, CV_64FC2 );
    image_Re = cvCreateImage( cvSize(dft_N, dft_M), IPL_DEPTH_64F, 1);
    image_Im = cvCreateImage( cvSize(dft_N, dft_M), IPL_DEPTH_64F, 1);

    // copy A to dft_A and pad dft_A with zeros
    cvGetSubRect( dft_A, &tmp, cvRect(0,0, im->width, im->height));
    cvCopy( complexInput, &tmp, NULL );
    if( dft_A->cols > im->width )
    {
        cvGetSubRect( dft_A, &tmp, cvRect(im->width,0, dft_A->cols - im->width, im->height));
        cvZero( &tmp );
    }

    // no need to pad bottom part of dft_A with zeros because of
    // use nonzero_rows parameter in cvDFT() call below

    cvDFT( dft_A, dft_A, CV_DXT_FORWARD, complexInput->height );

    cvNamedWindow("win", 0);
    cvNamedWindow("magnitude", 0);
    cvShowImage("win", im);

    // Split Fourier in real and imaginary parts
    cvSplit( dft_A, image_Re, image_Im, 0, 0 );

    // Compute the magnitude of the spectrum Mag = sqrt(Re^2 + Im^2)
    cvPow( image_Re, image_Re, 2.0);
    cvPow( image_Im, image_Im, 2.0);
    cvAdd( image_Re, image_Im, image_Re, NULL);
    cvPow( image_Re, image_Re, 0.5 );

    // Compute log(1 + Mag)
    cvAddS( image_Re, cvScalarAll(1.0), image_Re, NULL ); // 1 + Mag
    cvLog( image_Re, image_Re ); // log(1 + Mag)


    // Rearrange the quadrants of Fourier image so that the origin is at
    // the image center
    cvShiftDFT( image_Re, image_Re );

    cvMinMaxLoc(image_Re, &m, &M, NULL, NULL, NULL);
    cvScale(image_Re, image_Re, 1.0/(M-m), 1.0*(-m)/(M-m));
    cvShowImage("magnitude", image_Re);

    cvWaitKey(-1);
    cvDestroyWindow( "win" );
    cvDestroyWindow( "magnitude" );

    cvReleaseImage(&im);
    cvReleaseImage(&realInput);
    cvReleaseImage(&imaginaryInput);
    cvReleaseImage(&complexInput);
    cvReleaseImage(&image_Re);
    cvReleaseImage(&image_Im);
}




