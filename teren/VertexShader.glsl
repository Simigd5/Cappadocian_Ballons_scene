#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texcoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform sampler2D texture_0; // Height map texture
uniform float height_scale;  // Scaling factor for the height offset

out vec2 v_texture_coord;
out vec3 frag_world_position; 
out vec3 frag_world_normal;   
out float vertex_height;

void main()
{
    // Extrage poz i
    vec3 new_position = in_position;

    // Aplică deformarea pe axa Y folosind heightmap-ul
    float texelSize = 1.0 / 3.5;
    float height = texture(texture_0, in_texcoord).r;
    float hr = texture(texture_0, in_texcoord + vec2(texelSize, 0)).r; 
    float hu = texture(texture_0, in_texcoord + vec2(0, texelSize)).r; 

    // Deformarea poziției pe axa Y
    new_position.y += height * height_scale;

    // Calcularea diferențelor pe axele X si Z
    float dx = (hr - height) * height_scale;
    float dz = (hu - height) * height_scale;

    // Definirea vectorilor tangenta si bitangenta
    vec3 Tos = vec3(texelSize, dx, 0.0);
    vec3 Bos = vec3(0.0, dz, texelSize); 

    // Transmite coordonatele UV in inaltimea catre fragment shader
    v_texture_coord = in_texcoord;
    vertex_height = height;

    // Aplică transformarea de modelare pentru a obtine vectorii in sp lumii
    vec3 T_ws = (Model * vec4(Tos, 0.0)).xyz;
    vec3 B_ws = (Model * vec4(Bos, 0.0)).xyz;

    // Calculam normala folosind produsul vectorial dintre bitangenta si tangenta
    frag_world_normal = normalize(cross(B_ws, T_ws));

    // Transmite poz in sp lumii
    frag_world_position = (Model * vec4(new_position, 1.0)).xyz;

    // Transforma poz vârfului in sp de proiectie
    gl_Position = Projection * View * Model * vec4(new_position, 1.0);
}
