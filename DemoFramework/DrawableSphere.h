#pragma once

#include "OpenGL.h"
#include "IDrawable.h"
#include <math.h>

namespace Crawfis
{
	namespace Graphics
	{
		class DrawableSphere : public IDrawable
		{
		public:



			DrawableSphere(int desiredNumberOfTriangles, bool wireframe)
			{
				int subdivisions = (int)sqrtf(desiredNumberOfTriangles / 2);
				numberOfLongitudeSlices = subdivisions < minSubdivision ? minSubdivision : subdivisions;
				this->wireframe = wireframe;

				created = false;
				displayList = 0;
				CreateSphere();

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			virtual void Draw()
			{
				InternalDraw();
			}
		private:


			std::vector<float> vertices;
			std::vector<float> normals;
			std::vector<Vector3>colors;
			void Normalize3(GLfloat *v)
			{
				GLfloat length = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
				v[0] /= length;
				v[1] /= length;
				v[2] /= length;
			}



			void Tesselate(int level, float p_radius, GLfloat* a, GLfloat* b, GLfloat* c)
			{
				if (level > 1)
				{
					//calculating the mid points of all sides.
					GLfloat d[3] = { a[0] + b[0], a[1] + b[1], a[2] + b[2] };
					GLfloat e[3] = { b[0] + c[0], b[1] + c[1], b[2] + c[2] };
					GLfloat f[3] = { c[0] + a[0], c[1] + a[1], c[2] + a[2] };

					Normalize3(d);
					Normalize3(e);
					Normalize3(f);

					//Tesselating the sphere level by level considering the triangles formed by midpoints of sides
					Tesselate(level - 1, p_radius, a, d, f);
					Tesselate(level - 1, p_radius, d, b, e);
					Tesselate(level - 1, p_radius, f, e, c);
					Tesselate(level - 1, p_radius, f, d, e);
				}

				Vector3 vec1 = Vector3(a);
				Vector3 vec2 = Vector3(b);
				Vector3 vec3 = Vector3(c);
				// calculating the normal of each traingle by taking cross product
				Vector3 normal = cross(vec1 - vec3, vec2 - vec3);
				normal.normalize();

				normals.push_back(normal[0]);
				normals.push_back(normal[1]);
				normals.push_back(normal[2]);

				//making the vertices to lie on the sphere surface by multiplying with radius
				vertices.push_back(a[0] * p_radius);
				vertices.push_back(a[1] * p_radius);
				vertices.push_back(a[2] * p_radius);
				//assigning color to each vertex
				colors.push_back(Vector3(0.6, 0.1, 0.1));

				normals.push_back(normal[0]);
				normals.push_back(normal[1]);
				normals.push_back(normal[2]);
				vertices.push_back(b[0] * p_radius);
				vertices.push_back(b[1] * p_radius);
				vertices.push_back(b[2] * p_radius);
				colors.push_back(Vector3(0.6, 0.1, 0.1));

				normals.push_back(normal[0]);
				normals.push_back(normal[1]);
				normals.push_back(normal[2]);
				vertices.push_back(c[0] * p_radius);
				vertices.push_back(c[1] * p_radius);
				vertices.push_back(c[2] * p_radius);
				colors.push_back(Vector3(0.6, 0.1, 0.1));
			}


			void CreateSphere()
			{

				//two pyramids vertices
				GLfloat a[] = { 0.0f, 0.0f, 1.0f };
				GLfloat b[] = { 1.0f, 0.0f, 0.0f };
				GLfloat c[] = { 0.0f, 0.0f, -1.0f };
				GLfloat d[] = { 0.0f, 1.0f, 0.0f };
				GLfloat e[] = { -1.0f, 0.0f, 0.0f };
				GLfloat f[] = { 0.0f, -1.0f, 0.0f };

				int level = 5; // tesselating sphere upto 6 levela

				Tesselate(level, p_radius, a, b, d);
				Tesselate(level, p_radius, a, d, e);
				Tesselate(level, p_radius, a, e, f);
				Tesselate(level, p_radius, a, f, b);
				Tesselate(level, p_radius, b, c, d);
				Tesselate(level, p_radius, e, d, c);
				Tesselate(level, p_radius, f, e, c);
				Tesselate(level, p_radius, c, b, f);


				glGenVertexArrays(1, &vao);
				// Setup first Vertex Array Object
				glBindVertexArray(vao);
				// Allocate Vertex Buffer Object (get a handle or ID)
				glGenBuffers(1, &vbo);

				// VBO for vertex data
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				// Set the model data into the VBO.
				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
				// Define the layout of the vertex data.

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);


				//vbo for normals
				glGenBuffers(1, &normalbuffer);
				glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
				glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				//vbo for color
				glGenBuffers(1, &colorbuffer);
				glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
				glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(Vector3), &colors[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				//flag to avoid createing multiple times when already created
				created = true;


			}

			void InternalDraw() {

				if (!created)
					CreateSphere();

				//binding vertex
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);


				//binding normal
				glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
				glEnableVertexAttribArray(2);

				//binding color
				glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
				glEnableVertexAttribArray(1);

				glDrawArrays(GL_TRIANGLES, 0, vertices.size());

			}



		private:
			bool created;
			unsigned int displayList;
			int numberOfLongitudeSlices;
			bool wireframe;
			static const int minSubdivision = 10;
			const float p_radius = 1.0;
			unsigned int vao;
			unsigned int vbo;
			unsigned int normalbuffer;
			unsigned int colorbuffer;
		};
	}
}