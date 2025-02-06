#version 330

// Input
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texcoord;
layout(location = 3) in vec3 v_color; // Culoarea obiectului

// Uniform properties
uniform mat4 Model;      // Matricea Modelului
uniform mat4 View;       // Matricea Viziunii
uniform mat4 Projection; // Matricea Proiecției
uniform vec3 light_position1;   // Poziția luminii punctiforme (folosită pentru animație)
uniform vec3 light_position2;   // Poziția luminii punctiforme (folosită pentru animație)
uniform vec3 light_position3;   // Poziția luminii punctiforme (folosită pentru animație)
uniform vec3 light_position4;   // Poziția luminii punctiforme (folosită pentru animație)
uniform vec3 light_position5;   // Poziția luminii punctiforme (folosită pentru animație)
uniform vec3 light_position6;   // Poziția luminii punctiforme (folosită pentru animație)
uniform vec3 light_position7;   // Poziția luminii punctiforme (folosită pentru animație)
uniform vec3 light_position8;   // Poziția luminii punctiforme (folosită pentru animație)
uniform vec3 light_position9;   // Poziția luminii punctiforme (folosită pentru animație)
uniform float time;             // Timp pentru animație

// Output to Fragment Shader
out vec2 v_texture_coord;
out vec3 frag_world_position;  // Poziția în spațiul lumii
out vec3 frag_world_normal;    // Normalul în spațiul lumii

void main()
{
    // Transmit coordonatele de texturare către fragment shader
    v_texture_coord = in_texcoord;

    // Mutăm coordonatele de texturare pentru efecte animate
    if (time >= 0) {
        v_texture_coord.x -= time / 10.0f; // Mișcare în direcția X
    }

    // Transformăm poziția din spațiul modelului în spațiul lumii
    frag_world_position = (Model * vec4(in_position, 1.0)).xyz;

    // Transformăm normalul din spațiul modelului în spațiul lumii
    frag_world_normal = normalize(mat3(Model) * in_normal);

    // Calculăm poziția finală a vertebrului în spațiul ecranului
    gl_Position = Projection * View * Model * vec4(in_position, 1.0);
}
