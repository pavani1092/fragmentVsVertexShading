
#include "SceneNodeFactory.h"
#include "TransformFactory.h"
#include "MathFactory.h"
#include "GroupNode.h"
#include "DrawableProxy.h"
#include "DrawModeNode.h"
#include "MaterialProxy.h"
#include "RenderTargetProxy.h"
#include "LightSetNode.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "DrawableRenderState.h"
#include <string>

using namespace Crawfis::Graphics;
using namespace Crawfis::Math;
using namespace std;

ISceneNode* Crawfis::Factories::SceneNodeFactory::CreateSceneNode(ticpp::Element* sceneElement)
{
	string type = sceneElement->Value();

	ISceneNode* sceneNode = 0;

	if( type == "GroupNode" )
	{
		sceneNode = CreateGroupNode(sceneElement);
	}
	else if( type == "TransformNode" )
	{
		sceneNode = TransformFactory::CreateITransformNode(sceneElement);
	}
	else if( type == "DrawNode" )
	{
		sceneNode = CreateIDrawableNode(sceneElement);
	}
	else if( type == "StateNode" )
	{
		sceneNode = CreateIStateNode(sceneElement);
	}
	else
	{
		throw "Unknown transform type!";
	}
	return sceneNode;
}

GroupNode* Crawfis::Factories::SceneNodeFactory::CreateGroupNode(ticpp::Element* sceneElement)
{
	//string name = transformElement.FirstChild("VertexShader")->ToElement()->GetAttribute("filename");
	string name = sceneElement->GetAttribute("name");
	GroupNode* groupNode = new GroupNode(name);

	for( ticpp::Node* children = sceneElement->FirstChild(true); children; children = children->NextSibling(false) )
	{
		// Loop through the children and add them to the group.
		ISceneNode* child = CreateSceneNode(children->ToElement());
		groupNode->AddChild(child);
	}
	return groupNode;
}

IDrawableNode* Crawfis::Factories::SceneNodeFactory::CreateIDrawableNode(ticpp::Element* sceneElement)
{
	string name = sceneElement->GetAttribute("name");
	string type = sceneElement->FirstChild()->Value();

	IDrawableNode* drawableNode;
	if( type == "DrawableProxy" )
	{
		string model = sceneElement->FirstChild()->ToElement()->GetAttribute("model");
		drawableNode = new DrawableProxy(name, model);
	}
	else if (type == "DrawableRenderState") {
		string name = sceneElement->FirstChild()->ToElement()->GetAttribute("name");
		drawableNode = new DrawableRenderState(name);
	}
	else
	{
		throw "Unknown IDrawableNode type!";
	}
	return drawableNode;
}

IStateNode* Crawfis::Factories::SceneNodeFactory::CreateIStateNode(ticpp::Element* sceneElement)
{
	//string name = transformElement.FirstChild("VertexShader")->ToElement()->GetAttribute("filename");
	string name = sceneElement->GetAttribute("name");
	ticpp::Element* stateElement = sceneElement->FirstChild()->ToElement();
	string type = stateElement->Value();

	IStateNode* stateNode;
	if( type == "DrawMode" )
	{
		stateNode = CreateDrawModeNode(name, stateElement);
	}
	else if( type == "LightSet" )
	{
		stateNode = CreateLightSetNode(name, stateElement);
	}
	else if( type == "MaterialProxy" )
	{
		string material = stateElement->GetAttribute("material");
		ISceneNode* subject = SceneNodeFactory::CreateSceneNode(stateElement->FirstChild("Child")->FirstChild()->ToElement());
		stateNode = new MaterialProxy(name, material, subject);
	}
	else if( type == "RenderTargetProxy" )
	{
		string renderTarget = stateElement->GetAttribute("renderTarget");
		ISceneNode* subject = SceneNodeFactory::CreateSceneNode(stateElement->FirstChild("Child")->FirstChild()->ToElement());
		stateNode = new RenderTargetProxy(name, renderTarget, subject);
	}
	else
	{
		throw "Unknown IStateNode type!";
	}
	return stateNode;
}

IStateNode* Crawfis::Factories::SceneNodeFactory::CreateDrawModeNode(std::string name, ticpp::Element* stateElement)
{
	string drawMode = stateElement->GetAttribute("mode");
	DrawModeType drawType;
	if( drawMode == "Solid" )
		drawType = DrawModeType::SOLID;
	else if( drawMode == "Wireframe" )
		drawType = DrawModeType::WIREFRAME;
	else if( drawMode == "Points" )
		drawType = DrawModeType::POINTS;
	else
		throw "Unknow DrawModeType in DrawMode element";

	ISceneNode* subject = SceneNodeFactory::CreateSceneNode(stateElement->FirstChild("Child")->FirstChild()->ToElement());
	return new DrawModeNode(name, subject, drawType);
}

IStateNode* Crawfis::Factories::SceneNodeFactory::CreateLightSetNode(std::string name, ticpp::Element* stateElement)
{
	ISceneNode* subject = SceneNodeFactory::CreateSceneNode(stateElement->FirstChild("Child")->FirstChild()->ToElement());
	LightSetNode* lightSet = new LightSetNode(name, subject);

	for( ticpp::Node* children = stateElement->FirstChild(true); children; children = children->NextSibling(false) )
	{
		// Loop through the children and either rotate, translate or scale in order.
		ticpp::Element* child = children->ToElement();
		string type = child->Value();
		if( type == "PointLight" )
		{
			PointLight* light = new PointLight();
			Vector3 position = MathFactory::GetVector3(child->FirstChild("Position")->ToElement());
			light->setPosition(position);
			Color color = MathFactory::GetColor(child->FirstChild("Color")->ToElement());
			light->setColor(color);
			lightSet->AddLight(light);
		}
		else if( type =="DirectionalLight" )
		{
			DirectionalLight* light = new DirectionalLight();
			Vector3 direction = MathFactory::GetVector3(child->FirstChild("Direction")->ToElement());
			light->setDirection(direction);
			Color color = MathFactory::GetColor(child->FirstChild("Color")->ToElement());
			light->setColor(color);
			lightSet->AddLight(light);
		}
	}

	return lightSet;
}