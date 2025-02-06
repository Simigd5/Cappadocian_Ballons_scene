#pragma once

#include <string>
#include <unordered_map>

#include "components/simple_scene.h"
#include "components/transform.h"


namespace m1
{
    struct Balloon {
        float height;  // Înălțimea la care se rotește balonul
        float radius;  // Raza traiectoriei
        float speed;   // Viteza de rotație (omega)
        float angle;   // Unghiul de rotație pe traiectorie
    };
    class Lab9 : public gfxc::SimpleScene
    {
     public:
        Lab9();
        ~Lab9();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1), Texture2D* texture1 = NULL, Texture2D* texture2 = NULL);
        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, Texture2D* heightMap, Texture2D *texture1 = NULL, Texture2D *texture2 = NULL);
        Texture2D *CreateRandomTexture(unsigned int width, unsigned int height);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        std::unordered_map<std::string, Texture2D *> mapTextures;
        GLuint randomTextureID;
        GLboolean mixTextures;
        glm::mat4 modelMatrix;
        float translateX, translateY, translateZ;
        float scaleX, scaleY, scaleZ;
        float angularStepOX, angularStepOY, angularStepOZ;
        std::vector<Balloon> balloons;  
        std::vector<Balloon> balloons1;
        std::vector<Balloon> balloons2;
        std::vector<Balloon> balonMic;
        std::vector<Balloon> avion;
        glm::vec3 balloonPosition;  // Poziția curentă a balonului
        glm::vec3 balloonVelocity;  // Viteza curentă a balonului
        glm::vec3 gravity;          // Forța gravitației
        glm::vec3 windForce;        // Forța vântului (aleatorie)
        float windChangeInterval;   // Intervalul de schimbare a vântului
        float windTimer;            // Timpul curent pentru schimbarea vântului
        glm::vec3 lightPosition1;
        glm::vec3 lightPosition2;
        glm::vec3 lightPosition3;
        glm::vec3 lightPosition4;
        glm::vec3 lightPosition5;
        glm::vec3 lightPosition6;
        glm::vec3 lightPosition7;
        glm::vec3 lightPosition8;
        glm::vec3 lightPosition9;
        glm::vec3 lightDirection;
        glm::vec3 lightColor;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;
        float yOffset;
        std::vector<glm::vec3> lightPositions;
        std::vector<glm::vec3> lightIntensities;
        std::vector<glm::vec3> pointLightPositions;
        std::vector<glm::vec3> pointLightColors;
        float angle1=0.5f;
        float angle2=0.8f;
        float angle3 = 0.3f;
        float angle4 = 0.7f;
        float angle5 = 0.7f;
        float angle6 = 0.5f;
        float angle7 = 0.7f;
        float angle8 = 0.8f;
        float angle9 = 0.6f;
    };
}   // namespace m1
