#ifndef RESOURCES_H
#define RESOURCES_H

#include "Surface.h"
#include "Globals.h"
#include <String>
#include "../lpng1239/png.h"
#include "Sprite.h"


Sprite* PngToSprite(char *file_name);
Surface* PngToSurface(char *file_name);


#endif