#pragma once

#include "IVisitor.h"
#include "IDrawableNode.h"
#include "ITransformNode.h"
#include "IStateNode.h"
#include "GroupNode.h"

namespace Crawfis
{
	namespace Graphics
	{
		class RenderBoundingBoxVisitor : public IVisitor
		{
		public:
			virtual void Visit(IDrawableNode* drawable)
			{
				// TODO: Add a Bounding Box class and add / compute it in drawable.
				//BoundingBox* box = drawable->getBoundingBox();
				//Renderer::DrawBox( box );
			}
			virtual void Visit(ITransformNode* transform)
			{
				transform->Apply();
				transform->AcceptSubject(this);
				transform->Unapply();
			}
			virtual void Visit(IStateNode* state)
			{
				state->Apply();
				state->AcceptSubject(this);
				state->Unapply();
			}
			virtual void Visit(GroupNode* group)
			{
				group->AcceptChildren(this);
			}
		};
	}
}