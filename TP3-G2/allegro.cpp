/*
--- Control de Allegro
*/


#include "tp2_allegro.h"

using namespace std;




void Colocate_grid(int col, int fil, float size_floor);



bool init_allegro(allegro_t * allegro_p)
{

	allegro_p->display = NULL;           //Puntero a display
	allegro_p->event_queue = NULL;   //Puntero a cola de eventos
	allegro_p->timer = NULL;                //puntero a timer
	allegro_p->cleaner_robot = NULL;        //Puntero a imagen
	allegro_p->font = NULL;



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

	allegro_p->font = al_load_ttf_font("OpenSans-Bold.ttf", 20, 0); //cargo fuente
	if (!allegro_p->font) { //si falla lo aviso
		fprintf(stderr, "Could not load 'OpenSans-Bold.ttf'.\n");
		return 0;
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
	allegro_p->cleaner_robot = al_load_bitmap("robot_cleaner.png"); //Led apagado

	if (!allegro_p->cleaner_robot) //pregunto si imagen se inicializo correctamente
	{
		fprintf(stderr, "failed to load image !\n");
		al_destroy_timer(allegro_p->timer);
		return 1;
	}





	allegro_p->display = al_create_display(SCREEN_W, SCREEN_H); // Inicializo display 800*600
	if (!allegro_p->display)  //pregunto si display se inicializo correctamente
	{
		al_destroy_bitmap(allegro_p->cleaner_robot); //Si falla cierro todo lo que se inicializo
		al_destroy_timer(allegro_p->timer);
		fprintf(stderr, "failed to create display!\n");
		return 1;
	}


	allegro_p->event_queue = al_create_event_queue(); // inicializo cola de eventos

	/*display en negro------------------------*/
	al_clear_to_color(al_map_rgb(0, 0, 0)); //Hace clear del backbuffer del diplay al color RGB 0,0,0 (negro)

	if (!allegro_p->event_queue)  //pregunto si cola de eventos se inicializo correctamente
	{
		al_destroy_bitmap(allegro_p->cleaner_robot); //Si falla cierro todo lo que se inicializo
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
Muestra todo el piso sucio
recibe: int cantidad de columnas
		int cantidad de filas
		float tamaño de baldosa
devuelve: nada
*/
void Create_dirty_floor(int col, int fil, float size_floor)
{

	al_draw_filled_rectangle(0, 0, size_floor*col, size_floor*fil, al_map_rgb(50, 50, 50)); //coloca todo el piso gris
	Colocate_grid(col, fil, size_floor); //genera una grilla

	return;
}

/*
Muestra limpia una baldosa
recibe: int coordenada baldosa en x
		int coordenada baldosa en y
		float tamaño de baldosa
devuelve: nada
*/
void Clean_floor(int x, int y, float size_floor)
{
	al_draw_filled_rectangle(size_floor*x + THICKNESS_LINE, size_floor*y + THICKNESS_LINE, size_floor*(x + 1) - THICKNESS_LINE, size_floor*(y + 1) - THICKNESS_LINE, al_map_rgb(255, 255, 255));
	return;
}

/*
genera una grilla
recibe: int cantidad de columnas
		int cantidad de filas
		float tamaño de baldosa
devuelve: nada
*/
void Colocate_grid(int col, int fil, float size_floor)
{
	for (int i = 1; i < fil; i++)
		al_draw_line(0, size_floor*i, SCREEN_W, size_floor*i, al_map_rgb(0, 0, 0), THICKNESS_LINE);

	for (int i = 1; i < col; i++)
		al_draw_line(size_floor*i, 0, size_floor*i, SCREEN_H, al_map_rgb(0, 0, 0), THICKNESS_LINE);
}

/*
Muestra un robot en pantalla
recibe: float posicion en x
		float posicion en y
		float angulo de direccion
		allegro_t* para buscar imagen de robot
		float tamaño de baldosa
devuelve: nada
*/
void Set_robot(float x, float y, float angle, allegro_t * allegro_p, float size_floor)
{

	//al_draw_scaled_rotated_bitmap(allegro_p->cleaner_robot,0, 0, x*size_floor,y*size_floor, 0.001*size_floor, 0.001*size_floor,angle, 0);
	al_draw_filled_circle(x*size_floor, y*size_floor, 0.3*size_floor, al_map_rgb(140, 210, 50));
	return;

}


/*
Select Mode
cuando se invoca esta funcion pasa a tener todo el control hasta que se selecciona un modo.
recibe: int cantidad de columnas
		int cantidad de filas
		allegro_t* puntero a estructura auxiliar
devuelve: int modo de operacion. 1 o 2
*/
int Select_mode(int fil, int col, allegro_t* allegro_p)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));

	char str[50];
	sprintf(str, "Simulador %d x %d baldosas", fil, col);
	al_draw_text(allegro_p->font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 0, ALLEGRO_ALIGN_CENTRE, str);

	al_draw_text(allegro_p->font, al_map_rgb(255, 255, 255), SCREEN_W / 4, SCREEN_H / 2 - 100, ALLEGRO_ALIGN_CENTRE, "Modo 1");
	al_draw_text(allegro_p->font, al_map_rgb(255, 255, 255), 3 * (SCREEN_W / 4), SCREEN_H / 2 - 100, ALLEGRO_ALIGN_CENTRE, "Modo 2");

	al_draw_rectangle(SCREEN_W / 4 - 150, SCREEN_H / 2 - 100, SCREEN_W / 4 + 200, SCREEN_H / 2, al_map_rgb(255, 255, 255), THICKNESS_LINE);

	al_draw_rectangle(3 * SCREEN_W / 4 - 150, SCREEN_H / 2 - 100, 3 * SCREEN_W / 4 + 200, SCREEN_H / 2, al_map_rgb(255, 255, 255), THICKNESS_LINE);

	al_flip_display(); // actualizo display

	int mode = 0;

	ALLEGRO_MOUSE_STATE state;

	do {
		al_get_mouse_state(&state);

		if (state.buttons & 1)
		{
			if (state.x >= SCREEN_W / 7 && state.x <= (SCREEN_W / 3 + 50) && state.y >= SCREEN_H / 2 - 100 && state.y <= SCREEN_H / 2)
				mode = 1;

			if (state.x >= SCREEN_W / 2 + 200 && state.x <= (SCREEN_W / 2 + 510) && state.y >= SCREEN_H / 2 - 100 && state.y <= SCREEN_H / 2)
				mode = 2;
		}



	} while (mode == 0);

	al_clear_to_color(al_map_rgb(0, 0, 0));
	//al_draw_justified_text(allegro_p->font, al_map_rgb(255, 255, 255), 0, 100, 0, 200, 1, str);

	return mode;
}



