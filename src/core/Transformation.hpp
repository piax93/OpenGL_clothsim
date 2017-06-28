#pragma once

#include <glm/glm.hpp>
#include <stack>

/**
 * Static class representing model transformation
 */
class Transformation {
private:

    static std::stack<glm::vec3> modelStack;
    static glm::vec3 pos;                       // Position offset
    static glm::vec3 rot;                       // Rotation
    static glm::vec3 scale;                     // Scale

public:

    /**
     * Get transformation matrix
     */
    static glm::mat4 getMatrix();

    /**
     * Apply translation
     * @param offset Translation offset
     */
    static void translate(const glm::vec3& offset);

    /**
     * Apply rotation
     * @param angle Rotation angle in radians
     */
    static void rotateX(float angle);
    static void rotateY(float angle);
    static void rotateZ(float angle);

    /**
     * Apply scaling
     * @param amount Scaling multiplier
     */
    static void scaleX(float amount);
    static void scaleY(float amount);
    static void scaleZ(float amount);
    static void scaleAll(float amount);

    /**
     * Save current transformation state
     */
    static void push();

    /**
     * Restore transformation state
     */
    static void pop();

    /**
     * Reset transformation state
     */
    static void reset();

};