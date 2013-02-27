uniform sampler2DRect tex0;
 uniform float width, height, amount, intensity;

void main()
{
   vec4 sum = vec4(0);
   vec2 texcoord = gl_TexCoord[0].xy;
   int j;
   int i;

   for( i= -4 ;i < 4; i++)
   {
        for (j = -3; j < 3; j++)
        {
            sum += texture2DRect(tex0, texcoord + vec2(j, i)*0.004) * 0.25;
        }
   }
       if (texture2DRect(tex0, texcoord).r < 0.3)
    {
       gl_FragColor = sum*sum*0.012 + texture2DRect(tex0, texcoord);
    }
    else
    {
        if (texture2DRect(tex0, texcoord).r < 0.5)
        {
            gl_FragColor = sum*sum*0.009 + texture2DRect(tex0, texcoord);
        }
        else
        {
            gl_FragColor = sum*sum*0.0075 + texture2DRect(tex0, texcoord);
        }
    }
}