#ifndef CTEXTURE_H
#define CTEXTURE_H

#define GL_GLEXT_PROTOTYPES

#include <vector> 
#include <string> 
using namespace std; 

#define NO_SDL_GLEXT
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include "GL/gl.h"
#include "GL/glu.h"

#define PNG 0 
#define JPG 1
#define BMP 2
#define TGA 3


class CTexture{ 
	private :
	string path; 		// path to image file
	int format; 		// image format : png, jpg, bmp, etc

	private :
	GLuint texture;
	GLenum texture_format;
	GLint nOfColors;

	
	public :
	int makeTexture( string Path, int Format ); 		// loads the image into memory and creates an OpenGL texture : returns 1 on success
	int bindTexture( ); 					// binds the texture for subsequent geometry to be drawn with : returns 1 on success
	void unbindTexture( ); 					// disables textures

};

#endif // CTEXTURE_H
