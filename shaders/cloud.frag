uniform vec2 resolution;
uniform float time;
uniform vec3 mouse;

// noise
float hash(float p) { return fract(sin(p)*435678.5435); }

float noise(vec3 x) {
  vec3 p = floor(x);
  vec3 f = fract(x);
  
  f = f*f*(3.-2.*f);
  float n = p.x + p.y*57. + 113.*p.z;
  float res = mix(mix(mix( hash(n+  0.0), hash(n+  1.0),f.x),
                        mix( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y),
                    mix(mix( hash(n+113.0), hash(n+114.0),f.x),
                        mix( hash(n+170.0), hash(n+171.0),f.x),f.y),f.z);

  return res;
}
  
float noise(vec2 x) {
 return noise(vec3(x.x, x.y, 0.)); 
}

float fbm(vec3 p) {
 float f = 0.5 * noise(p); p = p * 2.;
 f += 0.25 * noise(p);     p = p * 2.;
 f += 0.125 * noise(p);    p = p * 2.;
 f += 0.0625 * noise(p);
 return f;
 
}

float _NoiseFreq = 2.;
float _NoiseAnim = 4.5;
float _NoiseAmp = 1.3;

float pyro(vec3 p) {
 float sph = length(p) - 2.2;
  return sph += fbm(p*_NoiseFreq + _NoiseAnim * time) * _NoiseAmp;
}

// color gradient 
// this should be in a 1D texture really
vec4 gradient(float x)
{
	// no constant array initializers allowed in GLES SL!
	const vec4 c0 = vec4(1,1,1,1);//vec4(2, 2, 1, 1);	// yellow
	const vec4 c1 = vec4(0.3,0.3,0.31,1);//vec4(1, 0.5, 0, 1);	// orange
	const vec4 c2 = vec4(0.6, 0.6, 0.6, 0.1); 	// black
	const vec4 c3 = vec4(1,1,1,0.4);//vec4(0.8, 0.1, 0., 0.5); 	// red 
 float gs = pow(fbm(vec3(x,x,x)),2.2);
	const vec4 c4 = vec4(0, 0, 0, 1.); 	// black
	
	x = clamp(x, 0., 0.999);
	float t = fract(x*4.0);
	vec4 c;
	if (x < 0.25) {
		c =  mix(c0, c1, t);
	} else if (x < 0.5) {
		c = mix(c1, c2, t);
	} else if (x < 0.75) {
		c = mix(c2, c3, t);
	} else {
		c = mix(c3, c4, t);		
	}
	//return vec4(x);
	//return vec4(t);
	return c;
}

vec4 volume(vec3 p) {
   float d = pyro(p);
   return gradient(d);
}

const float density = 0.3;

vec4 rm(vec3 rayOrigin, vec3 rayStep, out vec3 pos)
{
   vec4 sum = vec4(0.);
   pos = rayOrigin;
   
  for (int i=0; i < 164; ++i) {
    vec4 col = volume(pos);
    col.a *= density;
    
  col.rgb *= col.a;
  sum += col*(1.-sum.a);
  if (sum.a > 0.9)
    break;
    pos += rayStep;
  }
  
  return sum;
}

void main() {
      vec2 q = gl_FragCoord.xy / resolution.xy;
    vec2 p = -1.0 + 2.0 * q;
    p.x *= resolution.x/resolution.y;
	
    float rotx = time * 0.01 ;//mouse.y*4.0;
    float roty = -time * 0.01;//- mouse.x*4.0;

    float zoom = 0.3 + smoothstep(-1.,1., sin(time*0.2))*5.;

    // camera
    vec3 ro = zoom*normalize(vec3(cos(roty), cos(rotx), sin(roty)));
    vec3 ww = normalize(vec3(0.0,0.0,0.0) - ro);
    vec3 uu = normalize(cross( vec3(0.0,1.0,0.0), ww ));
    vec3 vv = normalize(cross(ww,uu));
    vec3 rd = normalize( p.x*uu + p.y*vv + 1.5*ww );

    ro += rd*2.0;
	
    // volume render
    vec3 hitPos;
    vec4 col = rm(ro, rd*0.05, hitPos);
    //vec4 col = gradient(p.x);
	    
    gl_FragColor = col;
  //vec2 tc = 2.*vec2(gl_FragCoord.xy / resolution.xy)-1.;

  //vec3 color = vec3(fbm(vec3(tc*6.,1.) + time));
  //gl_FragColor = gradient(color.x);//vec4(color, 1.);
}