#define _USE_MATH_DEFINES

#include "OpenGL.h"
#include "DevIL.h"

#include <string>
#include <ostream>
#include <vector>
#include "ticpp.h"

// Includes to handle scene nodes
#include "ISceneNode.h"
#include "DrawModeNode.h"
#include "MaterialFactory.h"
#include "SceneNodeFactory.h"

// Includes for the interaction.
#include "ExaminerCameraNode.h"
#include "DrawModeController.h"
#include "DefaultController.h"

// Includes for the model assets
#include "ModelManager.h"
#include "DrawableSphere.h"
#include "DrawableSphereVertex.h"
#include "DrawableCube.h"
#include "DrawableCubeVertex.h"
#include "DrawableSquare.h"
#include "DrawableFloor.h"
#include "DrawableTeapot.h"
#include "RenderTargetProxy.h"
#include "RenderTarget.h"
#include "DepthBuffer.h"
#include "RenderManager.h"
#include "ClearFrameCommand.h"
#include "ClearColorCommand.h"
#include "ClearDepthCommand.h"
#include "SwapCommand.h"

#include "BlankTexture2D.h"
#include "TextureBinding.h"
#include "TextureBindManager.h"
#include "TextureBindManagerOpenGL.h"
#include "TextureDataImage.h"
#include "SamplerApplicator.h"
#include "SimpleShaderMaterial.h"
#include "MaterialManager.h"
#include "TexParam2DNoMipMap.h"
#include "TexParam2DMipMap.h"
#include "NoDepthRasterOps.h"
#include "ShaderConstantVec4.h"
#include "ShaderConstantCollection.h"

// Includes for walking the scene graph
#include "SearchVisitor.h"
#include "PrintSceneVisitor.h"
#include "RenderVisitor.h"
#include "OpenGLErrorCheckVisitorDecorator.h"
#include "MatrixManager.h"

#include "CompilerTest.h"
using namespace Crawfis::Graphics;
using namespace Crawfis::Math;
using namespace std;

const std::string materialLibrary("../Media/BasicMaterials.xml");
const std::string sceneFile("../Media/TeapotTrophy.xml");
//const std::string sceneFile("../Media/Stairs.xml");

ISceneNode* rootSceneNode;
IVisitor* renderVisitor;
std::vector<IMouseHandler*> mouseHandlers;
std::vector<IKeyboardHandler*> keyboardHandlers;
ExaminerCameraNode* examinerController;

int windowGUID;
int windowWidth;
int windowHeight;

void LoadMaterialLibrary(std::string fileName)
{
	ITextureDataObject* texture = new BlankTexture2D(1024, 1024);
	ITextureDataObject* redTexture = new BlankTexture2D(1024, 1024, Color(1,0,0,1), GL_RGB );
	redTexture->setTextureParams(&TexParam2DNoMipMap::Instance);
	ITextureDataObject* imageTexture = new TextureDataImage("../Media/Textures/UVGrid.jpg", GL_RGB );
	imageTexture->setTextureParams(&TexParam2DMipMap::Instance);
	SamplerApplicator* uniformBinding = new SamplerApplicator("texture");
	TextureBinding* binding = TextureBindManager::Instance()->CreateBinding(imageTexture, uniformBinding);
	binding->Enable();
	binding->Disable();

	/*SimpleShaderMaterial* pavaniMaterial = new SimpleShaderMaterial("../Media/Shaders/VertexLight.vert", "../Media/Shaders/SolidColor.frag");
	ShaderConstantMat4* shaderConstModel = new ShaderConstantMat4("MVP");
	pavaniMaterial->setShaderConstant(shaderConstModel);
	MaterialManager::Instance()->RegisterMaterial("PavaniMaterial", pavaniMaterial);*/

	SimpleShaderMaterial* texturedMaterial = new SimpleShaderMaterial("../Media/Shaders/Textured.vert", "../Media/Shaders/Textured.frag" );
	texturedMaterial->setShaderConstant(uniformBinding);
	texturedMaterial->AddTexture(binding);
	MaterialManager::Instance()->RegisterMaterial("Textured", texturedMaterial );

	SimpleShaderMaterial* gradientMaterial = new SimpleShaderMaterial("../Media/Shaders/Gradient.vert", "../Media/Shaders/Gradient.frag" );
	gradientMaterial->setRasterOps( new NoDepthRasterOps() );
	ShaderConstantVec4* bottomColor = new ShaderConstantVec4( "bottomColor" );
	bottomColor->setValue( Color(0.07,0.02f,0.15f,1) );
	ShaderConstantVec4* topColor = new ShaderConstantVec4( "topColor" );
	topColor->setValue( Color(0.4f,0.7f,0.6f,1.0f) );
	ShaderConstantCollection* colors = new ShaderConstantCollection();
	colors->AddConstant(topColor);
	colors->AddConstant(bottomColor);
	gradientMaterial->setShaderConstant( colors );
	MaterialManager::Instance()->RegisterMaterial("GradientWash", gradientMaterial );

	std::vector<ITextureDataObject*> renderTextures;
	renderTextures.push_back(imageTexture);
	//DepthBuffer* depthBuffer = new DepthBuffer(512,512,false);
	RenderTarget* diffuseFBO = new RenderTarget(renderTextures, 0);
	RenderManager::Instance()->RegisterRenderTarget("PaintFBO",diffuseFBO);


	//Load the material library document
	ticpp::Document materialDoc( fileName );
    materialDoc.LoadFile();

	// Get the root. This must be a material library definition tag.
	ticpp::Element* root = materialDoc.FirstChildElement();
	// Loop through all children (all material tags)
	ticpp::Iterator< ticpp::Element > child("material");
	for ( child = child.begin( root ); child != child.end(); child++ )
	{
		// Pass the material element to our helper utility that will
		// read in the data for each material type, create the material
		// and register it with our Material Manager.
		Crawfis::Factories::MaterialFactory::CreateRegisteredMaterial(*child);
	}
}

