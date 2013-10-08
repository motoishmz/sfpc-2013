uniform float time;

void main()
{
	vec4 vertex = gl_Vertex;
	vertex.z = sin(vertex.x * 2.9 + time * 10.) * 0.25;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = gl_ModelViewProjectionMatrix * vertex;
}
