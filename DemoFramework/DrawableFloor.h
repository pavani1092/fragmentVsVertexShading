#pragma once

#include "OpenGL.h"
#include "IDrawable.h"

namespace Crawfis 
{
	namespace Graphics
	{
		//
		// A concrete drawable representing a simple flat mesh.
		// The orientation is in the xz plane.
		//
		class DrawableFloor : public IDrawable
		{
		public:
			//
			// Constructor.
			//
			DrawableFloor(int numHorizontalSamples, int numVerticalSamples) 
			{
				this->numHorizontalSamples = numHorizontalSamples;
				this->numVerticalSamples = numVerticalSamples;
				created = false;
			}
			//
			// Draw the floor.
			//
			virtual void Draw()
			{
				InternalDraw();
			}
		private:
			void CreateFloor()
			{
				stripSize = 2 * numHorizontalSamples;
				vertices = new float*[numVerticalSamples-1];
				int index = 0;
				float y = -1.0f;
				float x = -1;
				float z = -1;
				float deltaX = 2.0f / (float) (numHorizontalSamples-1);
				float deltaZ = 2.0f / (float) (numVerticalSamples-1);
				for( int j = 0; j < (numVerticalSamples-1); j++ )
				{
					x = -1;
					vertices[j] = new float[3*stripSize];
					index = 0;
					for( int i = 0; i < numHorizontalSamples; i++ )
					{
						vertices[j][index++] = x;
						vertices[j][index++] = y;
						vertices[j][index++] = z;
						vertices[j][index++] = x;
						vertices[j][index++] = y;
						vertices[j][index++] = z + deltaZ;
						x += deltaX;
					}
					z += deltaZ;
				}
				created = true;
			}

			void InternalDraw()
			{
				if (!created)
				{
					CreateFloor();
				}
				//
				// Actually draw the floor
				//
				//glNormal3f(0,1,0);
				glEnableClientState(GL_VERTEX_ARRAY);
				for( int j=1; j < numVerticalSamples; j++ )
				{
					glVertexPointer(3, GL_FLOAT, 0, vertices[j-1]);
					glDrawArrays(GL_TRIANGLE_STRIP, 0, stripSize);
					//glDrawElements(GL_TRIANGLE_STRIP, indices.Length, GL_UNSIGNED_INT, indices);
				}

				glDisableClientState(GL_VERTEX_ARRAY);
			}
		private:
			int numHorizontalSamples;
			int numVerticalSamples;
			bool created;
			float** vertices;
			int stripSize;
		};
	}
}