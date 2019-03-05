#include<opencv.hpp>

using namespace cv;
int main()
{
	Mat src = imread("C:/Users/SZJ/Desktop/1.jpg", 0);
	imshow("src", src);
	//�������
	MatND dstHist;
	int dims = 1;
	float hranges[] = { 0,255 };
	const float *ranges[] = { hranges };
	int size = 256;
	int channels = 0;
	//����ͼ���ֱ��ͼ
	calcHist(&src,1, &channels, Mat(), dstHist, dims, &size, ranges);

	int scale = 1;
	Mat dstImage(size*scale, size, CV_8UC1, Scalar(0));  //����ֱ��ͼͼ��
	
	//��ȡ���ֵ����Сֵ
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

	//����ֱ��ͼ
	int hpt = saturate_cast<int>(0.9*size);
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue*hpt / maxValue);
		rectangle(dstImage, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue), Scalar(255));
	}
	imshow("һάֱ��ͼ", dstImage);
	waitKey(0);
	return 0;
}


/*-------------------------copyto����ʾ��---------------------------------

// csdn_code.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;



//#define IMG_PATH  "..//figures//12.jpg"

#define IMG_PATH  "..//figures//lotus.jpg"

#define CAT_PATH  "..//figures//cat.jpg"

void testroi(void) {
	Mat img = imread(IMG_PATH);
	Mat cat = imread(CAT_PATH);
	if (img.empty() || cat.empty())
		cerr << "can not read image." << endl;

	// ָ������Ȥ�������ַ���
	Mat ROI = img(Rect(40, 40, cat.cols, cat.rows));
	Mat ROI2(img, Rect(40, 40, cat.cols, cat.rows));

	// չʾ roi ����
	imshow("roi", ROI);

	cout << endl
		<< "��è�ŵ�����Ȥ�������ַ���" << endl;
	//cat.copyTo(ROI);
	cat.copyTo(ROI, cat);
	imshow("lotus with cat", img);


	// ��ͼ���л��� ����
	rectangle(img, Rect(240, 240, cat.cols, cat.rows), Scalar(0, 0, 255));
	imshow("with rectangle box", img);

	//  ��һ�ַ���
	cout << endl
		<< "���� Rect ���淽��Ȼ��ʹ��" << endl;
	Rect r1 = Rect(100, 0, 200, 200);
	rectangle(img, r1, Scalar(255, 0, 0));
	imshow("with rectangle box 2", img);

}


void contour_roi(void) {
	Mat img = imread(IMG_PATH);
	Mat dst;
	Mat roi = Mat::zeros(img.size(), CV_8U);

	// ���� �߽�����roi����
	vector<vector<Point>> contour;
	vector<Point> pts;
	pts.push_back(Point(30, 45));
	pts.push_back(Point(100, 15));
	pts.push_back(Point(300, 145));
	pts.push_back(Point(330, 240));
	pts.push_back(Point(50, 250));
	contour.push_back(pts);

	// ����
	drawContours(roi, contour, 0, Scalar::all(255), -1);
	img.copyTo(dst, roi);

	imshow("roi", roi);
	imshow("img", img);
	imshow("dst", dst);

}

void circle_roi(void) {
	Mat image = imread(IMG_PATH);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat mask = Mat::zeros(image.size(), CV_8U);

	Point circleCenter(mask.cols / 2, mask.rows / 2);
	int radius = min(mask.cols, mask.rows) / 2;

	// ��Բ
	//circle(mask, circleCenter, radius, Scalar(255),-1);
	// ����Բ
	ellipse(mask, circleCenter, Size(240, 146), 10, -180, 180, Scalar(255), -1);

	image.copyTo(dst, mask);

	imshow("mask", mask);
	imshow("image", image);
	imshow("dst", dst);
}

int main()
{
	testroi();

	contour_roi();

	circle_roi();


	waitKey();
	system("pause");
	return 0;
}
*/