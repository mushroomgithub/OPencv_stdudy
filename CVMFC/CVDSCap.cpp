//---------------------------------------------------------
//  CVDSCap.cpp     2010.8.12
//---------------------------------------------------------

#include "stdafx.h"
#ifndef min
#define min(a,b)  (((a)<(b))?(a):(b))
#endif
//---------------------------------------------------------
//  ��Ƶ(����ͷ)�ɼ�����
 
CCameraDS  camera;

CvCapture* m_Video;                         //  ��Ƶָ��
IplImage*  m_Frame;                         //  OpenCV λͼָ��
IplImage** m_List;                          //  λͼָ���

int	    cap_shift=2;      //  ȡƽ������λ��                 1-2-3 
int        cap_num  =4;      //  ������������Ŀ(��������ֵ���) 2-4-8
int        frame_time;

int        frameSetW=640;                   //  �ɼ��ֱ�������ֵ
int        frameSetH=480;

int        frameW;
int        frameH;
int        cap_time;                        //  �����־

int  StartCapture(void)                     //  ������Ƶ
{
	int cam_count,i;

	//������ȡ����ͷ��Ŀ
	cam_count = CCameraDS::CameraCount();
	printf("There are %d cameras.\n", cam_count);

	if(cam_count==0)
		return(false);

	//��ȡ��������ͷ������
	for(i=0; i < cam_count; i++)
	{
		char camera_name[1024];  
		int retval = CCameraDS::CameraName(i, camera_name, sizeof(camera_name) );

		if(retval >0)
			printf("Camera #%d's Name is '%s'.\n", i, camera_name);
		else
			printf("Can not get Camera #%d's name.\n", i);
	}

	//�򿪵�һ������ͷ
	//if(! camera.OpenCamera(0, true)) //��������ѡ�񴰿�
	if(! camera.OpenCamera(0, false, frameSetW,frameSetH)) //����������ѡ�񴰿ڣ��ô����ƶ�ͼ���͸�
	{
		fprintf(stderr, "Can not open camera.\n");
		camera.CloseCamera();
		return(-1);
	}

	frameW=frameSetW;    frameH=frameSetH;  //  ȡ���÷ֱ���
	cap_time=0;                             //  �����־��ʼ��
 
	//-------------------------------------------
	cap_num=(1<<cap_shift);                 //  ȷ��������λͼ��

	m_List=(IplImage**) malloc(cap_num*sizeof(IplImage*));//Ϊλͼָ����������ڴ�ռ�
	for (i=0;i<cap_num;i++) {
		m_List[i]=cvCreateImage(cvSize(frameW,frameH), IPL_DEPTH_8U, 3);
		                                    //  ����λͼ������
	}
	frame_time=0;
	return(true);
}

BOOL OpenAviFile(CString strFileName)       //  ����Ƶ�ļ�
{
	m_Video = cvCreateFileCapture(strFileName);//��ѽ�����AVI�ļ�������һ��CvCaptureָ�룬��ָ�������Ҫ����avi�ļ�����Ϣ
	if (!m_Video) 
		return(false);
 	m_Frame=cvQueryFrame(m_Video);
	frameW =(int) cvGetCaptureProperty(m_Video,CV_CAP_PROP_FRAME_WIDTH);//����Ƶͷ�ļ��ж�����Ƶ֡ͼ��Ŀ�͸�
	frameH =(int) cvGetCaptureProperty(m_Video,CV_CAP_PROP_FRAME_HEIGHT);
 
 	cap_time=0;                             //  ��־��ʼ��

	//-------------------------------------------
	m_List=(IplImage**) malloc(cap_num*sizeof(IplImage*));
	for (int i=0;i<cap_num;i++) {
		m_List[i]=cvCreateImage(cvSize(frameW,frameH), IPL_DEPTH_8U, 3);//����λͼָ������
	}
	frame_time=0;
	return(true);
}

void StartAverage(void)
{
	frame_time=cap_num;
}

int  LoadImageFrame(IplImage* pImg,int f)   //  ������Ƶͼ��
{
	int  bl;

	if (m_Video) {//��ʾ�Ӵ򿪵�AVI�ļ��л�õ�֡ͼ��
 		m_Frame=cvQueryFrame(m_Video);      //  ȡ��λͼ
	}
	else {//��ʾ�ӵ�ǰ���ڴ򿪵�����ͷ�У��ɼ���֡ͼ��
		m_Frame=camera.QueryFrame();
	}
	if (m_Frame)//����õ��˵�֡ͼ��
	{
		if (frame_time==0) //��ʾ�Ǵ��ڿ�������ͷ���ߴ�AVI�ļ�
			bl=1;
		else 
		{                              //  ��ͼ��ƽ�������˵�ʱִ��
			frame_time--;
			memcpy(m_List[frame_time]->imageData,m_Frame->imageData,
					m_Frame->imageSize);    //  ����λͼ
			if (frame_time==0)//��ʾ�Ƕ�ʱ����μ���frame_time��ֱ��Ϊ0,2��ʾ��ʱ����������˲���
				bl=2;
			else bl=1;//��ʾ����Ƶ����ʱ����Ϊ��ʱframe_time��Ϊ0,���Ƕ�ʱ��������������Ƶ�����Ӳ˵�������
		}
	}
	else bl=0;

	if ((bl==1)&&(f==1)) {//��Ƶ����ʱ������õ�֡ͼ���׵�ַ������pimg�У�����
		memcpy(pImg->imageData,m_Frame->imageData,
				m_Frame->imageSize);        //  ����λͼ
 		cap_time++;                         //  ��Ƶ���������־�Լ�
	}
	return(bl);
}

