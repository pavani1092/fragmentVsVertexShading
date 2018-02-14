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
	//transforming position to worldspace
	gl_Position = mvp * vec4(vertexPos,1.0);

	 mat3 normalMatrix=transpose(inverse(mat3(mv)));//computing normalMatrix for normal transformations

	 fragNormal=normalize(normalMatrix*vertexNormal);//transforming normal
     fragVert=mat3(mv)*vertexPos; 
   
   // Set the color	
	fragmentColor = vec4(vertexColor.xyz,1.0);
  
	
}
