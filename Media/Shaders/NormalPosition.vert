varying vec3 vertexNormal;
varying vec3 eyePosition;
uniform mat4 ModelViewMatrix;
void main()
{
	gl_Position = ftransform();

	vertexNormal = vec3(gl_NormalMatrix * gl_Normal);
	vec4 ecPosition = ModelViewMatrix * gl_Vertex;
	eyePosition = vec3(ecPosition) / ecPosition.w;
}

