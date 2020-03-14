// v1.0.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//#include<stdafx.h>
#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui_c.h>
#include <windows.h>

using namespace cv;
using namespace std;

void Srceen();
bool HBitmapToMat(HBITMAP& _hBmp, Mat& _mat);
HBITMAP hBmp;
HBITMAP hOld;

int main()
{
    while (true)
    {
        Mat src;
        Mat dst;
        //屏幕截图
        Srceen();
        //类型转换
        HBitmapToMat(hBmp, src);
        //调整大小
        resize(src, dst, cvSize(500, 500), 0, 0);

        imshow("dst", dst);
        DeleteObject(hBmp);
        waitKey(200);       //帧数200ms=5帧
    }
}

//抓取窗口
void Srceen() {
    //创建画板
    HDC hSrceen = CreateDC(L"DISPLAY", NULL, NULL, NULL);
    HDC hCompDC = CreateCompatibleDC(hSrceen);
    //截取屏幕尺寸
    int w = 500;
    int h = 500;
    //创建Bitmap对象：Bit-map就是用一个bit位来标记某个元素对应的Value， 而Key即是该元素
    hBmp = CreateCompatibleBitmap(hSrceen, w, h);
    hOld = (HBITMAP)SelectObject(hCompDC, hBmp);
    //将一幅位图从一个设备场景复制到另一个
    BitBlt(hCompDC, 0, 0, w, h, hSrceen, 0,0, SRCCOPY);
    SelectObject(hCompDC, hOld);

    //释放对象
    DeleteDC(hSrceen);
    DeleteDC(hCompDC);
}

//把HBIEMAP转换成Mat型
bool HBitmapToMat(HBITMAP& _hBmp, Mat&_mat) {
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
