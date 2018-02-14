#include "MathFactory.h"

using namespace Crawfis::Math;
using namespace Crawfis::Graphics;

Vector2 Crawfis::Factories::MathFactory::GetVector2(ticpp::Element* element)
{
	float x, y;
	element->GetAttribute("x", &x);
	element->GetAttribute("y", &y);
	return Vector2(x, y);
}

Vector3 Crawfis::Factories::MathFactory::GetVector3(ticpp::Element* element)
{
	float x, y, z;
	element->GetAttribute("x", &x);
	element->GetAttribute("y", &y);
	element->GetAttribute("z", &z);
	return Vector3(x, y, z);
}

Vector4 Crawfis::Factories::MathFactory::GetVector4(ticpp::Element* element)
{
	float x, y, z, w;
	element->GetAttribute("x", &x);
	element->GetAttribute("y", &y);
	element->GetAttribute("z", &z);
	element->GetAttribute("w", &w);
	return Vector4(x, y, z, w);
}

Color Crawfis::Factories::MathFactory::GetColor(ticpp::Element* elementWithColorAttribs)
{
	float red, green, blue, alpha;
	elementWithColorAttribs->GetAttribute("r", &red);
	elementWithColorAttribs->GetAttribute("g", &green);
	elementWithColorAttribs->GetAttribute("b", &blue);
	elementWithColorAttribs->GetAttribute("a", &alpha);
	return Color(red, green, blue, alpha);
}
