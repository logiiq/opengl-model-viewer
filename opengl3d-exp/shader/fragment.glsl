// Lighting fshader
#version 460 core

#define NR_POINT_LIGHTS 10

out vec4 FragColor;

in vec3 normPos;
in vec2 texPos;
in vec3 fragPos;

uniform sampler2D txSampler;

struct Material
{
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform DirectionalLight dlight;
uniform PointLight plights[NR_POINT_LIGHTS];

// Update shader to have separate structs for each type of light (directional, point and spot*)
// Spot light should be implemented after multiple light integration

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDirection, vec3 fragPos);
vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection, vec3 fragPos);

void main()
{
    // Define lighting variables
    vec3 norm = normalize(normPos); // Normalize normals to unit vectors
    vec3 viewDir = normalize(-fragPos); // We just normalize the negated vector of the fragment because viewer is always (0, 0, 0);
    
    vec4 result;

    // phase 1: directional lighting
    result += vec4(calcDirectionalLight(dlight, norm, viewDir, fragPos), 1.0f);

    // phase 2: point lights
    for (unsigned int i = 0; i < NR_POINT_LIGHTS; i++) 
    {
        result += vec4(calcPointLight(plights[i], norm, viewDir, fragPos), 1.0f);
    }

    FragColor = result;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDirection, vec3 fragPos)
{
    vec3 lightDirection = normalize(light.position - fragPos);
    float lightDistance = length(light.position - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);

    // Calculate light attenuation
    float attenuation = 1.0f / (1.0f + 0.09f * lightDistance + 0.032f * (lightDistance * lightDistance));    

    float diff = max(dot(lightDirection, normal), 0.0f);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texPos));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texPos));
    vec3 specular = light.specular * spec * material.specular;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection, vec3 fragPos)
{
    vec3 lightDirection = normalize(-light.direction);

    float diff = max(dot(normal, lightDirection), 0.0f);

    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);    

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texPos));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texPos));
    vec3 specular = light.specular * spec * material.specular;

    return (ambient + diffuse + specular);
}