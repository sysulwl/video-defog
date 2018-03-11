#include <vector>  
#include <stdio.h>  
#include<opencv2/opencv.hpp>  
#include<opencv2/core/core.hpp>  
using namespace std;
using namespace cv;

void createAlphaMat(cv::Mat &mat)  
{  
	for(int i = 0; i < mat.rows; ++i) 
	{  
		for(int j = 0; j < mat.cols; ++j) 
		{  
			cv::Vec4b& rgba = mat.at<Vec4b>(i, j);  
			rgba[0]= UCHAR_MAX;
			//斜对角的渐变效果
			rgba[1]= saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) *UCHAR_MAX);  
			rgba[2]= saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) *UCHAR_MAX);  
			rgba[3]= saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));  
		}  
	}  
}  

int CreatePNG()  
{  
	//创建带alpha通道的Mat  
	cv::Mat mat(480, 640, CV_8UC4);  
	createAlphaMat(mat);  

	std::vector<int> compression_params;  
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);  
	compression_params.push_back(9);  

	try{  
		imwrite("C:\\Users\\lwl\\Desktop\\透明Alpha值图.png", mat, compression_params);  
	}  
	catch(runtime_error& ex) {  
		string str = ex.what();
		return 1;  
	}   
	return 0;  
}  

int UseExample( )  
{  
	Mat image= imread("C:\\Users\\lwl\\Desktop\\dota.jpg");  
	Mat logo= imread("C:\\Users\\lwl\\Desktop\\dota_logo.jpg");  

	//载入后先显示  
	namedWindow("【2】原画图");  
	imshow("【2】原画图",image);  
	cv::waitKey(6000);
	namedWindow("【3】logo图");  
	imshow("【3】logo图",logo);  
	cv::waitKey(6000);
	//定义一个Mat类型，用于存放，图像的ROI  
	cv::Mat imageROI;
	//方法一  
	imageROI=image(cv::Rect(100,100,logo.cols,logo.rows));  
	//将logo加到原图上  
	addWeighted(imageROI,0.5,logo,0.3,0.0,imageROI);

	//方法二  
	//imageROI=image(Range(350,350+logo.rows),Range(800,800+logo.cols));  
	//显示结果  
	namedWindow("【4】原画+logo图");  
	imshow("【4】原画+logo图",image);  

	//-----------------------------------【三、图像的输出】--------------------------------------  
	//     描述：将一个Mat图像输出到图像文件  
	//-----------------------------------------------------------------------------------------------  
	//输出一张jpg图片到工程目录下  
	imwrite("C:\\Users\\lwl\\Desktop\\混合.jpg",image);  
	waitKey();  
	return 0;  
}  

bool MultiChannelBlending()  
{  
	//【0】定义相关变量  
	Mat srcImage;  
	Mat logoImage;  
	vector<Mat>channels;  
	Mat  imageBlueChannel;  

	//=================【蓝色通道部分】=================  
	//     描述：多通道混合-蓝色分量部分  
	//============================================  

	//【1】读入图片  
	logoImage=imread("dota_logo.jpg",0);  
	srcImage=imread("dota_jugg.jpg");  

	if(!logoImage.data ) { printf("Oh，no，读取logoImage错误~！\n"); return false; }  
	if(!srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }  

	//【2】把一个3通道图像转换成3个单通道图像  
	split(srcImage,channels);//分离色彩通道  

	//【3】将原图的蓝色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变  
	imageBlueChannel=channels.at(0);  
	//【4】将原图的蓝色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageBlueChannel中  
	addWeighted(imageBlueChannel(cv::Rect(500,250,logoImage.cols,logoImage.rows)),1.0,  
		logoImage,0.5,0,imageBlueChannel(cv::Rect(500,250,logoImage.cols,logoImage.rows)));  

	//【5】将三个单通道重新合并成一个三通道  
	merge(channels,srcImage);  

	//【6】显示效果图  
	namedWindow("<1>游戏原画+logo蓝色通道 by浅墨");  
	imshow("<1>游戏原画+logo蓝色通道 by浅墨",srcImage);  


	//=================【绿色通道部分】=================  
	//     描述：多通道混合-绿色分量部分  
	//============================================  

	//【0】定义相关变量  
	Mat  imageGreenChannel;  

	//【1】重新读入图片  
	logoImage=imread("dota_logo.jpg",0);  
	srcImage=imread("dota_jugg.jpg");  

	if(!logoImage.data ) { printf("Oh，no，读取logoImage错误~！\n"); return false; }  
	if(!srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }  

	//【2】将一个三通道图像转换成三个单通道图像  
	split(srcImage,channels);//分离色彩通道  

	//【3】将原图的绿色通道的引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变  
	imageGreenChannel=channels.at(1);  
	//【4】将原图的绿色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageGreenChannel中  
	addWeighted(imageGreenChannel(cv::Rect(500,250,logoImage.cols,logoImage.rows)),1.0,  
		logoImage,0.5,0.,imageGreenChannel(cv::Rect(500,250,logoImage.cols,logoImage.rows)));  

	//【5】将三个独立的单通道重新合并成一个三通道  
	merge(channels,srcImage);  

	//【6】显示效果图  
	namedWindow("<2>游戏原画+logo绿色通道 by浅墨");  
	imshow("<2>游戏原画+logo绿色通道 by浅墨",srcImage);  



	//=================【红色通道部分】=================  
	//     描述：多通道混合-红色分量部分  
	//============================================  

	//【0】定义相关变量  
	Mat  imageRedChannel;  

	//【1】重新读入图片  
	logoImage=imread("dota_logo.jpg",0);  
	srcImage=imread("dota_jugg.jpg");  

	if(!logoImage.data ) { printf("Oh，no，读取logoImage错误~！\n"); return false; }  
	if(!srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }  

	//【2】将一个三通道图像转换成三个单通道图像  
	split(srcImage,channels);//分离色彩通道  

	//【3】将原图的红色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变  
	imageRedChannel=channels.at(2);  
	//【4】将原图的红色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageRedChannel中  
	addWeighted(imageRedChannel(cv::Rect(500,250,logoImage.cols,logoImage.rows)),1.0,  
		logoImage,0.5,0.,imageRedChannel(cv::Rect(500,250,logoImage.cols,logoImage.rows)));  

	//【5】将三个独立的单通道重新合并成一个三通道  
	merge(channels,srcImage);  

	//【6】显示效果图  
	namedWindow("<3>游戏原画+logo红色通道 by浅墨");  
	imshow("<3>游戏原画+logo红色通道 by浅墨",srcImage);  

	return true;  
}  