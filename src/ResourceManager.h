#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Surface.h"
#include "Types.h"
#include <String>
#include "Image.h"
#include "Vector2D.h"
#include <vector>

typedef std::pair<Image*, Surface*> ImageSurfacePair;

class ResourceManager
{
public:

	ResourceManager();
	~ResourceManager();
	Image* LoadImage(const std::string &path);
	void GenerateTextures(const Vector2i &maxSize);

protected:


private:
	
	std::vector<ImageSurfacePair> _preloadData;
	std::vector<Image*> _loadedImages;

	Surface* PngToSurface(const char *file_name);


};

#endif