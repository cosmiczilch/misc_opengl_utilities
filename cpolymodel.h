#ifndef CPOLYMODEL_H
#define CPOLYMODEL_H

#include "vbo_Utilities.h"
#include "ctexture.h"
#include "miscUtils.h"

#include <string>

using namespace std;

#define RENDER_FLAGS__DEFAULT 0
#define RENDER_FLAGS__MAKE_NOW 1
#define RENDER_FLAGS__PANIC 2

class CPolyModel {
    public :
	CVBO_Model vbo;

	vector4f color;
	bool useColor;

	string texturePath;
	int format;
	bool useTexture;
	CTexture texture;

	void (* p_make_vbo_arrays) (void);

	bool ready_for_render;
	
	CPolyModel ();

	void initialize ( void (*make_vbo_arrays) (void) );
	void setTexture (string texturePath, int format);
	void setColor (vector4f color);
	void setColor (GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void make_ready_for_render ();
	void draw (int flags = RENDER_FLAGS__DEFAULT);
};

#endif // CPOLYMODEL_H
