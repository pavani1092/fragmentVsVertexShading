#pragma once

#include "IVisitor.h"
#include "IDrawableNode.h"
#include "ITransformNode.h"
#include "IStateNode.h"
#include "GroupNode.h"
#include "OpenGL.h"

namespace Crawfis
{
	namespace Graphics
	{
		class OpenGLErrorCheckVisitorDecorator : public IVisitor
		{
		protected:
			IVisitor* realVisitor;
			void CheckForErrors(std::string nodeName)
			{
				GLenum error = glGetError();
				if (error != 0)
					std::cout << "OpenGL reported an error while traversing " << nodeName << std::endl;
			}
		public:
			OpenGLErrorCheckVisitorDecorator(IVisitor* visitorToDecorate)
			{
				this->realVisitor = visitorToDecorate;
			}
			virtual void Visit(IDrawableNode* drawable)
			{
				realVisitor->Visit(drawable);
				CheckForErrors(drawable->ToString());
			}
			virtual void Visit(ITransformNode* transform)
			{
				realVisitor->Visit(transform);
				CheckForErrors(transform->ToString());
			}
			virtual void Visit(IStateNode* state)
			{
				realVisitor->Visit(state);
				CheckForErrors(state->ToString());
			}
			virtual void Visit(GroupNode* group)
			{
				group->AcceptChildren(this);
				CheckForErrors(group->ToString());
			}
		};
	}
}