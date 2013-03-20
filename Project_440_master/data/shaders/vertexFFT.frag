 
 uniform sampler2DRect tex0;

 void main()
 {
	 float z = gl_TexCoord[0].z;
	 if(z < 1000){
		gl_FragColor = vec4(1.0,1.0,1.0,1.0);
	 }else{
		gl_FragColor = vec4(0.0,0.0,0.0,0.0);
	 }
 }