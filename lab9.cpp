#include "lab_m1/lab9/lab9.h"
#include "lab_m1/lab4/transform3D.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab9::Lab9()
{
}


Lab9::~Lab9()
{
}


void Lab9::Init()
{
    // Create the quad for the gradient background
    {
        vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(-1, -1, 0)), // Bottom-left
            VertexFormat(glm::vec3(1, -1, 0)),  // Bottom-right
            VertexFormat(glm::vec3(-1, 1, 0)),  // Top-left
            VertexFormat(glm::vec3(1, 1, 0))    // Top-right
        };

        vector<unsigned int> indices = { 0, 1, 2, 1, 3, 2 }; // Two triangles for the quad

        Mesh* quad = new Mesh("gradient_quad");
        quad->InitFromData(vertices, indices);
        meshes[quad->GetMeshID()] = quad;
    }
    {
        Shader* shader = new Shader("GradientShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "GradientShader", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "GradientShader", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Shader* shader = new Shader("lumina");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "lumina", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "lumina", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("teren");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "teren", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "teren", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("balon");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "balon", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "balon", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Light & material properties
    {
        lightDirection = glm::vec3(-1.0f, -1.0f, -1.0f);  // Direction of the directional light
        lightColor = glm::vec3(1.0f, 1.0f, 1.0f);  // White light (e.g., sunlight)

        //lightPosition = glm::vec3(0, 0.5, 0);
        materialShininess = 15;
        materialKd = 0.4;
        materialKs = 0.6;

    }

    balloons.push_back({ 9.5f, 4.0f, 0.4f, 0.5f });  // Balon 1
    balloons.push_back({ 11.0f, 5.0f, 0.5f, 0.8f });  // Balon 3
    balloons.push_back({ 15.5f, 3.0f, 0.3f, 0.3f });  // Balon 2

    balloons1.push_back({ 3.5f, 0.9f, 0.5f, 0.7f });  // Balon 1
    balloons1.push_back({ 13.5f, 6.0f, 0.3f, 0.7f });  // Balon 3
    balloons1.push_back({ 8.5f, 3.0f, 0.5f, 0.5f });  // Balon 2

    balloons2.push_back({ 6.5f, 2.5f, 0.3f, 0.7f });  // Balon 1
    balloons2.push_back({ 11.5f, 7.0f, 0.5f, 0.8f });  // Balon 3
    balloons2.push_back({ 14.5f, 5.0f, 0.4f, 0.6f });  // Balon 2

    balonMic.push_back({ 6.5f, 5.0f, 0.3f, 0.7f });  // Balon 1
    balonMic.push_back({ 6.5f, 1.0f, 0.3f, 0.7f });  // Balon 1
    balonMic.push_back({ 6.5f, 1.0f, 0.3f, 0.7f });  // Balon 1
    balonMic.push_back({ 6.5f, 1.0f, 0.3f, 0.7f });  // Balon 1
    balonMic.push_back({ 6.5f, 1.0f, 0.3f, 0.7f });  // Balon 1

    avion.push_back({ 6.5f, 4.0f, 0.3f, 0.7f });  // Balon 1
    avion.push_back({ 6.5f, 1.0f, 0.3f, 0.7f });  // Balon 1
    avion.push_back({ 6.5f, 1.0f, 0.3f, 0.7f });  // Balon 1
    avion.push_back({ 6.5f, 1.0f, 0.3f, 0.7f });  // Balon 1
    avion.push_back({ 6.5f, 1.0f, 0.3f, 0.7f });  // Balon 1

    // Initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0;
    translateZ = 0;

    // Initialize sx, sy and sz (the scale factors)
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;

    // Initialize angular steps
    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;

    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "textures");

    // Load textures
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "grass_bilboard.png").c_str(), GL_REPEAT);
        mapTextures["grass"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "crate.jpg").c_str(), GL_REPEAT);
        mapTextures["crate"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "earth.png").c_str(), GL_REPEAT);
        mapTextures["earth"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation", "bamboo", "bamboo.png").c_str(), GL_REPEAT);
        mapTextures["bamboo"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "blue.jpg").c_str(), GL_REPEAT);
        mapTextures["blue"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "pink.jpg").c_str(), GL_REPEAT);
        mapTextures["pink"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "pastel.jpg").c_str(), GL_REPEAT);
        mapTextures["pastel"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "yellow.png").c_str(), GL_REPEAT);
        mapTextures["yellow"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "paper.jpg").c_str(), GL_REPEAT);
        mapTextures["paper"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "heightmap256.png").c_str(), GL_REPEAT);
        mapTextures["heightmap"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "sand.png").c_str(), GL_REPEAT);
        mapTextures["sand"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "rock.png").c_str(), GL_REPEAT);
        mapTextures["rock"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "sun.jpg").c_str(), GL_REPEAT);
        mapTextures["sun"] = texture;
    }
    {
        mapTextures["random"] = CreateRandomTexture(25, 25);
    }

    // Load meshes
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("bamboo");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation", "bamboo"), "bamboo.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane256.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("ata");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "ata.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("avion");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "avion.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("balonMic");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "balloon.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    // Create a simple quad
    {
        vector<glm::vec3> vertices
        {
            glm::vec3(0.5f,   0.5f, 0.0f),    // top right
            glm::vec3(0.5f,  -0.5f, 0.0f),    // bottom right
            glm::vec3(-0.5f, -0.5f, 0.0f),    // bottom left
            glm::vec3(-0.5f,  0.5f, 0.0f),    // top left
        };

        vector<glm::vec3> normals
        {
            glm::vec3(0, 1, 1),
            glm::vec3(1, 0, 1),
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0)
        };

        vector<glm::vec2> textureCoords
        {
            // TODO(student): Complete texture coordinates for the square
            glm::vec2(0.0f, 0.0f),
            glm::vec2(0.f, 1.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(1.f, 0.f)
        };

        vector<unsigned int> indices =
        {
            0, 1, 3,
            1, 2, 3
        };

        Mesh* mesh = new Mesh("square");
        mesh->InitFromData(vertices, normals, textureCoords, indices);
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    mixTextures = false;
}


