#pragma once

#include "OpenGL.h"
#include "TransformNodeBase.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// A concrete implementation of the ITransformNode.
		//
		class ResetProjectionNode : public TransformNodeBase
		{
		public:
			//
			// Constructor. 
			//
			ResetProjectionNode(std::string name, ISceneNode* subject) : TransformNodeBase(name, subject)
			{
			}
			// 
			// Apply the transform. This implementation will use the OpenGL
			// state machine to track transformations.
			//
			virtual void Apply()
			{
				// TODO: Remove old Fixed Functionality
				//std::cout << "ResetProjNode onApply" << std::endl;
				MatrixManager* m = MatrixManager::Instance();
				m->MatrixMode( GL_PROJECTION );
				m->PushMatrix();
				m->LoadIdentity();
			}
			// 
			// Remove or undo the application of the transform. This implementation 
			// will use the OpenGL state machine to track transformations.
			//
			virtual void Unapply()
			{
				// TODO: Remove old Fixed Functionality
				MatrixManager* m = MatrixManager::Instance();
				m->MatrixMode( GL_PROJECTION );
				m->PopMatrix();
			}
		};
	}
}