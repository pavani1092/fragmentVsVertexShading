void main()
{
    // transform vertex to clip space coordinates
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    // Set the color
    gl_FrontColor = gl_Color;
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
