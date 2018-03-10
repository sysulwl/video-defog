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
		//fprintf(stderr,"图像转换成PNG格式发生错误：%s\n", ex.what());  
		return 1;  
	}  
	//fprintf(stdout,"PNG图片文件的alpha数据保存完毕~\n");  
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
	imageROI=image(cv::Rect(201,200,logo.cols,logo.rows));  
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