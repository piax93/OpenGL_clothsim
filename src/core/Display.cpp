#include "Display.hpp"
#include "Utils.hpp"

Display::Display(uint16_t width, uint16_t height, const std::string& title) {
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING)) die("Failed to init SDL");
    // Set GL options
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    // Create window
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (!window) die("Failed to create window");
    // Create OpenGL context
    glContext = SDL_GL_CreateContext(window);
    if (!glContext) die("Failed to init GL context");
    // More options
    SDL_GL_SetSwapInterval(1);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_ShowCursor(1);
    SDL_GetRelativeMouseState(NULL, NULL);
    // Init glew
    glewExperimental = true;
    if (glewInit() != GLEW_OK) die("Failed to init glew");
    glEnable(GL_DEPTH_TEST);
}

bool Display::update() {
    // Swap buffers
    SDL_GL_SwapWindow(window);
    // Poll events and check for termination
    SDL_Event e;
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)) return false;
    return true;
}

void Display::clear(float r, float g, float b) {
    // Set clear color
    glClearColor(r, g, b, 1.0f);
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::ivec2 Display::screenSize() {
    glm::ivec2 screenSize;
    SDL_GetWindowSize(window, &screenSize.x, &screenSize.y);
    return screenSize;
}

Display::~Display() {
    // Clear all
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}