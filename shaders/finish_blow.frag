#ifdef GL_ES
precision mediump float;
#endif
uniform float time;
uniform vec2 resolution;

float tim = time;
//dupa
vec2 rs = resolution;//vec2(1280,786);
float sintime = sin(tim), costime = cos(tim);

vec3 lpos = vec3(0.,-4.,-23.);

vec3 cp;
vec3 cubeSize;

vec3 n1 = vec3(1.,1.,0.8);
vec3 n4 = vec3(0.1,0.1,0.1);
vec3 n5 = vec3(0.6,0.4,0.4);
vec3 n7 = vec3(0.6,0.2,0.09);

int scene;

float rand(vec3 r) {
    return fract(sin(dot(r.xz, vec2(12.9898, 78.233))) * 43758.5453);
}

float rand(vec2 r) {
    return rand(vec3(r,r.y));
}

float smooth_noise(vec3 position) {
  vec3 integer = floor(position);
  vec3 fractional = position - integer;

  return mix(mix(mix(rand(integer),
         rand(integer + vec3(1, 0, 0)),
         fractional.x),
           mix(rand(integer + vec3(0, 1, 0)),
         rand(integer + vec3(1, 1, 0)),
         fractional.x),
           fractional.y),
       mix(mix(rand(integer + vec3(0, 0, 1)),
         rand(integer + vec3(1, 0, 1)),
         fractional.x),
           mix(rand(integer + vec3(0, 1, 1)),
         rand(integer + 1.), fractional.x),
           fractional.y),
       fractional.z) * .5 + .5;
}

float perlin(vec3 position) {
  return smooth_noise(position * .06125) * .5 +
         smooth_noise(position * .125) * .25 +
         smooth_noise(position * .25) * .125;
}

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

