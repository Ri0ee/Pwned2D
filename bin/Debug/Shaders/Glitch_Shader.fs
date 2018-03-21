uniform sampler2D tex0;
uniform vec2 resolution;
uniform float coef;
varying vec2 vTexCoord;

void main(void)
{
	vec3 Color = vec3(0.0, 0.0, 0.0); vec2 p = vec2(1.0 / resolution.xy);
	
	Color.r = texture2D(tex0, vec2(vTexCoord.x - 0.002 * coef, vTexCoord.y)).r;
	Color.g = texture2D(tex0, vec2(vTexCoord.x - 0.003 * coef, vTexCoord.y)).g;
	Color.b = texture2D(tex0, vec2(vTexCoord.x - 0.004 * coef, vTexCoord.y)).b;
	
	gl_FragColor = vec4(Color, texture2D(tex0, vTexCoord).a);
}