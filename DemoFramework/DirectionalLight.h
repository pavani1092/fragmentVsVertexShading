#pragma once

#include "ILight.h"
#include "Vector.h"
#include "Color.h"
#include "LightManager.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Pure Abstract base class for all material or effects
		//
		class DirectionalLight : public ILight
		{
		public:
			DirectionalLight()
			{
				this->direction[0] = 0;
				this->direction[1] = 1;
				this->direction[2] = 0;
				this->direction[3] = 0;
				setColor(Color(1,1,1,1));
			}

			DirectionalLight(Crawfis::Math::Vector3 direction)
			{
				this->direction[0] = direction.x;
				this->direction[1] = direction.y;
				this->direction[2] = direction.z;
				this->direction[3] = 0;
				setColor(Color(1,1,1,1));
			}

			//
			// Enable the light.
			//
			virtual void Enable()
			{
				// TODO: Add this to the Light Manager and Enable it
				LightManager* l = LightManager::Instance();
				l->addLight(Vector4(direction), Vector4(color));
			}
			//
			// Disable the light.
			//
			virtual void Disable()
			{
				// TODO: Disable the light using the Light Manager
				LightManager* l = LightManager::Instance();
				//l->popLight();
			}
			//
			// Get the light direction.
			//
			Crawfis::Math::Vector3 getDirection() const
			{
				return Crawfis::Math::Vector3(direction);
			}
			//
			// Set the light direction.
			//
			void setDirection(Crawfis::Math::Vector3 direction)
			{
				this->direction[0] = direction.x;
				this->direction[1] = direction.y;
				this->direction[2] = direction.z;
			}
			//
			// Get the light color.
			//
			Color getColor() const
			{
				return Color(color);
			}
			//
			// Set the light color.
			//
			void setColor(Color color)
			{
				this->color[0] = color.r;
				this->color[1] = color.g;
				this->color[2] = color.b;
				this->color[3] = color.a;
			}

		private:
			float direction[4];
			float color[4];
		};
	}
}