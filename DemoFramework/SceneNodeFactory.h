#pragma once

#include "ticpp.h"
#include "ISceneNode.h"
#include "GroupNode.h"
#include "IDrawableNode.h"
#include "IStateNode.h"

namespace Crawfis
{
	namespace Factories
	{
		class SceneNodeFactory
		{
		public:
			static Crawfis::Graphics::ISceneNode* CreateSceneNode(ticpp::Element* sceneElement);
		private:
			static Crawfis::Graphics::GroupNode* CreateGroupNode(ticpp::Element* sceneElement);
			static Crawfis::Graphics::IDrawableNode* CreateIDrawableNode(ticpp::Element* sceneElement);
			static Crawfis::Graphics::IStateNode* CreateIStateNode(ticpp::Element* sceneElement);
			static Crawfis::Graphics::IStateNode* CreateDrawModeNode(std::string name, ticpp::Element* stateElement);
			static Crawfis::Graphics::IStateNode* CreateLightSetNode(std::string name, ticpp::Element* stateElement);
		};
	}
}
