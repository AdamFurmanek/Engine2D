#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <vector>

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

struct Point2D {
	int x;
	int y;
	ALLEGRO_COLOR c;
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
	void Exception(string Error);
	void MainLoop();
	void Render();
	void Events();

	void Clear();
	void DrawPixels(vector <Point2D> pixels);
	void DrawTriangle(Point2D a, Point2D b, Point2D c, ALLEGRO_COLOR co);
};

