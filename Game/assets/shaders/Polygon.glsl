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
uniform int u_VertexCount;
uniform vec4 u_Color;

layout (location = 0) in vec2 v_Position;

#define PI 3.14159265359
#define TWO_PI 6.28318530718

float polygon(vec2 pos, int n)
{
	float aaf = fwidth(length(pos)); 
    float a = atan(pos.x, pos.y) + PI;
    float r = TWO_PI / float(n);

	float d = cos(floor(0.5 + a / r) * r - a) * length(pos);
	return smoothstep(0, aaf, 0.5 - d);
}

void main()
{
	// Convert position to from [-0.5, 0.5] to [-1, 1]
	vec2 pos = v_Position * 2.0;

	float shape = polygon(pos, u_VertexCount);

	color = vec4(u_Color.rgb, u_Color.a * shape);
}