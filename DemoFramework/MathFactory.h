#pragma once
#include "ticpp.h"
#include "Vector.h"
#include "Color.h"

namespace Crawfis
{
	namespace Factories
	{
		class MathFactory
		{
		public:
			static Crawfis::Math::Vector2 GetVector2(ticpp::Element* element);
			static Crawfis::Math::Vector3 GetVector3(ticpp::Element* element);
			static Crawfis::Math::Vector4 GetVector4(ticpp::Element* element);
			static Crawfis::Graphics::Color GetColor(ticpp::Element* elementWithColorAttribs);
		};
	}
}