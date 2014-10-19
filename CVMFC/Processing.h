//  Processing.h
//   2010.8.23

#ifndef		PROCESSING
#define		PROCESSING

//---------------------------------------------------------
//  

LPBITMAPINFO CtreateMapInfo(IplImage* workImg,int flag);	//获得位图信息
 
int  imageType(IplImage* p);//检测图像是否为二值图像类型
int  imageClone(IplImage* pi,IplImage** ppo);  //  复制 IplImage 位图
int  imageReplace(IplImage* pi,IplImage** ppo);  //  位图替换
 
//---------------------------------------------------------
//  常规图像处理

void ImageDwindle(IplImage *pi,IplImage *po,int n,int nCnls);   //图像整数倍缩小
int  NextColor(int start,int k,int step);            //  下一彩色号
void Histog(BYTE *buf,int *pg,int Dx,int Dy);  //直方图统计
int  BasicGlobalThreshold(int *pg,int start,int end);//基本全局阈值法
void GrayColorTransfor(RGBQUAD *pal); // 按变换曲线送各单元颜色分量

extern RGBQUAD VgaDefPal[256];
extern RGBQUAD VgaColorTab[256];

#endif  //PROCESSING
