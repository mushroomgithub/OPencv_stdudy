//  Processing.h
//   2010.8.23

#ifndef		PROCESSING
#define		PROCESSING

//---------------------------------------------------------
//  

LPBITMAPINFO CtreateMapInfo(IplImage* workImg,int flag);	//���λͼ��Ϣ
 
int  imageType(IplImage* p);//���ͼ���Ƿ�Ϊ��ֵͼ������
int  imageClone(IplImage* pi,IplImage** ppo);  //  ���� IplImage λͼ
int  imageReplace(IplImage* pi,IplImage** ppo);  //  λͼ�滻
 
//---------------------------------------------------------
//  ����ͼ����

void ImageDwindle(IplImage *pi,IplImage *po,int n,int nCnls);   //ͼ����������С
int  NextColor(int start,int k,int step);            //  ��һ��ɫ��
void Histog(BYTE *buf,int *pg,int Dx,int Dy);  //ֱ��ͼͳ��
int  BasicGlobalThreshold(int *pg,int start,int end);//����ȫ����ֵ��
void GrayColorTransfor(RGBQUAD *pal); // ���任�����͸���Ԫ��ɫ����

extern RGBQUAD VgaDefPal[256];
extern RGBQUAD VgaColorTab[256];

#endif  //PROCESSING
