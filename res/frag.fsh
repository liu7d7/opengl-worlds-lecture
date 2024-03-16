#version 460

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec4 v_color;

layout (location = 0) out vec4 f_color;

void main() {
  f_color = v_color;
}