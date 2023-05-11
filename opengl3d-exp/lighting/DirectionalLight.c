#include "DirectionalLight.h"

#include "../Shader.h"

DirectionalLight_t light_directional_new(float x, float y, float z)
{
	DirectionalLight_t tmp;
	light_directional_direction(&tmp, x, y, z);
	light_directional_ambient(&tmp, 0.5f, 0.5f, 0.5f);
	light_directional_diffuse(&tmp, 0.2f, 0.2f, 0.2f);
	light_directional_specular(&tmp, 0.0f, 0.0f, 0.0f);
	return tmp;
}

void light_directional_update(DirectionalLight_t *light, Shader_t *shader)
{
	shader_use(shader);

    shader_uniform3fv(shader, light->direction, "dlight.direction");
	shader_uniform3fv(shader, light->ambient, "dlight.ambient");
    shader_uniform3fv(shader, light->diffuse, "dlight.diffuse");
	shader_uniform3fv(shader, light->specular, "dlight.specular");

	shader_usei(0);
}

void light_directional_direction(DirectionalLight_t *light, float x, float y, float z)
{
	light->direction[0] = x;
	light->direction[1] = y;
	light->direction[2] = z;
}

void light_directional_ambient(DirectionalLight_t *light, float r, float g, float b)
{
	light->ambient[0] = r;
	light->ambient[1] = g;
	light->ambient[2] = b;
}

void light_directional_diffuse(DirectionalLight_t *light, float r, float g, float b)
{
	light->diffuse[0] = r;
	light->diffuse[1] = g;
	light->diffuse[2] = b;
}

void light_directional_specular(DirectionalLight_t *light, float r, float g, float b)
{
	light->specular[0] = r;
	light->specular[1] = g;
	light->specular[2] = b;
}