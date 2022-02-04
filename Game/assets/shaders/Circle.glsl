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
uniform float u_Thickness;
uniform float u_Circumference;
uniform int u_GapCount;
uniform float u_GapSize;
uniform float u_Rotation;

layout (location = 0) in vec2 v_Position;

#define H_PI 1.57079632679
#define PI 3.14159265359
#define TWO_PI 6.28318530718

vec2 rotate(vec2 pos, float angle)
{
    mat2 rot = mat2(cos(angle), sin(angle), -sin(angle), cos(angle));
    //return rot * pos;
	return pos;
}

void main()
{
	// Convert position to from [-0.5, 0.5] to [-1, 1]
	vec2 pos = rotate(v_Position * 2, u_Rotation * TWO_PI);
	float angle = H_PI - atan(pos.x * -1, pos.y * -1);
	float radius = 1;

	float distance = length(pos);
	float aa = fwidth(distance) * 2; 
	
	// Circle with radius
	float circle = smoothstep(0, aa, radius - distance);

	// Subtract circle to create thickness
	circle -= smoothstep(0, aa, radius - u_Thickness - distance);

	// Preserve only defined circumference
	circle *= 1 - smoothstep(0, 2 * aa, angle + H_PI - u_Circumference * TWO_PI + (u_Circumference == 0 ? 0.1 : 0.0));

	// Add gaps
	circle *= 1 - smoothstep(0 , 2 * aa, -1 + u_GapSize * 2 - cos( u_Rotation * TWO_PI + angle * u_GapCount));

	color = vec4(u_Color.rgb, u_Color.a * circle);
}