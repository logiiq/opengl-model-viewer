#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include "Shader.h"
#include "DirectionalLight.h"
#include "PointLight.h"

void lightman_init(void);

void lightman_add_point(PointLight_t *point);

void lightman_remove_point(PointLight_t *point);

void lightman_set_directional(DirectionalLight_t *directional);

void lightman_update(Shader_t *shader);

#endif