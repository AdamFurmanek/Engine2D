#include "Engine.h"

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
	/* Zwolnienie pamiêci */
	al_destroy_display(display);
	al_destroy_bitmap(buffer);
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

	/* Utworzenie kolejki eventów*/
	queue = al_create_event_queue();
	if (queue == NULL)
		Exception("Failed to create event queue.\n");
	
	/* Inicjalizacjia prymitywów. */
	if (!al_init_primitives_addon())
		Exception("Failed to initialize primitives addon.\n");

	/* Ustawienie fullscreena. */
	if(fullscreen)
		al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	/* Ustawienie rozdzielczoœci. */
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

	/* Rejestracja display jako Ÿród³o eventów */
	al_register_event_source(queue, al_get_display_event_source(display));

	/* Utworzenie timera */
	timer_FPS = al_create_timer(1.0 / 15);
	if (!timer_FPS)
		Exception("Failed to create FPS timer!\n");

	/* Rejestracja timera jako Ÿród³o eventów */
	al_register_event_source(queue, al_get_timer_event_source(timer_FPS));

	
	/* Instalacja klawiatury i myszy */
	al_install_keyboard();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_install_mouse();
	al_register_event_source(queue, al_get_mouse_event_source());

	al_init_image_addon();

	srand(NULL);
}

ALLEGRO_BITMAP* Engine::GetBuffer() {
	return buffer;
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

	/* Pêtla g³ówna */
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
	/* Wys³anie eventu do zmiennej event, w razie jego wyst¹pienie. */
	al_wait_for_event(queue, &event);

	/* Obs³uga eventu w zale¿noœci od jego typu. */
	switch (event.type)
	{

		/* Wy³¹czenie programu po nacisniêciu przycisku wyjœcia. */
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		loop = false;
		break;

		/* Odœwie¿enie display. */
	case ALLEGRO_EVENT_TIMER:
		time++;
		spriteObject->draw(buffer);
		Render();
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		spriteObject->x = rand() % 600;
		spriteObject->y = rand() % 400;
		break;
	case ALLEGRO_EVENT_KEY_CHAR:
		switch (event.keyboard.keycode) {
		case 23:
			spriteObject->y-=15;
			break;
		case 1:
			spriteObject->x -= 15;
			break;
		case 19:
			spriteObject->y += 15;
			break;
		case 4:
			spriteObject->x += 15;
			break;
		}
		break;
	
	default: break;
	}
}
