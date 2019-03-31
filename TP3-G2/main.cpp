#include <iostream>
#include <time.h>
#include "allegro.h"
#include "bird.h"
#include "ParseCmdLine.h"

#define OK	0
#define MAXBIRD 5000
#define MAX_ARGS 3
#define ESC -101

using namespace std;
int parseCallback(const char *key, const char *value, void *UserData);
void Draw_birds(Bird * birds, allegro_t* allegro_p, int Nbirds);

int main(int argc, const char **argv)
{
	srand(time(NULL));
	// inicializcion allegro
	allegro_t Allegro;						//instancia de estructura Allegro
	allegro_t * allegro_p = &Allegro;		//Creo puntero a la estructura de Allegro
	init_allegro(allegro_p);				//Inicializo allegro



	//parsecmdline
	enum opciones { Nbirds, Eyesight, RandomJiggleLimit };

	float	UserData[MAX_ARGS];			//Arreglo de int donde se guardan las opciones
	
	if (parseCmdLine(argc, argv, parseCallback, &UserData) == -1)	//Invoco al parse y almaceno su retorno
	{
		printf("Ingreso mal los parametros fila, col, robots, modo");
		return 0;
	}
	UserData[Nbirds] = 400; // <-- int con cantidad de pajaros
	UserData[RandomJiggleLimit] = 1;
	UserData[Eyesight] = 20;



	// Programa simulacion de pajaros
	Bird * birds = new Bird[UserData[Nbirds]];  //inicializo cantidad de pajaros

	for (int i = 0; i < UserData[Nbirds]; i++)   //le asigno valores random a los pajaros
	{
		birds[i].randomize(SCREEN_W,SCREEN_H);
	}

	char tecla = NULL;
	
	while (tecla != ESC) //mientras no se presione la tecla escape
	{
		switch (tecla)	//evaluo si se presiono una tecla
		{
		case 'q': UserData[RandomJiggleLimit] += 1; //si fue q aumento JiggleLimit
			break;

		case 'a': UserData[RandomJiggleLimit] -= 1; //si fue a bajo Jiggle Limit
			break;

		case 'w': UserData[Eyesight] += 1;	//si fue w aumento Eyesight
			break;

		case 's': UserData[Eyesight] -= 1; //si fue s bajo el Eyesight
			break;
		default: break;
		}

		for (int i = 0; i < UserData[Nbirds]; i++) //para cada pajaro calculo su proximo movimiento
		{
			birds[i].pre_move(birds,UserData[Nbirds],UserData[RandomJiggleLimit],UserData[Eyesight], SCREEN_W, SCREEN_H);
		}


		for (int i = 0; i < UserData[Nbirds]; i++) //los muevo
		{
			birds[i].move_birds();
		}

		Draw_birds(birds, allegro_p, UserData[Nbirds]); //dibujo todos los pajaros con ALlegro
		al_rest(0.005); //delay
		tecla = Al_askforbutton(allegro_p); // guardo si se presiono una tecla

	}

	delete[] birds; //destruyo pajaros y resto de allegro
	al_destroy_display(Allegro.display);
	al_destroy_bitmap(Allegro.image);
	al_destroy_event_queue(Allegro.event_queue);
	al_destroy_timer(Allegro.timer);
	//al_destroy_font(Allegro.font);
	return OK;
}

void show_data(int Nbirds, int Eyesight, int RandomJiggleLimit)
{


}



void Draw_birds(Bird * birds, allegro_t * allegro_p, int Nbirds)
{
	Al_set_background(allegro_p);			//Coloco fondo (paisaje)
	for (int i = 0; i < Nbirds; i++)
	{
		Al_set_image(birds[i].getX(), birds[i].getY(), birds[i].get_angle()+5, allegro_p); //coloco todos los pajaros
	}
	al_flip_display(); //actualizo display
	return;
}


int parseCallback(const char *key, const char *value, void *UserData)
{
	if (key == NULL)
	{
		//Guardar value en UserData, ya que lo que ingreso
		//es un parámetro
		return 1;	//Interpretacion correcta
	}
	if (key != NULL && value != NULL && (*value) != '-')
	{
		switch (*key)
		{
			case 'b':	if ((int)atoi(value) > MAXBIRD || (int)atoi(value) < 0)		//maxima cantidad de pajaros MAXBIRD
						{
							return 0;
						}else
						{
							*((int*)UserData) = (int)atoi(value);
						}
						break;

			case 'e':	if ((int)atoi(value) > 100 || (int)atoi(value) <= 0)			//Eyesight  *definir maximos
						{
							return 0;
						}else
						{
							*(((int*)UserData) + 1) = (int)atoi(value);
						}
						break;

			case 'r':	if ((int)atoi(value) < 0)										//RandomJiggleLimit   *definir maximos
						{
							return 0;
						}else
						{
							*(((int*)UserData) + 2) = (int)atoi(value);
						}
						break;

		
			default:	return 0;

		}

		return 1;
	}


	if (key != NULL && (value == NULL || (*value) == '-'))
	{
		printf("Error key: %s\n", key);
		return 0; //si tengo una clave sin valor, devuelvo 0
	}
	return 0;
}