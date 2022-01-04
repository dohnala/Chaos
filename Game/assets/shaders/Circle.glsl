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

float hash(vec2 p)  
{
    p = 50.0 * fract(p * 0.3183099 + vec2(0.71, 0.113));
    return -1.0 + 2.0 * fract(p.x * p.y * (p.x + p.y));
}

float noise( in vec2 p)
{
    vec2 i = floor(p);
    vec2 f = fract(p);
	
	vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(mix(hash(i + vec2(0.0, 0.0)), 
				   hash(i + vec2(1.0, 0.0)), u.x),
               mix(hash(i + vec2(0.0, 1.0)), 
                   hash(i + vec2(1.0, 1.0)), u.x), u.y);
}


#define COLOR_NOISE_ENABLED 1
#define COLOR_NOISE_FREQ 16

#define BORDER_NOISE_ENABLED 1
#define BORDER_NOISE_DISTANCE 0.25
#define BORDER_NOISE_FREQ 16

void main()
{
	// Convert position to from [-0.5, 0.5] to [-1, 1]
	vec2 xy = v_Position * 2 ;

	float distance = length(xy);

	float colorNoise =  min(1, 1 - COLOR_NOISE_ENABLED + (0.7 + 0.3 * noise(xy * COLOR_NOISE_FREQ)));
	float borderNoise = BORDER_NOISE_ENABLED * (0.7 + 0.3 * noise(xy * BORDER_NOISE_FREQ)) * BORDER_NOISE_DISTANCE;

	// Anti-aliasing distance
	float aaf = length(vec2(dFdx(distance), dFdy(distance))) * 2;
	float a1 = smoothstep(0.0, aaf,  1.0 - distance) * u_OuterAlpha;
	float a2 = smoothstep(1.0 - u_InnerRadius - borderNoise, 1.0 - u_InnerRadius + aaf, 1.0 - distance);

	color = vec4(mix(u_Color.rgb, u_Color.rgb * colorNoise, a2), u_Color.a * max(a1, a2));
}