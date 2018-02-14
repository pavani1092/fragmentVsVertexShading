#pragma once

#include "OpenGL.h"
#include "IDrawable.h"

namespace Crawfis 
{
	namespace Graphics
	{
		class DrawableSquare : public IDrawable
		{
		public:
			DrawableSquare() 
			{
			}
			virtual void Draw()
			{
				// TODO: Draw a conanical square
			}
		private:
		};
	}
}