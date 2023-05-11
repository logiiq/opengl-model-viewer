#include "PointLight.h"

#include <cglm/cglm.h>
#include <string.h>
#include "../Shader.h"

PointLight_t light_new(float x, float y, float z)
{
	PointLight_t tmp;
	light_point_position(&tmp, x, y, z);
	light_point_ambient(&tmp, 1.0f, 1.0f, 1.0f);
	light_point_diffuse(&tmp, 1.0f, 1.0f, 1.0f);
	light_point_specular(&tmp, 1.0f, 1.0f, 1.0f);
	return tmp;
}

void light_point_update(PointLight_t *light, Shader_t *shader, unsigned int index)
{
	shader_use(shader);

	vec3 pos;
	glm_mat4_mulv3(&shader->view, &light->position, 1.0f, &pos);

	char post[32];
	sprintf(post, "plights[%d].position", index);

	char amb[32];
	sprintf(amb, "plights[%d].ambient", index);

	char diff[32];
	sprintf(diff, "plights[%d].diffuse", index);

	char spec[32];
	sprintf(spec, "plights[%d].specular", index);

	shader_uniform3fv(shader, &pos, post);
	shader_uniform3fv(shader, &light->ambient, amb);
	shader_uniform3fv(shader, &light->diffuse, diff);
	shader_uniform3fv(shader, &light->specular, spec);
	shader_usei(0);
}

void light_point_position(PointLight_t *light, float x, float y, float z)
{
	light->position[0] = x;
	light->position[1] = y;
	light->position[2] = z;
}

void light_point_ambient(PointLight_t *light, float r, float g, float b)
{
	light->ambient[0] = r;
	light->ambient[1] = g;
	light->ambient[2] = b;
}

void light_point_diffuse(PointLight_t *light, float r, float g, float b)
{
	light->diffuse[0] = r;
	light->diffuse[1] = g;
	light->diffuse[2] = b;
}

void light_point_specular(PointLight_t *light, float r, float g, float b)
{
	light->specular[0] = r;
	light->specular[1] = g;
	light->specular[2] = b;
}