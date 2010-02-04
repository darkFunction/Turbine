#ifndef SURFACE_PACKER_H
#define SURFACE_PACKER_H

#include <vector>
#include "Platform.h"
#include "Surface.h"


class SurfacePacker
{
public:
	std::vector<Surface*>* CreatePackedSurfaces(std::vector<Surface*> aSurfaces);

private:

};

#endif