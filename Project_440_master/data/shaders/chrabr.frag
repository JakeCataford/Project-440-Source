 
 uniform sampler2DRect tex0;
 uniform float width, height, amount, intensity;



 void main()
 {
	 vec2 texc = gl_TexCoord[0].xy;
	 

	 vec4 finalColor = vec4(0.0,0.0,0.0,intensity);
	 texc.x -= amount;
	 vec4 color = texture2DRect (tex0, texc);
	 finalColor.x = color.x;

	 texc.x += amount/2;
	 color = texture2DRect (tex0, texc);
	 finalColor.y = color.y;

	 texc.x -= amount*2;
	 color = texture2DRect (tex0, texc);
	 finalColor.z = color.z;
	  
	 gl_FragColor = finalColor;
	 
 }