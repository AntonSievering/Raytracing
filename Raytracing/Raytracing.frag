#version 330 core

struct Material
{
	vec3 color;
	float fAmbient, fDiffuse, fSpecular, fReflectiveIndex;
};

struct AABB
{
	vec3 pos, size;
	Material material;
};

struct Light
{
	vec3 pos, color;
	float fStrength;
};

struct Circle
{
	vec3 middle;
	float fRadius;
	Material material;
};

struct RayHitResult
{
	int index;
	int type;
	float dist;
	vec3 cp, cn;
};

struct CollisionResult
{
	bool bHit;
	float dist;
	vec3 cp, cn;
};

uniform vec2 u_screenSize;
uniform float u_fFovHalf;
uniform vec3 u_pos;
uniform vec3 u_lookAt;
uniform vec3 u_sideWays;
uniform vec3 u_lookAtUp;

uniform int u_nObjects;
uniform int u_nLights;
uniform int u_nCircles;

uniform sampler1D u_AABBPos;
uniform sampler1D u_AABBSize;
uniform sampler1D u_AABBMaterial1;
uniform sampler1D u_AABBMaterial2;
uniform sampler1D u_CircleBounds;
uniform sampler1D u_CircleMaterial1;
uniform sampler1D u_CircleMaterial2;
uniform sampler1D u_lightPos;
uniform sampler1D u_lightColor;

AABB calculateAABB(int index)
{
	AABB aabb;
	float fSample = float(index + 0.5f) * 0.01f;
	
	aabb.pos = texture(u_AABBPos, fSample).xyz;
	aabb.size = texture(u_AABBSize, fSample).xyz;
	
	vec4 material1 = texture(u_AABBMaterial1, fSample);
	vec4 material2 = texture(u_AABBMaterial2, fSample);
	aabb.material.color = material1.xyz;
	aabb.material.fAmbient = material2.x;
	aabb.material.fDiffuse = material2.y;
	aabb.material.fSpecular = material2.z;
	aabb.material.fReflectiveIndex = material2.w;

	return aabb;
}

Circle calculateCircle(int index)
{
	Circle circle;
	float fSample = float(index + 0.5f) * 0.01f;
	
	vec4 bounds = texture(u_CircleBounds, fSample);
	circle.middle = bounds.xyz;
	circle.fRadius = bounds.w;

	vec4 material1 = texture(u_CircleMaterial1, fSample);
	vec4 material2 = texture(u_CircleMaterial2, fSample);
	circle.material.color = material1.xyz;
	circle.material.fAmbient = material2.x;
	circle.material.fDiffuse = material2.y;
	circle.material.fSpecular = material2.z;
	circle.material.fReflectiveIndex = material2.w;

	return circle;
}

Light calculateLight(int index)
{
	Light light;
	float fSample = float(index + 0.5f) * 0.01f;

	light.pos = texture(u_lightPos, fSample).xyz;
	vec4 color = texture(u_lightColor, fSample);
	light.color = color.xyz;
	light.fStrength = color.w;

	return light;
}

vec3 rotateVector(vec3 vector, vec3 normal, float fAngle)
{
	return vector * cos(fAngle) + cross(normal, vector) * sin(fAngle) + normal * dot(normal, vector) * (1.0f - cos(fAngle));
}

vec3 reflectVector(vec3 vector, vec3 normal)
{
	return vector - normal * 2.0f * dot(vector, normal);
}

CollisionResult AABBCollision(AABB object, vec3 origin, vec3 dir)
{
	vec3 invDir = vec3(1.0f / dir.x, 1.0f / dir.y, 1.0f / dir.z);
	vec3 lb = object.pos;
	vec3 rt = lb + object.size;

	float t1 = (lb.x - origin.x) * invDir.x;
	float t2 = (rt.x - origin.x) * invDir.x;
	float t3 = (lb.y - origin.y) * invDir.y;
	float t4 = (rt.y - origin.y) * invDir.y;
	float t5 = (lb.z - origin.z) * invDir.z;
	float t6 = (rt.z - origin.z) * invDir.z;

	float tminx = min(t1, t2);
	float tminy = min(t3, t4);
	float tminz = min(t5, t6);

	float tmaxx = max(t1, t2);
	float tmaxy = max(t3, t4);
	float tmaxz = max(t5, t6);

	float tmin = max(max(tminx, tminy), tminz);
	float tmax = min(min(tmaxx, tmaxy), tmaxz);

	CollisionResult result;
	result.bHit = !(tmax < 0.0f || tmin > tmax);
	
	if (result.bHit)
	{
		result.dist = tmin;
		result.cp = origin + dir * tmin;

		float fValX = 1.0f - 2.0f * float(origin.x < result.cp.x);
		float fValY = 1.0f - 2.0f * float(origin.y < result.cp.y);
		float fValZ = 1.0f - 2.0f * float(origin.z < result.cp.z);
		result.cn = vec3(fValX * float(tmin == tminx), fValY * float(tmin == tminy), fValZ * float(tmin == tminz));
	}

	return result;
}

CollisionResult CircleC(Circle object, vec3 origin, vec3 dir)
{
	dir = normalize(dir);
	vec3 L = origin - object.middle;
	float a = dot(dir, dir);
	float b = 2.0f * dot(dir, L);
	float c = dot(L, L) - object.fRadius * object.fRadius;
	float disciminent = b * b - 4.0f * a * c;
	float t = (-b - sqrt(disciminent)) / (2.0f * a);

	CollisionResult result;
	result.bHit = disciminent >= 0.0f && t > 0.0f;

	if (result.bHit)
	{
		result.cp = origin + dir * t;
		result.dist = distance(result.cp, origin);
		result.cn = normalize(result.cp - object.middle);
	}

	return result;
}

