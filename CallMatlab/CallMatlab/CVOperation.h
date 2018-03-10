#include <vector>  
#include <stdio.h>  
#include<opencv2/opencv.hpp>  
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