#pragma once

#include "ticpp.h"
#include "ITransformNode.h"
#include <string>

namespace Crawfis
{
	namespace Factories
	{
		class TransformFactory
		{
		public:
			static Crawfis::Graphics::ITransformNode* CreateITransformNode(ticpp::Element* transformElement);
		private:
			static Crawfis::Graphics::ITransformNode* CreateLookAtNode(std::string name, ticpp::Element* transformElement);
			static Crawfis::Graphics::ITransformNode* CreateTransformNode(std::string name, ticpp::Element* transformElement);
			static Crawfis::Graphics::ITransformNode* CreateFrustumNode(std::string name, ticpp::Element* transformElement);
			static Crawfis::Graphics::ITransformNode* CreatePerspectiveNode(std::string name, ticpp::Element* transformElement);
			static Crawfis::Graphics::ITransformNode* CreateResetModelViewNode(std::string name, ticpp::Element* transformElement);
			static Crawfis::Graphics::ITransformNode* CreateResetProjectionNode(std::string name, ticpp::Element* transformElement);
		};
	}
}