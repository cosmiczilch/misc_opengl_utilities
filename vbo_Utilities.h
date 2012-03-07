#ifndef VBO_UTILITIES_H
#define VBO_UTILITIES_H

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glu.h>

#include "glext.h"
#include "glInfo.h"

#include <cstdlib>

#define X 0
#define Y 1
#define Z 2
#define W 3

#define R 0
#define G 1
#define B 2
#define A 3

#define U 0
#define V 1

/* Currently only GL_QUADS are supported */
#define NUM_VERTS_PER_FACE 4

struct vector4f {
	GLfloat values[4];
}; 

struct vector3f {
	GLfloat values[3];
}; 

struct vector2f {
	GLfloat values[2];
}; 

class CVBO_Model {

    private :

	GLuint vertex_vbo;
	GLuint normal_vbo;
	GLuint color_vbo;
	GLuint texture_vbo;

	GLuint index_vbo;

    public : 

	int numVertices;
	int numFaces;

    	vector4f *vertices;
    	vector3f *normals;
    	vector4f *colors;
    	vector2f *textures;

	GLuint *indices;

	bool use_normals;
	bool use_colors;
	bool use_textures;

	bool ready_for_render;		// will be true after a call to make_VBOs ()
	// Constructor : 
	CVBO_Model ();

	// vertex attrib functions : 
	void bulk_init_vertices (int numVertices, vector4f Vertices[]);
	void bulk_init_normals (int numVertices, vector3f Normals[]);
	void bulk_init_colors (int numVertices, vector4f Colors[]);
	void bulk_init_textures (int numVertices, vector2f Textures[]);

	void add_vertex (vector4f *Vertex, vector3f *Normal, vector4f *Color, vector2f *Texture);

	void set_vertex (int vertex_idx, vector4f Vertex);
	void set_normal (int vertex_idx, vector3f Normal);
	void set_color (int vertex_idx, vector4f Color);
	void set_texture (int vertex_idx, vector2f Texture);

	// indices functions : 
	void bulk_init_indices (int numFaces, GLuint Indices[]);
	void add_face (GLuint face_indices[NUM_VERTS_PER_FACE]);

	void make_VBOs ();

	void draw ();

};

#endif // VBO_UTILITIES_H

