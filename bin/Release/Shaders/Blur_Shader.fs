uniform sampler2D tex0; 
uniform vec2 direction;
uniform float coef;
varying vec2 vTexCoord; 
void main() {
	vec4 sum = vec4(0.0); 
	vec2 startDir = -0.5*direction*4.0; 
	for (int i=0; i<5; i++) 
		sum += texture2D(tex0, vTexCoord + startDir + direction * float(i)) * (coef * i);
	gl_FragColor = sum;
}