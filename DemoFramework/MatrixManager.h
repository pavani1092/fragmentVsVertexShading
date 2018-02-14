#pragma once

#include "Matrix.h"
#include "Vector.h"
#include<stack>
#include "OpenGL.h"
#include "ShaderConstantMat4.h"
#include "MaterialManager.h"
using namespace Crawfis::Math;
namespace Crawfis
{
	namespace Graphics
	{
		
		class MatrixManager
		{

		public:
			static MatrixManager* Instance()
			{
				if (!created)
				{
					instance = new MatrixManager();
					Matrix4 I;
					modelView.push(I);
					projection.push(I);
					created = true;
				}
				return instance;
			}

			void MatrixMode(GLenum modeof) {
				this->mode = modeof;

			}
			void LoadIdentity() {
				Matrix4 mat;
				mat.identity();
				if (mode == GL_MODELVIEW)
					modelView.push(mat);
				else if (mode == GL_PROJECTION)
					projection.push(mat);


			}

			void PushMatrix() {
				if (mode == GL_MODELVIEW)
					modelView.push(modelView.top());
				else if (mode == GL_PROJECTION)
					projection.push(projection.top());
			}
			void PopMatrix() {
				if (mode == GL_MODELVIEW)
					modelView.pop();
				else if (mode == GL_PROJECTION)
					projection.pop();
			}
			void MultMatrixf(Matrix4 mult) {
				if (mode == GL_MODELVIEW) {
					Matrix4 temp = modelView.top();
					temp = temp*mult;
					modelView.pop();
					modelView.push(temp);
				}
				else if (mode == GL_PROJECTION) {
					Matrix4 temp = projection.top();
					temp = temp*mult;
					projection.pop();
					projection.push(temp);
				}
			}


			Matrix4 TopMatrix() {
				if (mode == GL_MODELVIEW)
					return modelView.top();
				else if (mode == GL_PROJECTION)
					return projection.top();
			}

			void LookAt(Vector3 eyePosition, Vector3 cof, Vector3 Up) {

				Vector3f a, b, c;
				c = eyePosition - cof;
				c.normalize();
				b = Up;
				a = b.cross(c);
				b = c.cross(a);
				a.normalize();
				b.normalize();
				Matrix4 mat;
				mat.setRowVector(0, Vector4(a, -a.dot(eyePosition)));
				mat.setRowVector(1, Vector4(b, -b.dot(eyePosition)));
				mat.setRowVector(2, Vector4(c, -c.dot(eyePosition)));
				MultMatrixf(mat);

			}
			void Perspective(float fov, float aspect, float znear, float zfar) {
				Matrix4 mat;
				float d2r = (3.14159 / 180.0)*fov;
				float tanHalfFovy = tan(d2r / 2.0);
				float f = 1.0 / tanHalfFovy;
				mat.setRowVector(0, Vector4(f / aspect, 0.0, 0.0, 0.0));
				mat.setRowVector(1, Vector4(0.0, f, 0.0, 0.0));
				float v1 = -(zfar + znear) / (zfar - znear);
				float v2 = -(2.0 * zfar * znear) / (zfar - znear);
				mat.setRowVector(2, Vector4(0.0, 0.0, v1, v2));
				mat.setRowVector(3, Vector4(0.0, 0.0, -1.0, 1.0));
				MultMatrixf(mat);
			}
			void Frustum(float left, float right, float bottom, float top, float zNear, float zFar) {
				Matrix4 mat;
				float v1 = 2.0*zNear / (right - left);
				float v2 = (right + left) / (right - left);
				mat.setRowVector(0, Vector4(v1, 0.0, v2, 0.0));
				v1 = 2.0*zNear / (top - bottom);
				v2 = (top + bottom) / (top - bottom);
				mat.setRowVector(1, Vector4(0.0, v1, v2, 0.0));
				v1 = (zFar + zNear) / (zFar - zNear);
				v2 = -(2.0 * zFar * zNear) / (zFar - zNear);
				mat.setRowVector(2, Vector4(0.0, 0.0, v1, v2));
				mat.setRowVector(3, Vector4(0.0, 0.0, 1.0, 1.0));
				MultMatrixf(mat);

			}




		private:


			MatrixManager();


			GLenum mode;
			static std::stack<Matrix4f> modelView;
			static std::stack<Matrix4f> projection;
			static bool created;
			static MatrixManager* instance;


		};

	}
}
