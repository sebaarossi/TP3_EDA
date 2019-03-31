#pragma once


#include<iostream>
#include <allegro5/allegro.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_audio.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_acodec.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <stdbool.h>


#define FPS			60.0 //cantidad de cuadros por segundo que se mostrara en pantalla
#define SCREEN_W		770
#define SCREEN_H		420
#define QUIT    'q'
#define THICKNESS_LINE 1.5


//COLORES//
#define BLACK al_map_rgb(0,0,0)
#define WHITE al_map_rgb(255,255,255)
#define LIGHT_GRAY al_map_rgb(224,224,224)
#define GRAY al_map_rgb(128,128,128)
#define DARK_GRAY al_map_rgb(64,64,64)
#define RED al_map_rgb(255,0,0)
#define PINK al_map_rgb(255,96,208)
#define PURPLE al_map_rgb(160,32,255)
#define LIGHT_BLUE al_map_rgb(80,208,255)
#define BLUE al_map_rgb(0,32,255)
#define LIGHT_GREEN al_map_rgb(96,255,128)
#define GREEN al_map_rgb(0,192,0)
#define YELLOW al_map_rgb(255,224,32)
#define ORANGE al_map_rgb(255,160,16)
#define BROWN al_map_rgb(160,128,96)
#define PALE_PINK al_map_rgb(255,208,160)



typedef struct
{
	ALLEGRO_DISPLAY * display;           //Puntero a display
	ALLEGRO_EVENT_QUEUE * event_queue;   //Puntero a cola de eventos
	ALLEGRO_EVENT  ev;
	ALLEGRO_TIMER * timer;                //puntero a timer
	ALLEGRO_BITMAP  * image;        //Puntero a imagen
	ALLEGRO_BITMAP * image2;
	ALLEGRO_FONT * font;

}allegro_t;


bool init_allegro(allegro_t*);			//inicializa allegro

/*
------ Al_set_image -------
coloca una imagen en la posicion del display que se le indique
recibe: float  coordenada x
		float  coordenada y
		float  angulo de rotacion
		allegro_t*  puntero a una estructura de allegro
devuelve nada.
*/
void Al_set_image(const float x,const float y,const float angle, allegro_t * allegro_p);


/*
------ Al_set_background -------
coloca una imagen de fondo
recibe:	allegro_t*  puntero a una estructura de allegro
devuelve nada
*/
void Al_set_background(allegro_t*);

/*
------ Al_askforbutton -------
indica si se presiono una tecla

recibe:	allegro_t*  puntero a una estructura de allegro
devuelve: char de tecla presionada
*/
char Al_askforbutton(allegro_t* allegro_p);
