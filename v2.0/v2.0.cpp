
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
        //Mat dst_Gray;
        
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
        Rect rect(cx - 150, cy, 300, 200);
        Mat roi = src(rect);
        cvtColor(roi, roi, COLOR_BGR2GRAY);
        Canny(roi, roi, 250, 350);
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



