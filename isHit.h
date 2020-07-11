#pragma once
#include<opencv2/opencv.hpp>
#include<windows.h>
#include <stdlib.h>
#include <iostream>
#include "source.h"
#include "user.h"
#include "grade.h"
using namespace cv;

class isHit
{
private:

public:
	int hit(Point2f center, Hinder *hin1,User u1)//判断是否碰撞障碍物
	{
		int x = hin1->getLocation_x();
		int y = hin1->getLocation_y();
		int w = hin1->getWeight();
		int h = hin1->getHigh();//获取障碍物的边界构成一个矩形框
		Rect rect(x, y, w, h);
		if (center.x > rect.x + rect.width) { return 0; }
		if (center.y > rect.y + rect.height) { return 0; }
		if (center.x + u1.getWeight() < rect.x) { return 0; }
		if (center.y + u1.getHigh() < rect.y) { return 0; }

		else return 1;

	}
	int hited(Mat frame, Point2f center, User u1, Hinder *h1, Hinder *h2, Hinder *h3, Hinder *h4)
	{
		if ( (this->hit(center, h1,u1) == 1 || this->hit(center, h2,u1) == 1 || this->hit(center, h3, u1) == 1 || this->hit(center, h4,u1) == 1) && h1->getT()>70)//留给玩家70帧的反应时间
		{
			h1->setFlag(1);
		}
		if (h1->getflag() == 1)
		{
			h1->setSpeed(0);
			h2->setSpeed(0);
			h3->setSpeed(0);
			h4->setSpeed(0);
			u1.dead(frame, center);
			Grade G2;
			G2.showcount(frame);
			static long T0;
			static int T1 = 1;
			if (T1 > 0) {
				time_t start;
				T0 = time(&start);
				T1--;
			}
			time_t end;
			time(&end);
			if (end - T0 >= 3) //出现游戏结图标，延迟3秒关闭
				return 1;
		}
	}
};