uniform float time;

void main()
{
	gl_FrontColor = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;


	vec4 pos = gl_Vertex;
	pos.z = sin(pos.x*2.0 + time*2.0) * 0.5;
	gl_Position = ftransform();
}
