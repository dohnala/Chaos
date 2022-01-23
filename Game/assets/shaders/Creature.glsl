#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

layout (location = 0) out vec2 v_Position;

void main()
{
	v_Position = a_Position.xy;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

#define PIXELS_PER_UNIT 10

layout(location = 0) out vec4 color;

uniform float u_Time;
uniform float u_Radius;
uniform int u_Pixelation;
uniform int u_Antialiasing;

layout (location = 0) in vec2 v_Position;

float circle(vec2 pos, vec2 center, float radius)
{
	float distance = length(pos - center);
	float aa = (u_Antialiasing == 1) ? fwidth(length(v_Position)) : 0; 
	return smoothstep(0, 2*aa, radius - distance);
}

void main()
{
	float pixels = PIXELS_PER_UNIT * u_Radius;
	
	// Convert position to from [-0.5, 0.5] to [-1, 1] and pixelize them
	vec2 pos = (u_Pixelation == 1) ? floor(v_Position * 2.0 * pixels) / pixels : v_Position * 2.0;

	float shape = circle(pos, vec2(0), 1);

	color = vec4(0.0, 0.0, 0.0, 1.0 * shape);
}