#pragma once

#include "IDrawableNode.h"
#include "RenderState.h"
#include "Vector.h"
#include "Color.h"
#include <sstream>
#include <string>
#include "MaterialManager.h"
#include "MatrixManager.h"

using namespace Crawfis::Math;

namespace Crawfis
{
	namespace Graphics
	{
		//
		// Concrete implementation of IDrawableNode
		// Draws text strings on the screen indicating the rendering
		// state (fps, ...).
		//
		class DrawableRenderState : public IDrawableNode
		{
		public:
			//
			// Constructor.
			//   All names should be unique.
			//   The model name should refer to a registered model.
			//
			DrawableRenderState(std::string name)
			{
				this->name = name;
				position = Vector3(0.2f, 0.4f, 0.9f);
				textColor = Color(0.1, 0.1, 0.9, 1);
			}
			// 
			// Draw the model.
			//
			void Draw()
			{
				RenderState::UpdateState();
				int fps = RenderState::FPS();
				glPushMatrix();
				glTranslatef(position.x, position.y, position.z);

				std::ostringstream stringStream;
				stringStream.precision(4);
				stringStream << "Pavani Komati ";
				//pavani 
				//glColor4f( textColor.r, textColor.g, textColor.b, textColor.a);
				RenderString(stringStream.str());
				glPopMatrix();
			}
			//
			// Get and Set the Position
			//
			Vector3 getPosition() const
			{
				return position;
			}
			void setPosition(Vector3 position)
			{
				this->position = position;
			}
			//
			// Get and set the Color
			//
			Color getColor() const
			{
				return textColor;
			}
			void setColor(Color textColor)
			{
				this->textColor = textColor;
			}
			//
			// Overrrided from ISceneNode
			//
			virtual std::string ToString()
			{
				return name;
			}

		private:
			void RenderString(std::string string)
			{
				glRasterPos2f(position.x, position.y);
				for (const char *c = string.c_str(); *c != '\0'; c++)
				{
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
					//glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
				}
			}

		private:
			std::string name;
			Crawfis::Math::Vector3 position;
			Color textColor;
		};
	}
}