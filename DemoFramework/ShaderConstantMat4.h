#pragma once

#include "IShaderConstant.h"
#include "Matrix.h"

namespace Crawfis
{
	namespace Graphics
	{
		//
		// Concrete implementation of a IShaderConstant for mat4 
		//
		class ShaderConstantMat4 : public IShaderConstant
		{
		public:
			//
			// Constructor.
			//
			ShaderConstantMat4(std::string constantName)
			{
				this->constantName = constantName;
			}
			void setValue(const Crawfis::Math::Matrix4f& value)
			{
				this->value = value;
			}
			//
			//
			// Note that there is no shader behavior that is publically callable. This 
			// object is not called directly in the rendering. As an IShaderConstant, 
			// it will be called by the ShaderProgram it is associated with
			//
		protected:
			//
			// Set-up any logic after a shader program has linked.
			// These should not be called by the user.
			//
			virtual void OnLink(unsigned int shaderID)
			{
				constantLocation = glGetUniformLocation(shaderID, constantName.c_str());
				//std::cout << "got location for " << constantName.c_str() << " " << constantLocation << std::endl;
			}
			//
			// Called once a Shader Program has been enabled (glUseProgram)
			// These should not be called by the user.
			//
			virtual void OnShaderEnabled(unsigned int shaderID)
			{

				if (constantLocation >= 0)
					glUniformMatrix4fv(constantLocation, 1, GL_FALSE, value.getValue());
				//std::cout << "sending matrix to loc  "<< constantLocation << std::endl;
			}

		private:
			std::string constantName;
			int constantLocation;
			Crawfis::Math::Matrix4f value;
		};
	}
}