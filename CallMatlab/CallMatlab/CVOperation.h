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

Mat img;  
int threshval = 160;            //轨迹条滑块对应的值，给初值160  
//-----------------------------【on_trackbar( )函数】------------------------------------  
//  描述：轨迹条的回调函数  
//-----------------------------------------------------------------------------------------------  
static void on_trackbar(int, void*)  
{  
	Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);  

	//定义点和向量  
	vector<vector<cv::Point> > contours;  
	vector<Vec4i> hierarchy;  

	//查找轮廓  
	findContours( bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );  
	//初始化dst  
	Mat dst = Mat::zeros(img.size(), CV_8UC3);  
	//开始处理  
	if( !contours.empty() && !hierarchy.empty() )  
	{  
		//遍历所有顶层轮廓，随机生成颜色值绘制给各连接组成部分  
		int idx = 0;  
		for( ; idx >= 0; idx = hierarchy[idx][0] )  
		{  
			Scalar color( (rand()&255), (rand()&255), (rand()&255) );  
			//绘制填充轮廓  
			drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );  
		}  
	}  
	//显示窗口  
	imshow( "Connected Components", dst );  
}  

int TrackbarExample()  
{  
	system("color 5F");    
	//载入图片  
	img = imread("", 0);  
	if( !img.data ) { printf("Oh，no，读取img图片文件错误~！ \n"); return -1; }  

	//显示原图  
	namedWindow( "C:\\Users\\lwl\\Desktop\\lena.jpg", 1 );  
	imshow( "Image", img );  

	//创建处理窗口  
	namedWindow( "Connected Components", 1 );  
	//创建轨迹条  
	createTrackbar( "Threshold", "Connected Components", &threshval, 255, on_trackbar );  
	on_trackbar(threshval, 0);//轨迹条回调函数  

	waitKey(0);  
	return 0;  
} 

int g_nContrastValue; //对比度值  
int g_nBrightValue;  //亮度值  
Mat g_srcImage,g_dstImage;  
static void ContrastAndBright(int, void *)  
{  

	//创建窗口  
	namedWindow("【原始图窗口】", 1);  

	//三个for循环，执行运算 g_dstImage(i,j) =a*g_srcImage(i,j) + b  
	for(int y = 0; y < g_srcImage.rows; y++ )  
	{  
		for(int x = 0; x < g_srcImage.cols; x++ )  
		{  
			for(int c = 0; c < 3; c++ )  
			{  
				g_dstImage.at<Vec3b>(y,x)[c]= saturate_cast<uchar>( (g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y,x)[c] ) + g_nBrightValue );  
			}  
		}  
	}  

	//显示图像  
	imshow("【原始图窗口】", g_srcImage);  
	imshow("【效果图窗口】", g_dstImage);  
}  
int ContrastAndBrightExample(  )  
{  
	//改变控制台前景色和背景色  
	system("color5F");   

	//读入用户提供的图像  
	g_srcImage= imread( "pic1.jpg");  
	if(!g_srcImage.data ) { printf("Oh，no，读取g_srcImage图片错误~!\n"); return false; }  
	g_dstImage= Mat::zeros( g_srcImage.size(), g_srcImage.type() );  

	//设定对比度和亮度的初值  
	g_nContrastValue=80;  
	g_nBrightValue=80;  

	//创建窗口  
	namedWindow("【效果图窗口】", 1);  

	//创建轨迹条  
	createTrackbar("对比度：", "【效果图窗口】",&g_nContrastValue,300,ContrastAndBright );  
	createTrackbar("亮   度：","【效果图窗口】",&g_nBrightValue,200,ContrastAndBright );  

	//调用回调函数  
	ContrastAndBright(g_nContrastValue,0);  
	ContrastAndBright(g_nBrightValue,0);  

	//输出一些帮助信息  
	cout<<endl<<"\t嗯。好了，请调整滚动条观察图像效果~\n\n"  
		<<"\t按下“q”键时，程序退出~!\n"  
		<<"\n\n\t\t\t\tby浅墨";  

	//按下“q”键时，程序退出  
	while(char(waitKey(1)) != 'q') {}  
	return 0;  
}  