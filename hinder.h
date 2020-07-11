#pragma once
#include<opencv2/opencv.hpp>
#include<windows.h>
#include <stdlib.h>
#include <iostream>
#include "source.h"
#include "user.h"
using namespace cv;

class Hinder
{
private:
	int weight;
	int high;
	String src;
	int speed;
	int direction;//1,2,3,4代表上下左右
	int location_x;
	int location_y;
	int T; //计时器
	int flag;//结束标志


public:
	int getT() { return T; }
	int getflag() { return flag; }
	int getWeight() { return weight; }
	int getHigh() { return high; }
	String getSrc() { return src; };
	int getSpeed() { return speed; }
	int getDirection() { return direction; }
	int getLocation_y() { return location_y; }
	int getLocation_x() { return location_x; }

	void setT(int n) { T = n; }
	void  setFlag(int n) { flag = n; }
	void setWeight(int w) { weight = w; }
	void setHigh(int h) { high = h; };
	void setSrc(String s) { src = s; };
	void setLocation_x(int n) { location_x = n; }
	void setLocation_y(int n) { location_y = n; }
	void setSpeed(int n) { speed = n; }

	Hinder(int w, int h, String s, int v, int d, int x, int y)
	{
		weight = w;
		high = h;
		src = s;
		speed = v;
		direction = d;
		location_x = x;
		location_y = y;
		T = 0;
		flag = 0;
	}
	void upshow(Mat frame, Point2f center)
	{

		int high_t = this->getHigh();
		int weight_t = this->getWeight();
		if (this->location_x + this->getWeight() >= frame.size().width)
			weight_t = frame.size().width - location_x;
		if (this->location_y + this->getHigh() >= frame.size().height)
			high_t = frame.size().height - location_y;
		if (high_t == 0 || weight_t == 0)
			return;
		//User u1 = User(50, 50, "C:/Users/lenovo/Desktop/23.png");
		Rect roi(this->location_x, this->location_y, weight_t, high_t);
		Mat frame_roi = frame(roi);
		Mat pic = imread(this->src);

		cv::resize(pic, pic, Size(this->weight, this->high));
		pic = pic(Range(0, high_t), Range(0, weight_t));
		//pic2 = pic2(Range::all(), Range(0, 30)); 当达到边界的时候需要裁剪
		cv::addWeighted(frame_roi, 0, pic, 1, 1, frame_roi);
		this->setLocation_x(location_x + speed);

		if (this->getLocation_x() >= frame.size().width)
		{
			this->setLocation_x(0);
			int ran = rand() % (frame.size().height - 100);//预留60个像素给小鸟通过
			this->setHigh(ran);
		}
	}

	void downshow(Mat frame, Point2f center, Hinder *up)
	{
		int high_t = this->getHigh();
		int weight_t = this->getWeight();
		if (this->location_x + this->weight >= frame.size().width)
			weight_t = frame.size().width - location_x;
		if (this->location_y + this->high >= frame.size().height)
			high_t = frame.size().height - location_y;
		if (high_t == 0 || weight_t == 0)
			return;
		//User u1 = User(50, 50, "C:/Users/lenovo/Desktop/23.png");
		Rect roi(this->location_x, this->location_y, weight_t, high_t);
		Mat frame_roi = frame(roi);
		Mat pic = imread(this->src);

		cv::resize(pic, pic, Size(this->weight, this->high));

		pic = pic(Range(0, high_t), Range(0, weight_t));
		//pic2 = pic2(Range::all(), Range(0, 30)); 当达到边界的时候需要裁剪
		cv::addWeighted(frame_roi, 0, pic, 1, 1, frame_roi);
		this->setLocation_x(location_x + speed);
		if (this->getLocation_x() >= frame.size().width)
		{
			this->setLocation_x(0);
			this->setHigh(frame.size().height - up->getHigh() - 100);
			this->setLocation_y(frame.size().height - this->getHigh());
		}
	}
	void hindershow(Mat frame, Point2f center, User u1, Hinder *h2, Hinder *h3, Hinder *h4)
	{

		Hinder h1(this->getWeight(), this->getHigh(), this->getSrc(), this->getSpeed(), this->getDirection(), this->getLocation_x(), this->getLocation_y());
		h1.upshow(frame, center);
		this->setLocation_x(h1.getLocation_x());
		this->setHigh(h1.getHigh());
		h2->downshow(frame, center, &h1);
		if (this->speed==0 || (this->T > (frame.size().width/2)/this->speed))  //第二组管道在第一组出来37帧后出现
		{
			h3->upshow(frame, center);
			h4->downshow(frame, center, h3);
		}

	}
};