void al_ShowTickCount(int tickcount, allegro_t* allegro_p)
{

	al_clear_to_color(al_map_rgb(0, 0, 0));

	char str[50];
	sprintf(str, "Cantidad de Tickcount: %d", tickcount);
	al_draw_text(allegro_p->font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTRE, str);

	char * str1 = { "exit" };
	al_draw_text(allegro_p->font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 3 * SCREEN_H / 4, ALLEGRO_ALIGN_CENTRE, str1);
	al_draw_rectangle(SCREEN_W / 2 - 100, 3 * SCREEN_H / 4, SCREEN_W / 2 + 100, 3 * SCREEN_H / 4 + 50, al_map_rgb(255, 255, 255), THICKNESS_LINE);
	al_flip_display();

	ALLEGRO_MOUSE_STATE state;
	bool check = false;
	do {
		al_get_mouse_state(&state);

		if (state.buttons & 1)
		{
			if (state.x >= SCREEN_W / 2 - 100 && state.x <= (SCREEN_W / 2 + 100) && state.y >= 3 * SCREEN_H / 4 && state.y <= 3 * SCREEN_H / 4 + 50)
			{
				check = true;
			}
		}



	} while (check == false);

	return;
}


void al_show_graph(double * indexTicks, int Nmax)
{
	//printf("Nmax: %d\n",Nmax);
	al_draw_filled_rectangle(SCREEN_W*0.01, SCREEN_H*0.05, SCREEN_W*0.99, SCREEN_H*0.95, al_map_rgb(240, 240, 240));
	al_draw_line(SCREEN_W * 0.025, SCREEN_H *0.1, SCREEN_W*0.025, SCREEN_H*0.905, al_map_rgb(0, 0, 0), 3 * THICKNESS_LINE);
	al_draw_line(SCREEN_W * 0.025, SCREEN_H *0.905, SCREEN_W*0.97, SCREEN_H*0.905, al_map_rgb(0, 0, 0), 3 * THICKNESS_LINE);

	float rangeX = SCREEN_W * (0.97 - 0.03);
	float rangeY = SCREEN_H * (0.9 - 0.2);

	float deltaPointsX = rangeX / (float)Nmax;
	float deltaPointsY = rangeY / MaxValue(indexTicks, Nmax);
	//printf("%f\n", MaxValue(indexTicks, Nmax));
	//printf("%f \n %f", deltaPointsX, deltaPointsY);

	for (int i = 0; i < Nmax; i++)
	{
		al_draw_filled_rectangle(SCREEN_W*0.03 + deltaPointsX * i, SCREEN_H*0.9 - deltaPointsY * indexTicks[i], SCREEN_W*0.03 + deltaPointsX * (i + 1) - SCREEN_W * 0.01, SCREEN_H*0.9, al_map_rgb(0, 180, 240));
	}


	ALLEGRO_FONT *font = al_load_ttf_font("OpenSans-Bold.ttf", 15, 0);
	char str1[50];
	sprintf(str1, "TickCountMax: %.0f", MaxValue(indexTicks, Nmax));
	al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W * 0.025 + 0.01, SCREEN_H*0.1, 0, str1);

	char str2[50];
	sprintf(str2, "cantRobotMax: %d", Nmax);
	al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W*0.8, SCREEN_H*0.9, 0, str2);
	al_flip_display();
	al_rest(6.0);
	return;

}

double MaxValue(double * indexTicks, int Nmax)
{
	double MaxVal = 0.0;
	for (int i = 0; i < Nmax; i++)
	{

		MaxVal = indexTicks[i] > MaxVal ? indexTicks[i] : MaxVal;
	}
	return MaxVal;
}