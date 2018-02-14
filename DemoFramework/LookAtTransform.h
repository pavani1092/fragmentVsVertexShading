#pragma once

#include "OpenGL.h"

#include "TransformNodeBase.h"
#include "Vector.h"
#include "Matrix.h"
#include "MatrixManager.h"

using namespace Crawfis::Math;

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
		class LookAtTransform : public TransformNodeBase
		{
		public:
			//
			// Constructor. 
			//
			LookAtTransform(std::string name, ISceneNode* subject) 
				: TransformNodeBase(name, subject)
			{
				this->eyePosition = Crawfis::Math::Vector3(10,0,0);
				this->centerOfInterest = Crawfis::Math::Vector3(0,0,0);
				this->viewUp = Crawfis::Math::Vector3(0,1,0);
			}
			LookAtTransform(std::string name, ISceneNode* subject,
				Vector3& eyePosition, Vector3& centerOfInterest, Vector3& viewUp) 
				: TransformNodeBase(name, subject)
			{
				this->eyePosition = eyePosition;
				this->centerOfInterest = centerOfInterest;
				this->viewUp = viewUp;
			}
			// 
			// Apply the transform. This implementation will use the OpenGL
			// state machine to track transformations.
			//
			virtual void Apply()
			{
				// TODO: Compute the matrix needed here
				// TODO: Remove old Fixed Functionality
				MatrixManager* m = MatrixManager::Instance();
				m->MatrixMode( GL_MODELVIEW );
				m->PushMatrix();
				m->LookAt(eyePosition,centerOfInterest,viewUp);
			}
			
			// 
			// Remove or undo the application of the transform. This implementation 
			// will use the OpenGL state machine to track transformations.
			//
			virtual void Unapply()
			{
				// TODO: Remove old Fixed Functionality
				MatrixManager* m = MatrixManager::Instance();
				m->MatrixMode( GL_MODELVIEW );
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
			Crawfis::Math::Vector3 eyePosition;
			Crawfis::Math::Vector3 centerOfInterest;
			Crawfis::Math::Vector3 viewUp;
		};
	}
}