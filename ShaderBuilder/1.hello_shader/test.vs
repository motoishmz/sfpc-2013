uniform float time; // ellapsed time

const float power = 1.2;
const float div = 1.4;
const float speed = 2.0;

void main()
{
	vec4 vertex = gl_Vertex;
	float x = sin(vertex.x * div + time * speed);
//Ω	float y = cos(vertex.y * div + time * speed);
	vertex.z = (x ) * power;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = gl_ModelViewProjectionMatrix * vertex;
}
