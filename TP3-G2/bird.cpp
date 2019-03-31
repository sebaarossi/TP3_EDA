#include "bird.h"
#define _USE_MATH_DEFINES
#include <math.h>

void Bird::randomize(double maxwidth, double maxheight)
{
	setX(RandomValue(0,maxwidth));
	setY(RandomValue(0, maxheight));
	set_angle(RandomValue(0,2*M_PI));
	return;
}

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



/*Define la siguiente posicion a partir del angulo y la posicion*/
/*MODO 1*/
void Bird::new_xy(int maxX, int maxY)
{
	
	double a = x + speed*cos(new_angle);		//sumandole a la posicion inicial el coseno y el seno del angulo (para las coordenadas 
	double b = y + speed*sin(new_angle);		//...X e Y, respectivamente) consigo la siguiente posicion del pajaro segun su angulo

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
	return;	
	
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
void Bird::pre_move(Bird* birds, int bird_count, double rand_jiggle_limit, double eyesight,int maxX, int maxY)
{
	double angleSum = 0;
	unsigned int divider = 0;
	for (int i = 0; i < bird_count; i++)
	{
		if (sqrt(pow(birds[i].x - x, 2) + pow(birds[i].y - y, 2)) != 0)
		{
			if (sqrt(pow(birds[i].x - x, 2) + pow(birds[i].y - y, 2)) < eyesight)
			{
				angleSum += birds[i].angle;
				divider++;
			}
		}
	}
	if (divider != 0)
	{
		new_angle = ((angleSum+angle)/(divider+1)) + (RandomSign()*(RandomValue(0,rand_jiggle_limit)*(M_PI/180)));
	}
	else
	{
		new_angle = angle;
	}

	new_xy(maxX, maxY);

	return;
}






/****************************************************************************************************************/

/*Genera el movimiento de todos los pajaros*/
/*MODO 1*/
void Bird::move_birds(void)
{
	angle = new_angle;
	x = newX;
	y = newY;
	return;
}










