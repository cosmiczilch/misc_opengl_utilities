#include "cpolymodel.h"

CPolyModel::CPolyModel () {
	useTexture = useColor = false;
	ready_for_render = false;

	return;
}

void CPolyModel::initialize ( void (*make_vbo_arrays) (void) ) {
	// caller would have passed in a function pointer which will
	// write the verts, normals, colors, textures, indices etc arrays
	// required to make the vbo
	this->p_make_vbo_arrays = make_vbo_arrays;

	return;
}

void CPolyModel::setTexture (string texturePath, int format) {
	this->texturePath = texturePath;
	this->format = format;
	useTexture = true;

	return;
}

void CPolyModel::setColor (vector4f color) {
	this->color.values[R] = color.values[R];
	this->color.values[G] = color.values[G];
	this->color.values[B] = color.values[B];
	this->color.values[A] = color.values[A];
	useColor = true;

	return;
}

void CPolyModel::setColor (GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	this->color.values[R] = r;
	this->color.values[G] = g;
	this->color.values[B] = b;
	this->color.values[A] = a;
	useColor = true;

	return;
}

void CPolyModel::make_ready_for_render () {
	// Prepare the vbo arrays using the function pointer
	p_make_vbo_arrays ();

	// Now, call make_VBOs ()
	vbo.make_VBOs ();

	// make the texture, if applicable
	if (useTexture) {
		texture.makeTexture (texturePath.c_str (), format);
	}

	ready_for_render = true;

	return;
}

void CPolyModel::draw (int flags) {
	if (!ready_for_render) {
		switch (flags) {
			case RENDER_FLAGS__DEFAULT : return;
			case RENDER_FLAGS__MAKE_NOW : this->make_ready_for_render (); break;
			case RENDER_FLAGS__PANIC : ASSERT (0, "render called with vbo unmade");
		}
	}

	if (useTexture) {
		texture.bindTexture ();
	}

	if (useColor) {
		glColor4f (color.values[R], color.values[G], color.values[B], color.values[A]);
	}

	vbo.draw ();

	return;
}

