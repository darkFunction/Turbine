#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Surface.h"
#include "Types.h"
#include <String>
#include "Image.h"
#include <map>
#include "Vector2D.h"

typedef std::map<std::string, Surface*> SurfaceByName;
typedef std::pair<std::string, Surface*> SurfaceNamePair;
typedef std::map<std::string, Image*> ImageByName;
typedef std::pair<std::string, Image*> ImageNamePair;

class ResourceManager
{
public:

	ResourceManager();
	~ResourceManager();
	Image* LoadImage(const std::string &path);
	void GenerateTextures(const Vector2i &maxSize);

protected:


private:
	
	SurfaceByName _loadedSurfaces;
	ImageByName	 _loadedImages;

	
	Surface* PngToSurface(const char *file_name);


};

#endif