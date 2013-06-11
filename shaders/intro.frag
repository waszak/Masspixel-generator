uniform sampler2D texture0;
uniform vec2 resolution;
uniform float time;

float tim = time;

vec2 rs = resolution;


vec3 lpos = vec3(0.,-4.,-20);


// todo; wyjebac niepotrzebne, dodac nowe
// color scheme: 
vec3 n0 = vec3(71, 48, 25) / 255.0;
vec3 n1 = vec3(249, 248, 212) / 255.0;
vec3 n2 = vec3(249, 171, 124) / 255.0;
vec3 n3 = vec3(63, 78, 65) / 255.0;
vec3 n4 = vec3(30, 36, 31) / 255.0;
vec3 n5 = vec3(154, 94, 110) / 255.0;
vec3 n6 = vec3(0.68,0.82,0.92);
vec3 n7 = vec3(0.62,0.23,0.09);

int scene = 1;

float rand(vec2 coordinate) {
    return fract(sin(dot(coordinate.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

// By Decipher http://www.pouet.net/user.php?who=16216
/* Given a position, this function generates a 2D co-ordinates based,
 * reconstructible static noise. */
float noise(vec3 position) {
	return rand(position.xz);
}

/* Given a position, this function generates a 3D co-ordinates based,
 * reconstructible linearly interpolated smooth noise. */
float smooth_noise(vec3 position)
{
	vec3 integer = floor(position);
	vec3 fractional = position - integer;

	return mix(mix(mix(noise(integer),
			   noise(integer + vec3(1, 0, 0)),
			   fractional.x),
		       mix(noise(integer + vec3(0, 1, 0)),
			   noise(integer + vec3(1, 1, 0)),
			   fractional.x),
		       fractional.y),
		   mix(mix(noise(integer + vec3(0, 0, 1)),
			   noise(integer + vec3(1, 0, 1)),
			   fractional.x),
		       mix(noise(integer + vec3(0, 1, 1)),
			   noise(integer + 1.), fractional.x),
		       fractional.y),
		   fractional.z) * .5 + .5;
}

/* Given a position, this function constructs the oh-so-famous Perlin
 * noise. */
float perlin(vec3 position) {
	return smooth_noise(position * .06125) * .5 +
	       smooth_noise(position * .125) * .25 +
	       smooth_noise(position * .25) * .125;
}

// cam
vec3 cp; // camera position
mat3 cr; // camera rotation

float sph(vec3 p, float r) {
  return length(p) - r;
}


vec2 join(vec2 a, vec2 b) {
  if (a.x < b.x) return a;
  return b;
}

float box( vec3 p, vec3 b ) {
  vec3 d = abs(p) - b;
  return min(max(d.x,max(d.y,d.z)),0.0) +
         length(max(d,0.0));
}

float cylinder( vec3 p, vec3 c ){
  return length(p.xz-c.xy)-c.z;
}

float torus( vec3 p, vec2 t ){
  vec2 q = vec2(length(p.xz)-t.x,p.y);
  return length(q)-t.y;
}

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

vec2 cube(vec3 r) {
  r += vec3(0, -30., 40.);
  vec3 rr = r;
  rX(rr, tim);
  rY(rr, tim);
  rZ(rr, tim);
  float boxSize = tim > 20. ? (tim - 20.) * 5. : (abs(sin(tim * 3.141592)) + .5);
  float d = box(rr, vec3(boxSize));
  float mt = mod(tim, 1.);
  float angle = atan(r.z, r.x);
  //r += noise(r) * .1;
  for (float i = 0.; i < 8.; ++i) {
    float radius = (i + mt) * 2.;
    d = min(d, torus(r + vec3(0., sin(angle * 4. + radius), 0.), vec2(radius, .5 / (1. + radius))));
  }
    
  return vec2(d, 1);
}

// todo: mozna jeszcze zmniejszyc:
vec2 tower(vec3 ro, vec3 r) {
  float ang = ro.y * 0.2;
  rY(ro, ang);
  float s = smoothstep(5,0,r.y); // overall shape of tower
  float m = box(ro, vec3(2.+s,25.,2.+s)); // exter
  float m2 = box(ro, vec3(s+1.3,25.,s+1.3)); // inter
  m = min(m, box(ro, vec3(2.)));
  float bb = max(-sph(ro,4.8),box(mod(r,2.)-vec3(1.),vec3(0.8)));
  m = min(m2,max(m,bb)); // cegly
  //top:
  rY(ro,-ang);
  float t = max(-box(mod(r,vec3(5))-vec3(2.5),vec3(1.8)),max(sph(r+vec3(0,-25,40),2.8),-box(r+vec3(0,-26,40),vec3(2.))));
  m = min(min(m,box(ro,vec3(1.,0.,1000.))),t); 
  //m = min(torus(ro, vec2(2.,1.)),m);
  float m3 = torus(ro+vec3(0,sin(tim)-3.,0),vec2(sin(tim*2.)+4.,0.2));
  return join(vec2(m,3),vec2(m3,1));
}

vec2 scene2(vec3 r) {
  vec2 terrain = vec2(r.y + perlin(r*20.+tim*5.) * 2. + perlin(r*2.+tim*4.5) * 5.-3.+sin(tim), 1.);
  
  	//float plan = box(r - vec3(0,-4,0),vec3(210,0.1,100)) - rand(vec2(floor(r.x * 0.5) + tim * 0.00002,floor(r.z * 0.5))) *0.35;
  vec2 t = tower(r+vec3(0,0,40.),r);
  vec2 c = cube(r);
  return join(terrain, join(t, c));  
}

vec2 scene1(vec3 p){
  //rY(p, tim);
  //float h1 = drago(p-vec3(2,0,0));
  //float h2 = drago(vec3(-p.x-3,p.y-1.5,p.z+2)); //-vec3(cos(tim),sin(tim),0)
  //float h3 = drago(vec3(-p.x-3,-p.y-1.5,p.z+2));
  float freq = 2.;
  float efftim = .2;// * tim;
  float i_delay = 1.;
  float plan = box(p - vec3(0,-4,0),vec3(210,0.1,100)) - (rand(vec2(floor(p.x * 0.5) + tim * 0.00002,floor(p.z * 0.5))) *0.35) * (efftim - clamp(abs(sin(tim * freq + 3.14159)), 0., efftim)) / efftim;

  vec3 p2 = p + vec3(0., tim * tim - 300., 0.);
  rX(p2, tim * .1);
  rY(p2, tim * .1);
  rZ(p2, tim * .1);
  float b2 = box(p2, vec3(20.));
  
  p -= 5. * vec3(0., abs(sin(tim * freq)) - .6, 0.);
  rX(p, tim * 3.);
  rY(p, tim * 3.);
  rZ(p, tim * 3.);
  float b = box(p, vec3(1.));
  //float plan = p.y + 3.+sin(p.x)*0.1 - rand(vec2(floor(p.x * 0.5),floor(p.z * 0.5))) * 0.08;

  return vec2(min(b2, min(b, plan)), 1);//min(cols(p),min(plan,min(h1,min(h2,h3))));
}


// columns
float cols(vec3 r) {
	 r.xz = mod(r.xz,10.) - vec2(4);
	 rY(r,r.y * 3.);
  rX(r,min(r.y,1.5) * 0.05);
  return min(cyl(r,0.5,10.),cyl(r-vec3(0.,-4.,0.),1.5,2.));
}

float impulse(float k, float x){float h = k*x;return h*exp(1.0-h);}
float skin(vec3 p){return rand(floor(p.zy*15.)) *0.03;}
float head(vec3 p){
  rY(p,-0.45); rZ(p,0.25);
  p += vec3(2,-0.25,2.5);
  float top = box(p, vec3(0.3+impulse(0.4,p.z) * 0.15,clamp(0.2+ impulse(0.5,p.z) * 0.05,0.05,0.6),1.));
  float jaw = box(p-vec3(0,-0.4,0), vec3(0.3 + impulse(0.4,p.z) * 0.15,0.08+p.z*0.1,1.));
  p.x = abs(p.x);
  float ok  = sph(p-vec3(0.4,0.,0.5),0.1);
  return min(min(top,jaw)+skin(p)*0.8,ok);
}

float drago(vec3 p, float move)
{
  p.x += move;
  float h=head(p);
  float t=p.z;
  p -=vec3(0,0,4);
  rZ(p,p.z*0.3);
  rX(p,1.1);
  float neck=cyl(p,0.3,5.);
  return min(h,neck+skin(p));
}

vec2 scene3(vec3 r) {
  rY(r,sin(tim*0.9) * 0.06);
  vec2 drag = vec2(drago(r-vec3(cos(tim), sin(tim),-27 + cos(tim)),sin(tim*5+r.z*0.8)),7);
  r.x =-r.x;
  vec2 drag2 = vec2(drago(r-vec3(cos(tim),-1.+sin(tim),-28),sin(tim*2+r.z*0.9+2.)),7);
  drag = join(drag,drag2);
  r.z -= tim;
  float terrain = r.y + 3.5 -rand(vec2(floor(r.x * 0.5),floor(r.z * 0.5))) * 0.5;
  float tc = -r.y+9. -rand(vec2(floor(r.x * 0.5),floor(r.z * 0.5))) *0.4;
  vec2 light = vec2(sph(r-lpos+vec3(0,-1,0),0.09),6);
  
  return join(join(light, drag),join(vec2(min(terrain,tc),4),vec2(cols(r), 5)));
}

// Distance Equation world function
vec2 de(vec3 r) {
  if (scene == 1) return scene1(r);
  if (scene == 2) return scene2(r);
  if (scene == 3) return scene3(r);
}

float ao(vec3 n) {
  float a = 1.;
  for (float i = 0.; i < 5.; ++i)
    a -= de(n * i * 0.1).x / pow(2.,i);
  return a;
}

// Gradient [normal vector]
vec3 g(vec3 p) {
	vec2 e = vec2(0.01, 0.0);
	return (vec3(de(p+e.xyy).x,de(p+e.yxy).x,de(p+e.yyx).x)-de(p).x)/e.x;
}


// Ambient Occlusion
const float k = 0.8;
float ao3(vec3 p, vec3 q) {
	float c = 1.;
	for (float i = 0.; i < 5.; ++i)
		c -= (i * k - de(p + q * i * k + 0.01).x) / pow(2., i);
	return clamp(c,0.,1.);
}

float sss(vec3 p, vec3 q) {	return ao3(p, q); }

vec3 rm(vec2 tc) {
  vec3 rp = vec3(-0.9);
  rp.xy = tc;
  rp.x *= rs.x/rs.y; // aspect ratio
  rp.z = -1.;
  vec3 rayDir = normalize(rp);
  float rayLength = 0.1;
  
  if (scene == 1) {
    cp = vec3(0., 0., 15.);// * vec3(cos(tim), 0., sin(tim));
  }
  else if (scene == 2)
    cp = vec3(0.,min(mix(1., tim * tim * .2, smoothstep(0,16,tim)), 25),max(-28., mix(10., 2-tim*200, smoothstep(0,88,tim)) ) ); //kamera - scena 2
  else if (scene == 3) {
    cp = vec3(0.,25,max(-28., mix(10., 2-tim*200, smoothstep(0,88,tim)) ) );
    cp = vec3(0.,4, -17 );
  }
    
  vec3 ray = rayDir * rayLength + cp;
  float eps = 0.0005;
  int steps = 0;
  vec2 h;
  bool hit = false;
  
/// raymarching b1tch:

  for (int i=0; i<64; ++i) {
    steps = i;
    
    if (hit) break;

    h = de(ray);
    
    if (h.x < eps)
      hit = true;

    rayLength += h.x;
    ray = rayDir * rayLength + cp;
  }
  
/// materials and other sh1t
  
  float glow_amount = smoothstep(0., 1., clamp(float(steps)/55.0,0.,1.));
  vec3 color = mix(n3, n4, length(tc.y * 1.1)); // bkg color
  
  if (hit) {
    
    if (h.y == 1.) {
      color = mix(color, mix(n4 + ao(g(ray)) * 0.05, n1, glow_amount), exp(-rayLength*0.09));
    }
    else if(h.y == 3) {
      color = mix(color, mix(n5 - ao(g(ray))*0.5, n5, glow_amount), exp(-rayLength*0.09));
    }
    else if (h.y == 2.) {
      vec3 n = g(ray);
      color = n0 * n1 * dot(n, normalize(vec3(1.,1.,2.)));
    }
    else if (h.y == 6) {
        color = n1;
    }
    else {
      vec3 bkg = color;
      float a = ao3(ray,g(ray));
      vec3 n = g(ray);
      vec3 ldir = lpos - ray;
      float ldst = dot(ldir,ldir);
      ldir = normalize(ldir); 
      float l=dot(n,ldir)*10./ldst + 0.2;
      
      if (h.y == 4) {
        color = a * 0.4 * n1 ;// mod(floor(ray.x*0.5)-floor(ray.z*0.5),3);
      }
      else if (h.y == 5) {
        color = n6*a*0.5+n7*sss(ray,-ldir)*5.;
      }
      else {
        color = n7*a*l+n4*sss(ray,-ldir)*2.;//vec3(1.,1.,0.);
      }
      
      color = mix(bkg, color, exp(-rayLength*0.09));
    }
  }
  
  return color;//mix(bkg, color, exp(-rayLength*0.09));//color * (tim - length(tc) + 0.005);
}


void main() {
  if (tim < 17.5)
    scene = 1;
  else if (tim < 40.) {
    scene = 2;
    tim -= 17.5;
  }
  else
    scene = 3;
    
  gl_FragColor.xyz = rm(-1. + 2.0 * gl_FragCoord.xy / rs.xy) ;
}