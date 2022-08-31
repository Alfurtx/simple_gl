/* date = August 31st 2022 11:58 am */

#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

struct Camera;
enum Direction;

#if defined(SIMPLE_CAMERA_IMPLEMENTATION)

#define WIDTH 1920
#define HEIGHT 1080
#define CAMERA_RENDER_DISTANCE 20.0f
#define CAMERA_YAW 90.0f
#define CAMERA_PITCH 0.0f
#define CAMERA_SPEED 1.5f
#define CAMERA_SENSITIVITY 0.1f
#define CAMERA_FOV 45.0f

inline internal void
update_vectors(Camera& camera) 
{
    glm::vec3 front;
    front.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    front.y = sin(glm::radians(camera.pitch));
    front.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    camera.front = glm::normalize(front);
    camera.right = glm::normalize(glm::cross(camera.front, camera.world_up));
    camera.up = glm::normalize(glm::cross(camera.right, camera.front));
}

enum Direction {
    UP, DOWN, RIGHT, LEFT, FORWARD, BACKWARD
};

struct Camera {
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;
    
    float yaw;
    float pitch;
    float speed;
    float sensitivity;
    float lastx;
    float lasty;
    
    bool firstmouse;
    
    Camera()
    {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);
        front = glm::vec3(0.0f, 0.0f, 1.0f);
        yaw = CAMERA_YAW;
        firstmouse = true;
        pitch = CAMERA_PITCH;
        speed = CAMERA_SPEED;
        sensitivity = CAMERA_SENSITIVITY;
        world_up = up;
        lastx = WIDTH / 2.0f;
        lasty = HEIGHT / 2.0f;
        update_vectors(*this);
    }
    
    glm::mat4 get_view() { return(glm::lookAt(position, position + front, up)); }
    glm::mat4 get_projection() { return(glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 10000.f)); }
    
    inline void process_keyboard(Direction direction, float delta_time)
    {
        float velocity = speed * delta_time;
        if (direction == Direction::FORWARD)
            position += front * velocity;
        if (direction == Direction::BACKWARD)
            position -= front * velocity;
        if (direction == Direction::LEFT)
            position -= right * velocity;
        if (direction == Direction::RIGHT)
            position += right * velocity;
        if (direction == Direction::DOWN)
            position -= up * velocity;
        if (direction == Direction::UP)
            position += up * velocity;
    }
    
    inline void process_cursor(float x_offset, float y_offset)
    {
        x_offset *= sensitivity;
        y_offset *= sensitivity;
        
        yaw   += x_offset;
        pitch -= y_offset;
        
        if(firstmouse) {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }
        
        update_vectors(*this);
    }
    
};

#endif // SIMPLE_CAMERA_IMPLEMENTATION

#endif //CAMERA_H
