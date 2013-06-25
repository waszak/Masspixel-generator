uniform vec2 resolution;
uniform float time;

vec3 origin = vec3(0,0,-7.);//vec3(cos(time * 0.5) * 0.5,1.5 + sin(time),-12.5 + sin(time * 0.25));

float sphere(vec3 p, float s)
{
	return length(p) - s;
}

float plane(vec3 p, vec3 n)
{
	return dot(p, n);
}


vec3 duplicate(vec3 p, vec3 m)
{
	return mod(p, m) - m * 0.5;
} 


float f(vec3 p)
{
	//float a = sin(p.z - p.x * 3 + time * 6) * (abs(cos(time * 3))) * 0.4 + plane(p,vec3(0.,1.,0.));
 float b = sphere(duplicate(p - vec3(0.,cos(time) * 1.,-time*40),vec3(12.5,3.5, 14.5)), 1.);
	
	float m1 = sphere(p - vec3(sin(time * 1.4) * 1.9,cos(time + time) * 0.4,sin(time) + 4.), 1.);
	float m2 = sphere(p - vec3(sin(time) * 1.9,cos(time) * 1.1, + cos(time) + 5.),1.);
	float srf = 1./(m1+0.5+0.005) + 1./(m2+0.5+0.005);

	float dsrf = 1. / srf - 0.25;
	return min(dsrf, b);
	//return min(a,b);
}

vec3 normal(vec3 p) {
	vec2 e = vec2(0.005, 0.0);
	return (vec3(f(p+e.xyy),f(p+e.yxy),f(p+e.yyx))-f(p))/e.x;
}

vec3 rm(vec3 ray)
{
	float dist = 0.5;
 int step;
 float d;

 for (step = 0; step < 64; ++step)
 {
   vec3 t = ray * dist + origin;
   d = f(t);
   if (d < 0.05) // epsilon
				return vec3(0.36,0.05,0.05)+ dot(vec3(1,1,0), reflect(normal(t), ray));//return vec3(cos(t.z),sin(t.x), mod(t.y,2.));
		dist += d;
 }

	float s = 1. - dist / 250.;
	return vec3(0.24,0.513, 0.62) * s;
//vec3((1.- length(gl_FragCoord.xy / resolution - 0.5)));
}

void main()
{
 float ratio = resolution.x / resolution.y;
 float fovY = tan(0.45 * 0.5);
 float fovX = fovY * ratio;
 vec3 pos = vec3(-1.0 + 2. * gl_FragCoord.xy / resolution, 1);
 vec3 ray = normalize( pos * vec3(fovX, fovY, 1.) );

	gl_FragColor = vec4(rm(ray), 1.);
//vec4(abs(pos.y),abs(pos.x),1,1);
}