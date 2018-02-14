#version 330

layout ( triangles ) in;
layout ( triangle_strip, max_vertices = 3 ) out;

out vec3 fragNormal;

void main()
{
    vec3 A = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 B = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 normal = normalize(cross(A,B));
    gl_Position = gl_in[0].gl_Position;
	fragNormal = normal;
    EmitVertex();
	fragNormal = normal;
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();
	fragNormal = normal;
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();
    EndPrimitive();
}