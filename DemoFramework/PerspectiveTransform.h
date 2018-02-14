#pragma once

#include "OpenGL.h"

#include "TransformNodeBase.h"
#include "MatrixManager.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// A concrete implementation of the ITransformNode.
		// This implementation simply mulitplies the frustum 
		// defined by the current projection transform.
		//
		class PerspectiveTransform : public TransformNodeBase
		{
		public:
			//
			// Constructor. 
			//
			PerspectiveTransform(std::string name, ISceneNode* subject) 
				: TransformNodeBase(name, subject)
			{
				this->fieldOfView = 45;
				this->width = 100;
				this->height = 200;
				this->zNear = 0.5;
				this->zFar = 1000;
			}
			PerspectiveTransform(std::string name, ISceneNode* subject,
				double fieldOfView, int width, int height, double zNear, double zFar) 
				: TransformNodeBase(name, subject)
			{
				this->fieldOfView = fieldOfView;
				this->width = width;
				this->height = height;
				this->zNear = zNear;
				this->zFar = zFar;
			}
			void setWidth(int width)
			{
				this->width = width;
			}
			void setHeight(int height)
			{
				this->height = height;
			}
			// 
			// Apply the transform. This implementation will use the OpenGL
			// state machine to track transformations.
			//
			virtual void Apply()
			{
				// TODO: Remove old Fixed Functionality
				MatrixManager* m = MatrixManager::Instance();
				m->MatrixMode( GL_PROJECTION );
				m->PushMatrix();
				glViewport(0,0,width, height);
				double aspectRatio = width / (double) height;
				m->Perspective(fieldOfView, aspectRatio, zNear, zFar);
				
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
			double fieldOfView;
			int width, height;
			double zNear, zFar;
		};
	}
}