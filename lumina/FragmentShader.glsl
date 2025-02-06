#version 330 core

in vec2 v_texture_coord;
in vec3 frag_world_position; // Poziția în spațiul lumii
in vec3 frag_world_normal;   // Normalul în spațiul lumii

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform bool mix_textures;
uniform vec3 light_position1;  // Poziția luminii punctiforme
uniform vec3 light_color1;     // Culoarea luminii punctiforme
uniform vec3 light_position2;  // Poziția luminii punctiforme
uniform vec3 light_color2;     // Culoarea luminii punctiforme
uniform vec3 light_position3;  // Poziția luminii punctiforme
uniform vec3 light_color3;     // Culoarea luminii punctiforme
uniform vec3 light_position4;  // Poziția luminii punctiforme
uniform vec3 light_color4;     // Culoarea luminii punctiforme
uniform vec3 light_position5;  // Poziția luminii punctiforme
uniform vec3 light_color5;     // Culoarea luminii punctiforme
uniform vec3 light_position6;  // Poziția luminii punctiforme
uniform vec3 light_color6;     // Culoarea luminii punctiforme
uniform vec3 light_position7;  // Poziția luminii punctiforme
uniform vec3 light_color7;     // Culoarea luminii punctiforme
uniform vec3 light_position8;  // Poziția luminii punctiforme
uniform vec3 light_color8;     // Culoarea luminii punctiforme
uniform vec3 light_position9;  // Poziția luminii punctiforme
uniform vec3 light_color9;     // Culoarea luminii punctiforme
uniform vec3 light_direction;  // Direcția luminii direcționale
uniform vec3 eye_position;     // Poziția camerei
uniform vec3 object_color;     // Culoarea obiectului
uniform float material_kd;     // Coeficient difuz
uniform float material_ks;     // Coeficient specular
uniform int material_shininess; // Luciu specular

// Output color
layout(location = 0) out vec4 out_color;

