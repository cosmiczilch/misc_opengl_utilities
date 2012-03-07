#include "vbo_Utilities.h"

// Constructor : 
CVBO_Model::CVBO_Model () {
	use_normals = false;
	use_colors = false;
	use_textures = false;

	ready_for_render = false;

	return;
}

// vertex attrib functions : 

void CVBO_Model::bulk_init_vertices (int numVertices, vector4f Vertices[]) {
	this->numVertices = numVertices;
	vertices = (vector4f *)malloc (sizeof(vector4f) * numVertices);

	for (int i=0; i<numVertices; i++) {
		for (int j=0; j<4; j++) {
			vertices[i].values[j] = Vertices[i].values[j];
		}
	}

	return;
}

void CVBO_Model::bulk_init_normals (int numVertices, vector3f Normals[]) {
	this->numVertices = numVertices;
	normals = (vector3f *)malloc (sizeof (vector3f) * numVertices);

	for (int i=0; i<numVertices; i++) {
		for (int j=0; j<3; j++) {
			normals[i].values[j] = Normals[i].values[j];
		}
	}

	use_normals = true;

	return;
}

void CVBO_Model::bulk_init_colors (int numVertices, vector4f Colors[]) {
	this->numVertices = numVertices;
	colors = (vector4f *)malloc (sizeof(vector4f) * numVertices);

	for (int i=0; i<numVertices; i++) {
		for (int j=0; j<4; j++) {
			colors[i].values[j] = Colors[i].values[j];
		}
	}

	use_colors = true;

	return;
}

void CVBO_Model::bulk_init_textures (int numVertices, vector2f Textures[]) {
	this->numVertices = numVertices;
	textures = (vector2f *)malloc (sizeof(vector2f) * numVertices);

	for (int i=0; i<numVertices; i++) {
		for (int j=0; j<2; j++) {
			textures[i].values[j] = Textures[i].values[j];
		}
	}

	use_textures = true;

	return;
}

void CVBO_Model::add_vertex (vector4f *Vertex, vector3f *Normal, vector4f *Color, vector2f *Texture) {
	vertices = (vector4f *)realloc (vertices, sizeof (vector4f) * (numVertices +1));
	normals = (vector3f *)realloc (normals, sizeof (vector3f) * (numVertices +1));
	colors = (vector4f *)realloc (colors, sizeof (vector4f) * (numVertices +1));
	textures = (vector2f *)realloc (textures, sizeof (vector2f) * (numVertices +1));

	for (int j=0; j<4; j++) {
		if (Vertex != NULL) {
			vertices[numVertices].values[j] = Vertex->values[j];
		}
		if (Color != NULL) {
			colors[numVertices].values[j] = Color->values[j];
		}
	}
	for (int j=0; j<3; j++) {
		if (Normal != NULL) {
			normals[numVertices].values[j] = Normal->values[j];
		}
	}
	for (int j=0; j<2; j++) {
		if (Texture != NULL) {
			textures[numVertices].values[j] = Texture->values[j];
		}
	}

	if (Normal)	{ use_normals = true; }
	if (Color)	{ use_colors = true; }
	if (Texture)	{ use_textures = true; }

	numVertices++;

	return;
}

void CVBO_Model::set_vertex (int vertex_idx, vector4f Vertex) {
	for (int j=0; j<4; j++) {
		vertices[vertex_idx].values[j] = Vertex.values[j];
	}

	return;
}

void CVBO_Model::set_normal (int vertex_idx, vector3f Normal) {
	for (int j=0; j<3; j++) {
		normals[vertex_idx].values[j] = Normal.values[j];
	}

	return;
}

void CVBO_Model::set_color (int vertex_idx, vector4f Color) {
	for (int j=0; j<4; j++) {
		colors[vertex_idx].values[j] = Color.values[j];
	}

	return;
}

void CVBO_Model::set_texture (int vertex_idx, vector2f Texture) {
	for (int j=0; j<2; j++) {
		textures[vertex_idx].values[j] = Texture.values[j];
	}

	return;
}


