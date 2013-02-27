 
 uniform sampler2DRect tex0;

 void main()
 {
	 vec2 texc = gl_TexCoord[0].xy;
	  
	 gl_FragColor = texture2DRect (tex0, texc);
	 
 }