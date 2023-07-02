#pragma once

#include <string>

const std::string vertex_source {
    "#version 330\n"
    "\n"
    "layout (location = 0) in vec2 a_pos;\n"
    "layout (location = 1) in vec2 a_uv;\n"
    "\n"
    "out vec2 v_uv;\n"
    "\n"
    "void main() {\n"
    "    v_uv = a_uv;\n"
    "    gl_Position = vec4(a_pos, 0.0, 1.0);\n"
    "}"};