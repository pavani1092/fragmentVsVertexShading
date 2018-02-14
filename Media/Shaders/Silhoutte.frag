#version 330 core
in vec4 fragmentColor;
out vec4 color;

void main( )
{

	/*if(fragmentColor.a== 1.0){
		color = vec4(1,1,1,1);
	}else*/
		color = fragmentColor;
	 
}  