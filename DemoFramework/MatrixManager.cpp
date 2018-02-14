#include "MatrixManager.h"
#include "Matrix.h"
#include<stack>
using namespace Crawfis::Graphics;

bool Crawfis::Graphics::MatrixManager::created = false;
GLenum mode;
Crawfis::Graphics::MatrixManager* Crawfis::Graphics::MatrixManager::instance = 0;
std::stack<Matrix4> Crawfis::Graphics::MatrixManager::modelView;
std::stack<Matrix4> Crawfis::Graphics::MatrixManager::projection;

MatrixManager::MatrixManager() {
}