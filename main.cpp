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
#include "lib/Model.h"

#define numVAOs 1
#define numVBOs 2

//vbo[0] for models
//vbo[1] for ui for now
#define MODEL_VBO vbo[0]
#define UI_VBO vbo[1]

Control camera{};

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];


int ScreenWidth, ScreenHeight;

float test;

std::string readShaderSource(const char* filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);
    std::string line = "";
    while (!fileStream.eof())
    {
        getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

GLuint createShaderProgram()
{
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string veShader = readShaderSource("shader/varingcolor.vert");
    std::string frShader = readShaderSource("shader/varingcolor.frag");

    const char* vshaderSource = veShader.c_str();
    const char* fshaderSource = frShader.c_str();

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    glCompileShader(vShader);
    glCompileShader(fShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    return vfProgram;
}

void setUpScene(GLFWwindow* window, double currentTime)
{
    glClear(GL_DEPTH_BUFFER_BIT);

    glUseProgram(renderingProgram);
    static GLuint projLoc, camLoc;
    static float aspect;
    static glm::mat4 pMat, camMat;

    //gettting ids from vertex shader
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
    camLoc = glGetUniformLocation(renderingProgram, "mv_matrix");

    aspect = (float)(ScreenWidth) / (float)(ScreenHeight);
    pMat = glm::perspective(60 * (3.14f / 180.0f), aspect, 0.01f, 1000.0f); // 3.14/180 radian to degree

    //mvMat = glm::translate(glm::mat4(1.0f), glm::vec3(-1, -1, -1));
    camMat = camera.mouseViewMatrix(window, currentTime, &test);

    //sending matrix and time factor to vertex shader
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
    glUniformMatrix4fv(camLoc, 1, GL_FALSE, glm::value_ptr(camMat));
}

void render(std::vector<Model>& models)
{
    //glm::mat4 tMat, rMat;

    for (Model& model : models)
    {
        glBindBuffer(GL_ARRAY_BUFFER, MODEL_VBO);
        glBufferData(GL_ARRAY_BUFFER, model.getNumVertices(), model.getVertices(), GL_STATIC_DRAW);

        // special for models
        glBindBuffer(GL_ARRAY_BUFFER, MODEL_VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        //Backface culling is closed in here
        glDisable(GL_CULL_FACE);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArraysInstanced(GL_TRIANGLES, 0, model.getNumTriangles(), 1);
    }

    
}

int main()
{
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Title", glfwGetPrimaryMonitor(), NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    glfwSwapInterval(1);

    //init
    renderingProgram = createShaderProgram();
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);
    

    //model loading
    Model torus   { "src/model/torus.obj" };
    //suzanne.setTexture(loadTexture("src/pic/green.png"));

    //creating list for to render models
    std::vector<Model> models;
    models.emplace_back(torus);

    //text rendering issuies
    textRenderer text_renderer (vao[0], UI_VBO, window);
    textShader text_shader { "shader/text.vert", "shader/text.frag" };
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

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glfwGetFramebufferSize(window, &ScreenWidth, &ScreenHeight);

        setUpScene(window, deltaTime);
        render(models);

        //setting out string and print that on screen
        std::string out{ std::to_string(static_cast<int>(std::floor(1 / deltaTime))) };
        text_renderer.RenderText(text_shader, out, 0.0f, ScreenHeight-50, 0.5f, Color::red);

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