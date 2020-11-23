#include "Engine.h"

using namespace std;

Engine* Engine::engine = NULL;
///Wywo³anie potrzebnych podstawowych pól dla silnika i nadanie im wartoœci pocz¹tkowych 
Engine::Engine()
{
	queue = NULL;
	timer_FPS = NULL;
	buffer = NULL;
	time = 0;
}
/// Zwolnienie pamiêci
Engine::~Engine() {
	al_destroy_display(display);
	al_destroy_bitmap(buffer);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer_FPS);
}
/// Metoda zwracaj¹ca singleton klasy Engine
/// <returns>engine</returns>
Engine* Engine::GetInstance() {
    if (Engine::engine == NULL)
        Engine::engine = new Engine();
    return Engine::engine;
}
/// Funkcja inicjuj¹ca/tworz¹ca wszystkie aspekty silnika(tak jak w zwyk³ych komentarzach kodu po kolei): Inicjalizacja biblioteki Allegro 5; Utworzenie kolejki eventów; Inicjalizacja prymitywów; Ustawienie fullscreena; Ustawienie rozdzielczoœci; Utworzenie bufora; Utworzenie ekranu; Ustawienie nazwy okna; Rejestracja display jako Ÿród³o eventów; Utworzenie timera; Rejestracja timera jako Ÿród³o eventów; Instalacja klawiatury i myszy
/// <param name="Title">zmienna przechowywuj¹ca tytu³ okna</param>
/// <param name="fullscreen">zmienna ustawiaj¹ca fullscreen</param>
/// <param name="res">zmienna zawieraj¹ca parê przyk³adowych rozdzielczoœci (FULLHD, HD, SVGA, VGA)</param>
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
	timer_FPS = al_create_timer(1.0 / 10);
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
/// Metoda zwracaj¹ca buffer
/// <returns>buffer</returns>
ALLEGRO_BITMAP* Engine::GetBuffer() {
	return buffer;
}
/// Funkcja wyœwietlaj¹ca napotkany problem oraz jego przyczynê
/// <param name="Error">przechowujê informacjê o wyst¹pionym b³êdzie</param>
void Engine::Exception(string Error) {
    al_show_native_message_box(NULL,"Error",Error.c_str(),"The program has been stopped.",NULL,ALLEGRO_MESSAGEBOX_ERROR);
	exit(0);
}
/// Funkcja zawieraj¹ca g³ówn¹ pêtlê s³u¿¹c¹ do uruchamiania licznika czasu i zdarzeñ
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
/// Funkcja renderuj¹ca ekran
void Engine::Render() {
	spriteObject->Destination(15);
	al_set_target_backbuffer(display);
	al_draw_bitmap(buffer, 0, 0, NULL);
	al_flip_display();
}
/// Funkcja dla wystêpuj¹cych zdarzeñ, wykonuje(tak jak w zwyk³ych komentarzach kodu po kolei): Wys³anie eventu do zmiennej event, w razie jego wyst¹pienia; Wy³¹czenie programu po nacisniêciu przycisku wyjœcia; Odœwie¿enie display
void Engine::Events() {
	/* Wys³anie eventu do zmiennej event, w razie jego wyst¹pienia. */
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
		/* Test obiektu sprite Object - klikniêcie wylosuje jego nowe wspó³rzêdne */
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		spriteObject->moveDestination(event.mouse.x, event.mouse.y);
		break;
		/* Test obiektu sprite Object - klawisze WASD - pozwalaj¹ poruszaæ obiektem */
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
