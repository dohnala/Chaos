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

// Controls frequency of the noise used
#define NOISE_FREQ 16
// Controls the speed of the noise used when animating shape and color
#define NOISE_SPEED 0.5

// Controls how falloff of the border noise distortion (0 - very blurry, 1 - very sharp)
#define BORDER_DISTORTION_FALLOFF 0.3
// Controls how much is the color gradient distorted (0 - no distortion, 1 - full distortion)
#define COLOR_GRADIENT_DISTORTION 0.1

layout(location = 0) out vec4 color;

uniform float u_Time;
uniform float u_Radius;
uniform vec4 u_ColorInside;
uniform vec4 u_ColorOutside;
uniform float u_ColorRatio;
uniform float u_BorderDistortion;
uniform vec2 u_Direction;
uniform float u_DirectionDistortion;

layout (location = 0) in vec2 v_Position;

float hash(vec2 p)  
{
    p = 50.0 * fract(p * 0.3183099 + vec2(0.71, 0.113));
    return -1.0 + 2.0 * fract(p.x * p.y * (p.x + p.y));
}

float noise(in vec2 p)
{
    vec2 i = floor(p);
    vec2 f = fract(p);
	
	vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(mix(hash(i + vec2(0.0, 0.0)), 
				   hash(i + vec2(1.0, 0.0)), u.x),
               mix(hash(i + vec2(0.0, 1.0)), 
                   hash(i + vec2(1.0, 1.0)), u.x), u.y);
}

float border(vec2 pos, vec2 dir)
{
	vec2 offset = dir * u_Time * NOISE_SPEED;
	float freq = (NOISE_FREQ * u_Radius);
	float dist = u_BorderDistortion;
	// Distortion of border based on velocity direction
	// Problem: the distortion is very big on the sides in the front
	dist *=  1 + clamp(length((pos - normalize(u_Direction))), 0, 1);

	return dist * (1 - BORDER_DISTORTION_FALLOFF + BORDER_DISTORTION_FALLOFF * noise((pos + offset) * freq));
}

float circle(vec2 pos, vec2 dir, vec2 center, float radius)
{
	float distance = length(pos - center);
	float aaf = length(vec2(dFdx(distance), dFdy(distance))) * 2; 
	return smoothstep(-border(pos, dir), aaf, radius - u_BorderDistortion - distance);
}

float distortion(vec2 pos, vec2 dir)
{
	float dirL = length(dir);
	float dirN = u_DirectionDistortion * dirL;

	// Left side distortion by velocity
	float leftD = circle(pos, dir, dir + dirN * vec2(dir.y, -dir.x), sqrt(pow(1 + dirL, 2) + pow(dirN * dirL, 2)));

	// Right side distortion by velocity
	float rightD = circle(pos, dir, dir + dirN * vec2(-dir.y, dir.x), sqrt(pow(1 + dirL, 2) + pow(dirN * dirL, 2)));

	return min(leftD, rightD);
}

vec4 colorGradient(vec2 pos, vec2 dir)
{
	float a = clamp(1 - u_ColorRatio + u_ColorRatio * length(pos), 0, 1);
	vec2 offset = dir * u_Time * NOISE_SPEED;
	a += COLOR_GRADIENT_DISTORTION * noise((pos + offset) * (NOISE_FREQ * u_Radius));

	return mix(u_ColorInside, u_ColorOutside, a);
}

void main()
{
	// Convert position to from [-0.5, 0.5] to [-1, 1]
	vec2 pos = v_Position * 2;
	vec2 dir = normalize(u_Direction);

	// Final shape from unit circle and shape distortion
	float shape = min(circle(pos, dir, vec2(0), 1), distortion(pos, dir));

	vec4 gradient = colorGradient(pos, dir);

	color = vec4(gradient.rgb, gradient.a * shape);
}