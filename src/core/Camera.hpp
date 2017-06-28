#pragma once

#include <glm/glm.hpp>

class Camera {

private:

    glm::vec2 fov;              // Vertical field of view
    glm::vec2 screenSize;       // Viewport size in pixels (width, height)
    glm::mat4 perspective;      // Perspective matrix
    glm::vec3 position;         // Position in 3D space
    glm::vec2 angle;            // X and Y angles
    glm::vec3 forward;          // Forward direction
    glm::vec3 up;               // Up direction

public:

    /**
     * Camera constructor
     * @param pos Position in 3D space
     * @param _fov Vertical field of view
     * @param _screenSize Size of the viewport in pixels
     * @param zNear Distance of the near plane
     * @param zFar Distance of the far plane
     */
    Camera(const glm::vec3& pos, float _fov, const glm::ivec2& _screenSize, float zNear, float zFar);

    /**
     * Move along the camera Z direction
     * @param dt Time interval
     */
    void moveZ(int dt);

    /**
     * Move along the camera X direction
     * @param dt Time interval
     */
    void moveX(int dt);

    /**
     * Rotate the camera
     * @param dx Pixel movement on the X screen axis
     * @param dy Pixel movement on the Y screen axis
     */
    void rotate(int dx, int dy);

    /**
     * Get view matrix
     */
    glm::mat4 getView() const;

    /**
     * Get perspective matrix
     */
    glm::mat4 getPerspective() const;

};