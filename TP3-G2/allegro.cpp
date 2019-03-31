#include<iostream>
#include "allegro.h"


#define ASCII_CONSTANT 96

using namespace std;




bool init_allegro(allegro_t * allegro_p)
{

	allegro_p->display = NULL;           //Puntero a display
	allegro_p->event_queue = NULL;   //Puntero a cola de eventos
	allegro_p->timer = NULL;                //puntero a timer
	allegro_p->image = NULL;        //Puntero a imagen
	allegro_p->image2 = NULL;


	if (!al_init())  //Inicializo allegro
	{ //Primera funcion a llamar antes de empezar a usar allegro.
		fprintf(stderr, "failed to initialize allegro!\n");
		return 1;
	}



	if (!al_install_mouse())  //Inicializo allegro
	{ //Primera funcion a llamar antes de empezar a usar allegro.
		fprintf(stderr, "failed to initialize allegro!\n");
		return 1;
	}



	if (!al_init_font_addon()) //inicializo fuentes 
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return 1;
	}

	if (!al_init_ttf_addon()) //inicializo fuente
	{
		return 1;
	}


	allegro_p->timer = al_create_timer(1.0 / FPS); //timer para actualizacion de pantalla
	if (!allegro_p->timer)
	{
		fprintf(stderr, "failed to create timer!\n");
		return 1;
	}


	if (!al_init_image_addon())
	{   // ADDON necesario para manejo(no olvidar el freno de mano) de imagenes 
		fprintf(stderr, "failed to initialize image addon !\n");
		al_destroy_timer(allegro_p->timer);
		return 1;
	}

	if (!al_init_primitives_addon())
	{   // ADDON necesario para manejo(no olvidar el freno de mano) de imagenes 
		fprintf(stderr, "failed to initialize image addon !\n");
		al_destroy_timer(allegro_p->timer);
		return 1;
	}

	if (!al_install_keyboard()) //Inicializo teclado
	{
		fprintf(stderr, "failed to initialize the keyboard!\n");
		al_destroy_timer(allegro_p->timer);
		return 1;
	}



	//Inicializo puntero de imagenes a imagenes correspondientes
	allegro_p->image = al_load_bitmap("atardecer.jpg"); //cargo imagen

	if (!allegro_p->image) //pregunto si imagen se inicializo correctamente
	{
		fprintf(stderr, "failed to load image !\n");
		al_destroy_timer(allegro_p->timer);
		return 1;
	}

	//Inicializo puntero de imagenes a imagenes correspondientes
	allegro_p->image2 = al_load_bitmap("bird.png"); //cargo imagen

	if (!allegro_p->image2) //pregunto si imagen se inicializo correctamente
	{
		fprintf(stderr, "failed to load image !\n");
		al_destroy_timer(allegro_p->timer);
		return 1;
	}


	allegro_p->display = al_create_display(SCREEN_W, SCREEN_H);		// Inicializo display 800*600
	
	if (!allegro_p->display)  //pregunto si display se inicializo correctamente
	{
		al_destroy_bitmap(allegro_p->image); //Si falla cierro todo lo que se inicializo
		al_destroy_timer(allegro_p->timer);
		fprintf(stderr, "failed to create display!\n");
		return 1;
	}


	allegro_p->event_queue = al_create_event_queue(); // inicializo cola de eventos

	/*display en negro------------------------*/
	al_clear_to_color(al_map_rgb(0, 0, 0)); //Hace clear del backbuffer del diplay al color RGB 0,0,0 (negro)

	if (!allegro_p->event_queue)  //pregunto si cola de eventos se inicializo correctamente
	{
		al_destroy_bitmap(allegro_p->image); //Si falla cierro todo lo que se inicializo
		al_destroy_display(allegro_p->display);
		al_destroy_timer(allegro_p->timer);
		fprintf(stderr, "failed to create event_queue!\n");
		return 1;
	}

	al_register_event_source(allegro_p->event_queue, al_get_display_event_source(allegro_p->display));
	al_register_event_source(allegro_p->event_queue, al_get_timer_event_source(allegro_p->timer)); //registro timer
	al_register_event_source(allegro_p->event_queue, al_get_keyboard_event_source()); //REGISTRAMOS EL TECLADO


	return 0;
}  //inicializo allegro




/*
Muestra una imagen en pantalla
recibe: float posicion en x
		float posicion en y
		float angulo de direccion
		allegro_t* para buscar imagen
		float 
devuelve: nada
*/
void Al_set_image(const float x,const float y,const float angle, allegro_t * allegro_p)
{
	al_draw_scaled_rotated_bitmap(allegro_p->image2,0, 0,x,y, 0.05, 0.05,angle, 0);
	//al_draw_filled_circle(x, y, 4, BLACK);
	return;
}

void Al_set_background(allegro_t* allegro_p)
{
	al_draw_scaled_bitmap(allegro_p->image, 0, 0, 770, 420, 0, 0, SCREEN_W, SCREEN_H, 0);
	return;
}



/*
-Al_askforbutton





*/


char Al_askforbutton(allegro_t* allegro_p)
{
	al_register_event_source(allegro_p->event_queue, al_get_keyboard_event_source());	//Registramos el teclado
	if (al_get_next_event(allegro_p->event_queue, &allegro_p->ev))											//Toma un evento de la cola
	{
		if (allegro_p->ev.type == ALLEGRO_EVENT_KEY_DOWN)								//si detecto que se presiono una tecla
		{
			return (char)(allegro_p->ev.keyboard.keycode)+ASCII_CONSTANT;
		}
	}


	return -1;
}