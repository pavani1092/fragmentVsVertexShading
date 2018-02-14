uniform sampler2D texture;
void main( )
{
	vec4 color = texture2D( texture, gl_TexCoord[0].st );
      gl_FragColor = color * gl_Color;
      //gl_FragColor = vec4(gl_TexCoord[0].st,1,1) * gl_Color;
} 