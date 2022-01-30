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

layout(location = 0) out vec4 color;

uniform float u_Time;
uniform vec4 u_Color;

layout (location = 0) in vec2 v_Position;

float circle(vec2 pos, vec2 center, float radius)
{
	float distance = length(pos - center);
	float aaf = fwidth(length(v_Position)); 
	return smoothstep(0, 2 * aaf, radius - distance);
}

void main()
{
	// Convert position to from [-0.5, 0.5] to [-1, 1]
	vec2 pos = v_Position * 2.0;

	float shape = circle(pos, vec2(0), 1);

	color = vec4(u_Color.rgb, u_Color.a * shape);
}