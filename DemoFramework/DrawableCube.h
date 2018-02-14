#pragma once

#include "OpenGL.h"
#include "IDrawable.h"

namespace Crawfis
{
	namespace Graphics
	{
		class DrawableCube : public IDrawable
		{
		public:
			DrawableCube()
			{
				created = false;
			}
			virtual void Draw()
			{
				// TODO: Create VBO. Give each vertex or face a color and a normal. Use Indexed draw mode.
				InternalDraw();

			}
			void CreateCube() {
				static const GLfloat g_vertex_buffer_data[] = {
					// Front face
					-1.0, -1.0,  1.0,
					1.0, -1.0,  1.0,
					1.0,  1.0,  1.0,
					-1.0,  1.0,  1.0,

					// Back face
					-1.0, -1.0, -1.0,
					-1.0,  1.0, -1.0,
					1.0,  1.0, -1.0,
					1.0, -1.0, -1.0,

					// Top face
					-1.0,  1.0, -1.0,
					-1.0,  1.0,  1.0,
					1.0,  1.0,  1.0,
					1.0,  1.0, -1.0,

					// Bottom face
					-1.0, -1.0, -1.0,
					1.0, -1.0, -1.0,
					1.0, -1.0,  1.0,
					-1.0, -1.0,  1.0,

					// Right face
					1.0, -1.0, -1.0,
					1.0,  1.0, -1.0,
					1.0,  1.0,  1.0,
					1.0, -1.0,  1.0,

					// Left face
					-1.0, -1.0, -1.0,
					-1.0, -1.0,  1.0,
					-1.0,  1.0,  1.0,
					-1.0,  1.0, -1.0,
				};

				GLfloat color_array[] = {

					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,

					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,

					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,

					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,

					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,


					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,
					0.1, 0.1, 0.9,


				};


				unsigned int indices[] = {
					0,  1,  2,      0,  2,  3,    // front
					4,  5,  6,      4,  6,  7,    // back
					8,  9,  10,     8,  10, 11,   // top
					12, 13, 14,     12, 14, 15,   // bottom
					16, 17, 18,     16, 18, 19,   // right
					20, 21, 22,     20, 22, 23,   // left
				};
				GLfloat normals[] = {
					0.0 , 0.0, 1.0,  //front
					0.0 , 0.0, 1.0,  //front
					0.0 , 0.0, 1.0,  //front
					0.0 , 0.0, 1.0,  //front

					0.0 , 0.0,-1.0,   //back
					0.0 , 0.0,-1.0,   //back
					0.0 , 0.0,-1.0,   //back
					0.0 , 0.0,-1.0,   //back

					0.0 , 1.0, 0.0,  //top
					0.0 , 1.0, 0.0,  //top
					0.0 , 1.0, 0.0,  //top
					0.0 , 1.0, 0.0,  //top

					0.0 ,-1.0, 0.0,  //bottom
					0.0 ,-1.0, 0.0,  //bottom
					0.0 ,-1.0, 0.0,  //bottom
					0.0 ,-1.0, 0.0,  //bottom

					1.0 ,0.0, 0.0,  //right
					1.0 ,0.0, 0.0,  //right
					1.0 ,0.0, 0.0,  //right
					1.0 ,0.0, 0.0,  //right

					-1.0 , 0.0, 0.0,  //left
					-1.0 , 0.0, 0.0,  //left
					-1.0 , 0.0, 0.0,  //left
					-1.0 , 0.0, 0.0,  //left




				};

				GLuint VertexArrayID;
				glGenVertexArrays(1, &VertexArrayID);
				glBindVertexArray(VertexArrayID);

				//GLuint verticesBuffer;
				glGenBuffers(1, &verticesBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				//normalBuffer
				glGenBuffers(1, &normalBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				//colorBuffer
				glGenBuffers(1, &colorBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(color_array), color_array, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				//indicesBuffer;
				glGenBuffers(1, &indicesBuffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				//created = true;
			}
			void InternalDraw()
			{
				if (!created)
				{
					CreateCube();
				}
				//binding vertex array
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

				//binding color array
				glEnableVertexAttribArray(1);
				glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

				//binding normal array
				glEnableVertexAttribArray(2);
				glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(2);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		private:
			bool created;
			GLuint verticesBuffer;
			GLuint indicesBuffer;
			GLuint colorBuffer;
			GLuint normalBuffer;
		};
	}
}