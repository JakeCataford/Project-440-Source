uniform vec3 light;
uniform float fft[10];


void main() {

			float scalar = fft[int(mod(gl_Vertex.x, 14))];
			scalar /= 100;
			
            gl_TexCoord[0] = gl_MultiTexCoord0;
            gl_Position = ftransform() + scalar;
}