#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform sampler2D dep;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform float heightMult;
out vec2 coord;
out vec3 n_p;

void main()
{
    float height = texture(dep, texcoord).r;
	vec3 new_pos = vec3(position.x, position.y, position.z);
	gl_Position = projection * view * model * vec4(new_pos, 1.0f);
	n_p = new_pos;
	coord = texcoord;
}
