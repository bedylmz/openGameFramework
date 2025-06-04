//need for rendering
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//need for math and matrix calculation
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

//need for getting glsl file
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

//text rendering
#include <ft2build.h>
#include FT_FREETYPE_H

//custom Classes
#include "lib/Camera.h"
#include "lib/textRenderer.h"

#include "lib/assimpModel.h"

#define numVAOs 1
#define numVBOs 2

//vbo[0] for models
//vbo[1] for ui for now
#define MODEL_VBO vbo[0]
#define UI_VBO vbo[1]

Control camera{};

GLuint vao[numVAOs];
GLuint vbo[numVBOs];

glm::mat4 proj_mat, cam_mat;

int ScreenWidth, ScreenHeight;

float test;

GLFWwindow* window;

//textShader text_shader;

void setUpScene(GLFWwindow* window, double currentTime, textRenderer text_renderer, textShader text_shader)
{
    static GLuint projLoc, camLoc;
    static float aspect;
    static bool cameraType = false;

    aspect = (float)(ScreenWidth) / (float)(ScreenHeight);
    proj_mat = glm::perspective(60 * (3.14f / 180.0f), aspect, 0.01f, 1000.0f); // 3.14/180 radian to degree


    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) cameraType = !cameraType;
    text_renderer.RenderText(text_shader, std::to_string(cameraType), 0.0f, ScreenHeight - 200, 0.5f, Color::green);
    

    if (cameraType) cam_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10));
    if (!cameraType) cam_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10)); cam_mat = camera.mouseViewMatrix(window, currentTime, &test);
}


void movement(GLFWwindow * window, Model& model, float speed, float deltaTime, textRenderer text_renderer, textShader text_shader)
{
    //Move forward
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        model.Move(0,0,-deltaTime * speed);
        text_renderer.RenderText(text_shader, std::to_string(deltaTime * speed), 0.0f, ScreenHeight - 150, 0.5f, Color::red);
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        model.Move(0, 0, deltaTime * speed);
        text_renderer.RenderText(text_shader, std::to_string(deltaTime * speed), 0.0f, ScreenHeight - 150, 0.5f, Color::red);
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        model.Move(deltaTime * speed, 0, 0);
        text_renderer.RenderText(text_shader, std::to_string(deltaTime * speed), 0.0f, ScreenHeight - 150, 0.5f, Color::red);
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        model.Move(-deltaTime * speed, 0, 0);
        text_renderer.RenderText(text_shader, std::to_string(deltaTime * speed), 0.0f, ScreenHeight - 150, 0.5f, Color::red);
    }

    ////Move forward
    //if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    //{
    //    model.Rotate(0, 0, -deltaTime * speed);
    //}
    //// Rotate backward
    //if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    //{
    //    model.Rotate(0, 0, deltaTime * speed);
    //}
    //// Strafe right
    //if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    //{
    //    model.Rotate(deltaTime * speed, 0, 0);
    //}
    //// Strafe left
    //if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    //{
    //    model.Rotate(-deltaTime * speed, 0, 0);
    //}
}

int main()
{
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(1000, 1000, "Title", NULL, NULL); //glfwGetPrimaryMonitor(), NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    glfwSwapInterval(1);

    ////init
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    textShader text_shader  { "shader/text.vert", "shader/text.frag" };
    textRenderer text_renderer(vao[0], UI_VBO, window);

    Shader texture     { "shader/texture.vert",     "shader/texture.frag" };
    Shader varingColor { "shader/varingcolor.vert", "shader/varingcolor.frag" };

    //Model baby{ "C:/Users/User/Desktop/Burger King(Evo City v3)/evocity_v3_burkerking.obj"};
    Model backpack{ "src/model/backpack/backpack.obj" };
    //Model tank{ "C:/Users/User/Desktop/bmc_kirpi/kirpi_mrap.obj" };
    //tank.Scale(0.01f, 0.01f, 0.01f);

    //text rendering issuies

    text_renderer.setUpFont("src/fonts/babesneue.otf", text_shader);

    // deltaTime setter
    double timer = glfwGetTime();
    int frames = 0;
    double oldTime = 0, newTime = 0, deltaTime;

    // mouse center location setting
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glfwSetCursorPos(window, width / 2, height / 2);
    }

    while (!glfwWindowShouldClose(window))
    {
        // deltaTime updating
        newTime = glfwGetTime();
        deltaTime = newTime - oldTime;
        oldTime = newTime;

        glClearColor(0.2f, 0.35f, 0.3f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT); //| GL_COLOR_BUFFER_BIT
        glClear(GL_COLOR_BUFFER_BIT); //| GL_COLOR_BUFFER_BIT

        glfwGetFramebufferSize(window, &ScreenWidth, &ScreenHeight);

        setUpScene(window, deltaTime, text_renderer, text_shader);

        //render(models);
        //backpack.Draw(varingColor, proj_mat, cam_mat);
        baby.Draw(varingColor, proj_mat, cam_mat);
        //tank.Draw(texture, proj_mat, cam_mat);
        

        //basic movement with arrow keys
        //movement(window, tank, 3, deltaTime, text_renderer, text_shader);

        ////setting out string and print that on screen
        std::string out{ std::to_string(static_cast<int>(std::floor(1 / deltaTime))) };
        text_renderer.RenderText(text_shader, out, 0.0f, ScreenHeight - 50, 0.5f, Color::red);

        std::string out2{ std::to_string(test) };
        text_renderer.RenderText(text_shader, out2, 0.0f, ScreenHeight - 100, 0.5f, Color::blue);

        glfwSwapBuffers(window);
        glfwPollEvents();
   
        //close with escape key
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
        
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}