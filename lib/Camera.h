#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class Control
{
private:
    double m_mousePos_x      {};
    double m_mousePos_y      {};
    float  m_horizontalAngle { 3.14f };   // horizontal angle : toward -Z 
    float  m_verticalAngle   { 0.0f };    // vertical angle   : 0, look at the horizon
    float  m_mouseSpeed      { 0.05f };

    float m_speed {};
    float m_fov   { 45.0f };              // Initial Field of View     

    glm::vec3 m_position { glm::vec3{0.0f, 0.0f, 1.0f}  }; //this init is arbiratry
    glm::vec3 m_front    { glm::vec3{0.0f, 0.0f, -1.0f} }; //this init is came from init HorizontalAngle and Vertical Angle
    glm::vec3 m_right    { glm::vec3{1.0f, 0.0f, 0.0f}  };
    glm::vec3 m_up       { glm::cross(m_right, m_front) };

public:
    glm::mat4 mouseViewMatrix(GLFWwindow* window, float deltaTime, float* Fov = nullptr);
};