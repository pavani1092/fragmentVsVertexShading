#include "VertexRoutine.h"
#include "BlankTexture2D.h"
#include "ClearColorCommand.h"
#include "ClearDepthCommand.h"
#include "ClearFrameCommand.h"
#include "Color.h"
#include "DefaultController.h"
#include "DepthBuffer.h"
#include "DepthTestedRasterOps.h"
#include "DevIL.h"
#include "DirectionalLight.h"
#include "DrawableCube.h"
#include "DrawableFloor.h"
#include "DrawableProxy.h"
#include "DrawableRenderState.h"
#include "DrawableSphere.h"
#include "DrawableSquare.h"
#include "DrawableTeapot.h"
#include "DrawModeController.h"
#include "DrawModeNode.h"
#include "ExaminerCameraNode.h"
#include "FileUtility.h"
#include "FragmentRoutine.h"
#include "FrustumTransform.h"
#include "GeometryRoutine.h"
#include "GroupNode.h"
#include "ICommand.h"
#include "IDepthBuffer.h"
#include "IDrawable.h"
#include "IDrawableNode.h"
#include "IKeyboardHandler.h"
#include "ILight.h"
#include "IMaterial.h"
#include "IMouseHandler.h"
#include "IRasterOps.h"
#include "IRenderTarget.h"
#include "ISceneNode.h"
#include "IShaderConstant.h"
#include "IShaderProgram.h"
#include "IShaderRoutine.h"
#include "IStateNode.h"
#include "ITextureApplicator.h"
#include "ITextureDataObject.h"
#include "ITextureParameters.h"
#include "ITransformNode.h"
#include "IVisitor.h"
#include "LightSetNode.h"
#include "LookAtTransform.h"
#include "MaterialFactory.h"
#include "MaterialManager.h"
#include "MaterialProxy.h"
#include "MathFactory.h"
#include "MathUtil.h"
#include "Matrix.h"
#include "ModelManager.h"
#include "NoDepthRasterOps.h"
#include "NullCommand.h"
#include "OpenGL.h"
#include "OpenGLErrorCheckVisitorDecorator.h"
//#include "PaintController.h"
#include "PerspectiveTransform.h"
#include "PointLight.h"
#include "PrintSceneVisitor.h"
#include "RenderManager.h"
#include "RenderState.h"
#include "RenderTarget.h"
#include "RenderTargetProxy.h"
#include "RenderVisitor.h"
#include "ResetModelViewNode.h"
#include "ResetProjectionNode.h"
#include "SamplerApplicator.h"
#include "SceneNodeFactory.h"
#include "SearchVisitor.h"
#include "ShadedMaterial.h"
#include "ShaderConstantCollection.h"
#include "ShaderConstantVec4.h"
#include "ShaderProgram.h"
#include "SimpleShaderMaterial.h"
#include "SingleFireCommand.h"
#include "SolidColorMaterial.h"
#include "StateNodeBase.h"
#include "SwapCommand.h"
#include "TexParam2DMipMap.h"
#include "TexParam2DNoMipMap.h"
#include "TexParam2DWrapped.h"
#include "TextureBinding.h"
#include "TextureBindManager.h"
#include "TextureBindManagerOpenGL.h"
#include "TextureData2DBase.h"
#include "TextureData2DBuilder.h"
#include "TextureDataImage.h"
#include "TextureParameterList.h"
#include "Trackball.h"
#include "TransformFactory.h"
#include "TransformMatrixNode.h"
#include "TransformNodeBase.h"
#include "Vector.h"