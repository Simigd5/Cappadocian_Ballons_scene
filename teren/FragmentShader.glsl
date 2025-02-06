#version 330 core

in vec2 v_texture_coord;
in vec3 frag_world_position; // Poziția în spațiul lumii
in vec3 frag_world_normal;   // Normalul în spațiul lumii
in float vertex_height;

uniform sampler2D texture_1; // Textura pentru înălțimi joase
uniform sampler2D texture_2; // Textura pentru înălțimi mari
uniform float LOW_LIMIT;     // Limita inferioară pentru interpolare
uniform float HIGH_LIMIT;    // Limita superioară pentru interpolare

// Lumina punctiformă
//1
uniform vec3 light_position1; // Poziția luminii punctiforme
uniform vec3 light_color1;    // Culoarea luminii punctiforme

//2
uniform vec3 light_position2; // Poziția luminii punctiforme
uniform vec3 light_color2;    // Culoarea luminii punctiforme

//3
uniform vec3 light_position3; // Poziția luminii punctiforme
uniform vec3 light_color3;    // Culoarea luminii punctiforme

//4
uniform vec3 light_position4; // Poziția luminii punctiforme
uniform vec3 light_color4;    // Culoarea luminii punctiforme

//5
uniform vec3 light_position5; // Poziția luminii punctiforme
uniform vec3 light_color5;    // Culoarea luminii punctiforme

//6
uniform vec3 light_position6; // Poziția luminii punctiforme
uniform vec3 light_color6;    // Culoarea luminii punctiforme

//7
uniform vec3 light_position7; // Poziția luminii punctiforme
uniform vec3 light_color7;    // Culoarea luminii punctiforme

//8
uniform vec3 light_position8; // Poziția luminii punctiforme
uniform vec3 light_color8;    // Culoarea luminii punctiforme

//9
uniform vec3 light_position9; // Poziția luminii punctiforme
uniform vec3 light_color9;    // Culoarea luminii punctiforme

// Lumina direcțională (Soarele)
uniform vec3 light_direction; // Direcția luminii soarelui
uniform vec3 dir_light_color; // Culoarea luminii soarelui

// Material
uniform vec3 eye_position;       // Poziția camerei
uniform float material_kd;       // Coeficient difuz
uniform float material_ks;       // Coeficient specular
uniform int material_shininess;  // Luciu specular

out vec4 frag_color;