RayHitResult getNearestGameObject(vec3 origin, vec3 dir, int ignoreId = -1, int type = 0)
{
	dir = normalize(dir);
	float fNearest = 1e30f;
	int index = -1, ty = -1;
	CollisionResult nearest;

	// AABBs
	for (int i = 0; i < u_nObjects; i++)
	{
		if (!(i == ignoreId && type == 0))
		{
			CollisionResult result = AABBCollision(calculateAABB(i), origin, dir);
		
			if (result.bHit && result.dist < fNearest)
			{
				nearest = result;
				index = i;
				ty = 0;
				fNearest = result.dist;
			}
		}
	}

	// Circles
	for (int i = 0; i < u_nCircles; i++)
	{
		if (!(i == ignoreId && type == 1))
		{
			CollisionResult result = CircleC(calculateCircle(i), origin, dir);

			if (result.bHit && result.dist < fNearest)
			{
				nearest = result;
				index = i;
				ty = 1;
				fNearest = result.dist;
			}
		}
	}

	RayHitResult result;
	result.dist = fNearest;
	result.index = index;
	result.type = ty;
	result.cp = nearest.cp;
	result.cn = nearest.cn;

	return result;
}

float rayHitScene(vec3 origin, vec3 dir, int ignoreId = -1, int type = 0)
{
	float fNearest = 1e30f;

	// check AABBs
	for (int i = 0; i < u_nObjects; i++)
	{
		if (!(i == ignoreId && type == 0))
		{
			CollisionResult result = AABBCollision(calculateAABB(i), origin, dir);

			if (result.bHit && result.dist < fNearest)
				fNearest = result.dist;
		}
	}

	// check Circles
	for (int i = 0; i < u_nCircles; i++)
	{
		if (!(i == ignoreId && type == 1))
		{
			CollisionResult result = CircleC(calculateCircle(i), origin, dir);

			if (result.bHit && result.dist < fNearest)
				fNearest = result.dist;
		}
	}

	return fNearest;
}

bool rayIsBlocked(vec3 origin, vec3 dir, int ignoreId)
{
	return rayHitScene(origin, normalize(dir), ignoreId) <= 1.0f;
}

float calculateLightBrightness(Light light, float dist)
{
	float x = dist / light.fStrength + 1.0f;
	return 1.0f / (x * x);
}

vec3 calculateSurfaceColor(int index, int type, vec3 cp, vec3 cn)
{
	vec3 blockColor = vec3(0.0f);
	if (type == 0)
	{
		blockColor = calculateAABB(index).material.color;
	}
	else if (type == 1)
	{
		blockColor = calculateCircle(index).material.color;
	}

	vec3 ambientColor = blockColor * 0.1f;
	vec3 diffuseColor = vec3(0.0f), specularColor = vec3(0.0f);
		
	for (int i = 0; i < u_nLights; i++)
	{
		Light light     = calculateLight(i);
		vec3 lightPos   = light.pos;
		vec3 lightDir   = normalize(lightPos - cp);

		if (!rayIsBlocked(cp, lightDir, index))
		{
			vec3 lightColor = light.color;
			float fBrightness = calculateLightBrightness(light, length(lightPos - cp));

			float fDiffuse = max(dot(cn, lightDir), 0.0f);
			diffuseColor += (lightColor * blockColor) * fDiffuse * fBrightness;

			float fSpecularStrength = 0.5f;
			vec3 viewDir = normalize(u_pos - cp);
			vec3 reflectDir = reflectVector(-lightDir, cn);
			float fSpecular = pow(max(dot(viewDir, reflectDir), 0.0f), 64.0f) * fSpecularStrength;
			specularColor += lightColor * fSpecular * fBrightness;
		}
	}

	return ambientColor + diffuseColor + specularColor;
}

vec3 calculateColorIterative(vec3 cpos, vec3 lookAt, int bounces)
{
	vec3 finalColor = vec3(0.0f);
	int ignoreId = -1;
	int ignoreType = -1;
	float r = 1.0f;

	for (int i = 0; i < bounces; i++)
	{
		RayHitResult result = getNearestGameObject(cpos, lookAt, ignoreId, ignoreType);
		
		if (result.index != -1 && r > 0.025f)
		{
			vec3 surfaceColor = calculateSurfaceColor(result.index, result.type, result.cp, result.cn);
			
			vec3 reflectedDir = reflectVector(lookAt, result.cn);
			cpos = result.cp;
			lookAt = reflectedDir;
			ignoreId = result.index;
			ignoreType = result.type;

			finalColor += surfaceColor * r;

			float reflectiveIndex = 0.0f;
			if (result.type == 0)
			{
				reflectiveIndex = calculateAABB(result.index).material.fReflectiveIndex;
			}
			else if (result.type == 1)
			{
				reflectiveIndex = calculateCircle(result.index).material.fReflectiveIndex;
			}

			r *= reflectiveIndex;
		}
		else
		{
			return finalColor;
		}
	}

	return finalColor;
}

void main()
{
	vec2 relativeCoordinate = vec2(2.0f * gl_FragCoord.x / u_screenSize.x - 1.0f, 2.0f * gl_FragCoord.y / u_screenSize.y - 1.0f);
	float fAspectRatio = u_screenSize.y / u_screenSize.x;
	vec2 angles = vec2(relativeCoordinate.x * u_fFovHalf, relativeCoordinate.y * u_fFovHalf * fAspectRatio);

	vec3 projX  = rotateVector(u_lookAt, u_lookAtUp, angles.x);
	vec3 projXY = rotateVector(projX,    u_sideWays, angles.y);

	gl_FragColor = vec4(calculateColorIterative(u_pos, projXY, 10), 1.0f);
}
