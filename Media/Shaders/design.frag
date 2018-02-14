#version 330 core
in vec3 fragVert;
in vec3 fragNormal;
in vec4 fragmentColor;
out vec4 color;

struct Material{
vec4 ambient;
vec4 diffuse;
vec4 specular;
float shininess;
};

struct Light{
vec4 position;
vec4 intensity;
};


uniform int lightCount;
uniform Material material;
uniform Light lights[10];




void main( )
{

		
		vec4 lightSum=vec4(0.0,0.0,0.0,0.0);

		for(int i=0;i<lightCount;i++){

			vec3 L = normalize(lights[i].position.xyz - fragVert);   
			vec3 E= normalize(-fragVert);
			vec3 R= normalize(reflect(-L,fragNormal));



			vec4 Iamb=material.ambient;
		
			float angleNL =clamp(dot(fragNormal,L),0.0,1.0);
			vec4 Idiff = material.diffuse * angleNL *lights[i].intensity;  
	
			float angleRE=clamp(dot(R,E),0.0,1.0);

			vec4 Ispec = material.specular*lights[i].intensity * pow(angleRE,material.shininess);
			Ispec = clamp(Ispec, 0.0, 1.0); 
			lightSum+=Iamb+Idiff+Ispec;
			
		}

	vec4 outColor = fragmentColor;
	float x =  mod(floor(gl_FragCoord.x),10.0);
    float y =  mod(floor(gl_FragCoord.y),10.0);
    float radisSq = 5.0*(x-5)*(x-5) + 2.0*(y-5)*(y-5);//ellipses 
    if(radisSq < 25) {
		 outColor = vec4(0.3,0.5,0.0,1.0); // value changing with slope;
  }
    color = outColor;//+lightSum;
	 
}  