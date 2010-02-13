#include "ResourceManager.h"

#include <iostream>
#include <fstream>
#include "../third_party/PicoPNG/picopng.h"
#include "Rect.h"

using namespace std;

// Texture atlas packing algorithm
struct Node
{
    Node **children;
    Rect rect;  
	boolean bTaken;

	Node()
	{
		children = NULL;
		bTaken = false;
	}

	~Node()
	{
		if (children)
			delete[] children;
	}

	Node* Insert(const Rect &aRect)
	{
		if (children) // not  a leaf
		{
			// try inserting into first child
			Node* node = children[0]->Insert(aRect);
			if (node)
				return node;

			// no room, insert into second
			return children[1]->Insert(aRect);
		}
		else 
		{
			if (bTaken)
				return NULL;
			
			if (	aRect.width > this->rect.width
				||	aRect.height > this->rect.height)
			{
				// node is too small, rect can't fit inside
				return NULL;
			}
			
			if (	aRect.width == this->rect.width
				&&	aRect.height == this->rect.height)
			{
				// fits perfectly
				this->bTaken = true;
				return this;
			}

			// otherwise split node and create kids
			children = new Node*[2];
			children[0] = new Node();
			children[1] = new Node();

			// decide which way to split
			int dw = this->rect.width - aRect.width;
			int dh = this->rect.height - aRect.height;

			if (dw > dh)
			{
				children[0]->rect = Rect(	this->rect.x,
											this->rect.y,                       
											aRect.width,
											this->rect.height);

				children[1]->rect = Rect(	this->rect.x + aRect.width,
											this->rect.y,                       
											this->rect.width - aRect.width,
											this->rect.height);
			}
			else
			{
				children[0]->rect = Rect(	this->rect.x,
											this->rect.y,
											this->rect.width,
											aRect.height);

				children[1]->rect = Rect(	this->rect.x,
											this->rect.y + aRect.height,
											this->rect.width,
											this->rect.height - aRect.height);
			}

			// insert into first child we created
			return children[0]->Insert(aRect);
		}
	}

};

// takes ownership of image data
Image* ResourceManager::LoadImage(const string &aPath)
{
	Surface* pSurface = PngToSurface(aPath.c_str());
	
	Image* pImage = NULL;

	if (pSurface)
	{
		pImage = new Image();
		pImage->_pPathName = aPath;
		pImage->_width = pSurface->GetWidth();
		pImage->_height = pSurface->GetHeight();

		_preloadData.push_back(ImageSurfacePair(pImage, pSurface));
	}

	return pImage;
}

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	while(!_preloadData.empty())
	{
		vector<ImageSurfacePair>::const_iterator it = _preloadData.begin();
		delete it->first;
		it->second->Destroy();		
		_preloadData.erase(it);
	}	
}



void ResourceManager::GenerateTextures(const Vector2i &maxSize)
{ 
	// sort by size
	for (uint16 i=0; i<_preloadData.size()-1; ++i)
	{
		Surface* s1 = _preloadData[i].second;
		Surface* s2 = _preloadData[i+1].second;

		if (s1->GetArea() < s2->GetArea())
		{
			Surface* temp = s1;
			s1 = s2;
			s2 = s1;
		}
	}

	vector<Surface*> masterTextures;

	int masterTextureCount = 0;
	while(!_preloadData.empty() && masterTextureCount < MAX_TEXTURES)
	{
		Surface* masterSurface = new Surface(NULL, maxSize.x, maxSize.y, 4);
		masterTextureCount ++;
		vector<Image*> imagesOnSurface;

		Node rootNode;
		rootNode.rect = Rect(0, 0, maxSize.x, maxSize.y);

		for (vector<ImageSurfacePair>::iterator it = _preloadData.begin(); it != _preloadData.end();)
		{
			Image* image = it->first;
			Surface* surface = it->second;

			Rect rect = Rect(0, 0, surface->GetWidth(), surface->GetHeight());
			Node* node = rootNode.Insert(rect);
			if (node)
			{		
				// we managed to fit it inside the master texture
				rect = node->rect;
				masterSurface->BlitSurface(surface, rect.x, rect.y);
				surface->Destroy();
				imagesOnSurface.push_back(image);				
				
				image->_textureX = (float)rect.x / masterSurface->GetWidth();
				image->_textureY = (float)rect.y / masterSurface->GetHeight();
				image->_textureW = (float)rect.width / masterSurface->GetWidth();
				image->_textureH = (float)rect.height / masterSurface->GetHeight();
				
				it = _preloadData.erase(it);				
			}
			else
				++it;
		}

		// OpenGl has reversed Y axis
		masterSurface->FlipY();

		GLuint texture = masterSurface->CreateGLTexture();
		masterSurface->Destroy();
		
		for (uint16 i=0; i<imagesOnSurface.size(); ++i)
		{
			imagesOnSurface[i]->_texture = texture;
		}
	}
}


// from picoPNG...
void loadFile(std::vector<unsigned char>& buffer, const std::string& filename) //designed for loading files from hard disk in an std::vector
{
	std::ifstream file(filename.c_str(), std::ios::in|std::ios::binary|std::ios::ate);

	//get filesize
	std::streamsize size = 0;
	if(file.seekg(0, std::ios::end).good()) size = file.tellg();
	if(file.seekg(0, std::ios::beg).good()) size -= file.tellg();

	//read contents of the file into the vector
	if(size > 0)
	{
	buffer.resize((size_t)size);
	file.read((char*)(&buffer[0]), size);
	}
	else buffer.clear();
}

/* Read a PNG file. */
Surface* ResourceManager::PngToSurface(const char *aFile_name)  
{
	//load and decode
	std::vector<unsigned char> buffer, image;
	loadFile(buffer, aFile_name);
	unsigned long w, h;
	int error = decodePNG(image, w, h, buffer.empty() ? 0 : &buffer[0], (unsigned long)buffer.size());
	
	// image now contains 32 bit png... that was easier than libPNG :)

	if(error != 0)
		return NULL;
	
	return new Surface(&image[0], w, h, 4);
}


