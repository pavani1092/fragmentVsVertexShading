#version 330 core
layout(location=0)  in vec3 vertexPos;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal;


uniform vec4 dummy;
uniform mat4 mvp;
uniform mat4 mv;

out vec3 fragVert;
out vec3 fragNormal;

out vec4 fragmentColor;

void main()
{
	gl_Position =mvp*vec4(vertexPos,1.0);

	mat3 normalMatrix = transpose(inverse(mat3(mv)));
	vec3 fragNormal = normalize(normalMatrix* vertexNormal);
	vec3 fragVert = vec3(mv*vec4(vertexPos,1.0));
	vec3 viewDir = normalize(-fragVert);
	float newOpacity = abs(dot(viewDir, fragNormal));

   fragmentColor = vec4( newOpacity,0.5,0.5,1.0); // changing red component with angle between  normal and campos
}