vec2 scene3(vec3 r) {
  vec3 rr = r;
  rX(rr, tim);
  rY(rr, tim);
  rZ(rr, tim);
  float d = box(rr, cubeSize);
  float at = atan(r.z, r.x) * 5.;
  for (float i = 1.; i < 5.; ++i) {
    float radius = (i + mod(tim, 1.)) * 4.;
    d = min(d,torus(r + vec3(0.,sin(at + radius), 0.),vec2(radius,.85/(1. + radius))));
  }
  return vec2(d,2.);
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

float drago(vec3 r, float move) {
  r.x += move;
  float h=head(r);
  float t=r.z;
  r-=vec3(0,0,3.8);
  rZ(r,r.z*0.3);
  rX(r,1.1);
  float neck=cyl(r,0.3,5.);
  return min(h,neck+skin(r));
}

vec2 tower(vec3 ro, vec3 r) {
  ro.x *= min(1,smoothstep(-8.,4.,ro.y));
  float c = max(-box(rep(ro,vec3(3.1)),vec3(1.5)),cyl(ro,2.3,135.));
  ro.x += (mod(floor(ro.y*4),2.))*0.5;
  rY(ro, ro.y * 0.3);
  float c2 = max(-box(rep(ro,vec3(3.1)),vec3(1.5)),cyl(r,3.,135.));
  return vec2(min(c,c2),4);
}

vec2 scene2(vec3 r) {
  rY(r,sin(tim*0.9) * 0.06);
  vec2 drag = vec2(drago(r-vec3(costime,sintime,-27. + cos(tim)),sin(tim*5.+r.z*0.8)),7);
  r.x =-r.x;
  vec2 drag2 = vec2(drago(r-vec3(costime,-1.+sintime,-28),sin(tim*2.+r.z*0.9+2.)),7);
  r.z -= tim;
  float terrain = min(r.y+4.,-r.y+14.) + rand(vec2(floor(r.x),floor(r.z*0.5)));
  r += vec3(0.,-25.,5.);
  r = rep(r,vec3(25.,50.,15.)); rZ(r,sign(r.x)*0.5); r.y=abs(r.y)-4.;
  return join(join(drag,drag2),join(vec2(terrain,1.), vec2(tower(r,r).x,5.)));
}

vec2 scene1(vec3 r) { 
  vec2 terrain = vec2(r.y + perlin(r*20.+time*5.) * 2. + perlin(r*2.+time*4.5)*5., 1.); 
  float plan = box(r - vec3(0,-4,0),vec3(210,0.1,100)) - rand(vec2(floor(r.x*0.5) + tim * 0.04,floor(r.z * 0.5))) *0.35;
  terrain.x = mix(plan, terrain.x, smoothstep(0.,7.,tim));
  return join(terrain,tower(r,r));
}


vec2 de(vec3 r) {
  if (scene == 1) return scene1(r);
  if (scene == 2) return scene2(r);
  return scene3(r);
}

float ao(vec3 n) {
  float a = 1.;
  for (float i = 0.; i < 5.; ++i)
    a -= de(n * i * 0.1).x / pow(2.,i);
  return a;
}

// Gradient [normal vector]
vec3 g(vec3 r) {
  vec2 e = vec2(0.01, 0.0);
  return (vec3(de(r+e.xyy).x,de(r+e.yxy).x,de(r+e.yyx).x)-de(r).x)/e.x;
} 


// Ambient Occlusion
float ao3(vec3 r, vec3 q) {
  float c = 1.;
  for (float i = 0.; i < 5.; ++i)
    c -= (i * 0.9 - de(r + q * i * 0.9 + 0.01).x) / pow(2., i);
  return clamp(c,0.,1.);
}
 
vec3 rm(vec2 tc) {
  vec3 rp = vec3(-0.9);
  rp.xy = tc;
  rp.x *= rs.x/rs.y;
  rp.z = -1.;
  vec3 rayDir = normalize(rp);
  float rayLength = 0.1;

  vec3 color = mix(vec3(0.2,0.3,0.3), n4, length(tc.y * 1.1));

  cp = vec3(5,5,20);
  if (scene == 1) {
    if (tim < 5.)
      cp = vec3(0,0,60);
    if (tim < 35.) {
      float t = tim -8;
      cp = vec3(4.-sintime*5.,min(mix(1., t * t * 0.6, smoothstep(0.,40.,t)), 135.),max(15., mix(70., 2.-t*160., smoothstep(0.,20.,t)) ) );
    }
  } 
  if (scene == 2)
    cp = vec3(0.,4., -17. );
  if (scene == 3) {
    cp = vec3(costime*10.,sin(tim * 5.2),6.+sintime*10.);
    cubeSize = vec3((abs(sin(tim*4.))*2.+1.));
  }    
  vec3 ray = rayDir * rayLength + cp;
  int steps = 0;
  vec2 h;
  bool hit = false;

  for (int i=0; i<64; ++i) {
    steps = i;
    h = de(ray);
    if (h.x < 0.01) {
      hit = true;
      break;
    }
    rayLength += max(h.x,0.01);
    ray = rayDir * rayLength + cp;
  }

  if (hit) {
    float glow_amount = smoothstep(0., 1., clamp(float(steps)/55.0,0.,1.));
    if (h.y == 1.) color = mix(color, mix(n4 + ao(g(ray)) * 0.05, n1, glow_amount), exp(-rayLength*0.09));
    else {
      vec3 bkg = color;
      float a = ao3(ray,g(ray));
      vec3 ldir = lpos - ray;
      float ldst = dot(ldir,ldir);
      ldir = normalize(ldir); 
      if (h.y == 4.) color = a * 0.4 * n1;
      if (h.y == 5.) color = vec3(0.7,0.8,0.9)*a*0.5+n7*ao3(ray,-ldir)*4.;
      else           color = n7*a*(dot(g(ray),ldir)*10./ldst + 0.2)+n4*ao3(ray,-ldir)*2.;   
      color = mix(bkg, color, exp(-rayLength*0.09));
    }
  }
  return color;
}

vec3 gamma(vec3 r) {
  return vec3(pow(r.x,2.2),pow(r.y,2.2),pow(r.z,2.2));
}

void main() {
  vec2 p=-1.+2.0*gl_FragCoord.xy/rs;  
  scene = 1;
  float m = mod(tim, 1.) < .5 ? 5. : -1.;
  if (tim > 5. && mod(tim,2.)>1.4) scene = 3; 
  if (tim > 18. && tim < 34.){
    scene = 3;
    tim-=m;
  }
  if (tim > 20.)
    scene = 1;
  if (tim > 33.) {
     scene = 2;
     if (tim>50. && mod(tim,1.)<0.3) scene = 1;
    tim-=m;
  }
  gl_FragColor.xyz=abs(p.y) > 0.8? n4 : gamma(rm(p)*3.)*(1.-length(p*0.2))-smoothstep(57.,58.,tim);
}
