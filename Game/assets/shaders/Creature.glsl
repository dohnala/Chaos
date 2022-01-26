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

#define PIXELS_PER_UNIT 20
#define PI 3.14159265358979323846

layout(location = 0) out vec4 color;

uniform float u_Time;
uniform float u_Radius;
uniform int u_Pixelation;
uniform int u_TentacleCount;
uniform float u_TentacleLength;
uniform float u_TentacleRigidity;
uniform vec2 u_Velocity;

layout (location = 0) in vec2 v_Position;

vec2 pixelate(vec2 pos)
{
	float pixels = PIXELS_PER_UNIT * u_Radius;

	pos *= pixels;

	pos = vec2(
		pos.x >= 0 ? floor(pos.x) : ceil(pos.x),
		pos.y >= 0 ? floor(pos.y) : ceil(pos.y)
	);
	
	pos /= pixels;

	return pos;
}

float circle(vec2 pos, vec2 center, float radius)
{
	float distance = length(pos - center);
	float aa = fwidth(length(v_Position)); 
	return smoothstep(0, 2 * aa, radius - distance);
}

float tentacles(vec2 pos, float radius)
{
	// Max offset of the tentacle
	float tentacleMaxOffset = 5.;

	// How much is the tentacle influenced by velocity
	float tentacleOffsetVelocityScale = 1.;

	// How fast can tentacle move when the creature is not moving
	float tentacleIdleSpeed = 2.;
	vec2 tentacleIdleCycles = vec2(1., 2.);

	// How much can tentacle move when the creature is not moving
	float tentacleIdleMaxOffset = 2.;
	
	vec2 tentaclePos = pos;
	float d = pow(length(pos) - (1. - u_TentacleLength) * radius, 2.);

	vec2 tentacleIdleOffset = vec2(
		cos(pos.y * tentacleIdleCycles.x + u_Time * tentacleIdleSpeed) * tentacleIdleMaxOffset * d,
		sin(pos.x * tentacleIdleCycles.y + u_Time * tentacleIdleSpeed) * tentacleIdleMaxOffset * d);
	
	vec2 tentacleMoveOffset = normalize(u_Velocity) * min(length(u_Velocity) * tentacleOffsetVelocityScale, tentacleMaxOffset) * d * (1. - u_TentacleRigidity);

	float a = clamp(length(u_Velocity) / (tentacleMaxOffset / tentacleOffsetVelocityScale), 0., 1.);
	tentaclePos += mix(tentacleIdleOffset, tentacleMoveOffset, a);

	return abs(sin((PI / u_TentacleCount + atan(tentaclePos.y, tentaclePos.x)) * u_TentacleCount * 0.5) * u_TentacleLength);
}

float creature(vec2 pos, vec2 center, float radius)
{
	float aa = fwidth(length(v_Position)); 

	float bodyIdleSpeed = 1.;
	float bodyIdleCycles = 10.;
	float bodyIdleAmplitude = 0.04;

	vec2 bodyPos = pos;
	bodyPos.x += cos(pos.y * bodyIdleCycles + u_Time * bodyIdleSpeed) * bodyIdleAmplitude;
	bodyPos.y += sin(pos.x * bodyIdleCycles + u_Time * bodyIdleSpeed) * bodyIdleAmplitude;
	float body = smoothstep(0, 2 * aa, radius - 0.04 - length(bodyPos - center) - tentacles(pos, radius));

	return body;
}

void main()
{
	// Convert position to from [-0.5, 0.5] to [-1, 1] and pixelate it if needed
	vec2 pos = (u_Pixelation == 1) ? pixelate(v_Position * 2.0) : v_Position * 2.0;

	float creature = creature(pos, vec2(0), 1);

	color = vec4(0, 0, 0, 1.0 * creature);
}