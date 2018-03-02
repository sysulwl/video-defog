#include <iostream>  
#include <fstream>  
#include <string>  
#include <windows.h>  
#include <gdiplus.h>  
#pragma comment(lib, "gdiplus.lib")  
  
using namespace std;  
using namespace Gdiplus;  
  
void ReadPhoto(const wstring& infilename, const string& outfilename)
{  
    GdiplusStartupInput gdiplusstartupinput;  
    ULONG_PTR gdiplustoken;  
    GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);  
    //wstring infilename(L"1.jpg");  
    //string outfilename("color.txt");  
	ofstream fout(outfilename.c_str());
    Bitmap* bmp = new Bitmap(infilename.c_str());  
    UINT height = bmp->GetHeight();  
    UINT width  = bmp->GetWidth();  
    fout << "width " << width << ", height " << height << endl;  
    Color color;  
	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width ; x++)  
		{  
			bmp->GetPixel(x, y, &color);  
			fout << x << "," << y << ";"  
				<< (int)color.GetRed()   << ","  
				<< (int)color.GetGreen() << ","  
				<< (int)color.GetBlue()  << endl;  
		}  
	}
    fout.close();  
    delete bmp;  
    GdiplusShutdown(gdiplustoken);    
}  

int EncodeTransform_MToW(const char* str, wchar_t* pBuf, int nBufLen, unsigned int nCodePage)
{
	//If_OMWarn_Return(str == NullPtr || pBuf == NullPtr || nBufLen <= 0, -1);

	pBuf[0] = 0;

	int nCalcLen = ::MultiByteToWideChar(nCodePage, 0, str, -1, NULL, 0);
	//If_OMWarn_Return(nCalcLen <= 0 || nCalcLen > nBufLen, -1);

	return ::MultiByteToWideChar(nCodePage, 0, str, -1, pBuf, nBufLen);
}

int AnsiToUnicode(const char* str, wchar_t* pBuf, int nBufLen)
{
	return EncodeTransform_MToW(str, pBuf, nBufLen, CP_ACP);
}