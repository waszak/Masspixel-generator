uniform vec2 resolution;

vec3 spos = vec3(-1.+2.*gl_FragCoord.xy/resolution, 0.);
const vec3 e = vec3(0.05,0., 0.01);
vec3 origin = vec3(0.,1.,-15.);
int matID;

float rand(vec2 co){return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);}
float sphere(vec3 p, float q){return length(p) - q;}
float box(vec3 p, vec3 q){	vec3 di=abs(p)-q;	return min(max(di.x,max(di.y,di.z)),length(max(di,0.)));}
float cyl(vec3 p, float r, float c){return max(length(p.xz)-r, abs(p.y)-c);}
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
float skin(vec3 p){return rand(floor(p.zy*15.)) *0.03;}
float cols(vec3 p)
{
	 p.xz = mod(p.xz,10.) - vec2(5.);
	 rY(p,p.y * 5);
  rX(p,min(p.y,2.) * 0.05);  
  return min(cyl(p,0.5,7.),cyl(p-vec3(0,-4,0),1.5,2.)) + skin(p);
}

float impulse(float k, float x){float h = k*x;return h*exp(1.0-h);}

float head(vec3 p){
  rY(p,-0.45); rZ(p,0.25);
  p += vec3(2,-0.25,2.5);
  float top = box(p, vec3(0.3+impulse(0.4,p.z) * 0.15,clamp(0.2+ impulse(0.5,p.z) * 0.05,0.05,0.6),1.));
  float jaw = box(p-vec3(0,-0.4,0), vec3(0.3 + impulse(0.4,p.z) * 0.15,0.08+p.z*0.1,1.));
  p.x = abs(p.x);
  float ok  = sphere(p-vec3(0.4,0.,0.5),0.1);
  return min(min(top,jaw)+skin(p)*0.8,ok);
}

float drago(vec3 p)
{
  float h=head(p);
  float t=p.z;
  p -=vec3(0,0,4);
  rZ(p,p.z*0.3);
  rX(p,1.1);
  float neck=cyl(p, 0.3,5.);
  return min(h,neck+skin(p));
}

float bone(vec3 p)
{
  p.y += 2.9;
  p.y *= 1.1;p.z*=0.9;
  float b = sphere(abs(p)-vec3(1.,0,0.15),0.2-p.z*0.1);
  rY(p,p.x*0.2);
  p.z += 0.2;
  float bb = box(p,vec3(1.,0.1,0.1));
  return min(b,bb);
}

float bones(vec3 p){
    float t = 15.;
  for (int i=0;i<4;++i){
    float rago = rand(vec2(i,i*i))-0.5;
    rY(p,rago*5.);
    t = min(t, bone(p+vec3(rago*4.,0,rago*10.)));
   }
   return t;}

float world(vec3 p)
{
  float plan = p.y + 3. -rand(vec2(floor(p.x * 0.5),floor(p.z * 0.5))) * 0.08;
  float drago = min(drago(p-vec3(2,0,0)),drago(vec3(-p.x-3,p.y-1.5,p.z+2)));//-vec3(cos(time),sin(time),0)
  float c = cols(p);
  float b = bones(p);
  matID = 1;
  if (plan < drago) { drago=plan; matID=3; }
  if (c < drago) { drago=c; matID=4; }
  if (b < drago) { drago=b; matID=5; }
	return drago;
}

vec3 normal(vec3 p)
{
	return normalize( vec3( world(p + e.xyy) - world(p - e.xyy), 
											 	 world(p + e.yxy) - world(p - e.yxy),
											  world(p + e.yyx) - world(p - e.yyx) )); 
}

const float k = 0.5;
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

	vec3 lpos = vec3(3.,3.,-2);
	vec3 ldir;
	float ldst;
	const float lp = 45.;

	float i, dst = 0.1;
	float d, sdst = 0.;
	vec3 p = origin, color;
 int mat = 0;
 vec3 n;
 float ao;
 float l;
	for (i=0.;i<1.;i+=1./128.)
	{
		p+=ray*dst;
		dst = world(p);
		if (dst < e.z)
		{
			ldir = lpos - p;
			ldst = dot(ldir,ldir);
			ldir = normalize(ldir);
   mat = matID;
   n=normal(p);
   ao=ao(p,n);
   l=dot(n,ldir)*lp/ldst-0.05*exp(dst*0.05);
		break;
}}
if (mat== 0) color=vec3(0,0,0);
else if (mat==1) color=vec3(0.54,0.56,0.8)*ao+vec3(0.72,0.43,0.29)*sss(p,-ldir)*1.5;
else if (mat==4) color=vec3(0.98,0.92,0.92)*ao+vec3(0.62,0.23,0.09)*sss(p,-ldir)*2.;
else if (mat==5) color=vec3(0.9)*ao;
else if (mat==6) color=vec3(0.1,0.3,1.);
else color=vec3(0.8,0.7,0.7)*(ao*0.6)+mod(floor(p.x*0.5)-floor(p.z*0.5),2)*0.1;
gl_FragColor=vec4(color*l,1.);
}