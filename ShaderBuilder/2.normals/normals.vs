uniform float time;

void main()
{
	gl_FrontColor.rgb = gl_Normal.xyz * sin(time * 5.) * 3.;
	gl_FrontColor.a = 1.0;

	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
