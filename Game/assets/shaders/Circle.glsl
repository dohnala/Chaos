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
#define BORDER_NOISE_DISTANCE 0.2	// [0, 1] -> should be uniform
#define BORDER_NOISE_FALLOFF 0.3	// [0, 1] -> should be uniform

// Scale real velocity down for distortion computation
#define VELOCITY_FORWARD_SCALE 0.05
#define VELOCITY_SIDE_SCALE 0.2

#define NOISE_FREQ 16
#define NOISE_SPEED 0.5

float shading(vec2 pos)
{
	// Try to reimplement this using HSV light shifting

	// should be uniform
	// controls how much is the color shaded
	// 0 - no shading
	// 1 - really hard shading
	float ratio = 0;

	// should be uniform
	// controls how far from center is shading applied
	// 0 - shading is everywhere
	// 0.5 - shading is not in the middle
	// 1 - shading is on border
	float distanceFromCenter = 0;

	vec2 offset = normalize(u_Velocity) * u_Time * NOISE_SPEED;
	float freq = (NOISE_FREQ * u_Radius);
	float n = 1 - ratio + ratio * noise((pos + offset) * freq);
	n += (1 - length(pos)) * distanceFromCenter;

	return min(1, 1 - COLOR_NOISE_ENABLED + n);
}

float border(vec2 pos)
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
	return smoothstep(-border(pos), aaf, radius - BORDER_NOISE_ENABLED * BORDER_NOISE_DISTANCE - distance);
}

vec3 colorGradient(vec2 pos, vec3 from, vec3 to)
{
	// should be uniform
	// controls the ration between from and to color
	// 0 - only to color
	// 1 - half to half
	// 3 and more - only from color
	float ratio = 1;
	float a = clamp(1 - ratio + ratio * length(pos), 0, 1);

	// should be parameter
	float distortion = 0.1;
	vec2 offset = normalize(u_Velocity) * u_Time * NOISE_SPEED;
	a += distortion * noise((pos + offset) * (NOISE_FREQ * u_Radius));

	return mix(from, to, a) * shading(pos);
}

void main()
{
	// Convert position to from [-0.5, 0.5] to [-1, 1]
	vec2 pos = v_Position * 2 ;

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

	vec3 cFrom = vec3(0.94, 0.8, 0.21);
	//vec3 cTo = vec3(0.15, 0.85, 0.15);
	vec3 cTo = vec3(0.75, 0.14, 0.15);

	color = vec4(colorGradient(pos, cFrom, cTo), u_Color.a * shape);
}