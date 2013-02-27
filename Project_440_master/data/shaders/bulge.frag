 varying highp vec2 texCoord;  

 uniform sampler2DRect tex0;
 uniform float width, height,radius;




 void main()
 {
	
     vec2 tex_size = vec2 (width, height);
	 vec2 texturecoord = gl_TexCoord[0].xy;
	 vec2 normcoord;
	 normcoord = texturecoord / (tex_size) - 1.0;
	 float r =  length (normcoord);
	 normcoord *= smoothstep (-0.8, 0.8, r*radius);
	 texturecoord = (normcoord + 1.0) * tex_size;
	 vec4 color = texture2DRect (tex0, texturecoord); 
	 gl_FragColor = color;
	 
 }