#include <vector>  
#include <stdio.h>  
#include<opencv2/opencv.hpp>  
#include<opencv2/core/core.hpp>  
using namespace std;
using namespace cv;
cv::Mat g_srcImage, g_dstImage;//原始图和效果图  
int g_nTrackbarNumer = 0;//0表示腐蚀erode, 1表示膨胀dilate  
int g_nStructElementSize = 3; //结构元素(内核矩阵)的尺寸  


//-----------------------------------【全局函数声明部分】--------------------------------------  
//            描述：全局函数声明  
//-----------------------------------------------------------------------------------------------  
void Process();//膨胀和腐蚀的处理函数  
void on_TrackbarNumChange(int, void *);//回调函数  
void on_ElementSizeChange(int, void *);//回调函数  


//-----------------------------------【main( )函数】--------------------------------------------  
//            描述：控制台应用程序的入口函数，我们的程序从这里开始  
//-----------------------------------------------------------------------------------------------  
int DilateAndErode()  
{  
	//改变console字体颜色  
	system("color5E");   

	//载入原图  
	g_srcImage= imread("1.jpg");  
	if(!g_srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }  

	//显示原始图  
	namedWindow("【原始图】");  
	imshow("【原始图】", g_srcImage);  

	//进行初次腐蚀操作并显示效果图  
	namedWindow("【效果图】");  
	//获取自定义核  
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));  
	erode(g_srcImage,g_dstImage, element);  
	imshow("【效果图】", g_dstImage);  

	//创建轨迹条  
	createTrackbar("腐蚀/膨胀", "【效果图】", &g_nTrackbarNumer, 1, on_TrackbarNumChange);  
	createTrackbar("内核尺寸", "【效果图】",&g_nStructElementSize, 21, on_ElementSizeChange);   

	//轮询获取按键信息，若下q键，程序退出  
	while(char(waitKey(1))!= 'q') {}  

	return 0;  
}  

//-----------------------------【Process( )函数】------------------------------------  
//            描述：进行自定义的腐蚀和膨胀操作  
//-----------------------------------------------------------------------------------------  
void Process()  
{  
	//获取自定义核  
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));  

	//进行腐蚀或膨胀操作  
	if(g_nTrackbarNumer== 0) {     
		erode(g_srcImage,g_dstImage, element);  
	}  
	else{  
		dilate(g_srcImage,g_dstImage, element);  
	}  

	//显示效果图  
	imshow("【效果图】", g_dstImage);  
}  


//-----------------------------【on_TrackbarNumChange( )函数】------------------------------------  
//            描述：腐蚀和膨胀之间切换开关的回调函数  
//-----------------------------------------------------------------------------------------------------  
void on_TrackbarNumChange(int, void *)  
{  
	//腐蚀和膨胀之间效果已经切换，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来  
	Process();  
}  


//-----------------------------【on_ElementSizeChange( )函数】-------------------------------------  
//            描述：腐蚀和膨胀操作内核改变时的回调函数  
//-----------------------------------------------------------------------------------------------------  
void on_ElementSizeChange(int, void *)  
{  
	//内核尺寸已改变，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来  
	Process();  
}  

int OpenOperation( )  
{  
	//载入原始图    
	Mat image = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	//创建窗口    
	namedWindow("【原始图】开运算");   
	namedWindow("【效果图】开运算");   
	//显示原始图   
	imshow("【原始图】开运算", image);   
	//定义核  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));   
	//进行形态学操作  
	morphologyEx(image,image, MORPH_OPEN, element);  
	//显示效果图   
	imshow("【效果图】开运算", image);   

	waitKey(0);   

	return 0;   
}  

int CloseOperation()  
{  
	//载入原始图    
	Mat image = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	//创建窗口    
	namedWindow("【原始图】闭运算");   
	namedWindow("【效果图】闭运算");   
	//显示原始图   
	imshow("【原始图】闭运算", image);   
	//定义核  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));   
	//进行形态学操作  
	morphologyEx(image,image, MORPH_CLOSE, element);  
	//显示效果图   
	imshow("【效果图】闭运算", image);   

	waitKey(0);   

	return 0;   
} 

int MorphGradient( )  
{  
	//载入原始图    
	Mat image = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	//创建窗口    
	namedWindow("【原始图】形态学梯度");   
	namedWindow("【效果图】形态学梯度");   
	//显示原始图   
	imshow("【原始图】形态学梯度", image);   
	//定义核  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));   
	//进行形态学操作  
	morphologyEx(image,image, MORPH_GRADIENT, element);  
	//显示效果图   
	imshow("【效果图】形态学梯度", image);   

	waitKey(0);   

	return 0;   
} 

int MorphTopHat( )  
{  
	//载入原始图    
	Mat image = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	//创建窗口    
	namedWindow("【原始图】顶帽运算");   
	namedWindow("【效果图】顶帽运算");   
	//显示原始图   
	imshow("【原始图】顶帽运算", image);   
	//定义核  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));   
	//进行形态学操作  
	morphologyEx(image,image, MORPH_TOPHAT, element);  
	//显示效果图   
	imshow("【效果图】顶帽运算", image);   

	waitKey(0);   

	return 0;   
}  

int MorphBlackHat()  
{  
	//载入原始图    
	Mat image = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	//创建窗口    
	namedWindow("【原始图】黑帽运算");   
	namedWindow("【效果图】黑帽运算");   
	//显示原始图   
	imshow("【原始图】黑帽运算", image);   
	//定义核  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));   
	//进行形态学操作  
	morphologyEx(image,image, MORPH_BLACKHAT, element);  
	//显示效果图   
	imshow("【效果图】黑帽运算", image);   

	waitKey(0);   

	return 0;   
} 

int MorphErode( )  
{  
	//载入原始图    
	Mat image = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	//创建窗口    
	namedWindow("【原始图】腐蚀");   
	namedWindow("【效果图】腐蚀");   
	//显示原始图   
	imshow("【原始图】腐蚀", image);   
	//定义核  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));   
	//进行形态学操作  
	morphologyEx(image,image, MORPH_ERODE, element);  
	//显示效果图   
	imshow("【效果图】腐蚀", image);   

	waitKey(0);   

	return 0;   
} 

int MorphDilate( )  
{  
	//载入原始图    
	Mat image = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图  
	//创建窗口    
	namedWindow("【原始图】膨胀");   
	namedWindow("【效果图】膨胀");   
	//显示原始图   
	imshow("【原始图】膨胀", image);   
	//定义核  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));   
	//进行形态学操作  
	morphologyEx(image,image, MORPH_DILATE, element);  
	//显示效果图   
	imshow("【效果图】膨胀", image);   

	waitKey(0);   

	return 0;   
} 