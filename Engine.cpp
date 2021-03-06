#include "Engine.h"

using namespace std;

Engine* Engine::engine = NULL;
///Wywo�anie potrzebnych podstawowych p�l dla silnika i nadanie im warto�ci pocz�tkowych 
Engine::Engine()
{
	queue = NULL;
	timer_FPS = NULL;
	buffer = NULL;
	time = 0;
}
/// Zwolnienie pami�ci
Engine::~Engine() {
	al_destroy_display(display);
	al_destroy_bitmap(buffer);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer_FPS);
}
/// Metoda zwracaj�ca singleton klasy Engine
/// <returns>engine</returns>
Engine* Engine::GetInstance() {
    if (Engine::engine == NULL)
        Engine::engine = new Engine();
    return Engine::engine;
}
/// Funkcja inicjuj�ca/tworz�ca wszystkie aspekty silnika(tak jak w zwyk�ych komentarzach kodu po kolei): Inicjalizacja biblioteki Allegro 5; Utworzenie kolejki event�w; Inicjalizacja prymityw�w; Ustawienie fullscreena; Ustawienie rozdzielczo�ci; Utworzenie bufora; Utworzenie ekranu; Ustawienie nazwy okna; Rejestracja display jako �r�d�o event�w; Utworzenie timera; Rejestracja timera jako �r�d�o event�w; Instalacja klawiatury i myszy
/// <param name="Title">zmienna przechowywuj�ca tytu� okna</param>
/// <param name="fullscreen">zmienna ustawiaj�ca fullscreen</param>
/// <param name="res">zmienna zawieraj�ca par� przyk�adowych rozdzielczo�ci (FULLHD, HD, SVGA, VGA)</param>
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
	timer_FPS = al_create_timer(1.0 / 10);
	if (!timer_FPS)
		Exception("Failed to create FPS timer!\n");

	/* Rejestracja timera jako �r�d�o event�w */
	al_register_event_source(queue, al_get_timer_event_source(timer_FPS));
	
	/* Instalacja klawiatury i myszy */
	al_install_keyboard();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_install_mouse();
	al_register_event_source(queue, al_get_mouse_event_source());

	al_init_image_addon();

	srand(NULL);
}
/// Metoda zwracaj�ca buffer
/// <returns>buffer</returns>
ALLEGRO_BITMAP* Engine::GetBuffer() {
	return buffer;
}
/// Funkcja wy�wietlaj�ca napotkany problem oraz jego przyczyn�
/// <param name="Error">przechowuj� informacj� o wyst�pionym b��dzie</param>
void Engine::Exception(string Error) {
    al_show_native_message_box(NULL,"Error",Error.c_str(),"The program has been stopped.",NULL,ALLEGRO_MESSAGEBOX_ERROR);
	exit(0);
}
/// Funkcja zawieraj�ca g��wn� p�tl� s�u��c� do uruchamiania licznika czasu i zdarze�
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
/// Funkcja renderuj�ca ekran
void Engine::Render() {
	spriteObject->Destination(15);
	al_set_target_backbuffer(display);
	al_draw_bitmap(buffer, 0, 0, NULL);
	al_flip_display();
}
/// Funkcja dla wyst�puj�cych zdarze�, wykonuje(tak jak w zwyk�ych komentarzach kodu po kolei): Wys�anie eventu do zmiennej event, w razie jego wyst�pienia; Wy��czenie programu po nacisni�ciu przycisku wyj�cia; Od�wie�enie display
void Engine::Events() {
	/* Wys�anie eventu do zmiennej event, w razie jego wyst�pienia. */
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
		spriteObject->draw(buffer);
		Render();
		break;
		/* Test obiektu sprite Object - klikni�cie wylosuje jego nowe wsp�rz�dne */
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		spriteObject->moveDestination(event.mouse.x, event.mouse.y);
		break;
		/* Test obiektu sprite Object - klawisze WASD - pozwalaj� porusza� obiektem */
	case ALLEGRO_EVENT_KEY_CHAR:
		switch (event.keyboard.keycode) {
		case 23:
			spriteObject->move(UP, 15);
			break;
		case 1:
			spriteObject->move(LEFT, 15);
			break;
		case 19:
			spriteObject->move(DOWN, 15);
			break;
		case 4:
			spriteObject->move(RIGHT, 15);
			break;
		}
		break;
	
	default: break;
	}
}
