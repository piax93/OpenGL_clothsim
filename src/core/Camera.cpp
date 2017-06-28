#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

#define CAMERA_ZSPEED 0.0020f       // Camera speed on its Z axis
#define CAMERA_XSPEED 0.0015f       // Camera speed on its X axis


Camera::Camera(const glm::vec3& pos, float _fov, const glm::ivec2& _screenSize, float zNear, float zFar)
    : perspective(glm::perspective(_fov, _screenSize.x / (float) _screenSize.y, zNear, zFar)),
      position(pos), screenSize(_screenSize), fov(_fov * _screenSize.x / (float)_screenSize.y, _fov),
      forward(0, 0, -1), up(0, 1, 0), angle(0, 0) { }

void Camera::moveZ(int dt) {
    position += (dt * CAMERA_ZSPEED) * glm::normalize(forward); 
}

void Camera::moveX(int dt) { 
    position += (dt * CAMERA_XSPEED) * glm::normalize(glm::cross(forward, up));
}

void Camera::rotate(int dx, int dy) {
    if (dx == 0 && dy == 0) return;
    // Eval rotation angle in radians
    angle.x += glm::radians((dx / screenSize.x) * fov.x);
    angle.y += glm::radians((dy / screenSize.y) * fov.y);
    // Update forward and up vectors
    forward.x = glm::cos(angle.y) * glm::sin(angle.x);
    forward.y = -glm::sin(angle.y);
    forward.z = -glm::cos(angle.x) * glm::cos(angle.y);
    up.y = glm::cos(angle.y) < 0.0f ? -1.0f : 1.0f;
}

glm::mat4 Camera::getView() const {
    return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::getPerspective() const {
    return perspective;
}