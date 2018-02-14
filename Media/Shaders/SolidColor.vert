#version 330 core
//layout(location = 1) in vec3 vertexColor;
//out vec4 fragmentColor;
uniform mat4 ModelViewProjectionMatrix
void main()
{
    // transform vertex to clip space coordinates
    gl_Position = ModelViewProjectionMatrix * gl_Vertex;
    // Set the color
    //fragmentColor = vec4(vertexColor.xyz,1.0);
}
