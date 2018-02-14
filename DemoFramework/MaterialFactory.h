#pragma once
#include "ticpp.h"
#include "IMaterial.h"

namespace Crawfis
{
	namespace Factories
	{
		class MaterialFactory
		{
		public:
			static void CreateRegisteredMaterial(ticpp::Element materialElement);
		private:
			static Crawfis::Graphics::IMaterial* CreateShadedMaterial(ticpp::Element& materialElement);
			static Crawfis::Graphics::IMaterial* CreateSimpleShaderMaterial(ticpp::Element& materialElement);
		};
	}
}