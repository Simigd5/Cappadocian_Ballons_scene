#version 330 core

// Input
layout(location = 0) in vec3 v_position;      // Poziția verticelor
layout(location = 1) in vec3 v_normal;        // Normalul
layout(location = 2) in vec2 v_texture_coord; // Coordonatele de texturare
layout(location = 3) in vec3 v_color;         // Culoarea obiectului

// Uniform properties
uniform mat4 Model;      // Matricea Modelului
uniform mat4 View;       // Matricea viziunii
uniform mat4 Projection; // Matricea proiecției
uniform int num_lights;  // Numărul de lumini
uniform vec3 light_positions[10];     // Pozițiile surselor de lumină (max 10)
uniform vec3 light_intensities[10];   // Intensitățile fiecărei lumini (max 10)
uniform vec3 eye_position;            // Poziția camerei
uniform float time;                   // Timp pentru animație

// Output to Fragment Shader
out vec3 frag_world_position;  // Poziția în spațiul lumii
out vec3 frag_world_normal;    // Normalul în spațiul lumii
out vec2 texcoord;             // Coordonatele de texturare

// Transmit informațiile despre lumină către fragment shader
out vec3 light_positions_out[10];  // Pozițiile surselor de lumină
out vec3 light_intensities_out[10]; // Intensitățile luminii

void main()
{
    // 1. Coord texel - animație
    texcoord = v_texture_coord;

    // Animație bazată pe timp (mișcare pe x și efect de undă pe y)
    if (time >= 0.0) {
        texcoord = vec2(texcoord.x - time / 10.0, texcoord.y + sin(time * 0.5) * 0.05);
    }

    // 2. Deformare bazată pe poziția `y`
    vec3 modifiedPosition = v_position;

    if (v_position.y >= -0.9 && v_position.y <= 0.0) {
        float stretchFactor = 1.5 + (0.4 + v_position.y) * 0.1;
        modifiedPosition.y *= stretchFactor;
    }

    // 3. Transformări în spațiul lumii
    frag_world_position = (Model * vec4(modifiedPosition, 1.0)).xyz;
    frag_world_normal = normalize(mat3(Model) * v_normal); // Normalizat pentru corectitudine

    // 4. Transmitere poziții și intensități ale luminilor
    for (int i = 0; i < num_lights; i++) {
        light_positions_out[i] = light_positions[i];
        light_intensities_out[i] = light_intensities[i];
    }

    // 5. Poziția finală în spațiul de proiecție
    gl_Position = Projection * View * Model * vec4(modifiedPosition, 1.0);
}
