#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui_c.h>
#include <windows.h>
#include"key.cpp"

using namespace cv;
using namespace std;

void Srceen();
bool HBitmapToMat(HBITMAP& _hBmp, Mat& _mat);
HBITMAP hBmp;
HBITMAP hOld;


int main()
{
    Sleep(2000);
    while (true)
    {
        Mat src;
        vector<Vec4i> plines;

        //屏幕截图
        Srceen();
        //类型转换
        HBitmapToMat(hBmp, src);

        //调整大小
        //resize(src, dst, cvSize(400, 250), 0, 0);

        int h = src.rows;
        int w = src.cols;
        // 获取ROI
        int cy = h / 2;
        int cx = w / 2;
        Rect rect(cx - 150, cy, 300, 200);  //这些参数都可以根据自己的情况来改变
        Mat roi = src(rect);
        //roi = Mat::zeros(roi.size(), roi.type());
        cvtColor(roi, roi, COLOR_BGR2GRAY);
        /*
        void Canny(	InputArray image, 
			OutputArray edges,
			double threshold1,          下限阈值，当图像像素梯度低于下限阈值就不会被认为边缘
			double threshold2,          上限阈值，当图像像素梯度高于上限阈值就不会被认为边缘（低阈值为0.4*高阈值）
			int apertureSize = 3,       为Sobel()运算提供内核大小，默认值为3
			bool L2gradient = false);   计算图像梯度幅值的标志，默认值为false

        */
        Canny(roi, roi, 108, 270);
        /*
        void GaussianBlur( InputArray src, 
                           OutputArray dst, 
                           Size ksize,                       高斯内核大小
                           double sigmaX,                    高斯核函数在X方向上的标准偏差
                           double sigmaY = 0,                高斯核函数在Y方向上的标准偏差
                           int borderType = BORDER_DEFAULT );推断图像外部像素的某种便捷模式

        */
        GaussianBlur(roi, roi, Size(5, 5), 0, 0);
        /*
        cv::HoughLinesP(
                        InputArray src,         输入图像（8位灰度图像）
                        OutputArray lines,      输出直线两点坐标（vector<Vec4i>）
                        double rho,             生成极坐标时候的像素扫描步长
                        double theta,           生成极坐标时候的角度步长（一般取CV_PI/180）
                        int threshold,          累加器阈值，获得足够交点的极坐标点才被看成是直线
                        double minLineLength=0; 直线最小长度
                        double maxLineGap=0;    直线最大间隔
        )
        */
        
        HoughLinesP(roi, plines, 1.0, CV_PI / 180, 400, 150, 300);//roi, plines, 1.0, CV_PI / 180, 400, 150, 300
        for (size_t i = 0; i < plines.size(); i++)
        {
            Vec4i points = plines[i];
            line(roi, Point(points[0], points[1]), Point(points[2], points[3]), Scalar(0, 255, 255), 3, CV_AA);
        }
        
        imshow("roi", roi);


        DeleteObject(hBmp);
        waitKey(100);       //帧数200ms=5帧

        //class Key_Down_Up a;
        //a.W();
    }
}

//抓取窗口
void Srceen() {
    //创建画板
    HDC hSrceen = CreateDC(L"DISPLAY", NULL, NULL, NULL);
    HDC hCompDC = CreateCompatibleDC(hSrceen);
    //截取屏幕尺寸
    int w = 800;
    int h = 500;
    //创建Bitmap对象：Bit-map就是用一个bit位来标记某个元素对应的Value， 而Key即是该元素
    hBmp = CreateCompatibleBitmap(hSrceen, w, h);
    hOld = (HBITMAP)SelectObject(hCompDC, hBmp);
    //将一幅位图从一个设备场景复制到另一个
    //BitBlt(hCompDC, 0, 0, 录制画面宽度, 录制画面高度, hSrceen, 录制起点横坐标, 录制起点纵坐标, SRCCOPY);
    BitBlt(hCompDC, 0, 0, w, h, hSrceen, 5, 60, SRCCOPY);

    SelectObject(hCompDC, hOld);

    //释放对象
    DeleteDC(hSrceen);
    DeleteDC(hCompDC);
}

//把HBIEMAP转换成Mat型
bool HBitmapToMat(HBITMAP& _hBmp, Mat& _mat) {
    //BITMAP操作
    BITMAP bmp;
    GetObject(_hBmp, sizeof(BITMAP), &bmp);
    int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
    int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
    //Mat操作
    Mat v_mat;
    v_mat.create(cvSize(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8U, nChannels));
    GetBitmapBits(_hBmp, bmp.bmHeight * bmp.bmWidth * nChannels, v_mat.data);
    _mat = v_mat;
    return TRUE;
}
