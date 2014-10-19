; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCVMFCView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CVMFC.h"
LastPage=0

ClassCount=6
Class1=CVMFCApp
Class2=CVMFCDoc
Class3=CCVMFCView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDR_MULTIMTYPE

[CLS:CVMFCApp]
Type=0
HeaderFile=CVMFC.h
ImplementationFile=CVMFC.cpp
Filter=N

[CLS:CVMFCDoc]
Type=0
HeaderFile=CVMFCDoc.h
ImplementationFile=CVMFCDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CVMFCDoc

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=CVMFC.cpp
ImplementationFile=CVMFC.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_APP_ABOUT
CommandCount=4

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MULTIMTYPE]
Type=1
Class=CCVMFCView
Command1=ID_FILE_OPEN
Command2=ID_REFRESH
Command3=ID_FILE_CLOSE
Command4=ID_CONSERVATION_IMAGE
Command5=ID_FILE_MRU_FILE1
Command6=ID_COLOR_IMAGE_REFRESH
Command7=ID_FILE_SAVE_AS
Command8=ID_APP_EXIT
Command9=ID_COLOR_TO_GRAY
Command10=ID_IMAGE_INVERT
Command11=ID_FLIP_V
Command12=ID_FLIP_H
Command13=ID_FLIP
Command14=ID_ROTATION_30
Command15=ID_WARP_AFFINE
Command16=ID_WARP_PERSPECT
Command17=ID_IMAGE_ADJUST
Command18=ID_IMAGE_HISTOGRAM
Command19=ID_HIST_EQUALIZE
Command20=ID_BLUR_SMOOTH
Command21=ID_GAUSS_SMOOTH
Command22=ID_MEDIAN_SMOOTH
Command23=ID_SOBEL
Command24=ID_LAPLACE
Command25=ID_THRESHOLDING_1
Command26=ID_THRESHOLDING_2
Command27=ID_ADAPTIVE_THRESHOLD
Command28=ID_BASIC_GLOBAL_THRESHOLD
Command29=ID_MIN_AREA_RECT_2
Command30=ID_AREA_RECT
Command31=ID_MIN_AREA_RECT
Command32=ID_APPROX_POLY
Command33=ID_CONVEX_HULL_2
Command34=ID_CONVEX_HULL
Command35=ID_AREA_CONVEX_HULL
Command36=ID_CONVEXITY_DEFECTS
Command37=ID_CONTOUR_TRACK
Command38=ID_DISTANCE
Command39=ID_EROSION
Command40=ID_DILATION
Command41=ID_OPENNING
Command42=ID_CLOSING
Command43=ID_GRADS
Command44=ID_GRAY_TOPHAT
Command45=ID_GRAY_BLACKHAT
Command46=ID_IMAGE_RGB
Command47=ID_IMAGE_HSV
Command48=ID_IMAGE_LAB
Command49=ID_IMAGE_RGB_C
Command50=ID_IMAGE_XYZ
Command51=ID_IMAGE_YCRCB
Command52=ID_IMAGE_LUV
Command53=ID_2D_HISTOGRAM
Command54=ID_BLUR_SMOOTH_C
Command55=ID_GAUSS_SMOOTH_C
Command56=ID_MEDIAN_SMOOTH_C
Command57=ID_SOBEL_C
Command58=ID_LAPLACE_C
Command59=ID_IMAGE_SHRINK
Command60=ID_RADIAL_GRADS
Command61=ID_CANNY_BORDDETEC
Command62=ID_HOUGH_LINES
Command63=ID_HOUGH_CIRCLE
Command64=ID_SQUARES_TEST
Command65=ID_FLOOD_FILL
Command66=ID_PYR_SEGMENTATION
Command67=ID_FIT_ELLIPSE
Command68=ID_SNAKE
Command69=ID_WATERSHED
Command70=ID_CORNERS_TEST
Command71=ID_CLUSTERS
Command72=ID_SEQ_PARTITION
Command73=ID_ROTATION_TRACK
Command74=ID_FACE_DETECT
Command75=ID_DYNAMIC_BORDER_TEST
Command76=ID_OPTICAL_FLOW_TRACK
Command77=IF_FOREGROUND_DETECT
Command78=ID_MOTION_DETECT
Command79=ID_CAM_SHIFT_DEMO
Command80=ID_FACE_DETECT_2
Command81=ID_START_CAPTURE
Command82=ID_OPEN_AVI_FILE
Command83=ID_VIEW_CONTINUE
Command84=ID_CAPTURE_IMAGE
Command85=ID_AVERAGE_IMAGE
Command86=ID_CAP_ABORT
Command87=ID_SET_PARAMETER
Command88=ID_DRAWING
Command89=ID_DELAUNAY
Command90=ID_LOG_POLAR
Command91=ID_DFT
Command92=ID_WINDOW_CASCADE
Command93=ID_WINDOW_TILE_HORZ
Command94=ID_APP_ABOUT
CommandCount=94

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:CCVMFCView]
Type=0
HeaderFile=CVMFCview.h
ImplementationFile=CVMFCview.cpp
BaseClass=CScrollView
LastObject=ID_FLOOD_FILL
Filter=C
VirtualFilter=VWC

