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
#define SCREEN_W		1000
#define SCREEN_H		700
#define QUIT    'q'
#define THICKNESS_LINE 1.5





typedef struct
{
	ALLEGRO_DISPLAY * display;           //Puntero a display
	ALLEGRO_EVENT_QUEUE * event_queue;   //Puntero a cola de eventos
	ALLEGRO_TIMER * timer;                //puntero a timer
	ALLEGRO_BITMAP  * cleaner_robot;        //Puntero a imagen
	ALLEGRO_FONT *font;

}allegro_t;


bool init_allegro(allegro_t*);			//inicializa allegro
void Create_dirty_floor(int col, int fil, float size_floor); //coloca todos los pisos sucios. recibe columna y fila.
void Clean_floor(int x, int y, float);
void Set_robot(float x, float y, float angle, allegro_t * allegro_p, float size_floor);
int Select_mode(int fil, int col, allegro_t*);
void al_ShowTickCount(int tickcount, allegro_t* allegro_p);
void al_show_graph(double * indexTicks, int Nmax);
double MaxValue(double * indexTicks, int Nmax);