void Lab9::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab9::Update(float deltaTimeSeconds)
{
    {
        // Dezactivează testul de adâncime
        glDisable(GL_DEPTH_TEST);

        glm::mat4 modelMatrix = glm::mat4(1);
        RenderMesh(meshes["gradient_quad"], shaders["GradientShader"], modelMatrix);

        // Re-activează testul de adâncime
        glEnable(GL_DEPTH_TEST);
    }
    // Parametrii pentru oscilație
    float amplitude = 0.2;  // Amplitudinea oscilației
    float omegaOscillation = 0.8f;  // Frecvența oscilației

    // Iterăm prin fiecare balon
    for (auto& balloon : balloons) {
        // Calculăm unghiul de rotație pe baza vitezei
        balloon.angle += balloon.speed * deltaTimeSeconds;  // Unghiul în radiani

        // Calculăm poziția pe traiectorie
        float x = balloon.radius * cos(balloon.angle);  // Coordonata X
        float z = balloon.radius * sin(balloon.angle);  // Coordonata Z

        // Adăugăm un parametru global pentru timpul total
        static float totalTime = 0.0f; // Timpul acumulat

        // Incrementăm timpul total
        totalTime += deltaTimeSeconds;

        // Oscilația pe axa OY
        float y = balloon.height + amplitude * sin(omegaOscillation * totalTime); // Oscilația depinde de totalTime


        // Matricea modelului pentru balon
        glm::mat4 balloonModelMatrix = glm::mat4(1);
        balloonModelMatrix = glm::translate(balloonModelMatrix, glm::vec3(x, y, z));  // Poziționare pe traiectorie
        balloonModelMatrix = glm::rotate(balloonModelMatrix, balloon.angle, glm::vec3(0, 1, 0));  // Rotație pe axa Y

        // Desenăm balonul
        RenderSimpleMesh(meshes["sphere"], shaders["balon"], balloonModelMatrix, mapTextures["blue"], nullptr);

        // Corpul atașat balonului
        glm::mat4 bodyMatrix = balloonModelMatrix;  // Se bazează pe matricea balonului
        bodyMatrix = glm::translate(bodyMatrix, glm::vec3(0.0f, -1.2f, 0.0f));  // Poziționează corpul sub balon
        bodyMatrix = glm::scale(bodyMatrix, glm::vec3(0.7f, 0.4f, 0.3f));  // Scalare pentru corp
        RenderSimpleMesh(meshes["box"], shaders["lumina"], bodyMatrix, mapTextures["crate"], nullptr);

        // Primul picior
        glm::mat4 leg1Matrix = bodyMatrix;  // Se bazează pe corp
        leg1Matrix = glm::translate(leg1Matrix, glm::vec3(0.45f, 1.1f, 0.4f));  // Ajustează poziția piciorului
        leg1Matrix = glm::scale(leg1Matrix, glm::vec3(0.07f, 1.5f, 0.07f));  // Scalare pentru picior
        RenderSimpleMesh(meshes["box"], shaders["lumina"], leg1Matrix, mapTextures["crate"], nullptr);

        // Al doilea picior
        glm::mat4 leg2Matrix = bodyMatrix;  // Se bazează pe corp
        leg2Matrix = glm::translate(leg2Matrix, glm::vec3(0.45f, 1.1f, -0.4f));  // Ajustează poziția piciorului
        leg2Matrix = glm::scale(leg2Matrix, glm::vec3(0.07f, 1.5f, 0.07f));  // Scalare pentru picior
        RenderSimpleMesh(meshes["box"], shaders["lumina"], leg2Matrix, mapTextures["crate"], nullptr);

        // Al treilea picior
        glm::mat4 leg3Matrix = bodyMatrix;  // Se bazează pe corp
        leg3Matrix = glm::translate(leg3Matrix, glm::vec3(-0.45f, 1.1f, 0.4f));  // Ajustează poziția piciorului
        leg3Matrix = glm::scale(leg3Matrix, glm::vec3(0.07f, 1.5f, 0.07f));  // Scalare pentru picior
        RenderSimpleMesh(meshes["box"], shaders["lumina"], leg3Matrix, mapTextures["crate"], nullptr);

        // Al patrulea picior
        glm::mat4 leg4Matrix = bodyMatrix;  // Se bazează pe corp
        leg4Matrix = glm::translate(leg4Matrix, glm::vec3(-0.45f, 1.1f, -0.4f));  // Ajustează poziția piciorului
        leg4Matrix = glm::scale(leg4Matrix, glm::vec3(0.07f, 1.5f, 0.07f));  // Scalare pentru picior
        RenderSimpleMesh(meshes["box"], shaders["lumina"], leg4Matrix, mapTextures["crate"], nullptr);
        
    }

    // Render the point light in the scene
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(lightDirection.x + 35.0f, lightDirection.y + 19.0f, lightDirection.z));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(5.0f));
        RenderSimpleMesh(meshes["sphere"], shaders["Simple"], modelMatrix, mapTextures["sun"], nullptr);
    }
    //1
    // Render the point light in the scene
    angle1 += 0.4f * deltaTimeSeconds;
    float x1 = 4.0f * cos(angle1);
    float y1 = 7.9f + 0.2f + sin(2.0f * deltaTimeSeconds);
    float z1= 4.0f * sin(angle1);
    lightPosition1 = glm::vec3(x1, y1, z1);
    glm::mat4 light1Matrix = glm::mat4(1);
    light1Matrix = glm::translate(light1Matrix, lightPosition1);  // Ajustează poziția piciorului
    light1Matrix = glm::rotate(light1Matrix, angle1, glm::vec3(0, 1, 0));  // Rotație pe axa Y
    light1Matrix = glm::scale(light1Matrix, glm::vec3(0.01f));  // Scalare pentru picior
    RenderSimpleMesh(meshes["sphere"], shaders["Simple"], light1Matrix, mapTextures["Simple"], nullptr);

    //2
    // Render the point light in the scene
    angle2 += 0.5f * deltaTimeSeconds;
    float x2 = 5.0f * cos(angle2);
    float y2 = 9.4f + 0.2f + sin(2.0f * deltaTimeSeconds);
    float z2 = 5.0f * sin(angle2);
    lightPosition2 = glm::vec3(x2, y2, z2);
    glm::mat4 light2Matrix = glm::mat4(1);
    light2Matrix = glm::translate(light2Matrix, lightPosition2);  // Ajustează poziția piciorului
    light2Matrix = glm::rotate(light2Matrix, angle2, glm::vec3(0, 1, 0));  // Rotație pe axa Y
    light2Matrix = glm::scale(light2Matrix, glm::vec3(0.01f));  // Scalare pentru picior
    RenderSimpleMesh(meshes["sphere"], shaders["Simple"], light2Matrix, mapTextures["Simple"], nullptr);

    //3
   // Render the point light in the scene
    angle3 += 0.3f * deltaTimeSeconds;
    float x3 = 3.0f * cos(angle3);
    float y3 = 13.9 + 0.2f + sin(2.0f * deltaTimeSeconds);
    float z3 = 3.0f * sin(angle3);
    lightPosition3 = glm::vec3(x3, y3,z3);
    glm::mat4 light3Matrix = glm::mat4(1);
    light3Matrix = glm::translate(light3Matrix, lightPosition3);  // Ajustează poziția piciorului
    light3Matrix = glm::rotate(light3Matrix, angle3, glm::vec3(0, 1, 0));  // Rotație pe axa Y
    light3Matrix = glm::scale(light3Matrix, glm::vec3(0.01f));  // Scalare pentru picior
    RenderSimpleMesh(meshes["sphere"], shaders["Simple"], light3Matrix, mapTextures["Simple"], nullptr);

    // Parametrii pentru oscilație
    float amplitude1 = 0.4f;  // Amplitudinea oscilației
    float omegaOscillation1 = 0.2f;  // Frecvența oscilației

    // Iterăm prin fiecare balon
    for (auto& balloon1 : balloons1) {
        // Calculăm unghiul de rotație pe baza vitezei
        balloon1.angle += balloon1.speed * deltaTimeSeconds;  // Unghiul în radiani

        // Calculăm poziția pe traiectorie
        float x = balloon1.radius * cos(balloon1.angle);  // Coordonata X
        float z = balloon1.radius * sin(balloon1.angle);  // Coordonata Z

        // Adăugăm un parametru global pentru timpul total
        static float totalTime = 0.0f; // Timpul acumulat

        // Incrementăm timpul total
        totalTime += deltaTimeSeconds;

        // Oscilația pe axa OY
        float y = balloon1.height + amplitude1 * sin(omegaOscillation1 * totalTime); // Oscilația depinde de totalTime


        // Matricea modelului pentru balon
        glm::mat4 balloon1ModelMatrix = glm::mat4(1);
        balloon1ModelMatrix = glm::translate(balloon1ModelMatrix, glm::vec3(x, y, z));  // Poziționare pe traiectorie
        balloon1ModelMatrix = glm::rotate(balloon1ModelMatrix, balloon1.angle, glm::vec3(0, 1, 0));  // Rotație pe axa Y

        // Desenăm balonul
        RenderSimpleMesh(meshes["sphere"], shaders["balon"], balloon1ModelMatrix, mapTextures["pink"], nullptr);

        // Corpul atașat balonului
        glm::mat4 bodyMatrix = balloon1ModelMatrix;  // Se bazează pe matricea balonului
        bodyMatrix = glm::translate(bodyMatrix, glm::vec3(0.0f, -1.2f, 0.0f));  // Poziționează corpul sub balon
        bodyMatrix = glm::scale(bodyMatrix, glm::vec3(0.7f, 0.4f, 0.3f));  // Scalare pentru corp
        RenderSimpleMesh(meshes["box"], shaders["lumina"], bodyMatrix, mapTextures["crate"], nullptr);

        // Primul picior
        glm::mat4 leg1Matrix = bodyMatrix;  // Se bazează pe corp
        leg1Matrix = glm::translate(leg1Matrix, glm::vec3(0.45f, 1.1f, 0.4f));  // Ajustează poziția piciorului
        leg1Matrix = glm::scale(leg1Matrix, glm::vec3(0.07f, 1.5f, 0.07f));  // Scalare pentru picior
        RenderSimpleMesh(meshes["box"], shaders["lumina"], leg1Matrix, mapTextures["crate"], nullptr);

        // Al doilea picior
        glm::mat4 leg2Matrix = bodyMatrix;  // Se bazează pe corp
        leg2Matrix = glm::translate(leg2Matrix, glm::vec3(0.45f, 1.1f, -0.4f));  // Ajustează poziția piciorului
        leg2Matrix = glm::scale(leg2Matrix, glm::vec3(0.07f, 1.5f, 0.07f));  // Scalare pentru picior
        RenderSimpleMesh(meshes["box"], shaders["lumina"], leg2Matrix, mapTextures["crate"], nullptr);

        // Al treilea picior
        glm::mat4 leg3Matrix = bodyMatrix;  // Se bazează pe corp
        leg3Matrix = glm::translate(leg3Matrix, glm::vec3(-0.45f, 1.1f, 0.4f));  // Ajustează poziția piciorului
        leg3Matrix = glm::scale(leg3Matrix, glm::vec3(0.07f, 1.5f, 0.07f));  // Scalare pentru picior
        RenderSimpleMesh(meshes["box"], shaders["lumina"], leg3Matrix, mapTextures["crate"], nullptr);

        // Al patrulea picior
        glm::mat4 leg4Matrix = bodyMatrix;  // Se bazează pe corp
        leg4Matrix = glm::translate(leg4Matrix, glm::vec3(-0.45f, 1.1f, -0.4f));  // Ajustează poziția piciorului
        leg4Matrix = glm::scale(leg4Matrix, glm::vec3(0.07f, 1.5f, 0.07f));  // Scalare pentru picior
        RenderSimpleMesh(meshes["box"], shaders["lumina"], leg4Matrix, mapTextures["crate"], nullptr);
    }
  //4
  // Render the point light in the scene
    angle4 += 0.5f * deltaTimeSeconds;
    float x4 = 0.9f * cos(angle4);
    float y4 = 1.9f + 0.4f + sin(2.3f * deltaTimeSeconds);
    float z4 = 0.9f * sin(angle4);
    lightPosition4 = glm::vec3(x4, y4, z4);
    glm::mat4 light4Matrix = glm::mat4(1);
    light4Matrix = glm::translate(light4Matrix, lightPosition4);  // Ajustează poziția piciorului
    light4Matrix = glm::rotate(light4Matrix, angle4, glm::vec3(0, 1, 0));  // Rotație pe axa Y
    light4Matrix = glm::scale(light4Matrix, glm::vec3(0.01f));  // Scalare pentru picior
    RenderSimpleMesh(meshes["sphere"], shaders["Simple"], light4Matrix, mapTextures["Simple"], nullptr);

    //5
  // Render the point light in the scene
    angle5 += 0.3f * deltaTimeSeconds;
    float x5 = 6.0f * cos(angle5);
    float y5 = 11.9f + 0.4f + sin(2.3f * deltaTimeSeconds);
    float z5 = 6.0f * sin(angle5);
    lightPosition5 = glm::vec3(x5, y5, z5);
    glm::mat4 light5Matrix = glm::mat4(1);
    light5Matrix = glm::translate(light5Matrix, lightPosition5);  // Ajustează poziția piciorului
    light5Matrix = glm::rotate(light5Matrix, angle5, glm::vec3(0, 1, 0));  // Rotație pe axa Y
    light5Matrix = glm::scale(light5Matrix, glm::vec3(0.01f));  // Scalare pentru picior
    RenderSimpleMesh(meshes["sphere"], shaders["Simple"], light5Matrix, mapTextures["Simple"], nullptr);


    //6
  // Render the point light in the scene
    angle6 += 0.5f * deltaTimeSeconds;
    float x6 = 8.5f * cos(angle6);
    float y6 = 1.4f + 0.4f + sin(2.3f * deltaTimeSeconds);
    float z6 = 8.5f * sin(angle6);
    lightPosition6 = glm::vec3(x6, y6, z6);
    glm::mat4 light6Matrix = glm::mat4(1);
    light6Matrix = glm::translate(light6Matrix, lightPosition6);  // Ajustează poziția piciorului
    light6Matrix = glm::rotate(light6Matrix, angle6, glm::vec3(0, 1, 0));  // Rotație pe axa Y
    light6Matrix = glm::scale(light6Matrix, glm::vec3(0.01f));  // Scalare pentru picior
    RenderSimpleMesh(meshes["sphere"], shaders["Simple"], light6Matrix, mapTextures["Simple"], nullptr);

    // Parametrii pentru oscilație
    float amplitude2 = 0.6f;  // Amplitudinea oscilației
    float omegaOscillation2 = 0.4f;  // Frecvența oscilației

    // Iterăm prin fiecare balon
    for (auto& balloon2 : balloons2) {
        // Calculăm unghiul de rotație pe baza vitezei
        balloon2.angle += balloon2.speed * deltaTimeSeconds;  // Unghiul în radiani

        // Calculăm poziția pe traiectorie
        float x = balloon2.radius * cos(balloon2.angle);  // Coordonata X
        float z = balloon2.radius * sin(balloon2.angle);  // Coordonata Z

        // Adăugăm un parametru global pentru timpul total
        static float totalTime = 0.0f; // Timpul acumulat

        // Incrementăm timpul total
        totalTime += deltaTimeSeconds;

        // Oscilația pe axa OY
        float y = balloon2.height + amplitude2 * sin(omegaOscillation2 * totalTime); // Oscilația depinde de totalTime


        // Matricea modelului pentru balon
        glm::mat4 balloon2ModelMatrix = glm::mat4(1);
        balloon2ModelMatrix = glm::translate(balloon2ModelMatrix, glm::vec3(x, y, z));  // Poziționare pe traiectorie
        balloon2ModelMatrix = glm::rotate(balloon2ModelMatrix, balloon2.angle, glm::vec3(0, 1, 0));  // Rotație pe axa Y

        // Desenăm balonul
        RenderSimpleMesh(meshes["sphere"], shaders["balon"], balloon2ModelMatrix, mapTextures["pastel"], nullptr);

        // Corpul atașat balonului
        glm::mat4 bodyMatrix = balloon2ModelMatrix;  // Se bazează pe matricea balonului
        bodyMatrix = glm::translate(bodyMatrix, glm::vec3(0.0f, -1.2f, 0.0f));  // Poziționează corpul sub balon
        bodyMatrix = glm::scale(bodyMatrix, glm::vec3(0.7f, 0.4f, 0.3f));  // Scalare pentru corp
        //RenderSimpleMesh(meshes["box"], shaders["LabShader"], bodyMatrix, mapTextures["crate"], nullptr);
        RenderSimpleMesh(meshes["box"], shaders["lumina"], bodyMatrix, mapTextures["crate"], nullptr);

        // Primul picior
        glm::mat4 leg1Matrix = bodyMatrix;  // Se bazează pe corp
        leg1Matrix = glm::translate(leg1Matrix, glm::vec3(0.45f, 1.1f, 0.4f));  // Ajustează poziția piciorului
        leg1Matrix = glm::scale(leg1Matrix, glm::vec3(0.07f, 1.5f, 0.07f));  // Scalare pentru picior
        RenderSimpleMesh(meshes["box"], shaders["lumina"], leg1Matrix, mapTextures["crate"], nullptr);

        // Al doilea picior
        glm::mat4 leg2Matrix = bodyMatrix;  // Se bazează pe corp
        leg2Matrix = glm::translate(leg2Matrix, glm::vec3(0.45f, 1.1f, -0.4f));  // Ajustează poziția piciorului
        leg2Matrix = glm::scale(leg2Matrix, glm::vec3(0.07f, 1.5f, 0.07f));  // Scalare pentru picior
        RenderSimpleMesh(meshes["box"], shaders["lumina"], leg2Matrix, mapTextures["crate"], nullptr);

        // Al treilea picior
        glm::mat4 leg3Matrix = bodyMatrix;  // Se bazează pe corp
        leg3Matrix = glm::translate(leg3Matrix, glm::vec3(-0.45f, 1.1f, 0.4f));  // Ajustează poziția piciorului
        leg3Matrix = glm::scale(leg3Matrix, glm::vec3(0.07f, 1.5f, 0.07f));  // Scalare pentru picior
        RenderSimpleMesh(meshes["box"], shaders["lumina"], leg3Matrix, mapTextures["crate"], nullptr);

        // Al patrulea picior
        glm::mat4 leg4Matrix = bodyMatrix;  // Se bazează pe corp
        leg4Matrix = glm::translate(leg4Matrix, glm::vec3(-0.45f, 1.1f, -0.4f));  // Ajustează poziția piciorului
        leg4Matrix = glm::scale(leg4Matrix, glm::vec3(0.07f, 1.5f, 0.07f));  // Scalare pentru picior
        RenderSimpleMesh(meshes["box"], shaders["lumina"], leg4Matrix, mapTextures["crate"], nullptr);
    }

  //7
 // Render the point light in the scene
    angle7 += 0.3f * deltaTimeSeconds;
    float x7 = 2.5f * cos(angle7);
    float y7 = 4.9f + 0.6f + sin(2.5f * deltaTimeSeconds);
    float z7 = 2.5f * sin(angle7);
    lightPosition7 = glm::vec3(x7, y7, z7);
    glm::mat4 light7Matrix = glm::mat4(1);
    light7Matrix = glm::translate(light7Matrix, lightPosition7);  // Ajustează poziția piciorului
    light7Matrix = glm::rotate(light7Matrix, angle7, glm::vec3(0, 1, 0));  // Rotație pe axa Y
    light7Matrix = glm::scale(light7Matrix, glm::vec3(0.01f));  // Scalare pentru picior
    RenderSimpleMesh(meshes["sphere"], shaders["Simple"], light7Matrix, mapTextures["Simple"], nullptr);

    //8
 // Render the point light in the scene
    angle8 += 0.5f * deltaTimeSeconds;
    float x8 = 0.7f * cos(angle8);
    float y8 = 9.9f + 0.6f + sin(2.5f * deltaTimeSeconds);
    float z8 = 0.7f * sin(angle8);
    lightPosition8 = glm::vec3(x8, y8, z8);
    glm::mat4 light8Matrix = glm::mat4(1);
    light8Matrix = glm::translate(light8Matrix, lightPosition8);  // Ajustează poziția piciorului
    light8Matrix = glm::rotate(light8Matrix, angle8, glm::vec3(0, 1, 0));  // Rotație pe axa Y
    light8Matrix = glm::scale(light8Matrix, glm::vec3(0.01f));  // Scalare pentru picior
    RenderSimpleMesh(meshes["sphere"], shaders["Simple"], light8Matrix, mapTextures["Simple"], nullptr);

    //9
 // Render the point light in the scene
    angle9 += 0.4f * deltaTimeSeconds;
    float x9 = 5.0f * cos(angle9);
    float y9 = 12.9f + 0.6f + sin(2.5f * deltaTimeSeconds);
    float z9 = 5.0f * sin(angle9);
    lightPosition9 = glm::vec3(x9, y9, z9);
    glm::mat4 light9Matrix = glm::mat4(1);
    light9Matrix = glm::translate(light9Matrix, lightPosition9);  // Ajustează poziția piciorului
    light9Matrix = glm::rotate(light9Matrix, angle9, glm::vec3(0, 1, 0));  // Rotație pe axa Y
    light9Matrix = glm::scale(light9Matrix, glm::vec3(0.01f));  // Scalare pentru picior
    RenderSimpleMesh(meshes["sphere"], shaders["Simple"], light9Matrix, mapTextures["Simple"], nullptr);

    // Parametrii pentru oscilație
    float amplitudeb = 0.5f;  // Amplitudinea oscilației
    float omegaOscillationb = 0.5f;  // Frecvența oscilației

    // Iterăm prin fiecare balon
    for (auto& balonM : balonMic) {
        // Calculăm unghiul de rotație pe baza vitezei
        balonM.angle += balonM.speed * deltaTimeSeconds;  // Unghiul în radiani

        // Calculăm poziția pe traiectorie
        float x = balonM.radius * cos(balonM.angle);  // Coordonata X
        float z = balonM.radius * sin(balonM.angle);  // Coordonata Z

        // Oscilația pe axa OY
        float y = balonM.height + amplitudeb * sin(omegaOscillationb * deltaTimeSeconds);

        // Matricea modelului pentru balon
        glm::mat4 balloonMModelMatrix = glm::mat4(1);
        balloonMModelMatrix = glm::translate(balloonMModelMatrix, glm::vec3(x, y, z));  // Poziționare pe traiectorie
        balloonMModelMatrix = glm::rotate(balloonMModelMatrix, balonM.angle, glm::vec3(0, 1, 0));  // Rotație pe axa Y
        balloonMModelMatrix = glm::scale(balloonMModelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));  // Scalare pentru picior
        // Desenăm balonul
        RenderSimpleMesh(meshes["balonMic"], shaders["LabShader"], balloonMModelMatrix, mapTextures["yellow"], nullptr);
        RenderSimpleMesh(meshes["ata"], shaders["LabShader"], balloonMModelMatrix, mapTextures["blue"], nullptr);
    }

    // Parametrii pentru oscilație
    float amplitudev = 0.5f;  // Amplitudinea oscilației
    float omegaOscillationv = 0.5f;  // Frecvența oscilației

    // Iterăm prin fiecare balon
    for (auto& avionH : avion) {
        // Calculăm unghiul de rotație pe baza vitezei
        avionH.angle += avionH.speed * deltaTimeSeconds;  // Unghiul în radiani

        // Calculăm poziția pe traiectorie
        float x = avionH.radius * cos(avionH.angle);  // Coordonata X
        float z = avionH.radius * sin(avionH.angle);  // Coordonata Z

        // Oscilația pe axa OY
        float y = avionH.height + amplitudev * sin(omegaOscillationv * deltaTimeSeconds);

        // Matricea modelului pentru balon
        glm::mat4 avionModelMatrix = glm::mat4(1);
        avionModelMatrix = glm::translate(avionModelMatrix, glm::vec3(x, y, z));  // Poziționare pe traiectorie
        avionModelMatrix = glm::rotate(avionModelMatrix, avionH.angle, glm::vec3(0, y, 0));  // Rotație pe axa Y
        avionModelMatrix = glm::scale(avionModelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));  // Scalare pentru picior
        // Desenăm balonul
        RenderSimpleMesh(meshes["avion"], shaders["LabShader"], avionModelMatrix, mapTextures["paper"], nullptr);
    }

    {
        glm::mat4 modelMatrix1 = glm::mat4(1);
        modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(0, 0, 0));
        modelMatrix1 = glm::scale(modelMatrix1, glm::vec3(50));

        RenderSimpleMesh(
            meshes["plane"],
            shaders["teren"],
            modelMatrix1,
            mapTextures["heightmap"],     // Height map
            mapTextures["sand"], // Textură pentru înălțimi joase
            mapTextures["rock"]  // Textură pentru înălțimi mari
        );
    }

}


