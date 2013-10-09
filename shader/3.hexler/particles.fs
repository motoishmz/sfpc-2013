uniform sampler2D tex;
uniform float time;

void main()
{
	float color = 0.0;
	vec2 spec = vec2(time);
	vec2 resolution = vec2(512.0, 512.0);
	vec2 uv = (gl_FragCoord.xy / resolution) * 1.0 - 1.0;

	uv.x += sin(time*6.0 + uv.y*1.5) * spec.y;
	color += abs(1.0/uv.x) * spec.x;
	
	gl_FragColor = vec4(color, color, color, 1.0);
}
