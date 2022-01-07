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
uniform float u_Radius;
uniform vec2 u_Velocity;

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

#define COLOR_NOISE_ENABLED 1		// 0 or 1 -> should be uniform

#define BORDER_NOISE_ENABLED 1		// 0 or 1 -> should be uniform
#define BORDER_NOISE_DISTANCE 0.25	// [0, 1] -> should be uniform
#define BORDER_NOISE_FALLOFF 0.25	// [0, 1] -> should be uniform

// Scale real velocity down for distortion computation
#define VELOCITY_FORWARD_SCALE 0.05
#define VELOCITY_SIDE_SCALE 0.2

#define NOISE_FREQ 16
#define NOISE_SPEED 0.5

float colorNoise(vec2 pos)
{
	vec2 offset = normalize(u_Velocity) * u_Time * NOISE_SPEED;
	float freq = (NOISE_FREQ * u_Radius);

	return min(1, 1 - COLOR_NOISE_ENABLED + (0.7 + 0.3 * noise((pos + offset) * freq)));
}

float borderNoise(vec2 pos)
{
	vec2 offset =  normalize(u_Velocity) * u_Time * NOISE_SPEED;
	float freq = (NOISE_FREQ * u_Radius);
	float dist = BORDER_NOISE_DISTANCE * clamp(length((pos - normalize(u_Velocity))), 0.0, 1);

	return BORDER_NOISE_ENABLED * dist * (1 - BORDER_NOISE_FALLOFF + BORDER_NOISE_FALLOFF * noise((pos + offset) * freq));
}

float circleF(vec2 pos, vec2 center, float radius)
{
	float distance = length(pos - center);
	float aaf = length(vec2(dFdx(distance), dFdy(distance))) * 2; 
	return smoothstep(-borderNoise(pos), aaf, radius - BORDER_NOISE_ENABLED * BORDER_NOISE_DISTANCE - distance);
}

void main()
{
	// Convert position to from [-0.5, 0.5] to [-1, 1]
	vec2 pos = v_Position * 2 ;

	float distance = length(pos);

	// Normalize velocity to given scale
	vec2 vForward = u_Velocity * VELOCITY_FORWARD_SCALE;
	float vL = length(vForward);

	// Velocity side offset based on velocity length
	float vSide = 1 + vL * VELOCITY_SIDE_SCALE;

	// Unit circle
	float circle = circleF(pos, vec2(0), 1);

	// Left side distortion by velocity
	float leftD = circleF(pos, vForward + vSide * vec2(vForward.y, -vForward.x), sqrt(pow(1 + vL, 2) + pow(vSide * vL, 2)));

	// Right side distortion by velocity
	float rightD = circleF(pos, vForward + vSide * vec2(-vForward.y, vForward.x), sqrt(pow(1 + vL, 2) + pow(vSide * vL, 2)));

	// Final shape
	float shape = min(circle, min(leftD, rightD));

	color = vec4(mix(u_Color.rgb, u_Color.rgb * colorNoise(pos), shape), u_Color.a * shape);
}