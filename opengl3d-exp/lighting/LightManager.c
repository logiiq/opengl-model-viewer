#define NR_POINT_LIGHTS_MAX 10

#include "../Shader.h"
#include "DirectionalLight.h"
#include "PointLight.h"

static DirectionalLight_t *directionalLight;
static PointLight_t *pointLights[NR_POINT_LIGHTS_MAX];
static unsigned int nrLights = 0;

void lightman_init(void)
{
	directionalLight = NULL;

	for (unsigned int i = 0; i < NR_POINT_LIGHTS_MAX; i++)
	{
		pointLights[i] = NULL;
	}
}

void lightman_add_point(PointLight_t *point)
{
	if (nrLights < NR_POINT_LIGHTS_MAX)
	{
		for (unsigned int i = 0; i < NR_POINT_LIGHTS_MAX; i++)
		{
			if (pointLights[i] == NULL)
			{
				pointLights[i] = point;
				nrLights++;
				break;
			}
		}
	}
	else
	{
		printf("ERROR: Max point light limit reached, please remove an instance or consider increasing max point light limit\n");
	}
}

void lightman_remove_point(PointLight_t *point)
{
	for (unsigned int i = 0; i < NR_POINT_LIGHTS_MAX; i++)
	{
		if (pointLights[i] == point)
		{
			pointLights[i] = NULL;
			nrLights--;
			return;
		}
	}
	printf("ERROR: Unable to remove light, reference does not exist in array or something has gone wrong\n");
}

void lightman_set_directional(DirectionalLight_t *directional)
{
	directionalLight = directional;
}

void lightman_update(Shader_t *shader)
{
	shader_use(shader);
	// phase 1: directional
	if (directionalLight != NULL)
	{
		light_directional_update(directionalLight, shader);
	}

	// phase 2: point
	for (unsigned int i = 0; i < nrLights; i++)
	{
		if (pointLights[i] != NULL)
		{
			light_point_update(pointLights[i], shader, i);
		}
	}

	shader_usei(0);
}