void main()
{
    // 1. Sampling textures
    vec4 color1 = texture(texture_1, v_texture_coord);
    vec4 color2 = texture(texture_2, v_texture_coord);
    vec4 final_texture_color = mix_textures ? mix(color1, color2, 0.5) : color1;

    // 2. Normalize normals
    vec3 N = normalize(frag_world_normal);

    // 3. Compute view direction
    vec3 V = normalize(eye_position - frag_world_position);

    // --- Point Light ---
    //1
    vec3 L_point1 = normalize(light_position1 + frag_world_position);
    float distance_to_light1 = length(light_position1 - frag_world_position);
    float attenuation1 = 1.0 / (1.0 + 0.14 * distance_to_light1 + 0.07 * distance_to_light1 * distance_to_light1);

    float diffuse_point1 = max(dot(N, L_point1), 0.0);
    float specular_point1 = 0.0;

    if (diffuse_point1 > 0.0) {
        vec3 H_point1 = normalize(L_point1 + V);
        specular_point1 = pow(max(dot(N, H_point1), 0.0), material_shininess);
    }

    vec3 point_light_color1 = light_color1*1.5 * (material_kd * diffuse_point1 + material_ks * specular_point1) * attenuation1;

    //2
    vec3 L_point2 = normalize(light_position2 + frag_world_position);
    float distance_to_light2 = length(light_position2 - frag_world_position);
    float attenuation2 = 1.0 / (1.0 + 0.14 * distance_to_light2 + 0.07 * distance_to_light2 * distance_to_light2);

    float diffuse_point2 = max(dot(N, L_point2), 0.0);
    float specular_point2 = 0.0;

    if (diffuse_point2 > 0.0) {
        vec3 H_point2 = normalize(L_point2 + V);
        specular_point2 = pow(max(dot(N, H_point2), 0.0), material_shininess);
    }

    vec3 point_light_color2 = light_color2*1.5 * (material_kd * diffuse_point2 + material_ks * specular_point2) * attenuation2;

    //3
    vec3 L_point3 = normalize(light_position3 + frag_world_position);
    float distance_to_light3 = length(light_position3 - frag_world_position);
    float attenuation3 = 1.0 / (1.0 + 0.14 * distance_to_light3 + 0.07 * distance_to_light3 * distance_to_light3);

    float diffuse_point3 = max(dot(N, L_point3), 0.0);
    float specular_point3 = 0.0;

    if (diffuse_point3 > 0.0) {
        vec3 H_point3 = normalize(L_point3 + V);
        specular_point3 = pow(max(dot(N, H_point3), 0.0), material_shininess);
    }

    vec3 point_light_color3 = light_color3*1.5 * (material_kd * diffuse_point3 + material_ks * specular_point3) * attenuation3;

    //4
    vec3 L_point4 = normalize(light_position4 + frag_world_position);
    float distance_to_light4 = length(light_position4 - frag_world_position);
    float attenuation4 = 1.0 / (1.0 + 0.14 * distance_to_light4 + 0.07 * distance_to_light4 * distance_to_light4);

    float diffuse_point4 = max(dot(N, L_point4), 0.0);
    float specular_point4 = 0.0;

    if (diffuse_point4 > 0.0) {
        vec3 H_point4 = normalize(L_point4 + V);
        specular_point4 = pow(max(dot(N, H_point4), 0.0), material_shininess);
    }

    vec3 point_light_color4 = light_color4*1.5 * (material_kd * diffuse_point4 + material_ks * specular_point4) * attenuation4;

    //5
    vec3 L_point5 = normalize(light_position5 + frag_world_position);
    float distance_to_light5 = length(light_position5 - frag_world_position);
    float attenuation5 = 1.0 / (1.0 + 0.14 * distance_to_light5 + 0.07 * distance_to_light5 * distance_to_light5);

    float diffuse_point5 = max(dot(N, L_point5), 0.0);
    float specular_point5 = 0.0;

    if (diffuse_point5 > 0.0) {
        vec3 H_point5 = normalize(L_point5 + V);
        specular_point5 = pow(max(dot(N, H_point5), 0.0), material_shininess);
    }

    vec3 point_light_color5 = light_color5*1.5 * (material_kd * diffuse_point5 + material_ks * specular_point5) * attenuation5;

    //6
    vec3 L_point6 = normalize(light_position6 + frag_world_position);
    float distance_to_light6 = length(light_position6 - frag_world_position);
    float attenuation6 = 1.0 / (1.0 + 0.14 * distance_to_light6 + 0.07 * distance_to_light6 * distance_to_light6);

    float diffuse_point6 = max(dot(N, L_point6), 0.0);
    float specular_point6 = 0.0;

    if (diffuse_point6 > 0.0) {
        vec3 H_point6 = normalize(L_point6 + V);
        specular_point6 = pow(max(dot(N, H_point6), 0.0), material_shininess);
    }

    vec3 point_light_color6 = light_color6*1.5 * (material_kd * diffuse_point6 + material_ks * specular_point6) * attenuation6;

     //7
    vec3 L_point7 = normalize(light_position7 + frag_world_position);
    float distance_to_light7 = length(light_position7 - frag_world_position);
    float attenuation7 = 1.0 / (1.0 + 0.14 * distance_to_light7 + 0.07 * distance_to_light7 * distance_to_light7);

    float diffuse_point7 = max(dot(N, L_point7), 0.0);
    float specular_point7 = 0.0;

    if (diffuse_point7 > 0.0) {
        vec3 H_point7 = normalize(L_point7 + V);
        specular_point7 = pow(max(dot(N, H_point7), 0.0), material_shininess);
    }

    vec3 point_light_color7 = light_color7*1.5 * (material_kd * diffuse_point7 + material_ks * specular_point7) * attenuation7;

    //8
    vec3 L_point8 = normalize(light_position8 + frag_world_position);
    float distance_to_light8 = length(light_position8 - frag_world_position);
    float attenuation8 = 1.0 / (1.0 + 0.14 * distance_to_light8 + 0.07 * distance_to_light8 * distance_to_light8);

    float diffuse_point8 = max(dot(N, L_point8), 0.0);
    float specular_point8 = 0.0;

    if (diffuse_point8 > 0.0) {
        vec3 H_point8 = normalize(L_point8 + V);
        specular_point8 = pow(max(dot(N, H_point8), 0.0), material_shininess);
    }

    vec3 point_light_color8 = light_color8*1.5 * (material_kd * diffuse_point8 + material_ks * specular_point8) * attenuation8;

     //9
    vec3 L_point9 = normalize(light_position9 + frag_world_position);
    float distance_to_light9 = length(light_position9 - frag_world_position);
    float attenuation9 = 1.0 / (1.0 + 0.14 * distance_to_light9 + 0.07 * distance_to_light9 * distance_to_light9);

    float diffuse_point9 = max(dot(N, L_point9), 0.0);
    float specular_point9 = 0.0;

    if (diffuse_point9 > 0.0) {
        vec3 H_point9 = normalize(L_point9 + V);
        specular_point9 = pow(max(dot(N, H_point9), 0.0), material_shininess);
    }

    vec3 point_light_color9 = light_color9*1.5 * (material_kd * diffuse_point9 + material_ks * specular_point9) * attenuation9;

    // --- Directional Light ---
    vec3 L_dir = normalize(-light_direction);
    float diffuse_dir = max(dot(N, L_dir), 0.0);
    float specular_dir = 0.0;

    if (diffuse_dir > 0.0) {
        vec3 H_dir = normalize(L_dir + V);
        specular_dir = pow(max(dot(N, H_dir), 0.0), material_shininess);
    }

    vec3 directional_light_color = vec3(1.0, 1.0, 1.0) *1.9f* (material_kd * diffuse_dir + material_ks * specular_dir);

    // --- Combine Lighting ---
    float ambient_light = 0.2;
    vec3 final_light_color = ambient_light * object_color + point_light_color1+point_light_color2+point_light_color3+point_light_color4+ point_light_color5+ point_light_color6+ point_light_color7+ point_light_color8+ point_light_color9 + directional_light_color;

    // 4. Apply lighting to texture
    vec3 final_color = final_texture_color.rgb * final_light_color;

    // 5. Set final fragment color
    out_color = vec4(final_color, final_texture_color.a);

    // 6. Discard transparent fragments
    if (out_color.a < 0.5) {
        discard;
    }
}
