#include "lighting.hpp"

// these functions just call the glMaterialfv or the glLightfv functions
// and set the lighting and material to the given class arguments
void ObjectMaterial::setLighting() const {
    glMaterialfv(GL_FRONT, GL_AMBIENT, &m_amb[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &m_diff[0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &m_spec[0]);
    glMaterialfv(GL_FRONT, GL_SHININESS, &m_shininess);
}

void ObjectLighting::setLighting() const {
    glLightfv(m_light, GL_AMBIENT, &m_amb[0]);
    glLightfv(m_light, GL_DIFFUSE, &m_diff[0]);
    glLightfv(m_light, GL_SPECULAR, &m_spec[0]);
    glLightfv(m_light, GL_SHININESS, &m_pos[0]);
}