void Lab9::FrameEnd()
{
    // DrawCoordinateSystem();
}


void Lab9::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* heightMap, Texture2D* texture1, Texture2D* texture2)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Setare uniformă pentru lumina punctiformă
    //1
    GLint locLightPos1 = glGetUniformLocation(shader->program, "light_position1");
    glUniform3fv(locLightPos1, 1, glm::value_ptr(lightPosition1));

    glm::vec3 lightColor1 = glm::vec3(0.0f, 0.0f, 1.0f); 
    GLint locLightColor1 = glGetUniformLocation(shader->program, "light_color1");
    glUniform3fv(locLightColor1, 1, glm::value_ptr(lightColor1));

  //2
    // Setare uniformă pentru lumina punctiformă
    GLint locLightPos2 = glGetUniformLocation(shader->program, "light_position2");
    glUniform3fv(locLightPos2, 1, glm::value_ptr(lightPosition2));

    glm::vec3 lightColor2 = glm::vec3(0.0f, 1.0f, 0.0f); 
    GLint locLightColor2 = glGetUniformLocation(shader->program, "light_color2");
    glUniform3fv(locLightColor2, 1, glm::value_ptr(lightColor2));
    
    //3
    // Setare uniformă pentru lumina punctiformă
    GLint locLightPos3 = glGetUniformLocation(shader->program, "light_position3");
    glUniform3fv(locLightPos3, 1, glm::value_ptr(lightPosition3));

    glm::vec3 lightColor3 = glm::vec3(1.0f, 0.0f, 0.0f); 
    GLint locLightColor3 = glGetUniformLocation(shader->program, "light_color3");
    glUniform3fv(locLightColor3, 1, glm::value_ptr(lightColor3));
    
    //4
    // Setare uniformă pentru lumina punctiformă
    GLint locLightPos4 = glGetUniformLocation(shader->program, "light_position4");
    glUniform3fv(locLightPos4, 1, glm::value_ptr(lightPosition4));

    glm::vec3 lightColor4 = glm::vec3(1.0f, 0.0f, 0.0f); 
    GLint locLightColor4 = glGetUniformLocation(shader->program, "light_color4");
    glUniform3fv(locLightColor4, 1, glm::value_ptr(lightColor4));
    
    //5
    // Setare uniformă pentru lumina punctiformă
    GLint locLightPos5 = glGetUniformLocation(shader->program, "light_position5");
    glUniform3fv(locLightPos5, 1, glm::value_ptr(lightPosition5));

    glm::vec3 lightColor5 = glm::vec3(0.0f, 1.0f, 0.0f); 
    GLint locLightColor5 = glGetUniformLocation(shader->program, "light_color5");
    glUniform3fv(locLightColor5, 1, glm::value_ptr(lightColor5));

    //6
    // Setare uniformă pentru lumina punctiformă
    GLint locLightPos6 = glGetUniformLocation(shader->program, "light_position6");
    glUniform3fv(locLightPos6, 1, glm::value_ptr(lightPosition6));

    glm::vec3 lightColor6 = glm::vec3(0.0f, 0.0f, 1.0f);
    GLint locLightColor6 = glGetUniformLocation(shader->program, "light_color6");
    glUniform3fv(locLightColor6, 1, glm::value_ptr(lightColor6));

    //7
    // Setare uniformă pentru lumina punctiformă
    GLint locLightPos7 = glGetUniformLocation(shader->program, "light_position7");
    glUniform3fv(locLightPos7, 1, glm::value_ptr(lightPosition7));

    glm::vec3 lightColor7 = glm::vec3(1.0f, 0.0f, 0.0f); 
    GLint locLightColor7 = glGetUniformLocation(shader->program, "light_color7");
    glUniform3fv(locLightColor7, 1, glm::value_ptr(lightColor7));

    //8
    // Setare uniformă pentru lumina punctiformă
    GLint locLightPos8 = glGetUniformLocation(shader->program, "light_position8");
    glUniform3fv(locLightPos8, 1, glm::value_ptr(lightPosition8));

    glm::vec3 lightColor8 = glm::vec3(0.0f, 0.0f, 1.0f);
    GLint locLightColor8 = glGetUniformLocation(shader->program, "light_color8");
    glUniform3fv(locLightColor8, 1, glm::value_ptr(lightColor8));

    //9
    // Setare uniformă pentru lumina punctiformă
    GLint locLightPos9 = glGetUniformLocation(shader->program, "light_position9");
    glUniform3fv(locLightPos9, 1, glm::value_ptr(lightPosition9));

    glm::vec3 lightColor9 = glm::vec3(0.0f, 0.1f, 0.0f); 
    GLint locLightColor9 = glGetUniformLocation(shader->program, "light_color9");
    glUniform3fv(locLightColor9, 1, glm::value_ptr(lightColor9));
    
    // Setare uniformă pentru lumina direcțională (Soarele)
   glm::vec3 lightDirection = glm::normalize(glm::vec3(-3.02f, -4.0f, -0.92f)); // Direcția luminii soarelui
    GLint locLightDir = glGetUniformLocation(shader->program, "light_direction");
    glUniform3fv(locLightDir, 1, glm::value_ptr(lightDirection));

    glm::vec3 dirLightColor = glm::vec3(1.0f, 1.0f, 1.0f); // Culoare albă pentru soare
    GLint locDirLightColor = glGetUniformLocation(shader->program, "dir_light_color");
    glUniform3fv(locDirLightColor, 1, glm::value_ptr(dirLightColor));

    // Setare poziție cameră
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    GLint locEyePos = glGetUniformLocation(shader->program, "eye_position");
    glUniform3fv(locEyePos, 1, glm::value_ptr(eyePosition));

    // Proprietăți materiale
    GLint locMaterialShininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(locMaterialShininess, materialShininess);

    GLint locMaterialKd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(locMaterialKd, materialKd);

    GLint locMaterialKs = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(locMaterialKs, materialKs);


    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Setează heightmap-ul
    if (heightMap) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, heightMap->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_0"), 0);
    }

    // Textura pentru înălțimi joase
    if (texture1) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 1);
    }

    // Textura pentru înălțimi mari
    if (texture2) {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 2);
    }

    // Setează limitele de interpolare și factorul de scalare
    glUniform1f(glGetUniformLocation(shader->program, "height_scale"), 0.4f);
    glUniform1f(glGetUniformLocation(shader->program, "LOW_LIMIT"), 0.2f);
    glUniform1f(glGetUniformLocation(shader->program, "HIGH_LIMIT"), 0.5f);

    // Desenează obiectul
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}
void Lab9::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Texture2D* texture1, Texture2D* texture2)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    GLint locLightPos1 = glGetUniformLocation(shader->program, "light_position1");
    glUniform3fv(locLightPos1, 1, glm::value_ptr(lightPosition1));


    // Set eye position (camera position)
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    GLint locEyePos = glGetUniformLocation(shader->program, "eye_position");
    glUniform3fv(locEyePos, 1, glm::value_ptr(eyePosition));

    // Set material property uniforms (shininess, kd, ks, object color)
    GLint locMaterialShininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(locMaterialShininess, materialShininess);

    GLint locMaterialKd = glGetUniformLocation(shader->program, "material_kd");  // Diffuse coefficient
    glUniform1f(locMaterialKd, materialKd);

    GLint locMaterialKs = glGetUniformLocation(shader->program, "material_ks");  // Specular coefficient
    glUniform1f(locMaterialKs, materialKs);

    GLint locObjectColor = glGetUniformLocation(shader->program, "object_color");
    glUniform1i(glGetUniformLocation(shader->program, "mix_textures"), mixTextures);

    if (texture1)
    {
        // TODO(student): Do these:
        // - activate texture location 0
        // - bind the texture1 ID
        // - send theuniform value

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }

    if (texture2)
    {
        // TODO(student): Do these:
        // - activate texture location 1
        // - bind the texture2 ID
        // - send the uniform value
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
    }

    glUniform3fv(locObjectColor, 1, glm::value_ptr(color));

    // Bind model matrix
    GLint locModelMatrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(locModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    GLint locViewMatrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(locViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    GLint locProjectionMatrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(locProjectionMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

Texture2D* Lab9::CreateRandomTexture(unsigned int width, unsigned int height)
{
    GLuint textureID = 0;
    unsigned int channels = 3;
    unsigned int size = width * height * channels;
    unsigned char* data = new unsigned char[size];

    // TODO(student): Generate random texture data
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = rand() % 256;
    }


    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // TODO(student): Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Use glTexImage2D to set the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // TODO(student): Generate texture mip-maps
    glGenerateMipmap(GL_TEXTURE_2D);
    Texture2D* texture = new Texture2D();
    texture->Init(textureID, width, height, channels);
    SAFE_FREE_ARRAY(data);

    return texture;
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab9::OnInputUpdate(float deltaTime, int mods)
{
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
    }
    {
        // Pozitia quad-ului
        glm::vec3 quadPosition = glm::vec3(0.0f, 0.5f, 0.0f);

        // Obtineti pozitia camerei
        glm::vec3 cameraPosition = GetSceneCamera()->m_transform->GetWorldPosition();

        // Calculati vectorul de la quad la camera
        glm::vec3 direction = cameraPosition - quadPosition;

        // Proiectați vectorul pe planul XZ 
        direction.y = 0.0f;
        direction = glm::normalize(direction);

        // Calculati unghiul de rotatie in radiani
        float angle = atan2(direction.x, direction.z);

        // Creati matricea modelului
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, quadPosition);
        modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0)); // Rotește pe axa Y
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

        // Desenati quad-ul cu matricea modelului rotita
        RenderSimpleMesh(meshes["square"], shaders["LabShader"], modelMatrix, mapTextures["grass"]);
    }
    float speed = 2;

    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

        // Control light position using on W, A, S, D, E, Q
        if (window->KeyHold(GLFW_KEY_W)) lightDirection -= forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_A)) lightDirection -= right * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_S)) lightDirection += forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_D)) lightDirection += right * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_E)) lightDirection += up * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_Q)) lightDirection -= up * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_P)) std::cout << lightDirection.x << " " << lightDirection.y << " " << lightDirection.z << "\n";
    }
}


void Lab9::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab9::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab9::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab9::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab9::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab9::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab9::OnWindowResize(int width, int height)
{
}