ISceneNode* LoadScene(std::string fileName)
{
	//Load the material library document
	ticpp::Document sceneDoc( fileName );
    sceneDoc.LoadFile();

	// Get the root. This must be a material library definition tag.
	ticpp::Element* root = sceneDoc.FirstChildElement();
	string type = root->Value();
	if( type != "scene" )
		throw "The first and only element in the xml file must be a scene tag";

	ISceneNode* rootNode = Crawfis::Factories::SceneNodeFactory::CreateSceneNode(root->FirstChild()->ToElement());

	return rootNode;
}

void CreateModelLibrary()
{
	IDrawable* sphere = new DrawableSphere(10000, false);
	ModelManager::Instance()->RegisterModel("Sphere10000", sphere);
	IDrawable* cube = new DrawableCube();
	ModelManager::Instance()->RegisterModel("Cube", cube);
	IDrawable* sphereVertex = new DrawableSphereVertex(10000, false);
	ModelManager::Instance()->RegisterModel("SphereVertex", sphereVertex);
	IDrawable* cubeVertex = new DrawableCubeVertex();
	ModelManager::Instance()->RegisterModel("CubeVertex", cubeVertex);
	IDrawable* floor = new DrawableFloor(20,30);
	ModelManager::Instance()->RegisterModel("Floor", floor);
	IDrawable* teapot = new DrawableTeapot();
	ModelManager::Instance()->RegisterModel("Teapot", teapot);
	IDrawable* square = new DrawableSquare();
	ModelManager::Instance()->RegisterModel("Background", square);
	ModelManager::Instance()->RegisterModel("Brush", square);
}

ISceneNode* CreateSceneGraph()
{
	CreateModelLibrary();
	LoadMaterialLibrary(materialLibrary);
	ISceneNode* rootNode = LoadScene(sceneFile);
	renderVisitor = new OpenGLErrorCheckVisitorDecorator(new RenderVisitor());
	return rootNode;
}

DrawModeController* CreateDrawModeNode(ISceneNode* rootNode)
{
	DrawModeController* drawModeController = new DrawModeController("DrawModeController", rootNode);
	return drawModeController;
}

ExaminerCameraNode* CreateExaminer(ISceneNode* rootNode)
{
	ExaminerCameraNode* examiner = new ExaminerCameraNode("Examiner", rootNode);
	examiner->setWidth(windowWidth);
	examiner->setHeight(windowHeight);
	return examiner;
}

