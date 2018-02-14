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
		class PointLight : public ILight
		{
		public:
			PointLight()
			{
				this->position[0] = 0;
				this->position[1] = 10;
				this->position[2] = 0;
				this->position[3] = 1;
				setColor(Color(1,1,1,1));
			}

			PointLight(Crawfis::Math::Vector3 position)
			{
				this->position[0] = position.x;
				this->position[1] = position.y;
				this->position[2] = position.z;
				this->position[3] = 1;
				setColor(Color(1,1,1,1));
			}

			//
			// Enable the light.
			//
			virtual void Enable()
			{
				// TODO: Add this to the Light Manager and Enable it
				LightManager* l = LightManager::Instance();
				l->addLight(Vector4(position), Vector4(color));

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
			// Get the light position.
			//
			Crawfis::Math::Vector3 getPosition() const
			{
				return Crawfis::Math::Vector3(position);
			}
			//
			// Set the light position.
			//
			void setPosition(Crawfis::Math::Vector3 position)
			{
				this->position[0] = position.x;
				this->position[1] = position.y;
				this->position[2] = position.z;
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
			float position[4];
			float color[4];
		};
	}
}