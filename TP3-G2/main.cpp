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
void ManageKeyboard(float* data, int*mode, Bird* birds, bool *info, char tecla);
void show_data(float* data, allegro_t * allegro_p);

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
	for (int i = 0; i < MAX_ARGS; i++)
		UserData[i] = NULL;

	if (parseCmdLine(argc, argv, parseCallback, &UserData) == -1)	//Invoco al parse y almaceno su retorno
	{
		printf("Ingreso mal los parametros");
		return 1;
	}



	
	UserData[Nbirds] = 100; // <-- int con cantidad de pajaros
	UserData[RandomJiggleLimit] = 5;
	UserData[Eyesight] = 30;
	

	for (int i = 0; i < MAX_ARGS; i++)	//verifico que se hayan cargado todos los argumentos necesarios
		if (UserData[i] == NULL)
		{
			printf("Falta asignar valor a una opcion: ");
			switch (i)
			{
			case Nbirds: printf("Cantidad de pajaros '-b' = ? \n");
				break;
			case Eyesight: printf("Eyesight '-e' = ? \n");
				break;
			case RandomJiggleLimit: printf("RandomJiggleLimit '-r' = ? \n");
				break;
			}
			return 1;
		}




	// Programa simulacion de pajaros
	Bird * birds = new Bird[UserData[Nbirds]];  //inicializo cantidad de pajaros

	for (int i = 0; i < UserData[Nbirds]; i++)   //le asigno valores random a los pajaros
	{
		birds[i].randomize(SCREEN_W,SCREEN_H);
	}

	char tecla = NULL;
	int modo = 1;
	bool ShowInfo = false;
	
	while (tecla != ESC) //mientras no se presione la tecla escape
	{
		
		ManageKeyboard(UserData, &modo, birds, &ShowInfo, tecla);

		
		
		for (int i = 0; i < UserData[Nbirds]; i++) //para cada pajaro calculo su proximo movimiento
		{
			birds[i].pre_move(birds,UserData[Nbirds],UserData[RandomJiggleLimit],UserData[Eyesight], SCREEN_W, SCREEN_H);
		}


		for (int i = 0; i < UserData[Nbirds]; i++) //los muevo
		{
			birds[i].move_birds();
		}

		Draw_birds(birds, allegro_p, UserData[Nbirds]); //dibujo todos los pajaros con Allegro

		if (ShowInfo == true)
		{
			show_data(UserData, allegro_p);
		}

		al_rest(0.005); //delay
		tecla = Al_askforbutton(allegro_p); // guardo si se presiono una tecla

	}




	delete[] birds; //destruyo pajaros y resto de allegro
	al_destroy_display(Allegro.display);
	al_destroy_bitmap(Allegro.image);
	al_destroy_bitmap(Allegro.image2);
	al_destroy_event_queue(Allegro.event_queue);
	al_destroy_font(Allegro.font);

	return OK;
}




void show_data(float* data, allegro_t * allegro_p) //Muestro en pantalla info de opciones en tiempo real
{
	enum opciones { Nbirds, Eyesight, RandomJiggleLimit };
	al_draw_filled_rectangle(0, 0, 120, 3*20, WHITE);
	al_draw_textf(allegro_p->font, BLACK, 0, 0, 0, "CantBird = %4.0f", data[Nbirds]);
	al_draw_textf(allegro_p->font, BLACK, 0, 20, 0, "Eyesight = %3.1f", data[Eyesight]);
	al_draw_textf(allegro_p->font, BLACK, 0, 2*20, 0, "JiggleLim = %2.1f", data[RandomJiggleLimit]);



	al_flip_display();
	return;
}

void ManageKeyboard(float* data, int*mode, Bird* birds, bool *info, char tecla)
{
	enum opciones { Nbirds, Eyesight, RandomJiggleLimit };
	switch (tecla)	//evaluo si se presiono una tecla
	{
	case 'q':
	{
		data[RandomJiggleLimit] += 0.1; //si fue q aumento JiggleLimit
		//cout << "RandomJiggleLimit = " << data[RandomJiggleLimit] << endl;
		break;
	}

	case 'a':
	{
		if (data[RandomJiggleLimit] > 0)
		{
			data[RandomJiggleLimit] -= 0.1; //si fue a bajo Jiggle Limit
		}
		//cout << "RandomJiggleLimit = " << data[RandomJiggleLimit] << endl;
		break;
	}

	case 'w':
	{
		data[Eyesight] += 1;	//si fue w aumento Eyesight
		//cout << "Eyesight = " << data[Eyesight] << endl;
		break;
	}

	case 's':
	{
		data[Eyesight] -= 1; //si fue s bajo el Eyesight
		if (data[Eyesight] < 0)
		{
			data[Eyesight] = 0;
		}
		//cout << "Eyesight = " << data[Eyesight] << endl;
		break;
	}

	case 'm':
	{
		if (*mode == 2)
		{
			for (int i = 0; i < data[Nbirds]; i++)
			{
				birds[i].set_speed(1.0);
			}
			*mode = 1;
		}
		else if (*mode == 1)
		{
			for (int i = 0; i < data[Nbirds]; i++)
			{
				birds[i].set_speed(RandomValue(0.5, 2.0));
			}
			*mode = 2;

		}
		//cout << "Modo " << *mode << endl;
		break;
	}
	case 'i':
		if (*info == false) { *info = true; }
		else if (*info == true) { *info = false; }
		break;

	default: break;
	}

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
		//es un par�metro
		return 0;	//Interpretacion correcta
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
							*((float*)UserData) = (float)atoi(value);
						}
						break;

			case 'e':	if ((float)atof(value) > 100 || (float)atof(value) <= 0)			//Eyesight  *definir maximos
						{
							return 0;
						}else
						{
							*(((float*)UserData) + 1) = (float)atof(value);
						}
						break;

			case 'r':	if ((float)atof(value) < 0)										//RandomJiggleLimit   *definir maximos
						{
							return 0;
						}else
						{
							*(((float*)UserData) + 2) = (float)atof(value);
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