#include "SurfacePacker.h"

using namespace std;

/*
struct Node
{
    Node* child[2];
    Rectangle rc;
    int imageID;
}
        */

vector<Surface*>* SurfacePacker::CreatePackedSurfaces(vector<Surface*> aSurfaces)
{
	vector<Surface*>* masterSurfaces = new vector<Surface*>();

		


	return masterSurfaces;
}
/*
int32 TextureCache::Insert(const Image& img)
{
    pnode = m_root->Insert(img)
    if pnode != NULL
        copy pixels over from img into pnode->rc part of texture
        pnode->imageID = new handle
    else
       return INVALID_HANDLE
}
*/

/*
Node* Node::Insert(const Image& img)
{
    if we're not a leaf then
        (try inserting into first child)
        newNode = child[0]->Insert( img )
        if newNode != NULL return newNode
        
        (no room, insert into second)
        return child[1]->Insert( img )
    else
        (if there's already a lightmap here, return)
        if imageID != NULL return NULL

        (if we're too small, return)
        if img doesn't fit in pnode->rect
            return NULL

        (if we're just right, accept)
        if img fits perfectly in pnode->rect
            return pnode
        
        (otherwise, gotta split this node and create some kids)
        pnode->child[0] = new Node
        pnode->child[1] = new Node
        
        (decide which way to split)
        dw = rc.width - img.width
        dh = rc.height - img.height
        
        if dw > dh then
            child[0]->rect = Rectangle(rc.left, rc.top, 
                                       rc.left+width-1, rc.bottom)
            child[1]->rect = Rectangle(rc.left+width, rc.top, 
                                       rc.right, rc.bottom)
        else
            child[0]->rect = Rectangle(rc.left, rc.top, 
                                       rc.right, rc.top+height-1)
            child[1]->rect = Rectangle(rc.left, rc.top+height, 
                                       rc.right, rc.bottom)
        
        (insert into first child we created)
        return Insert( img, pnode->child[0] )
}
*/