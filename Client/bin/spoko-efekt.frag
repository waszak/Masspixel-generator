uniform float time;
uniform vec2 resolution;

// position screen-centered
vec3 spos = vec3(-1. + 2. * gl_FragCoord.xy / resolution, 0.);
const vec3 e = vec3(0.05,0., 0.01);


vec3 origin = vec3(0.,1.,-15.);
int matID;

vec3 hsv(float h,float s,float v) {
	return mix(vec3(1.),clamp((abs(fract(h+vec3(3.,2.,1.)/3.)*6.-3.)-1.),0.,1.),s)*v;
}

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

/// objects

float sphere(vec3 p, float q) { return length(p) - q; }
float box(vec3 p, vec3 q) {
	vec3 di = abs(p) - q;
	return min(max(di.x,max(di.y,di.z)), length(max(di,0.)));
}
float cyl(vec3 p, float r, float c) {
    return max(length(p.xz)-r, abs(p.y)-c);
}


/// modifiers
vec3 rep(vec3 p, vec3 q) { return mod(p,q) - 0.5*q; }

void rX(inout vec3 p, float a) {
	float c,s;vec3 q=p;
	c = cos(a); s = sin(a);
	p.y = c * q.y - s * q.z;
	p.z = s * q.y + c * q.z;
}

void rY(inout vec3 p, float a) {
	float c,s;vec3 q=p;
	c = cos(a); s = sin(a);
	p.x = c * q.x + s * q.z;
	p.z = -s * q.x + c * q.z;
}

void rZ(inout vec3 p, float a) {
	float c,s;vec3 q=p;
	c = cos(a); s = sin(a);
	p.x = c * q.x - s * q.y;
	p.y = s * q.x + c * q.y;
}

float cols(vec3 p)
{
	p.xz = mod(p.xz,10.) - vec2(5.);
	rY(p,p.y * 5);
	rX(p,min(p.y,2.) * 0.05);  
	return min(cyl(p,0.5,7.),cyl(p-vec3(0,-4,0),1.5,2.)) + rand(floor(p.zy*15.)) *0.02;
}

float head(vec3 p)
{
  rY(p,-0.45); rZ(p,0.25);
  p += vec3(2,-0.25,2.5);
  float top = box(p, vec3(0.25 + p.z*(p.z+0.4)*0.15,0.2+(p.z*p.z*(p.z+0.1)*0.3),1.));
  float jaw = box(p-vec3(0,-0.4,0), vec3(0.3 + p.z * 0.2,0.08+p.z*0.1,1.));
  p.x = abs(p.x);
  float ok  = sphere(p-vec3(0.4,0.,0.5),0.1);
  float r = min(top,jaw);
  if (ok<r) matID = 1;
  return min(r,ok);
}

float drago(vec3 p)
{
  matID = 0;
  float h = head(p);
  float t = p.z;
  p -= vec3(0,0,4);
  rZ(p,p.z*0.3);
  rX(p,1.1);
  float neck = cyl(p, 0.3,5.);
  return min(h,neck + rand(floor(p.zy*10.)) *0.03);
}

float world(vec3 p)
{
  float h1 = drago(p-vec3(2,0,0));
  float h2 = drago(vec3(-p.x-3,p.y-1.5,p.z+2)); //-vec3(cos(time),sin(time),0)
  float h3 = drago(vec3(-p.x-3,-p.y-1.5,p.z+2));
  float plan = p.y + 3.+sin(p.x)*0.1 - rand(vec2(floor(p.x * 0.5),floor(p.z * 0.5))) * 0.08;

	return min(cols(p),min(plan,min(h1,min(h2,h3))));
}


/// tools
vec3 normal(vec3 p)
{
	return normalize( vec3( world(p + e.xyy) - world(p - e.xyy), 
											 	 world(p + e.yxy) - world(p - e.yxy),
											  world(p + e.yyx) - world(p - e.yyx) )); 
}

const float k = 0.85;
float ao(vec3 p, vec3 q) {
	float c = 1.;
	for (float i = 0.; i < 5.; ++i)
		c -= (i * k - world(p + q * i * k + e.z)) / pow(2., i);
	return clamp(c,0.,1.);
}

float sss(vec3 p, vec3 q) {	return ao(p, q); }


void main()
{
	vec3 ray = vec3(spos * vec2(tan(0.45) * resolution.x / resolution.y, tan(0.45)), 1.);

	vec3 lpos = vec3(3.,5.,-2);
	vec3 ldir;
	float ldst;
	const float lp = 35.;

	float i, dst = 0.1;
	float d, sdst = 0.;
	vec3 p = origin, color = vec3(0.);
	for (i = 0.; i < 1.; i += 1./128.)
	{
		p += ray * dst;
		d = world(p);
		if (d < e.z)
		{
			ldir = lpos - p;
			ldst = dot(ldir,ldir);
			ldir = normalize(ldir);

   vec3 n = normal(p);
			if (p.y < -2.2) 
				{ color = vec3(0.8,0.7,0.7) * ao(p,n)* dot(n,ldir) * lp / ldst - 0.05 * exp(dst * 0.05); break; }
			
			color = (+ vec3(0.98,0.92,0.92) * ao(p,n));// + vec3(0.62,0.23,0.09) * sss(p,-ldir) * 2.) * dot(n,ldir) * lp / ldst - 0.05 * exp(dst * 0.04);
			break;
		}
		dst = d;
	}
  
//if (matID == time) color = vec3(1,0,0);
 

	
	gl_FragColor = vec4(color,1.);
}