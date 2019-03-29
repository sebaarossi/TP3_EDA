#include <stdio.h>
#include "allegro.h"

allegroStruct_t* init_allegro (allegroStruct_t* usrAllegro)
{
  
  usrAllegro = (allegroStruct_t*)malloc(sizeof(allegroStruct_t));

  if(!al_init())//inicio allegro
  {
      printf("Could not initialize Allegro!\n");
      return -1;
  }
  
  
  usrAllegro->display = al_create_display(SCREEN_W, SCREEN_H);
  if(!display)//inicio display
  {
      printf("Could not initialize Display!.\n");
      return -1;
  }
  

  usrAllegro->event_queue = al_create_event_queue();
  if(!event_queue)//inicio cola de eventos
  {
      printf("Could not initialize event queue!.\n");
      al_destroy_display(usrAllegro->display);
      return -1;
  }
  

  
  if(!al_install_keyboard())//Inicio teclado
  {
      printf("Failed to initialize the keyboard!\n");
      return -1;
  }
  
  al_init_image_addon();
  al_init_font_addon();
  al_init_ttf_addon();
  
  
  

  //Solo estético, pone nombre a la ventana abierta
  al_set_window_title(usrAllegro->display, "Birds");
  
  //Registro eventos de todo tipo
  al_register_event_source(event_queue, al_get_display_event_source(usrAllegro->display));
  
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  

  
  //libero memoria
  al_destroy_display(usrAllegro->display);
  al_destroy_event_queue(usrAllegro->event_queue);
        

}

void allegro_destroy(allegroStruct_t* usrAllegro)
{
	al_destroy_display(usrAllegro->display);
	usrAllegro->display = NULL;
    al_destroy_event_queue(usrAllegro->event_queue);
    usrAllegro->event_queue = NULL;
	free(usrAllegro);
	usrAllegro = NULL;
        

	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
}
