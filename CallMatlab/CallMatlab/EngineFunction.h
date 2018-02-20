#include "engine.h"
void ShowEngine()
{
	Engine *ep;  
    // open engine  
    if ((ep = engOpen("\0")) == NULL)  
    {  
        return;  
    }  
  
    // generate variables  
    int Nsample = 50;  
    const double PI = 3.1415926;  
    double *t = new double[Nsample] ;  
  
    for(int i = 0; i < Nsample; i++)  
    {  
        t[i] = i * 2 * PI / Nsample;  
    }  
  
    mxArray *T = NULL;  
    T = mxCreateDoubleMatrix(1, Nsample, mxREAL);  //1. 行数, 2. 列数  3.实数
    memcpy((void *)mxGetPr(T), (void *)t, Nsample*sizeof(t[0])); //copy内容 
  
    engPutVariable(ep, "T", T);         // put data to engine  
  
    // execute matlab operations  
    engEvalString(ep, "Y=sin(T);");  
    engEvalString(ep, "plot(T,Y);");  
    engEvalString(ep, "title('y=sin(t)');");  
    engEvalString(ep, "xlabel('t');");  
    engEvalString(ep, "ylabel('y');");  
  
    // clean operation(don't forget!!!)  
    mxDestroyArray(T); 
	T = NULL;
    //engEvalString(ep, "close;");  

	delete t;
	t = NULL;
    // close engine  
    engClose(ep);  
	ep = NULL;
}