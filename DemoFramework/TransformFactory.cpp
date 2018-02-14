
#include "TransformFactory.h"
#include "SceneNodeFactory.h"
#include "LookAtTransform.h"
#include "TransformMatrixNode.h"
#include "PerspectiveTransform.h"
#include "FrustumTransform.h"
#include "ResetModelViewNode.h"
#include "ResetProjectionNode.h"
#include "MathFactory.h"
#include <string>

using namespace Crawfis::Graphics;
using namespace Crawfis::Factories;
using namespace Crawfis::Math;
using namespace std;

ITransformNode* Crawfis::Factories::TransformFactory::CreateITransformNode(ticpp::Element* transformElement)
{
	string name = transformElement->GetAttribute("name");
	string type = transformElement->FirstChild()->Value();
	transformElement = transformElement->FirstChild()->ToElement();

	ITransformNode* transform = 0;

	if( type == "LookAt" )
	{
		transform = CreateLookAtNode(name, transformElement);
	}
	else if( type == "TransformMatrixNode" )
	{
		transform = CreateTransformNode(name, transformElement);
	}
	else if( type == "Perspective" )
	{
		transform = CreatePerspectiveNode(name, transformElement);
	}
	else if( type == "Frustum" )
	{
		transform = CreateFrustumNode(name, transformElement);
	}
	else if( type == "ResetModelView" )
	{
		transform = CreateResetModelViewNode(name, transformElement);
	}
	else if( type == "ResetProjection" )
	{
		transform = CreateResetProjectionNode(name, transformElement);
	}
	else
	{
		throw "Unknown transform type!";
	}
	return transform;
}

ITransformNode* Crawfis::Factories::TransformFactory::CreateLookAtNode(string name, ticpp::Element* transformElement)
{
	ISceneNode* subject = SceneNodeFactory::CreateSceneNode(transformElement->FirstChild("Child")->FirstChild()->ToElement());
	Vector3 eyePosition = MathFactory::GetVector3(transformElement->FirstChild("EyePoint")->ToElement());
	Vector3 centerOfInterest = MathFactory::GetVector3(transformElement->FirstChild("COI")->ToElement());
	Vector3 viewUp = MathFactory::GetVector3(transformElement->FirstChild("ViewUp")->ToElement());
	LookAtTransform* transform = new LookAtTransform(name, subject, eyePosition, centerOfInterest, viewUp);
	return transform;
}

ITransformNode* Crawfis::Factories::TransformFactory::CreateTransformNode(string name, ticpp::Element* transformElement)
{
	ISceneNode* subject = SceneNodeFactory::CreateSceneNode(transformElement->FirstChild("Child")->FirstChild()->ToElement());
	TransformMatrixNode* transform = new TransformMatrixNode(name, subject);
	for( ticpp::Node* children = transformElement->FirstChild(true); children; children = children->NextSibling(false) )
	{
		// Loop through the children and either rotate, translate or scale in order.
		ticpp::Element* child = children->ToElement();
		string type = child->Value();
		if( type == "Rotate" )
		{
			Vector3 axis = MathFactory::GetVector3(child);
			float angle = child->GetAttribute<float>("angle");
			angle*= 3.1415926f / 180.0f;
			transform->Rotate(angle, axis);
		}
		else if( type =="Translate" )
		{
			Vector3 translate = MathFactory::GetVector3(child);
			transform->Translate(translate.x, translate.y, translate.z);
		}
		else if( type == "Scale" )
		{
			Vector3 scale = MathFactory::GetVector3(child);
			transform->Scale(scale.x, scale.y, scale.z);
		}
	}
	return transform;
}

ITransformNode* Crawfis::Factories::TransformFactory::CreatePerspectiveNode(string name, ticpp::Element* transformElement)
{
	ISceneNode* subject = SceneNodeFactory::CreateSceneNode(transformElement->FirstChild("Child")->FirstChild()->ToElement());
	PerspectiveTransform* transform = new PerspectiveTransform(name, subject);
	return transform;
}

ITransformNode* Crawfis::Factories::TransformFactory::CreateFrustumNode(string name, ticpp::Element* transformElement)
{
	float left = transformElement->GetAttribute<float>("left");
	float right = transformElement->GetAttribute<float>("right");
	float top = transformElement->GetAttribute<float>("top");
	float bottom = transformElement->GetAttribute<float>("bottom");
	float zNear = transformElement->GetAttribute<float>("near");
	float zFar = transformElement->GetAttribute<float>("far");
	ISceneNode* subject = SceneNodeFactory::CreateSceneNode(transformElement->FirstChild("Child")->FirstChild()->ToElement());
	FrustumTransform* transform = new FrustumTransform(name, subject, left, right, top, bottom, zNear, zFar);
	return transform;
}

ITransformNode* Crawfis::Factories::TransformFactory::CreateResetModelViewNode(string name, ticpp::Element* transformElement)
{
	ISceneNode* subject = SceneNodeFactory::CreateSceneNode(transformElement->FirstChild("Child")->FirstChild()->ToElement());
	ResetModelViewNode* transform = new ResetModelViewNode(name, subject);
	return transform;
}

ITransformNode* Crawfis::Factories::TransformFactory::CreateResetProjectionNode(string name, ticpp::Element* transformElement)
{
	ISceneNode* subject = SceneNodeFactory::CreateSceneNode(transformElement->FirstChild("Child")->FirstChild()->ToElement());
	ResetProjectionNode* transform = new ResetProjectionNode(name, subject);
	return transform;
}