void main()
{
    // Step 1: Interpolarea texturilor
    float t = clamp((vertex_height - LOW_LIMIT) / (HIGH_LIMIT - LOW_LIMIT), 0.0, 1.0);
    vec4 color1 = texture(texture_1, v_texture_coord);
    vec4 color2 = texture(texture_2, v_texture_coord);

    // Culoarea terenului bazată pe înălțime
    vec4 terrain_color = mix(color1, color2, t);

    // Step 2: Calculul normalizat
    vec3 N = frag_world_normal;  // Normalul normalizat
    vec3 V = normalize(eye_position - frag_world_position); // Direcția privitorului (camera)

    // Lumina punctiformă1
    vec3 L_point1 = normalize(light_position1 - frag_world_position); // Direcția luminii punctiforme
    vec3 H_point1 = normalize(L_point1 + V); // Vectorul median pentru specular

    float diffuse_point1= max(dot(N, L_point1), 0.0);
    float specular_point1 = 0.0;
    if (diffuse_point1 > 0.0) {
        specular_point1 = pow(max(dot(N, H_point1), 0.0), material_shininess);
    }
   vec3 ambient1 = 0.03 * material_kd * light_color1; // Amplifică puțin lumina ambientală
vec3 diffuse1 = 0.08 * material_kd * diffuse_point1 * light_color1; // Crește contribuția difuză
vec3 point_light1 = ambient1 + diffuse1 + material_ks * specular_point1 * light_color1;

    
     // Lumina punctiformă2
    vec3 L_point2 = normalize(light_position2 - frag_world_position); // Direcția luminii punctiforme
    vec3 H_point2 = normalize(L_point2 + V); // Vectorul median pentru specular

    float diffuse_point2= max(dot(N, L_point2), 0.0);
    float specular_point2 = 0.0;
    if (diffuse_point2 > 0.0) {
        specular_point2 = pow(max(dot(N, H_point2), 0.0), material_shininess);
    }
 vec3 ambient2 = 0.03 * material_kd * light_color2; // Amplifică puțin lumina ambientală
vec3 diffuse2 = 0.05 * material_kd * diffuse_point2 * light_color2; // Crește contribuția difuză
vec3 point_light2 = ambient2 + diffuse2 + material_ks * specular_point2 * light_color2;

      // Lumina punctiformă3
    vec3 L_point3 = normalize(light_position3 - frag_world_position); // Direcția luminii punctiforme
    vec3 H_point3 = normalize(L_point3 + V); // Vectorul median pentru specular

    float diffuse_point3= max(dot(N, L_point3), 0.0);
    float specular_point3 = 0.0;
    if (diffuse_point3 > 0.0) {
        specular_point3 = pow(max(dot(N, H_point3), 0.0), material_shininess);
    }
    vec3 ambient3 = 0.03 * material_kd * light_color3; // Amplifică puțin lumina ambientală
vec3 diffuse3 = 0.05 * material_kd * diffuse_point3 * light_color3; // Crește contribuția difuză
vec3 point_light3 = ambient3 + diffuse3 + material_ks * specular_point3 * light_color3;
    
      // Lumina punctiformă4
    vec3 L_point4 = normalize(light_position4 - frag_world_position); // Direcția luminii punctiforme
    vec3 H_point4 = normalize(L_point4 + V); // Vectorul median pentru specular

    float diffuse_point4= max(dot(N, L_point4), 0.0);
    float specular_point4 = 0.0;
    if (diffuse_point4 > 0.0) {
        specular_point4 = pow(max(dot(N, H_point4), 0.0), material_shininess);
    }
    vec3 ambient4 = 0.05 * material_kd * light_color4; // Amplifică puțin lumina ambientală
vec3 diffuse4 =0.03 * material_kd * diffuse_point4 * light_color4; // Crește contribuția difuză
vec3 point_light4 = ambient4 + diffuse4 + material_ks * specular_point4 * light_color4;

      // Lumina punctiformă5
    vec3 L_point5 = normalize(light_position5 - frag_world_position); // Direcția luminii punctiforme
    vec3 H_point5 = normalize(L_point5 + V); // Vectorul median pentru specular

    float diffuse_point5= max(dot(N, L_point5), 0.0);
    float specular_point5 = 0.0;
    if (diffuse_point5 > 0.0) {
        specular_point5 = pow(max(dot(N, H_point5), 0.0), material_shininess);
    }
    vec3 ambient5 = 0.03 * material_kd * light_color5; // Amplifică puțin lumina ambientală
vec3 diffuse5 = 0.04 * material_kd * diffuse_point5 * light_color5; // Crește contribuția difuză
vec3 point_light5 = ambient5 + diffuse5 + material_ks * specular_point5 * light_color5;

      // Lumina punctiformă6
    vec3 L_point6 = normalize(light_position6 - frag_world_position); // Direcția luminii punctiforme
    vec3 H_point6 = normalize(L_point6 + V); // Vectorul median pentru specular

    float diffuse_point6= max(dot(N, L_point6), 0.0);
    float specular_point6 = 0.0;
    if (diffuse_point6 > 0.0) {
        specular_point6 = pow(max(dot(N, H_point6), 0.0), material_shininess);
    }
    vec3 ambient6 =0.03 * material_kd * light_color6; // Amplifică puțin lumina ambientală
vec3 diffuse6 = 0.03 * material_kd * diffuse_point6 * light_color6; // Crește contribuția difuză
vec3 point_light6 = ambient6 + diffuse6 + material_ks * specular_point6 * light_color6;

      // Lumina punctiformă7
    vec3 L_point7 = normalize(light_position7 - frag_world_position); // Direcția luminii punctiforme
    vec3 H_point7 = normalize(L_point7 + V); // Vectorul median pentru specular

    float diffuse_point7= max(dot(N, L_point7), 0.0);
    float specular_point7 = 0.0;
    if (diffuse_point7 > 0.0) {
        specular_point7 = pow(max(dot(N, H_point7), 0.0), material_shininess);
    }
   vec3 ambient7 = 0.03 * material_kd * light_color7; // Amplifică puțin lumina ambientală
vec3 diffuse7 =0.09 * material_kd * diffuse_point7 * light_color1; // Crește contribuția difuză
vec3 point_light7 = ambient7 + diffuse7 + material_ks * specular_point7 * light_color7;

      // Lumina punctiforma8
    vec3 L_point8 = normalize(light_position8 - frag_world_position); // Direcția luminii punctiforme
    vec3 H_point8 = normalize(L_point8 + V); // Vectorul median pentru specular

    float diffuse_point8= max(dot(N, L_point8), 0.0);
    float specular_point8 = 0.0;
    if (diffuse_point8 > 0.0) {
        specular_point8 = pow(max(dot(N, H_point8), 0.0), material_shininess);
    }
  vec3 ambient8 = 0.03 * material_kd * light_color8; // Amplifică puțin lumina ambientală
vec3 diffuse8 =0.05 * material_kd * diffuse_point8 * light_color8; // Crește contribuția difuză
vec3 point_light8 = ambient8 + diffuse8 + material_ks * specular_point8 * light_color8;

      // Lumina punctiformă9
    vec3 L_point9 = normalize(light_position9 - frag_world_position); // Direcția luminii punctiforme
    vec3 H_point9 = normalize(L_point9 + V); // Vectorul median pentru specular

    float diffuse_point9= max(dot(N, L_point9), 0.0);
    float specular_point9 = 0.0;
    if (diffuse_point9 > 0.0) {
        specular_point9 = pow(max(dot(N, H_point9), 0.0), material_shininess);
    }
   vec3 ambient9 = 0.03 * material_kd * light_color9; // Amplifică puțin lumina ambientală
vec3 diffuse9 = 0.07 * material_kd * diffuse_point9 * light_color9; // Crește contribuția difuză
vec3 point_light9 = ambient9 + diffuse9 + material_ks * specular_point9 * light_color9;
  
    // Lumina direcțională (Soarele)
    vec3 L_dir = normalize(-light_direction); // Direcția luminii soarelui
    vec3 H_dir = normalize(L_dir + V); // Vectorul median pentru specular

    float diffuse_dir = max(dot(N, L_dir), 0.0);
    float specular_dir = 0.0;
    if (diffuse_dir > 0.0) {
        specular_dir = pow(max(dot(N, H_dir), 0.0), material_shininess);
    }
    vec3 directional_light = material_kd * diffuse_dir * dir_light_color + material_ks * specular_dir * dir_light_color;

    // Componenta ambientală
    float ambient_light = 0.3;
    vec3 ambient = ambient_light * terrain_color.rgb;

    // Combinația totală de lumină
    vec3 final_color = ambient + point_light1+point_light2+point_light3+point_light4+point_light5+point_light6+point_light7+point_light8+point_light9 + directional_light; 
    final_color *= terrain_color.rgb;

    // Setăm culoarea finală
    frag_color = vec4(final_color, terrain_color.a);
}