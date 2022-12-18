#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void log_verbose(const char *message);

texture_t texture_new(const char *path, int flip, GLint type)
{
	log_verbose("==== texture_new() call ====");

	int id = 0;

	int width = 0;
	int height = 0;
	int nrChannels = 0;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	log_verbose("Texture generated and bound");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	log_verbose("Attempting to load texture into buffer...");

	stbi_set_flip_vertically_on_load(flip);
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

	log_verbose("Texture successfully loaded into buffer");

#if DEBUG_MODE == 1
	printf("DEBUG: STBI: %s\n", stbi_failure_reason());
#endif

	log_verbose("Attempting to send buffer to GPU...");

	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	log_verbose("Sent data over to GPU, generated mipmaps");
	log_verbose("Cleaning up texture...");

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);

	log_verbose("==== end texture_new() ====");

	return id;
}

void texture_use(const texture_t t)
{
	glBindTexture(GL_TEXTURE_2D, t);
}