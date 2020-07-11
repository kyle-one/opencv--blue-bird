#pragma once
#include<opencv2/opencv.hpp>
#include<windows.h>
#include <stdlib.h>
#include <iostream>
#include "source.h"
#include "hinder.h"
using namespace cv;

class User
{
private:
	int weight;
	int high;
	String src;
public:
	int getWeight() { return weight; }
	int getHigh() { return high; }
	String getSrc() { return src; };

	void setWeight(int w) { this->weight = w; }
	void setHIgh(int h) { this->high = h; }
	void setSrc(String s) { this->src = s; }

	User(int w, int h, String s)
	{
		weight = w;
		high = h;
		src = s;
	}

	void dead(Mat frame, Point2f center)
	{
		Source src;
		Rect roi(230, 170, 300, 150);
		Mat frame_roi = frame(roi);
		Mat pic = imread(src.gameover);

		cv::resize(pic, pic, Size(300, 150));
		cv::addWeighted(frame_roi, 0, pic, 1, 1, frame_roi);
	}

	void show(Mat frame, Point2f center)
	{
		//User u1 = User(50, 50, "C:/Users/lenovo/Desktop/23.png");
		//防止图片过界限
		//pic2 = pic2(Range::all(), Range(0, 30)); 当达到边界的时候需要裁剪
		//重新定义图片尺寸，防止越界
		int high_t = getHigh();
		int weight_t = getWeight();
		if (center.x + this->getWeight() >= frame.size().width)
			weight_t = frame.size().width - center.x;
		if (center.y + this->getHigh() >= frame.size().height)
			high_t = frame.size().height - center.y;

		//灰度图
		Mat grayPng = imread(src, 0);
		threshold(grayPng, grayPng, 180, 255, CV_THRESH_BINARY);
		//掩模反色
		Mat mask = 255 - grayPng;
		resize(mask, mask, Size(weight, high));
		mask = mask(Range(0, high_t), Range(0, weight_t));


		Mat png = imread(src);
		//调整为固定大小
		resize(png, png, Size(weight, high));
		//如果超出边界，则裁剪掉超出部分
		png = png(Range(0, high_t), Range(0, weight_t));

		Mat imROI;
		imROI = frame(Rect(center.x, center.y, png.cols, png.rows));
		png.copyTo(imROI, mask);


		/*
		Rect roi(center.x, center.y, weight_t, high_t);
		Mat frame_roi = frame(roi);
		Mat pic = imread(this->getSrc());

		cv::resize(pic, pic, Size(weight_t, high_t));
		cv::addWeighted(frame_roi, 0, pic, 1, 1, frame_roi);)*/
	}

};
