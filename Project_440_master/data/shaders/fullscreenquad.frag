#version 120

uniform sampler2DRect right;
uniform sampler2DRect left;

uniform vec2 u_display_resolution;

varying vec2 v_texCoord;

void main(void)
{
  vec3 texelr = texture2DRect(right,gl_FragCoord.xy).rgb; 
  vec3 texell = texture2DRect(left,gl_FragCoord.xy).rgb; 
  //gl_FragColor = vec4(v_texCoord.st, 0.0, 1.0);
  gl_FragColor = vec4(texelr.r, texell.gb, 1.0);
}
