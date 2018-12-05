#version 150 core

uniform sampler2D Texture;

uniform vec3 AmbientColor;
uniform vec3 LightColor;
uniform vec3 CamPosition;
uniform vec4 SpecColor;

in vec2 UV;
in vec3 Normal;
in vec3 LightDirOp;
in vec3 Position;

out vec4 Color;

void main()
{
    vec3 lightDir = normalize(LightDirOp);
	vec3 viewDirection = normalize(CamPosition - Position);
	vec3 normal = normalize(Normal);
	float nDotl = dot(lightDir, normal);
	vec3 halfVec = normalize(lightDir + viewDirection);
	float nDoth = dot(normal, halfVec);

	vec4 sampledColor = texture(Texture, UV);
	vec3 ambient = AmbientColor.rgb * sampledColor.rgb;
	vec3 diffuse = clamp(LightColor.rgb * nDotl * sampledColor.rgb, 0.0f, 1.0f);
	vec3 specular = SpecColor.rgb * min(pow(clamp(nDoth, 0.0f, 1.0f), SpecColor.a), sampledColor.w);

	Color.rgb = ambient + diffuse + specular;
	Color.a = sampledColor.a;
}