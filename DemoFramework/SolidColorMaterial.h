#pragma once

#include "OpenGL.h"

#include "IMaterial.h"
#include "DepthTestedRasterOps.h"
#include "ShaderProgram.h"
#include "Color.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Concrete implementation of IMaterial.
		//   - Set all fragments to a solid color.
		//   - standard depth testing
		// Old - Delete
		//
		class SolidColorMaterial : public IMaterial
		{
		public:
			//
			// Constructor.
			//
			SolidColorMaterial( Color color)
			{
				this->color = color;
				this->shaderProgram = new ShaderProgram();
				this->rasterOps = new DepthTestedRasterOps();
			}
			//
			// Enable the material.
			//
			virtual void Enable()
			{
				glColor4f( color.r, color.g, color.b, color.a );
				glPushAttrib(GL_ENABLE_BIT);
				glDisable(GL_LIGHTING);
				shaderProgram->Enable();
				rasterOps->Enable();
			}
			//
			// Disable the material. This will be a no-op for our system, since
			// we will require these to be set at the beginning of every material
			// when it is enabled.
			//
			virtual void Disable()
			{
				glPopAttrib();
			}
		private:
			IRasterOps* rasterOps;
			IShaderProgram* shaderProgram;
			Color color;
		};
	}
}