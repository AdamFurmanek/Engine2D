#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "Engine.h"
#include <allegro5/allegro_primitives.h>
#include <vector>

using namespace std;

Engine* Engine::engine = NULL;

Engine::Engine()
{
	queue = NULL;
	timer_FPS = NULL;
	buffer = NULL;
	time = 0;
}

Engine::~Engine() {
	/* Zwolnienie pami�ci */
	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer_FPS);
}

Engine* Engine::GetInstance() {
    if (Engine::engine == NULL)
        Engine::engine = new Engine();
    return Engine::engine;
}

void Engine::Init(string Title, bool fullscreen, resolution res) {
	/* Inicjalizacja biblioteki Allegro 5. */
	if (!al_init())
		Exception("Failed to initialize Allegro5 library.\n");

	/* Utworzenie kolejki event�w*/
	queue = al_create_event_queue();
	if (queue == NULL)
		Exception("Failed to create event queue.\n");
	
	/* Inicjalizacjia prymityw�w. */
	if (!al_init_primitives_addon())
		Exception("Failed to initialize primitives addon.\n");

	/* Ustawienie fullscreena. */
	if(fullscreen)
		al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	/* Ustawienie rozdzielczo�ci. */
	int x, y;
	switch (res) {
	case FULLHD:
		x = 1920;
		y = 1080;
		break;
	case HD:
		x = 1280;
		y = 720;
		break;
	case SVGA:
		x = 800;
		y = 600;
		break;
	case VGA:
	default:
		x = 640;
		y = 480;
		break;
	}
	/* Utworzenie bufora. */
	buffer = al_create_bitmap(x, y);

	/* Utworzenie ekranu. */
	display = al_create_display(x, y);
	if(!display)
		Exception("Failed to create Allegro5 display.\n");
	/* Ustawienie nazwy okna. */
	al_set_window_title(display, Title.c_str());

	/* Rejestracja display jako �r�d�o event�w */
	al_register_event_source(queue, al_get_display_event_source(display));

	/* Utworzenie timera */
	timer_FPS = al_create_timer(1.0 / 30);
	if (!timer_FPS)
		Exception("Failed to create FPS timer!\n");

	/* Rejestracja timera jako �r�d�o event�w */
	al_register_event_source(queue, al_get_timer_event_source(timer_FPS));

	
	/* Instalacja klawiatury i myszy */
	al_install_keyboard();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_install_mouse();
	al_register_event_source(queue, al_get_mouse_event_source());

}

void Engine::Exception(string Error) {
    al_show_native_message_box(NULL,"Error",Error.c_str(),"The program has been stopped.",NULL,ALLEGRO_MESSAGEBOX_ERROR);
	exit(0);
}

void Engine::MainLoop() {
	/* Wystartowanie timera */
	al_start_timer(timer_FPS);

	/* Ustawienie loop na true*/
	loop = true;

	/* P�tla g��wna */
	while (loop) {
		Events();
	}
}

void Engine::Render() {
	al_set_target_backbuffer(display);
	al_draw_bitmap(buffer, 0, 0, NULL);
	al_flip_display();
}

void Engine::Events() {
	/* Wys�anie eventu do zmiennej event, w razie jego wyst�pienie. */
	al_wait_for_event(queue, &event);

	/* Obs�uga eventu w zale�no�ci od jego typu. */
	switch (event.type)
	{

		/* Wy��czenie programu po nacisni�ciu przycisku wyj�cia. */
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		loop = false;
		break;

		/* Od�wie�enie display. */
	case ALLEGRO_EVENT_TIMER:
		time++;
		Render();
		break;

	default: break;
	}
}

void Engine::Clear() {
	al_set_target_bitmap(buffer);
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void Engine::DrawPixels(vector <Point2D> pixels) {
	al_set_target_bitmap(buffer);
	for (int i = 0; i < pixels.size();i++) {
		al_draw_pixel(pixels[i].x, pixels[i].y, pixels[i].c);
	}
}

void Engine::DrawTriangle(Point2D a, Point2D b, Point2D c, ALLEGRO_COLOR co) {
	al_draw_triangle(a.x, a.y, b.x, b.y, c.x, c.y, co, 1);
}