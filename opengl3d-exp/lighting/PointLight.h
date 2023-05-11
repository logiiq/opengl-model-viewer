#ifndef LIGHT_H
#define LIGHT_H

#include <cglm/cglm.h>
#include "../Shader.h"

typedef struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
} PointLight_t;

PointLight_t light_new(float x, float y, float z);

void light_point_update(PointLight_t *light, Shader_t *shader, unsigned int index);

void light_point_position(PointLight_t *light, float x, float y, float z);

void light_point_ambient(PointLight_t *light, float r, float g, float b);

void light_point_diffuse(PointLight_t *light, float r, float g, float b);

void light_point_specular(PointLight_t *light, float r, float g, float b);

#endif