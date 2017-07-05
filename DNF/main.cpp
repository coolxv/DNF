#include <iostream> 
#include <time.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/opencv.hpp>
#include "Game.h"
#include "OtherObject.h"
using namespace cv;
CGame game;

void onMouse(int Event, int x, int y, int flags, void* param)
{
	game.onMouse(Event, x, y, flags, param);
}
int main()
{
	srand(unsigned(time(0)));
	cvNamedWindow("DNF");
	cvSetMouseCallback("DNF", &onMouse, NULL);
	game.Run();
	return 0;
}
