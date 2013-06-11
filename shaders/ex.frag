uniform vec2 resolution;
uniform float time;

vec2 rs = resolution;

// color scheme: 
vec3 n0 = vec3(71, 48, 25) / 255.0;
vec3 n1 = vec3(249, 248, 212) / 255.0;
vec3 n2 = vec3(249, 171, 124) / 255.0;
vec3 n3 = vec3(63, 78, 65) / 255.0;
vec3 n4 = vec3(30, 36, 31) / 255.0;

// cam
vec3 cp; // camera position
mat3 cr; // camera rotation

float sph(vec3 p, float r) {
  return length(p) - r;
}

vec4 world(vec3 r) {
  return vec4(n3, sph(r + vec3(sin(time)*0.2,0,cos(time) + 2.5),0.2));
}

vec3 rm(vec2 tc) {
  vec3 rp = vec3(-0.9);
  rp.xy = tc;
  rp.x *= rs.x/rs.y; // aspect ratio
  rp.z = -0.9;
  vec3 rayDir = normalize(rp);
  float rayLength = 0.1;  
  vec3 ray = rayDir * rayLength + cp;
  float eps = 0.0005;
  int steps = 0;
  vec4 h;
  bool hit = false;
  for (int i=0; i<150; ++i) {
    steps = i;
    if (hit) break;
    
    h = world(ray);
    if (h.w < eps)
      hit = true;
    rayLength += h.w;
    ray = rayDir * rayLength + cp;
  }
  float glow_amount = float(steps)/150.0;
  
  vec3 color = n4;
  if (hit) {
    color = mix(n3, n0, glow_amount);
  }
  
  return color;
}


void main() {
  cp = vec3(0.,0.,-1.);
  gl_FragColor.xyz = rm(-1. + 2.0 * gl_FragCoord.xy / rs.xy);
}