void CreateGLUTWindow(std::string windowTitle)
{
	windowWidth = 800;
	windowHeight = 600;
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize( windowWidth, windowHeight );
	windowGUID = glutCreateWindow(windowTitle.c_str());
}

void InitializeOpenGLExtensions()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
	  /* Problem: glewInit failed, something is seriously wrong. */
	  fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	  throw "Error initializing GLEW";
	}
	//if (!GLEW_VERSION_2_1)
	//{
	//	throw "Fatal Error: OpenGL 2.1 is required";
	//}

	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void InitializeDevIL()
{
	::ilInit();
	::iluInit();
	::ilutInit();
	::ilOriginFunc( IL_ORIGIN_LOWER_LEFT );
	::ilEnable( IL_ORIGIN_SET );
}

void DisplayFrame()
{
	rootSceneNode->Accept(renderVisitor);
}

void ReshapeWindow(int newWidth, int newHeight)
{
	windowWidth = newWidth;
	windowHeight = newHeight;
	examinerController->setWidth(newWidth);
	examinerController->setHeight(newHeight);
}

void KeyboardController(unsigned char key, int x, int y)
{
	printf("Key Pressed: %c\n", key);
	std::vector<IKeyboardHandler*>::iterator handlerIterator;
	for( handlerIterator = keyboardHandlers.begin(); handlerIterator != keyboardHandlers.end(); handlerIterator++ )
	{
		(*handlerIterator)->KeyPress(key, x, y);
	}
}

void NumPadController(int key, int x, int y)
{
	std::vector<IKeyboardHandler*>::iterator handlerIterator;
	for( handlerIterator = keyboardHandlers.begin(); handlerIterator != keyboardHandlers.end(); handlerIterator++ )
	{
		(*handlerIterator)->NumPadPress(key, x, y);
	}
}

void MousePressController(int button, int state, int ix, int iy)
{
	std::vector<IMouseHandler*>::iterator handlerIterator;
	for( handlerIterator = mouseHandlers.begin(); handlerIterator != mouseHandlers.end(); handlerIterator++ )
	{
		(*handlerIterator)->MouseEvent(button, state, ix, iy);
	}
}

void MouseMotionController(int ix, int iy)
{
	std::vector<IMouseHandler*>::iterator handlerIterator;
	for( handlerIterator = mouseHandlers.begin(); handlerIterator != mouseHandlers.end(); handlerIterator++ )
	{
		(*handlerIterator)->MouseMoved(ix, iy);
	}
}

void IdleCallback()
{
}

void InitializeDevices()
{
	CreateGLUTWindow("OpenGL Demo Framework");
	InitializeOpenGLExtensions();
	TextureBindManagerOpenGL::Init();
	InitializeDevIL();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	InitializeDevices();

	GroupNode* rootGroupNode = new GroupNode("Root");
	ISceneNode* scene = CreateSceneGraph();

	DefaultController* overlay = new DefaultController("MainController", windowGUID);
	keyboardHandlers.push_back(overlay);
	DrawModeController* drawModeController = CreateDrawModeNode(scene);
	keyboardHandlers.push_back(drawModeController);
	examinerController = CreateExaminer(drawModeController);
	keyboardHandlers.push_back(examinerController);
	mouseHandlers.push_back(examinerController);

	rootGroupNode->AddChild(examinerController);
	rootGroupNode->AddChild(overlay);
	IRenderTarget* screen = new RenderTarget();
	RenderManager::Instance()->RegisterRenderTarget("Screen",screen);
	screen->setEnableCommand( new ClearFrameCommand(Colors::Brown) );
	screen->setDisableCommand( new SwapCommand(true) );
	RenderTargetProxy* frameBuffer = new RenderTargetProxy("Screen Display", "Screen", rootGroupNode);

	rootSceneNode = frameBuffer;

	PrintSceneVisitor* printVisitor = new PrintSceneVisitor();
	rootSceneNode->Accept(printVisitor);

	glutKeyboardFunc(KeyboardController);
	glutSpecialFunc(NumPadController);
	glutMouseFunc(MousePressController); 
	glutMotionFunc(MouseMotionController);

	glutDisplayFunc(DisplayFrame);
	glutReshapeFunc(ReshapeWindow);

	//glutIdleFunc(IdleCallback);

	glutMainLoop();
	return 0;
}