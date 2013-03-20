 
 uniform sampler2DRect tex0;

 uniform vec2 distortionParams;

 void main()
 {
	 vec2 texc = gl_TexCoord[0].xy;

	 texc.x += distortionParams.x * mod(texc.y,distortionParams.y);
	 
	 gl_FragColor = texture2DRect(tex0,texc); 


 }