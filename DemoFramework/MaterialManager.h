#pragma once

#include <string>
#include <map>
#include "IMaterial.h"
#include "IShaderProgram.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// MaterialManager implements a Singleton design pattern for global
		// access and registration of materials.
		//
		class MaterialManager
		{
		public:
			//
			// Get the one and only instance of the MaterialManager
			//
			static MaterialManager* Instance()
			{
				if( !created)
				{
					instance = new MaterialManager();
					created = true;
				}
				return instance;
			}
			//
			// Look-up a material registered by it's name and
			// enable it. If the material is not registered an
			// exception will be thrown.
			//
			void EnableMaterial(std::string name)
			{
				IMaterial* material = materialMap[name];
				material->Enable();
			}
			//
			// Look-up a material registered by it's name and
			// disable it.If the material is not registered an
			// exception will be thrown.
			//
			void DisableMaterial(std::string name)
			{
				IMaterial* material = materialMap[name];
				material->Disable();
			}
			//
			// Register a new material with the system.
			// If the material was already registered, the name will
			// now be associated with the new material.
			//
			void RegisterMaterial(std::string name, IMaterial* material)
			{
				materialMap[name] = material;
			}

			void RegisterShaderProgram(unsigned int guid, IShaderProgram* program)
			{
				//std::cout << "saving guid " << guid << std::endl;
				programMap[guid] = program;
			}
			IShaderProgram* getShaderProgram(unsigned int guid)
			{
				return programMap[guid];
			}

		private:
			MaterialManager()
			{
			}
		private:
			static bool created;
			static MaterialManager* instance;
			std::map<std::string,IMaterial*> materialMap;
			std::map<unsigned int, IShaderProgram*> programMap;
		};
	}
}
