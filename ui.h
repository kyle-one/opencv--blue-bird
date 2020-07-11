#pragma once
#include "source.h"
#include<opencv2/opencv.hpp>
#include<windows.h>
#include <stdlib.h>
#include <iostream>
using namespace cv;
using namespace std;

class Ui {
private:
	int flag = 1;

public:
	void picture(Mat frame, Point2f center) {
		//显示一张图片，半透明，图片分成四个区域。
		Rect roi(0, 0, 640, 480);
		Mat frame_roi = frame(roi);
		Source s;
		Mat pic = imread(s.uiImage);

		cv::resize(pic, pic, Size(640, 480));
		pic = pic(Range(0, 480), Range(0, 640));
		cv::addWeighted(frame_roi, 0.5, pic, 0.5, 1, frame_roi);  //调整透明度
	}

	int choice(int location_x, int location_y) {
		if (location_x < 320 && location_y < 240) {
			static int a1 = 1;
			static int b1 = 1;
			static long t1 = 0;
			if (b1 > 0) {
				time_t start;
				t1 = time(&start);
				b1--;
			}//刷新时间
			time_t end;
			time(&end);
			if (end - t1 == 3 && a1 > 0) {
				printf("左上角\n");
				a1--;
				flag = 1;
			}
		}
		else if (location_x > 320 && location_y < 240) {
			static int a2 = 1;
			static int b2 = 1;
			static long t2 = 0;
			if (b2 > 0) {
				time_t start;
				t2 = time(&start);
				b2--;
			}
			time_t end;
			time(&end);
			if (end - t2 == 3 && a2 > 0) {
				printf("右上角\n");
				a2--;
				flag = 2;
			}
		}
		else if (location_x < 320 && location_y>240) {
			static int a3 = 1;
			static int b3 = 1;
			static long t3 = 0;
			if (b3 > 0) {
				time_t start;
				t3 = time(&start);
				b3--;
			}
			time_t end;
			time(&end);
			if (end - t3 == 3 && a3 > 0) {
				printf("左下角\n");
				a3--;
				flag = 4;
			}
		}
		else if (location_x > 320 && location_y > 240) {
			static int a4 = 1;
			static int b4 = 1;
			static long t4 = 0;
			if (b4 > 0) {
				time_t start;
				t4 = time(&start);
				b4--;
			}//刷新时间
			time_t end;
			time(&end);
			if (end - t4 == 3 && a4 > 0) {
				printf("右下角\n");
				a4--;
				flag = 3;
			}
		}
		return flag;
	}
	void countdown(Mat frame) {     //游戏开始倒计时
		static int time_m = 1;
		static long ti1 = 0;  //获取时间
		Source s2;
		Mat pic = imread(s2.num3);
		Mat pic2 = imread(s2.num2);
		Mat pic3 = imread(s2.num1);
		if (time_m > 0) {
			time_t start1 = 0;
			ti1 = time(&start1);
			time_m--;
		}
		time_t end1;
		time(&end1);
		if (end1 - ti1 >= 1 && end1 - ti1 <= 2) {
			Rect roi(250, 170, 150, 150);
			Mat frame_roi = frame(roi);
			cv::resize(pic, pic, Size(150, 150));
			pic = pic(Range(0, 150), Range(0, 150));
			Mat grayPng = imread(s2.num3, 0);
			threshold(grayPng, grayPng, 180, 255, CV_THRESH_BINARY);
			Mat mask = 255 - grayPng;
			resize(mask, mask, Size(150, 150));
			mask = mask(Range(0, 150), Range(0, 150));
			resize(pic, pic, Size(150, 150));
			pic = pic(Range(0, 150), Range(0, 150));

			Mat imROI;
			imROI = frame(roi);
			pic.copyTo(imROI, mask);
		}
		if (end1 - ti1 > 2 && end1 - ti1 <= 3) {
			Rect roi(250, 170, 150, 150);
			Mat frame_roi = frame(roi);
			cv::resize(pic2, pic2, Size(150, 150));
			pic2 = pic2(Range(0, 150), Range(0, 150));
			Mat grayPng = imread(s2.num2, 0);
			threshold(grayPng, grayPng, 180, 255, CV_THRESH_BINARY);
			Mat mask = 255 - grayPng;
			resize(mask, mask, Size(150, 150));
			mask = mask(Range(0, 150), Range(0, 150));
			resize(pic2, pic2, Size(150, 150));
			pic2 = pic2(Range(0, 150), Range(0, 150));

			Mat imROI;
			imROI = frame(roi);
			pic2.copyTo(imROI, mask);
		}
		if (end1 - ti1 > 3 && end1 - ti1 <= 4) {
			Rect roi(250, 170, 150, 150);
			Mat frame_roi = frame(roi);
			cv::resize(pic3, pic3, Size(150, 150));
			pic3 = pic3(Range(0, 150), Range(0, 150));
			Mat grayPng = imread(s2.num1, 0);
			threshold(grayPng, grayPng, 180, 255, CV_THRESH_BINARY);
			Mat mask = 255 - grayPng;
			resize(mask, mask, Size(150, 150));
			mask = mask(Range(0, 150), Range(0, 150));
			resize(pic3, pic3, Size(150, 150));
			pic3 = pic3(Range(0, 150), Range(0, 150));

			Mat imROI;
			imROI = frame(roi);
			pic3.copyTo(imROI, mask);
		}
	}
	void gameui(Mat frame) {
		Rect roi(0, 0, 640, 480);
		Mat frame_roi = frame(roi);
		Source s3;
		Mat pic = imread(s3.background);

		cv::resize(pic, pic, Size(640, 480));
		pic = pic(Range(0, 480), Range(0, 640));
		cv::addWeighted(frame_roi, 0.3, pic, 0.7, 1, frame_roi);  //调整透明度
	}
	void gamecount(Mat frame) {     //时间计时器
		int  timing;
		String text;
		static long startlock;
		static int timelock = 1;
		if (timelock > 0) {
			time_t start;
			startlock = time(&start);
			timelock--;
		}
		time_t end;
		time(&end);
		timing = end - startlock;
		text = "gametime:" + to_string(timing);
		putText(frame, text, Point(230, 40), CV_FONT_HERSHEY_TRIPLEX, 1.0, Scalar(0, 255, 0), 1, CV_AA);

	}
};