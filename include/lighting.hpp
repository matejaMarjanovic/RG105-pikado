#pragma once

#include <GL/glut.h>
#include <vector>

class ObjectMaterial {
public:
    ObjectMaterial(std::vector<GLfloat> amb, std::vector<GLfloat> diff, std::vector<GLfloat> spec, GLfloat shininess)
        : m_amb{amb}, m_diff{diff}, m_spec{spec}, m_shininess{shininess} { }
    void setLighting() const;
private:
    std::vector<GLfloat> m_amb, m_diff, m_spec;
    GLfloat m_shininess;
};

class ObjectLighting {
public:
    ObjectLighting(std::vector<GLfloat> amb, std::vector<GLfloat> diff, std::vector<GLfloat> spec, std::vector<GLfloat> pos, GLenum light)
        : m_amb{amb}, m_diff{diff}, m_spec{spec}, m_pos{pos}, m_light{light} { }
    void setLighting() const;
private:
    std::vector<GLfloat> m_amb, m_diff, m_spec, m_pos;
    GLenum m_light;
};
