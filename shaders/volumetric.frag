uniform vec2 resolution;
uniform float time;

vec3 origin = vec3(0,0,-3.);//vec3(cos(time * 0.5) * 0.5,1.5 + sin(time),-12.5 + sin(time * 0.25));

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

///modified hsv (original idea unc)
vec3 hsv(float h,float s,float v) {
	return mix(vec3(1.),clamp((abs(fract(h+vec3(3.,2.,1.)/3.)*6.-3.)-1.),0.,1.),s)*v;
}

float rand(vec2 coordinate) {
    return fract(sin(dot(coordinate.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

// By Decipher http://www.pouet.net/user.php?who=16216
/* Given a position, this function generates a 3D co-ordinates based,
 * reconstructible static noise. */
float noise(vec3 position)
{
	position.x += position.y * 57. + position.z * 21.;
	return sin(cos(position.x) * position.x);

	/* The following is an alternative for the previous line:
	 * return fract(position.x * position.x * .0013) * 2. - 1.; */
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

int material;

float f(vec3 p)
{
	float a = sphere(p - vec3(0.,0.,2.), 1.);
	return a;
}


vec3 probe(vec3 p)
{
	
	return vec3(perlin(p * 100. + time * 40.) * 0.1);
	
}


vec3 rm(vec3 ray)
{
	vec3 pos;
	float distance = 0.4 * sin(rand(vec2(ray.x + time, ray.y + time)));
	vec3 color = vec3(0.);

	float step = 0.;
	for (step = 0.; step < 64.; step += 1.)
	{
		pos = origin + ray * distance;
		if (f(pos) < 0.005)		
			color += probe(pos);
		
				distance += 0.1;
	}

	return color + vec3(0.43, 0.123, 0.5);
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