uniform vec4 bottomColor;
uniform vec4 topColor;
void main( )
{
	vec4 color = mix(bottomColor,topColor,gl_TexCoord[0].t);
      gl_FragColor = color;
} 