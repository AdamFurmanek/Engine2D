#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

enum resolution
{
	/* 640x480 */
	VGA,
	/* 800x600 */
	SVGA,
	/* 1280x720 */
	HD,
	/* 1920x1080 */
	FULLHD
};

class Engine
{
private:
	static Engine* engine;
	/* Wskaünik ekranu */
	ALLEGRO_DISPLAY* display;
	/* Wskaünik kolejki eventÛw */
	ALLEGRO_EVENT_QUEUE* queue;
	/* Wskaünik eventu */
	ALLEGRO_EVENT event;
	/* Wskaünik timera */
	ALLEGRO_TIMER* timer_FPS;
	/* Zmienna kontynuuacji pÍtli */
	bool loop;

	/* Zmienna liczπca czas dzia≥ania (iloúÊ sekund*30) */
	int time;

	/* Buffer ekranu */
	ALLEGRO_BITMAP* buffer;

	/* Konstruktor */
	Engine();
	/* Dekonstruktor */
	~Engine();

public:
	static Engine* GetInstance();
	void Init(string Title, bool fullscreen, resolution res);
	ALLEGRO_BITMAP* GetBuffer();
	void Exception(string Error);
	void MainLoop();
	void Render();
	void Events();

};

