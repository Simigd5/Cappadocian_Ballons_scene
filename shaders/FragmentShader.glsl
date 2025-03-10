﻿#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
// TODO(student): Declare various other uniforms
uniform bool mix_textures;
// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.
    out_color = vec4(1);
    vec4 colour1 = texture(texture_1, texcoord);
	vec4 colour2 = texture(texture_2, texcoord);
	
	if (mix_textures == true)
	{
		out_color = mix(colour1, colour2, .5f);
	} else
	{
		out_color = colour1;

	}
	
	
	if (out_color.a < 0.5f)
	{
		discard;
	}
}
