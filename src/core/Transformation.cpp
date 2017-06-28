#include "Transformation.hpp"
#include <glm/gtx/transform.hpp>

std::stack<glm::vec3> Transformation::modelStack;
glm::vec3 Transformation::pos(0.0f);
glm::vec3 Transformation::rot(0.0f);
glm::vec3 Transformation::scale(1.0f);


glm::mat4 Transformation::getMatrix() {
    glm::mat4 posMatrix(glm::translate(pos));
    glm::mat4 rotMatrix(glm::rotate(rot.z, glm::vec3(0, 0, 1))
                      * glm::rotate(rot.y, glm::vec3(0, 1, 0))
                      * glm::rotate(rot.x, glm::vec3(1, 0, 0)));
    glm::mat4 scaleMatrix(glm::scale(scale));
    return posMatrix * rotMatrix * scaleMatrix;
}

void Transformation::translate(const glm::vec3& offset) {
    pos += offset;
}

void Transformation::rotateX(float angle) {
    rot.x += angle;
}

void Transformation::rotateY(float angle) {
    rot.y += angle;
}

void Transformation::rotateZ(float angle) {
    rot.z += angle;
}

void Transformation::scaleX(float amount) {
    scale.x *= amount;
}

void Transformation::scaleY(float amount) {
    scale.y *= amount;
}

void Transformation::scaleZ(float amount) {
    scale.z *= amount;
}

void Transformation::scaleAll(float amount) {
    scale *= amount;
}

void Transformation::push() {
    modelStack.push(pos);
    modelStack.push(rot);
    modelStack.push(scale);
}

void Transformation::pop() {
    scale = modelStack.top();
    modelStack.pop();
    rot = modelStack.top();
    modelStack.pop();
    pos = modelStack.top();
    modelStack.pop();
}

void Transformation::reset() {
    pos = glm::vec3(0.0f);
    rot = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);
}