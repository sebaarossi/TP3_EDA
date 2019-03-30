#ifndef BIRD_H
#define BIRD_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Bird
{
public:
	Bird(double coor_x, double coor_y, double speed_, double angle_)
	{
		x = coor_x;
		y = coor_y;
		speed = speed_;
		angle = angle_;
		newX = 0.0;
		newY = 0.0;
	}

	void pre_move(Bird* pajaro, int bird_count, double rand_jiggle_limit, double eyesight, int maxX, int maxY);
	void pre_move(Bird* pajaros, int bird_count, double rand_jiggle_limit, double eyesight, int maxX, int maxY, double speed_);

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
	/*Se fija el angulo de los pajaros dentro del eyesight y devuelve el nuevo angulo a partir de ello.
	Si no hay pajaros en el eyesight, devuelve el angulo original*/
	double get_new_angle(Bird* pajaro, int bird_count, double rand_jiggle_limit, double eyesight);

	double x;
	double y;
	double newX;
	double newY;
	double speed;
	double angle;
};

/*Genera el movimiento de todos los pajaros*/
void move_birds(Bird* pajaros, int bird_count, double rand_jiggle_limit, double eyesight, int maxX, int maxY, double speed_);
void move_birds(Bird* pajaros, int bird_count, double rand_jiggle_limit, double eyesight, int maxX, int maxY);


Bird* create_birds(int bird_count, double eyesight, double maxSpeed, int maxX, int maxY);

void destroy_birds(Bird* pajaros);
#endif