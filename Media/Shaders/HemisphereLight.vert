#version 330 core


layout(location=0)  in vec3 vertexPos;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 mvp;
uniform mat4 mv;

out vec3 fragVert;
out vec3 fragNormal;



out vec3 fragmentColor;


void main()
{
	gl_Position = mvp*vec4(vertexPos,1.0);
	mat3 normalMatrix = transpose(inverse(mat3(mv)));
	vec3 fragNormal = normalize(normalMatrix* vertexNormal);
    vec3 hemisphereDirection = vec3(1.0,0.0,0.0); // setting direction along x axis
   float NdotL	= dot(fragNormal, hemisphereDirection);
   // from [-1, 1] to [0, 1] range
   float lightInfluence	= NdotL * 0.5 + 0.5;
   // interpolate colors from upper and lower hemispheres
   vec3 upper = vec3(0.9,0.9,0.0);
   vec3 lower = vec3(0.0,0.0,0.9);
   fragmentColor = mix(upper, lower, lightInfluence);
}

