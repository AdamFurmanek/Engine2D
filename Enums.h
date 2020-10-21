#ifndef Enums_h
#define Enums_h

#define Black al_map_rgb(0, 0, 0)
#define White al_map_rgb(255,255,255)
#define Red al_map_rgb(255,0,0)
#define DarkRed al_map_rgb(100,0,0)
#define Green al_map_rgb(0,255,0)
#define DarkGreen al_map_rgb(0,100,0)
#define Blue al_map_rgb(0,0,255)
#define DarkBlue al_map_rgb(0,0,100)
#define Orange al_map_rgb(255,100,0)
#define Magenta al_map_rgb(255,0,255)
#define Yellow al_map_rgb(255,255,0)

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

enum direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

#endif