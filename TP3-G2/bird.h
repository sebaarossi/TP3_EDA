#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "random.h"

class Bird
{
public:
	Bird()
	{
		set_speed(1.0);
	}		//constructor

	void randomize(double maxwidth,double maxheight);
	void pre_move(Bird* birds, int bird_count, double rand_jiggle_limit, double eyesight,int maxX,int maxY);
	void move_birds(void);

	/*GETTERS*/
	double getX();
	double getY();
	double get_nX();
	double get_nY();
	double get_angle();
	double get_speed();
	/*SETTERS*/
	void setX(double a);
	void setY(double b);
	void set_speed(double s);
	void set_angle(double c);

private:
	/*Define la siguiente posicion a partir del angulo y la posicion*/
	void new_xy(int maxX, int maxY);
	void new_xy(int maxX, int maxY, double speed_);


	double x;
	double y;
	double newX;
	double newY;
	double speed;
	double angle;
	double new_angle;
};

/*Genera el movimiento de todos los pajaros*/


