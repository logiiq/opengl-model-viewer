#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <cglm/cglm.h>

#include "../Shader.h"

typedef struct DirectionalLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
} DirectionalLight_t;

DirectionalLight_t light_directional_new(float x, float y, float z);

void light_directional_update(DirectionalLight_t *light, Shader_t *shader);

void light_directional_direction(DirectionalLight_t *light, float x, float y, float z);

void light_directional_ambient(DirectionalLight_t *light, float r, float g, float b);

void light_directional_diffuse(DirectionalLight_t *light, float r, float g, float b);

void light_directional_specular(DirectionalLight_t *light, float r, float g, float b);

#endif