// indices functions : 
void CVBO_Model::bulk_init_indices (int numFaces, GLuint Indices[]) {
	this->numFaces = numFaces;
	indices = (GLuint *)malloc (sizeof(GLuint) * numFaces * NUM_VERTS_PER_FACE);

	for (int i=0; i < (numFaces * NUM_VERTS_PER_FACE); i++) {
		indices[i] = Indices[i];
	}

	return;
}

void CVBO_Model::add_face (GLuint face_indices[NUM_VERTS_PER_FACE]) {
	indices = (GLuint *)realloc (indices, sizeof(GLuint) * (numFaces + 1) * NUM_VERTS_PER_FACE);

	for (int i=numFaces; i < (numFaces + NUM_VERTS_PER_FACE); i++) {
		indices[i] = face_indices[i-numFaces];
	}

	numFaces++;

	return;
}
	

void CVBO_Model::make_VBOs () {
	if (vertex_vbo == (GLuint)0) {
		glGenBuffersARB (1, &vertex_vbo);
		glBindBufferARB (GL_ARRAY_BUFFER_ARB, vertex_vbo);
		glBufferDataARB (GL_ARRAY_BUFFER_ARB, sizeof(vector4f) * numVertices, vertices, GL_STATIC_DRAW_ARB);
	}

	if (use_normals && normal_vbo == (GLuint)0) {
		glGenBuffersARB (1, &normal_vbo);
		glBindBufferARB (GL_ARRAY_BUFFER_ARB, normal_vbo);
		glBufferDataARB (GL_ARRAY_BUFFER_ARB, sizeof(vector3f) * numVertices, normals, GL_STATIC_DRAW_ARB);
	}

	if (use_colors && color_vbo == (GLuint)0) {
		glGenBuffersARB (1, &color_vbo);
		glBindBufferARB (GL_ARRAY_BUFFER_ARB, color_vbo);
		glBufferDataARB (GL_ARRAY_BUFFER_ARB, sizeof(vector4f) * numVertices, colors, GL_STATIC_DRAW_ARB);
	}

	if (use_textures && texture_vbo == (GLuint)0) {
		glGenBuffersARB (1, &texture_vbo);
		glBindBufferARB (GL_ARRAY_BUFFER_ARB, texture_vbo);
		glBufferDataARB (GL_ARRAY_BUFFER_ARB, sizeof(vector2f) * numVertices, textures, GL_STATIC_DRAW_ARB);
	}


	if (index_vbo == (GLuint)0) {
		glGenBuffersARB (1, &index_vbo);
		glBindBufferARB (GL_ELEMENT_ARRAY_BUFFER_ARB, index_vbo);
		glBufferDataARB (GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(GLuint) * numFaces * NUM_VERTS_PER_FACE, indices, GL_STATIC_DRAW_ARB);
	}

	ready_for_render = true;

	return;
}

void CVBO_Model::draw () {
	if (!ready_for_render) {
		return;
	}

	glBindBufferARB (GL_ARRAY_BUFFER_ARB, vertex_vbo);
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer (4, GL_FLOAT, 0, 0);

	if (use_normals) {
		glBindBufferARB (GL_ARRAY_BUFFER_ARB, normal_vbo);
		glEnableClientState (GL_NORMAL_ARRAY);
		glNormalPointer (GL_FLOAT, 0, 0);
	}

	if (use_colors) {
		glBindBufferARB (GL_ARRAY_BUFFER_ARB, color_vbo);
		glEnableClientState (GL_COLOR_ARRAY);
		glColorPointer (4, GL_FLOAT, 0, 0);
	}

	if (use_textures) {
		glBindBufferARB (GL_ARRAY_BUFFER_ARB, texture_vbo);
		glEnableClientState (GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer (2, GL_FLOAT, 0, 0);
	}

	glBindBufferARB (GL_ELEMENT_ARRAY_BUFFER_ARB, index_vbo);
	glEnableClientState(GL_INDEX_ARRAY);
	glDrawElements (GL_QUADS, numFaces * NUM_VERTS_PER_FACE, GL_UNSIGNED_INT, 0);

	return;
}

