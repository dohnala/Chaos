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

uniform vec4 u_Color;
uniform float u_InnerRadius;
uniform float u_OuterAlpha;

layout (location = 0) in vec2 v_Position;

void main()
{
	// Convert position to from [-0.5, 0.5] to [-1, 1]
	vec2 xy = v_Position * 2 ;

	float distance = length(xy);

	// Anti-aliasing distance
	float aaf = length(vec2(dFdx(distance), dFdy(distance))) * 2;
	float a1 = smoothstep(0.0, aaf,  1.0 - distance) * u_OuterAlpha;
	float a2 = smoothstep(1.0 - u_InnerRadius, 1.0 - u_InnerRadius + aaf, 1.0 - distance);

	color = vec4(u_Color.rgb, u_Color.a * max(a1, a2));
}