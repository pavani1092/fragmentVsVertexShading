#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include <string>
#include "Vector.h"
#include <vector>

using namespace Crawfis::Math;
namespace Crawfis
{
	namespace Graphics
	{
		//
		// LightManager implements a Singleton design pattern for global
		// access and registration of Lights.
		//
		struct Light {
			Vector4 position;
			Vector4 intensity;
		};
		class LightManager
		{
		public:
			//
			// Get the one and only instance of the LightManager
			//
			static LightManager* Instance()
			{
				if (!created)
				{
					instance = new LightManager();
					created = true;
				}
				return instance;
			}

			void addLight(Vector4 position, Vector4 intensity) {
				Light light;
				light.position = position;
				light.intensity = intensity;
				lights.push_back(light);

			}

			Light getLight(int i) {
				
				return lights.at(i);
			}

			int getLightsCount() {
				return lights.size();
			}
			
		private:
			LightManager()
			{
			}
		private:
			static bool created;
			static LightManager* instance;
			std::vector<Light> lights;
		};
	}
}
#endif
