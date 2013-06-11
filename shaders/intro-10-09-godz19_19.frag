uniform vec2 resolution;
uniform float time;

vec2 rs = resolution;

// color scheme: 
vec3 n0 = vec3(71, 48, 25) / 255.0;
vec3 n1 = vec3(249, 248, 212) / 255.0;
vec3 n2 = vec3(249, 171, 124) / 255.0;
vec3 n3 = vec3(63, 78, 65) / 255.0;
vec3 n4 = vec3(30, 36, 31) / 255.0;


float rand(vec2 coordinate) {
    return fract(sin(dot(coordinate.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

// By Decipher http://www.pouet.net/user.php?who=16216
/* Given a position, this function generates a 3D co-ordinates based,
 * reconstructible static noise. */
float noise(vec3 position) {
	//position.x += position.y * 57. + position.z * 21.;
	//return sin(cos(position.x) * position.x);
	/* The following is an alternative for the previous line:*/
	return rand(position.xz);//fract(position.x * position.x * .0013) * 2. - 1.; 
}

/* Given a position, this function generates a 3D co-ordinates based,
 * reconstructible linearly interpolated smooth noise.
 *
 * This function uses the noise() function above for its underlying
 * noise texture. */
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
float perlin(vec3 position)
{
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

float max(vec3 p) {
  return max(p.x,max(p.y, p.z));
}



float box( vec3 p, vec3 b )
{
  vec3 d = abs(p) - b;
  return min(max(d.x,max(d.y,d.z)),0.0) +
         length(max(d,0.0));
}


vec4 world(vec3 r) {
  float fl = r.y + perlin(r*20) * 2.0 + perlin(r*2) * 5;
  float b = 100000000;
  for (int i = 0; i < 8; ++i)
     b = min(b, rand(vec2(i,time)) + box(r + vec3(i * cos(time * i),i * sin(time * i),10 + cos(2 * i * 3.14) * 5.),vec3(1)));
  if (fl < b) return vec4(n4,fl);
  else return vec4(vec3(0.),b);
}

float ao(vec3 r) {
  float a = 1.;
  for (int i = 0; i < 5; ++i)
    a -= world(r * i * 0.1).w / pow(2.,i);
  return a;
}

vec3 rm(vec2 tc) {
  vec3 rp = vec3(-0.9);
  rp.xy = tc;
  rp.x *= rs.x/rs.y; // aspect ratio
  rp.z = -1.;
  vec3 rayDir = normalize(rp);
  float rayLength = 0.1;  
  vec3 ray = rayDir * rayLength + cp;
  float eps = 0.0005;
  int steps = 0;
  vec4 h;
  bool hit = false;
  for (int i=0; i<150; ++i) {
    steps = i;
    if (hit) {
      steps--;
      break;
    }
    
    h = world(ray);
    if (h.w < eps)
      hit = true;
    rayLength += h.w;
    ray = rayDir * rayLength + cp;
  }
  
  float glow_amount = smoothstep(0, 1, clamp(float(steps)/55.0,0,1));
  
 vec3 bkg = mix(n3, n4, length(tc.y * 1.1));
  vec3 color = bkg;
  if (hit) {
    color = mix(h.xyz, n1, glow_amount) * 0.6;
  }
  
  return mix(bkg, color, exp(-rayLength*0.09));//color * (time - length(tc) + 0.005);
}


void main() {
  cp = vec3(0.,0.,-1.);
  gl_FragColor.xyz = rm(-1. + 2.0 * gl_FragCoord.xy / rs.xy) ;
}