void AverageImage(IplImage* pImg)           //  ��OnTimer������ʵ�ֶ�ͼ��ƽ����ͨ��
{                                           //  OpenCV���ʵ��
	IplImage* pImg32f = NULL;
	IplImage* pImg32s = NULL;
	int   i,j,k,*pi;
	BYTE  *pb;

 	pImg32f = cvCreateImage(cvGetSize(pImg),
				IPL_DEPTH_32F,pImg->nChannels);
 	pImg32s = cvCreateImage(cvGetSize(pImg),
				IPL_DEPTH_32S,pImg->nChannels);

	cvZero(pImg32f);
	for (i=0;i<cap_num;i++) {
		cvAcc(m_List[i],pImg32f,NULL);      //  ���Ӵ���Ƶ��������ͷ�л�õĵ�֡λͼ�������ݣ���LoadImageFrame������ͨ��memcpy���������õ������ӵ�pImg32fλͼ������
	}
	cvConvertScale(pImg32f,pImg32s,1.0,0);  //  ת��Ϊ����

	k=min(pImg->width,pImg32s->width);
	for (i=0;i<pImg->height;i++) {
		pb=(BYTE*) (pImg->imageData+i*pImg->widthStep);
		pi=(int*)  (pImg32s->imageData+i*pImg32s->widthStep);
		for (j=0;j<k*pImg->nChannels;j++) 
			pb[j]=(BYTE) (pi[j]>>cap_shift);  //  pi[j]/cap_num  ƽ�� ����pb[j]����pImg->imageDataÿ���׵�ַ��Ӧͨ����ֵ��
															//��pb�ĸ�ֵ��ʵ���Ƕ�pImg�Ĳ���������ͼ��ƽ���Ľ��Ҳ��pImgָ�뷵��
	}

	cvReleaseImage(&pImg32f);
	cvReleaseImage(&pImg32s);
}

/*
void AverageImage(IplImage* pImg)           //  ��(��)ͼ��ƽ��
{                                           //  C ���ʵ��
	WORD *buffer,*bufferp;
	BYTE *bufp;
	int  i,k,bpl,size;
  
	bpl=(pImg->width*pImg->depth*pImg->nChannels+31)/32*4;
  	size=bpl*pImg->height;

	buffer=(WORD*) malloc(size*sizeof(WORD));
	memset(buffer,0,size*sizeof(WORD));     //  ���ֺ�����

	for (k=0;k<cap_num;k++) {
		bufp=(BYTE*)m_List[k]->imageData;
 		bufferp=buffer;     
		for (i=0;i<size;i++) {
			(*bufferp)+=(WORD)(*bufp++);    //  ����ֵ����
			bufferp++;
		}
	}
 
	bufp=(BYTE*)pImg->imageData;     
	bufferp=buffer;
	for (i=0;i<size;i++) {
		(*bufp++)=(BYTE) ((*bufferp++)>>cap_shift);  //  ����ֵȡƽ��
	}

 	free(buffer);
}
*/

void AbortCapture(IplImage* pImg)           //  �ر���Ƶ
{
	if (cap_time==0) {                      //  ������δ����
		LoadImageFrame(pImg,1);             //  ������Ƶͼ��
	}
	if (m_Video) {
 		cvReleaseCapture(&m_Video);         //  �ͷ���Ƶ
	}
	else {
		camera.CloseCamera();               //  �ر�����ͷ
	}

	//-------------------------------------------
	for (int i=0;i<cap_num;i++) {
 		cvReleaseImage(&m_List[i]);         //  �ͷ�λͼ������
	}
	free(m_List);
	frame_time=0;
}

BOOL SetParameter(void)                     //  ����ѡ��
{
	int cam_count;

	//������ȡ����ͷ��Ŀ
	cam_count = CCameraDS::CameraCount();
	printf("There are %d cameras.\n", cam_count);


	//��ȡ��������ͷ������
	for(int i=0; i < cam_count; i++)
	{
		char camera_name[1024];  
		int retval = CCameraDS::CameraName(i, camera_name, sizeof(camera_name) );

		if(retval >0)
			printf("Camera #%d's Name is '%s'.\n", i, camera_name);
		else
			printf("Can not get Camera #%d's name.\n", i);
	}


	if(cam_count==0) 
	{
		fprintf(stderr, "Can not open camera.\n");
 		return(false);
	}

	if( camera.OpenCamera(0, true))         //  ��������ѡ�񴰿�
	{
		frameSetW=camera.GetWidth();        //  ��ȡ���÷ֱ���
		frameSetH=camera.GetHeight();
		camera.CloseCamera();               //  �ر�����ͷ
		return(true);
	}
	else
	{
		fprintf(stderr, "Can not open camera.\n");
 		return(false);
	}
}

