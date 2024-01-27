#version 420 core
in vec4 pos;
out vec4 FragColor;

uniform vec4 spheres[5];
uniform int SPHERESCOUNT;

uniform vec3 boxesPos[5];
uniform vec3 boxesRad[5];
uniform int BOXCOUNT;

float floorLevel =3 ;
vec3 centre;
float dst;
int sphereHit;


float k = 1.5f;
float outlineT = 0.25f;

float smoothmax(float a, float b)
{
	return log(exp(k*a) + exp(k*b)) / k;
}

float smoothmin(float a, float b)
{
	return -smoothmax(-a,-b);
}

int nearestSphere()
{
	int res = 0;
	float dist = distance(centre, spheres[0].xyz);
	for(int i=0; i<SPHERESCOUNT; i++)
	{
		if(distance(centre, spheres[i].xyz) < dist) res = i;
	}
	return res;
}

float sphereSdf(vec3 pos, vec4 s)
{
	return  distance(pos, s.xyz) - s.w;
}

float boxSdf(vec3 pos, vec3 boxPos, vec3 boxRad)
{
	return length(max(abs(pos - boxPos)-boxRad,0));
}

float sdf(vec3 pos)
{ 
	int so = 0;
	int bo = 0;
	float result;
	if (SPHERESCOUNT > 0)
	{
			result = sphereSdf(pos, spheres[0]);
			so++;
	}
	else if (BOXCOUNT > 0)
	{
			result = boxSdf(pos, boxesPos[0], boxesRad[0]);
			bo++;
	}
	else 
		return 1;
		for(int i=so; i<SPHERESCOUNT; i++)
		{
			result = smoothmin(result,sphereSdf(pos, spheres[i]));
		}
		for(int i=bo; i<BOXCOUNT; i++)
		{
			result = smoothmin(result, boxSdf(pos, boxesPos[i], boxesRad[i]));
		}
	if(result > pos.y+floorLevel) return pos.y+floorLevel;
	return result;
}

vec3 getNormal(vec3 pos)
{
	float eps = 0.001;
	vec3 v1 = vec3
	(
	sdf(pos + vec3(eps,0,0)),
	sdf(pos + vec3(0,eps,0)),
	sdf(pos + vec3(0,0,eps))
	);	
	vec3 v2 = vec3
	(
	sdf(pos - vec3(eps,0,0)),
	sdf(pos - vec3(0,eps,0)),
	sdf(pos - vec3(0,0,eps))
	);
	return normalize(v1-v2);
}

float shadow(vec3 origin, vec3 light)
{
	vec3 dir = normalize(light - origin);
	float maxDist = length(light - origin);
	float initStep = 0.1f;
	vec3 pos = origin + dir*initStep;
	float s = sdf(pos);
	float totalDist = initStep;
	float closestDist = s;
	while(s > 0.001 && totalDist < maxDist)
	{
		pos = pos + s*dir;
		totalDist += s;
		s = sdf(pos);
		if(closestDist > s) closestDist = s;
	}
	if(closestDist<=0.001)
	{
		return 1;
	}
	return 0;
}

void main()
{
	vec4 bg = vec4(0.5, 0.5, 0.8, 1.0f);
	vec4 outline = vec4(0.9, 0.9, 0.9, 1.0f);

   vec3 ls = vec3(0,20,10);
   vec4 p = pos; 
   vec3 spherecoord = vec3(p.x, p.y, 1)/2;
   vec3 dir = spherecoord;

   float s;
   p*=3.1415/6;
   centre = vec3(0,3,0);
   s = sdf(centre);

   float mindist = 1;
   while(s > 0.01 && dst < 100)
   {
		dst += s;
		centre +=dir*s;
		s = sdf(centre);
		if(mindist > s)
			mindist = s;
   }
   if(s < 0.01) 
   {
	  if(centre.y + floorLevel < 0.01)
	  {
	    float sh = shadow(centre,ls);
		float px = floor(centre.x);
		float pz = floor(centre.z);
		int coef = (int(px) + int(pz)) % 2;
		if(coef == 0)
		{
			FragColor = vec4(0.5, 0.5, 0.5, 1.0f)*(1-sh); 
		}
		else
		{
			FragColor = vec4(0.8, 0.8, 0.8, 1.0f)*(1-sh); 
		}
	  }
	  else
	  {
		  float sh = shadow(centre,ls);
		  sphereHit = nearestSphere();
		  float shade = dot(normalize(ls - centre), getNormal(centre));
		  if(sh == 0)
			FragColor = vec4(1*shade, 0, 0, 1.0f) + vec4(0.3,0.3,0.3,0); 
		  else
			FragColor = vec4(1*(1-sh), 0, 0, 1.0f) + vec4(0.3,0.3,0.3,0); 
	  }
   }
   else if(mindist < outlineT)
   {
   		FragColor = outline * ((outlineT - mindist)/outlineT) + mindist/outlineT*bg; 
   }
   else
		FragColor = bg; 

}