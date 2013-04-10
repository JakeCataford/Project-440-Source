#version 120

attribute vec4 a_vertex;
attribute vec2 a_texCoord;

varying vec2 v_texCoord;

void main(void)
{
  v_texCoord = a_texCoord.st;
  
  gl_Position = a_vertex;
}
