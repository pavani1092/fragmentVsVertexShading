
#include "MaterialFactory.h"
#include "MaterialManager.h"
#include "SolidColorMaterial.h"
#include "SimpleShaderMaterial.h"
#include "ShadedMaterial.h"
#include "MathFactory.h"
#include <string>

using namespace Crawfis::Graphics;
using namespace Crawfis::Factories;
using namespace std;

void Crawfis::Factories::MaterialFactory::CreateRegisteredMaterial(ticpp::Element materialElement)
{
	string name = materialElement.GetAttribute("name");
	string type = materialElement.GetAttribute("type");
	std::cout << "Parsing material " << name << " with type " << type << "\n";

	IMaterial* material = 0;

	if( type == "SimpleShader" )
	{
		material = CreateSimpleShaderMaterial(materialElement);
	}
	else if( type == "ShadedMaterial" )
	{
		material = CreateShadedMaterial(materialElement);
	}
	else if( type == "SolidColor" )
	{
		Color color = MathFactory::GetColor( materialElement.FirstChild()->ToElement() );
		material = new SolidColorMaterial(color);
	}
	else
	{
		throw "Unknown material type!";
	}

	if( material != 0 )
	{
		MaterialManager::Instance()->RegisterMaterial(name, material);
	}
}

IMaterial* Crawfis::Factories::MaterialFactory::CreateSimpleShaderMaterial(ticpp::Element& materialElement)
{
	Color color = MathFactory::GetColor(materialElement.FirstChild()->ToElement());
	string vertex = materialElement.FirstChild("VertexShader")->ToElement()->GetAttribute("filename");
	string fragment = materialElement.FirstChild("FragmentShader")->ToElement()->GetAttribute("filename");
	
	SimpleShaderMaterial* material = new SimpleShaderMaterial(vertex, fragment);
	material->setColor(color);
	return material;
}

IMaterial* Crawfis::Factories::MaterialFactory::CreateShadedMaterial(ticpp::Element& materialElement)
{
	string vertex = materialElement.FirstChild("VertexShader")->ToElement()->GetAttribute("filename");
	string fragment = materialElement.FirstChild("FragmentShader")->ToElement()->GetAttribute("filename");
	ShadedMaterial* material = new ShadedMaterial(vertex, fragment);

	Color ambient = MathFactory::GetColor( materialElement.FirstChild("ambient")->FirstChild()->ToElement() );
	material->setAmbientReflection(ambient);
	Color diffuse = MathFactory::GetColor( materialElement.FirstChild("diffuse")->FirstChild()->ToElement() );
	material->setDiffuseReflection(diffuse);
	Color specular = MathFactory::GetColor( materialElement.FirstChild("specular")->FirstChild()->ToElement() );
	material->setSpecularReflection(specular);
	float shininess = materialElement.FirstChild("specular")->ToElement()->GetAttribute<float>("shininess");
	material->setShininess(shininess);
	return material;
}
