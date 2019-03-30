#include <iostream>
#include "allegro.h"
#include "bird.h"
#include "ParseCmdLine.h"

#define OK	0
#define MAXBIRD 5000
#define MAX_ARGS 3

using namespace std;

int main(int argc, char *argv[])
{
	// inicializcion allegro
	allegro_t Allegro;						//instancia de estructura Allegro
	allegro_t * allegro_p = &Allegro;		//Creo puntero a la estructura de Allegro
	init_allegro(allegro_p);				//Inicializo allegro
	


	//parsecmdline
	enum opciones {Nbirds,Eyesight,RandomJiggleLimit};

	int		UserData[MAX_ARGS];			//Arreglo de int donde se guardan las opciones
	int		parseCmdLine_Return;		//Variable que almacena el retorno de parseCmdLine

	if (parseCmdLine(argc, argv, parseCallback, &UserData) == -1)	//Invoco al parse y almaceno su retorno
	{
		printf("Ingreso mal los parametros fila, col, robots, modo");
		return 0;
	}
	UserData[Nbirds]; // <-- int con cantidad de pajaros



	// Programa simulacion de pajaros





	Al_set_background(allegro_p);			//Coloco fondo (paisaje)
	printf("%c", Al_askforbutton(allegro_p)); //tecla
	al_rest(3.0); //delay
	return OK;
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