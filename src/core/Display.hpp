 #pragma once

#include <string>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Display {

private:

    SDL_Window* window;         // Viewport
    SDL_GLContext glContext;    // OpenGL context

public:
    
    /**
     * Create OpenGL viewport
     * @param width Window width in pixels
     * @param height Window height in pixels
     * @param title Window title string
     */
    Display(uint16_t width, uint16_t height, const std::string& title);
    
    /**
     * Swap buffers and check for window close events
     * @return false if the window must be closed, true otherwise
     */
    bool update();

    /**
     * Clear display using color
     * @param r Red value
     * @param b Blue value
     * @param g Green value
     */
    void clear(float r, float g, float b);
    
    /**
     * Get the window size
     * @return Integer vector containing width and height
     */
    glm::ivec2 screenSize();
    
    virtual ~Display();

};