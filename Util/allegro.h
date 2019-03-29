#ifndef ALLEGRO_H
#define ALLEGRO_H

#include <stdio.h>

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>

typedef struct
{

	ALLEGRO_DISPLAY *display;	//puntero al display que se utiliza en el proyecto
    ALLEGRO_EVENT_QUEUE *event_queue; //puntero a la cola de eventos

} allegroStruct_t;