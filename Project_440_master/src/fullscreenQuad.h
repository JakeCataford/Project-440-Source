#pragma once

#include "ofMain.h"

/*
 
 
*/

class FullscreenQuad {

private:
  static GLuint mVao;
  static GLuint mVbo;
  static bool   mBisSetup;

public:
  static void setup(GLuint pos_attrib=0, GLuint tex_attrib=1) {
    if (mBisSetup) return;
    
    // VAO + VBO
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    glGenBuffers(1, &mVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    
    float s = 1.0f;
    float verts[] = {
      -s, -s, 0.0f, 0.0f, // x, y, s, t
      s, -s, 1.0f, 0.0f,
      s, s, 1.0f, 1.0f,

      -s, -s, 0.0f, 0.0f,
      s, s, 1.0f, 1.0f,
      -s, s, 0.0f, 1.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    
    setAttributeLocations(pos_attrib, tex_attrib);
    
    mBisSetup = true;
  }

  static void setAttributeLocations(GLuint pos_attrib, GLuint tex_attrib) {
    glBindVertexArray(mVao);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);

    glEnableVertexAttribArray(pos_attrib);
    glEnableVertexAttribArray(tex_attrib);

    glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (GLvoid*)0);
    glVertexAttribPointer(tex_attrib, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (GLvoid*)8);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  static void draw() {
    glBindVertexArray(mVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
  }

  static void clear() {
    glDeleteVertexArrays(1, &mVao);
    glDeleteBuffers(1, &mVbo);
  }
};
