#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 tex_coord;

out vec2 v_tex_coord;
out vec3 vColor;

void main()
{
	gl_Position = position;
	vColor = aColor;
	v_tex_coord = tex_coord;
}

/* --------------------------------------------------------------- */

#shader fragment
#version 330 core

layout(location =  0) out vec4 color;

in vec3 vColor;
in vec2 v_tex_coord;

uniform sampler2D u_texture;

void main()
{
	vec4 texcolor = texture(u_texture, v_tex_coord);
	color = texcolor;
};