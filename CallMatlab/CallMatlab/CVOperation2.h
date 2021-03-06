﻿#include <vector>  
#include <stdio.h>  
#include<opencv2/opencv.hpp>  
#include<opencv2/core/core.hpp>  
using namespace std;
using namespace cv;

cv::Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3;//存储图片的Mat类型  
int g_nBoxFilterValue=3;  //方框滤波参数值  
int g_nMeanBlurValue=3;  //均值滤波参数值  
int g_nGaussianBlurValue=3;  //高斯滤波参数值  


//-----------------------------------【全局函数声明部分】--------------------------------------  
//     描述：全局函数声明  
//-----------------------------------------------------------------------------------------------  
//轨迹条的回调函数  
static void on_BoxFilter(int, void *);            //方框滤波  
static void on_MeanBlur(int, void *);           //均值滤波  
static void on_GaussianBlur(int, void *);                    //高斯滤波  



//-----------------------------------【main( )函数】--------------------------------------------  
//     描述：控制台应用程序的入口函数，我们的程序从这里开始  
//-----------------------------------------------------------------------------------------------  
int OpenCV8_Filter(  )  
{  
	//改变console字体颜色  
	system("color5E");   

	//载入原图  
	g_srcImage= imread( "1.jpg", 1 );  
	if(!g_srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }  

	//克隆原图到三个Mat类型中  
	g_dstImage1= g_srcImage.clone( );  
	g_dstImage2= g_srcImage.clone( );  
	g_dstImage3= g_srcImage.clone( );  

	//显示原图  
	namedWindow("【<0>原图窗口】", 1);  
	imshow("【<0>原图窗口】",g_srcImage);  


	//=================【<1>方框滤波】==================  
	//创建窗口  
	namedWindow("【<1>方框滤波】", 1);  
	//创建轨迹条  
	createTrackbar("内核值：", "【<1>方框滤波】",&g_nBoxFilterValue, 40,on_BoxFilter );  
	on_MeanBlur(g_nBoxFilterValue,0);  
	imshow("【<1>方框滤波】", g_dstImage1);  
	//================================================  

	//=================【<2>均值滤波】==================  
	//创建窗口  
	namedWindow("【<2>均值滤波】", 1);  
	//创建轨迹条  
	createTrackbar("内核值：", "【<2>均值滤波】",&g_nMeanBlurValue, 40,on_MeanBlur );  
	on_MeanBlur(g_nMeanBlurValue,0);  
	//================================================  

	//=================【<3>高斯滤波】=====================  
	//创建窗口  
	namedWindow("【<3>高斯滤波】", 1);  
	//创建轨迹条  
	createTrackbar("内核值：", "【<3>高斯滤波】",&g_nGaussianBlurValue, 40,on_GaussianBlur );  
	on_GaussianBlur(g_nGaussianBlurValue,0);  
	//================================================  


	//输出一些帮助信息  
	cout<<endl<<"\t嗯。好了，请调整滚动条观察图像效果~\n\n"  
		<<"\t按下“q”键时，程序退出~!\n"  
		<<"\n\n\t\t\t\tby浅墨";  

	//按下“q”键时，程序退出  
	while(char(waitKey(1))!= 'q') {}  

	return 0;  
}  


//-----------------------------【on_BoxFilter( )函数】------------------------------------  
//     描述：方框滤波操作的回调函数  
//-----------------------------------------------------------------------------------------------  
static void on_BoxFilter(int, void *)  
{  
	//方框滤波操作  
	boxFilter(g_srcImage, g_dstImage1, -1,cv::Size( g_nBoxFilterValue+1, g_nBoxFilterValue+1));  
	//显示窗口  
	imshow("【<1>方框滤波】", g_dstImage1);  
}  


//-----------------------------【on_MeanBlur( )函数】------------------------------------  
//     描述：均值滤波操作的回调函数  
//-----------------------------------------------------------------------------------------------  
static void on_MeanBlur(int, void *)  
{  
	//均值滤波操作  
	blur(g_srcImage, g_dstImage2, cv::Size( g_nMeanBlurValue+1, g_nMeanBlurValue+1),Point(-1,-1));  
	//显示窗口  
	imshow("【<2>均值滤波】", g_dstImage2);  
}  


//-----------------------------【on_GaussianBlur( )函数】------------------------------------  
//     描述：高斯滤波操作的回调函数  
//-----------------------------------------------------------------------------------------------  
static void on_GaussianBlur(int, void *)  
{  
	//高斯滤波操作  
	GaussianBlur(g_srcImage, g_dstImage3, cv::Size( g_nGaussianBlurValue*2+1,g_nGaussianBlurValue*2+1 ), 0, 0);  
	//显示窗口  
	imshow("【<3>高斯滤波】", g_dstImage3);  
} 

void MedianBlur( )  
{  
	//载入原图  
	Mat image=imread("1.jpg");  

	//创建窗口  
	namedWindow("中值滤波【原图】" );  
	namedWindow("中值滤波【效果图】");  

	//显示原图  
	imshow("中值滤波【原图】", image );  

	//进行中值滤波操作  
	Mat out;  
	medianBlur( image, out, 7);  
	//显示效果图  
	imshow("中值滤波【效果图】" ,out );  
	waitKey(0 );      
} 

void BilateralFilter( )  
{  
	//载入原图  
	Mat image=imread("1.jpg");  

	//创建窗口  
	namedWindow("双边滤波【原图】" );  
	namedWindow("双边滤波【效果图】");  

	//显示原图  
	imshow("双边滤波【原图】", image );  

	//进行双边滤波操作  
	Mat out;  
	bilateralFilter( image, out, 25, 25*2, 25/2 );  

	//显示效果图  
	imshow("双边滤波【效果图】" ,out );  

	waitKey(0 );      
} 

int Erode()  
{  
	//载入原图   
	Matimage = imread("1.jpg");  

	//创建窗口   
	namedWindow("【原图】腐蚀操作");  
	namedWindow("【效果图】腐蚀操作");  

	//显示原图  
	imshow("【原图】腐蚀操作", image);  


	//获取自定义核  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  
	Mat out;  

	//进行腐蚀操作  
	erode(image,out, element);  

	//显示效果图  
	imshow("【效果图】腐蚀操作", out);  

	waitKey(0);  

	return 0;  
}  