#include "Camera.h"

#include <iostream>

glm::mat4 Control::mouseViewMatrix(GLFWwindow* window, float deltaTime, float * Fov)
{
    static int width, height;
    float verticalAngleTurn = 0;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwGetWindowSize(window, &width, &height);
    glfwGetCursorPos(window, &m_mousePos_x, &m_mousePos_y);
    glfwSetCursorPos(window, width / 2, height / 2);//this must be center of the window(app) not monitor, fix it

    // Compute new orientation
    m_horizontalAngle += m_mouseSpeed * deltaTime * (float)((width / 2) - m_mousePos_x);
    
    //limit vertical view for not to cause wrong direction
    verticalAngleTurn = m_mouseSpeed * (float)(width / height) * deltaTime * (float)((height / 2) - m_mousePos_y);
    if ((m_verticalAngle >= -3.14f/4 && verticalAngleTurn < 0) || (m_verticalAngle <= 3.14f/4 && verticalAngleTurn > 0))
    {
        m_verticalAngle += verticalAngleTurn;
    }

    if(Fov != nullptr) (*Fov) = m_verticalAngle;

    // Front : Spherical coordinates to Cartesian coordinates conversion
    m_front = glm::vec3(
        (float)cos(m_verticalAngle) * (float)sin(m_horizontalAngle),
        (float)sin(m_verticalAngle),
        (float)cos(m_verticalAngle) * (float)cos(m_horizontalAngle));

    // Right vector
    m_right = glm::vec3((float)sin(m_horizontalAngle - 3.14f / 2.0f), 0.0f, (float)cos(m_horizontalAngle - 3.14f / 2.0f));
    m_up = glm::cross(m_right, m_front);

    // Acceleration with shift
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
    {
        m_speed = 5.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        m_speed = 1.5f;
    }

    //Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
    {
        m_position += m_front * deltaTime * m_speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
    {
        m_position -= m_front * deltaTime * m_speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
    {
        m_position += m_right * deltaTime * m_speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
    {
        m_position -= m_right * deltaTime * m_speed;
    }


    // Camera matrix
    return  glm::lookAt(
        m_position,              // Camera is here
        m_position + m_front,    // and looks here : at the same position, plus "front"
        m_up);                   // Head is up (set to 0,-1,0 to look upside-down)
        
}