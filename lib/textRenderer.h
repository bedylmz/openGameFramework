#pragma once
#ifndef TEXT_RENDERER
#define TEXT_RENDERER

#include <iostream>
#include <map>
#include <string>

#include "textShader.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Color
{
	constexpr glm::vec3 blue  { glm::vec3(0.0f, 0.0f, 1.0f) };
	constexpr glm::vec3 green { glm::vec3(0.0f, 1.0f, 0.0f) };
	constexpr glm::vec3 red   { glm::vec3(1.0f, 0.0f, 0.0f) };
}

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class textRenderer
{
	private:
        std::map<GLchar, Character> Characters;

		GLFWwindow * m_window;
		int windowWidth{ 0 }, windowHeight{ 0 };
		unsigned int m_VAO;
		unsigned int m_VBO;


	public:
		textRenderer(unsigned int VAO, unsigned int VBO, GLFWwindow * window)
			: m_VAO { VAO }, m_VBO { VBO }, m_window { window }
		{
			glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
		}

        void setUpFont(const char * fontPath, textShader shader);

		void RenderText(textShader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif