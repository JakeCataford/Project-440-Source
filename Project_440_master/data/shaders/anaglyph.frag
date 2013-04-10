 uniform sampler2DRect right;
 uniform sampler2DRect left;

 uniform vec2 u_display_resolution;

 varying vec2 v_texCoord;

void main()
{
	 vec2 finalCoord = v_texCoord * u_display_resolution;
	 // Screenspace xy -> gl_FragCoord.xy	 
	 vec3 l = texture2DRect(left,finalCoord).rgb; 
	 vec3 r = texture2DRect(right,finalCoord).rgb; 

	 float red = l.r;
	 float green = r.g;
     float blue = r.b;
	 gl_FragColor = vec4(red,green,blue,1.0);
}

