#pragma once

#include "OpenGL.h"

#include "TransformNodeBase.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// A concrete implementation of the ITransformNode.
		// This implementation simply mulitplies the frustum 
		// defined by the current projection transform.
		//
		// This class is immutable.
		//
		class FrustumTransform : public TransformNodeBase
		{
		public:
			//
			// Constructor. 
			//
			FrustumTransform(std::string name, ISceneNode* subject,
				double left, double right, double bottom, double top, double zNear, double zFar) 
				: TransformNodeBase(name, subject)
			{
				this->left = left;
				this->right = right;
				this->bottom = bottom;
				this->top = top;
				this->zNear = zNear;
				this->zFar = zFar;
			}
			// 
			// Apply the transform. This implementation will use the OpenGL
			// state machine to track transformations.
			//
			virtual void Apply()
			{
				//std::cout << "Frustrum Trans onApply" << std::endl;
				MatrixManager* m = MatrixManager::Instance();
				m->MatrixMode( GL_PROJECTION );
				m->PushMatrix();
				m->Frustum(left, right, bottom, top, zNear, zFar);
			}
			// 
			// Remove or undo the application of the transform. This implementation 
			// will use the OpenGL state machine to track transformations.
			//
			virtual void Unapply()
			{
				MatrixManager* m = MatrixManager::Instance();
				m->MatrixMode( GL_PROJECTION );
				m->PopMatrix();
			}
			//
			// Overrrided from ITransformNode
			//
			virtual std::string ToString()
			{
				std::string name = this->TransformNodeBase::ToString();
				// TODO: add more information about this transform node
				//   to the string.
				return name;
			}

		private:
			double left, right;
			double bottom, top;
			double zNear, zFar;
		};
	}
}