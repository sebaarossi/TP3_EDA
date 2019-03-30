#include "bird.h"
#define _USE_MATH_DEFINES
#include <math.h>

/*GETTERS*/
double Bird::getX()
{
	return x;
}
double Bird::getY()
{
	return y;
}
double Bird::get_nX()
{
	return newX;
}
double Bird::get_nY()
{
	return newY;
}
double Bird::get_angle()
{
	return angle;
}
double Bird::get_speed()
{
	return speed;
}

/*SETTERS*/
void Bird::setX(double a)
{
	x = a;
	return;
}
void Bird::setY(double b)
{
	y = b;
	return;
}
void Bird::set_speed(double s)
{
	speed = s;
	return;
}
void Bird::set_angle(double c)
{
	angle = c;
	return;
}

/*Se fija el angulo de los pajaros dentro del eyesight y devuelve el nuevo angulo a partir de ello.
Si no hay pajaros en el eyesight, devuelve el angulo original*/
double Bird::get_new_angle(Bird* pajaros, int bird_count, double rand_jiggle_limit, double eyesight)
{
	double sum_angle = 0;
	int birds_in_sight = 0;

	for (int i = 0; i < bird_count; i++)
	{
		double a=pajaros[i].x;			//raiz de (x1-x2)^2+(y1-y2)^2 //sqrt(pow
		double b= pajaros[i].y;
		if (sqrt(pow((a - x), 2) + pow((b - y), 2))<eyesight)
		{
			sum_angle += pajaros[i].angle;
			birds_in_sight++;
		}
	}

	double r = (double)rand() / (RAND_MAX/rand_jiggle_limit);
	if (birds_in_sight == 0)
	{
		r = 0;
		birds_in_sight = 1;
	}
	if (sum_angle == 0)
	{
		sum_angle = angle;
	}
	
	return ((sum_angle / (double)birds_in_sight)+r);
}

/*Define la siguiente posicion a partir del angulo y la posicion*/
/*MODO 1*/
void Bird::new_xy(int maxX, int maxY)
{
	
	double a = x + (speed*cos(angle*M_PI / 180.0));		//sumandole a la posicion inicial el coseno y el seno del angulo (para las coordenadas 
	double b = y + (speed*sin(angle*M_PI / 180.0));		//...X e Y, respectivamente) consigo la siguiente posicion del robot segun su angulo

	if (a >= maxX)	//si se pasa del limite
	{
		a -= maxX;
	}
	if (b >= maxY)
	{
		b -= maxY;
	}
	if (a <= 0)
	{
		a += maxX;
	}
	if (b <= 0)
	{
		b += maxY;
	}

	newX = a;		//defino nueva posicion X
	newY = b;		//defino nueva posicion Y
	return;	//Devuelvo true indicando que hubo movimiento
	
}
/*MODO 2*/
void Bird::new_xy(int maxX, int maxY, double speed_)
{

	double a = x + (speed_*cos(angle*M_PI / 180.0));		//sumandole a la posicion inicial el coseno y el seno del angulo (para las coordenadas 
	double b = y + (speed_*sin(angle*M_PI / 180.0));		//...X e Y, respectivamente) consigo la siguiente posicion del robot segun su angulo

	if (a >= maxX)	//si se pasa del limite
	{
		a -= maxX;
	}
	if (b >= maxY)
	{
		b -= maxY;
	}
	if (a <= 0)
	{
		a += maxX;
	}
	if (b <= 0)
	{
		b += maxY;
	}

	newX = a;		//defino nueva posicion X
	newY = b;		//defino nueva posicion Y
	return;	//Devuelvo true indicando que hubo movimiento

}

/*Define el nuevo angulo segun los pajaros dentro del eyesight y define la siguiente posicion*/
/*MODO 1*/
void Bird::pre_move(Bird* pajaros, int bird_count, double rand_jiggle_limit, double eyesight, int maxX, int maxY)
{
	set_angle(get_new_angle(pajaros, bird_count, rand_jiggle_limit, eyesight));
	new_xy(maxX, maxY);
}
/*MODO 2*/
void Bird::pre_move(Bird* pajaros, int bird_count, double rand_jiggle_limit, double eyesight, int maxX, int maxY, double speed_)
{
	set_angle(get_new_angle(pajaros, bird_count, rand_jiggle_limit, eyesight));
	new_xy(maxX, maxY, speed_);
}

/****************************************************************************************************************/

/*Genera el movimiento de todos los pajaros*/
/*MODO 1*/
void move_birds(Bird* pajaros, int bird_count, double rand_jiggle_limit, double eyesight, int maxX, int maxY)
{
	for (int i = 0; i < bird_count; i++)
	{
		pajaros[i].pre_move(pajaros, bird_count, rand_jiggle_limit, eyesight, maxX, maxY);
	}
	for (int i = 0; i < bird_count; i++)
	{
		pajaros[i].setX(pajaros[i].get_nX());
		pajaros[i].setY(pajaros[i].get_nY());
	}
	return;
}
/*MODO 2*/
void move_birds(Bird* pajaros, int bird_count, double rand_jiggle_limit, double eyesight, int maxX, int maxY, double speed_)
{
	for (int i = 0; i < bird_count; i++)
	{
		pajaros[i].pre_move(pajaros, bird_count, rand_jiggle_limit, eyesight, maxX, maxY, speed_);
	}
	for (int i = 0; i < bird_count; i++)
	{
		pajaros[i].setX(pajaros[i].get_nX());
		pajaros[i].setY(pajaros[i].get_nY());
	}
	return;
}

/*Crea un "string" de pajaros con valores randomizados dentro de ciertos parametros*/
Bird* create_birds(int bird_count, double eyesight, double maxSpeed, int maxX, int maxY)
{
	Bird* pajaros = NULL;
	pajaros = (Bird*)malloc(sizeof(Bird)*bird_count);
	if (pajaros != NULL)
	{
		for (int i = 0; i < bird_count; i++)
		{
			pajaros[i].setX((double)rand() / (RAND_MAX/maxX));
			pajaros[i].setY((double)rand() / (RAND_MAX/maxY));
			pajaros[i].set_angle((double)rand() / (RAND_MAX/360.0));
			pajaros[i].set_speed(1.0+((double)rand() / (RAND_MAX/(maxSpeed-1.0))));		//TIENE 1 COMO MINIMO
		}
		
	}
	else
	{
		free(pajaros);
	}
	return pajaros;
}

/*Destruye los pajaros*/
void destroy_birds(Bird* pajaros)
{
	free(pajaros);
	return;
}