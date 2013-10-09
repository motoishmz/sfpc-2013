uniform float time;

void main()
{
	gl_PointSize = 2.0;
	gl_FrontColor = vec4( sin(time) );
	gl_FrontColor.a = 1.0;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
