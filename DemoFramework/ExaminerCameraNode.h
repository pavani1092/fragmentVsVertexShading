#pragma once

#include "ITransformNode.h"
#include "IKeyboardHandler.h"
#include "IMouseHandler.h"
#include "PerspectiveTransform.h"
#include "TransformMatrixNode.h"
#include "LookAtTransform.h"
#include "Trackball.h"
#include "OpenGL.h"

using namespace Crawfis::Controller;

namespace Crawfis
{
	namespace Graphics
	{
		enum MouseState { NONE, TRACKBALL, ZOOM, PAN };
		//
		// A composite ITransformNode used for camera set-up and
		// user-interaction, such as an examiner style manipulation.
		// Also supports the IKeyboardHandler and IMouseHandler interfaces.
		//
		class ExaminerCameraNode : public ITransformNode, public IKeyboardHandler, public IMouseHandler
		{
		public:
			//
			// Constructor. 
			//
			ExaminerCameraNode(std::string name, ISceneNode* subject) : dollyDelta(0.1f)
			{
				// Final transform = Perspective * M4 * M3 * M2 * M1 * Camera * Scene
				// M1 and M3 indicate the distance along the view ray to the center of rotation.
				// M2 is the rotation node used in the mouse trackball and the 
				// M4 can bring the camera closer or further from the scene.
				this->name = name;
				rotationDepth = 10;
				LookAtTransform* camera = new LookAtTransform("LookAt", subject);
				TransformMatrixNode* preTranslate = new TransformMatrixNode("PreTranslate", camera);
				preTranslate->Translate(0, 0, rotationDepth);
				examinerTransform = new TransformMatrixNode("Examiner", preTranslate);
				TransformMatrixNode* postTranslate = new TransformMatrixNode("PostTranslate", examinerTransform);
				postTranslate->Translate(0, 0, -rotationDepth);
				dollyNode = new TransformMatrixNode("Dolly", postTranslate);
				perspectiveNode = new PerspectiveTransform("Perspective", dollyNode);

				trackball = new Crawfis::Controller::Trackball(examinerTransform);

				this->rootNode = perspectiveNode;
			}
			void setWidth(int width)
			{
				windowWidth = width;
				perspectiveNode->setWidth(width);
			}
			void setHeight(int height)
			{
				windowHeight = height;
				perspectiveNode->setHeight(height);
			}
			//
			// Overrided from ISceneNode
			//
			virtual void Accept(IVisitor* visitor)
			{
				visitor->Visit(this);
			}
			//
			// Traverse the child node.
			//
			void AcceptSubject(IVisitor* visitor)
			{
				rootNode->Accept(visitor);
			}
			// 
			// Apply the transform.
			// This is a no-op here, as the real transforms are in
			// the composite.
			//
			virtual void Apply() { }
			// 
			// Remove or undo the application of the transform.
			// This is a no-op here, as the real transforms are in
			// the composite.
			//
			virtual void Unapply() { }
			//
			// Overrrided from ISceneNode
			//
			virtual std::string ToString()
			{
				return name;
			}
			//
			// Handle the main keyboard key presses. 
			// Called on both key down and key up.
			//
			virtual void KeyPress(unsigned char key, int x, int y)
			{
				switch (key)
				{
				case 'z':
					dollyNode->Translate(0.0, 0.0, dollyDelta);
					glutPostRedisplay();
					break;
				case 'Z':
					dollyNode->Translate(0.0, 0.0, -dollyDelta);
					glutPostRedisplay();
					break;
				}
			}
			//
			// Handle the arrow keys and numeric keypad.
			//
			virtual void NumPadPress(int key, int x, int y)
			{
				switch (key)
				{
				case GLUT_KEY_LEFT:
					// TODO: Pan the camera to the left (translate examinerTransform)
					//currentMouseState = PAN;
					examinerTransform->Translate(-dollyDelta, 0, 0);
					glutPostRedisplay();
					break;
				case GLUT_KEY_RIGHT:
					// TODO: Pan the camera to the right
					//currentMouseState = PAN;
					examinerTransform->Translate(dollyDelta, 0, 0);
					glutPostRedisplay();
					break;
				case GLUT_KEY_UP:
					// TODO: Pan the camera up
					//currentMouseState = PAN;
					examinerTransform->Translate(0, dollyDelta, 0);
					glutPostRedisplay();
					break;
				case GLUT_KEY_DOWN:
					// TODO: Pan the camera down
					//currentMouseState = PAN;
					examinerTransform->Translate(0, -dollyDelta, 0);
					glutPostRedisplay();
					break;
				}
			}
			//
			// Handle any mouse button events, both press and release.
			//
			virtual void MouseEvent(int button, int state, int ix, int iy)
			{
				if (button == GLUT_LEFT_BUTTON)
				{
					float x, y;
					MapMouse(ix, iy, x, y);
					if (state == GLUT_DOWN)
					{
						currentMouseState = TRACKBALL;
						trackball->BeginManipulation(x, y);
					}
					else
					{
						currentMouseState = NONE;
						trackball->EndManipulation(x, y);
					}
				}
			}
			//
			// Handle any mouseMove events. Note, with GLUT this 
			// is only called when a mouse button is pressed by
			// default.
			//
			virtual void MouseMoved(int ix, int iy)
			{
				if (currentMouseState == TRACKBALL)
				{
					float x, y;
					MapMouse(ix, iy, x, y);
					trackball->ManipulateTo(x, y);
					glutPostRedisplay();
				}
			}

		private:
			void MapMouse(int ix, int iy, float& x, float &y)
			{
				x = (float)ix / (float)windowWidth; // map to 0 to 1
				x = 2 * x - 1; // map to -1 to 1
				y = (float)iy / (float)windowHeight; // map to 0 to 1
				y = 1 - 2 * y; // map to 1 to -1 (flip the window coordinates)
			}

		private:
			std::string name;
			ITransformNode* rootNode;
			float rotationDepth;
			PerspectiveTransform* perspectiveNode;
			TransformMatrixNode* dollyNode;
			TransformMatrixNode* examinerTransform;
			const float dollyDelta;
			Crawfis::Controller::Trackball* trackball;
			float viewDistance;
			MouseState currentMouseState;
			int windowWidth, windowHeight;
		};
	}
}