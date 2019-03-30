#include <iostream>
#include "allegro.h"
#include "bird.h"
#include "ParseCmdLine.h"

#define OK	0

using namespace std;

int main(int argc, char *argv[])
{
	allegro_t Allegro;						//instancia de estructura Allegro
	allegro_t * allegro_p = &Allegro;		//Creo puntero a la estructura de Allegro
	init_allegro(allegro_p);				//Inicializo allegro




	Al_set_background(allegro_p);			//Coloco fondo (paisaje)
	printf("%c", Al_askforbutton(allegro_p)); //tecla
	al_rest(3.0); //delay
	return OK;
}