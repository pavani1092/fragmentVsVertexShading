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


uniform Light lights[10];
uniform Material material;
uniform int lightCount;
uniform vec4 Color;


void main( )
{

		
		vec4 lightVal=vec4(0.0,0.0,0.0,0.0);

		for(int i=0;i<lightCount;i++){

			vec3 L; //light direction
			if(lights[i].position.w == 0.0) {//directional light
				 L = normalize(lights[i].position.xyz);   
			}else{
				 L = normalize(lights[i].position.xyz - fragVert);   //point light
			}
			vec3 E= normalize(-fragVert); //cameradirection
			vec3 R= normalize(reflect(-L,fragNormal)); //reflection



			vec4 Iamb=material.ambient; //ambient component
		
			float cosA=clamp(dot(fragNormal,L),0.0,1.0);
			vec4 Idiff = material.diffuse * cosA *lights[i].intensity;  //diffuse component
	
			float cosTheta=clamp(dot(R,E),0.0,1.0);

			vec4 Ispec = material.specular*lights[i].intensity * pow(cosTheta,material.shininess);//specular component
			Ispec = clamp(Ispec, 0.0, 1.0); 
			lightVal=lightVal+Iamb+Idiff+Ispec;
			
		}

	

    color = fragmentColor+lightVal;
	 
}  
