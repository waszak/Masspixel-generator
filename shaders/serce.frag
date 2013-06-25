uniform vec2 resolution;
uniform float time;

float segm( float a, float b, float c, float x )
{
    return smoothstep(a-c,a,x) - smoothstep(b,b+c,x);
}


vec3 heart( float x, float y )
{
    float s = mod( time, 2.0 )/2.0;
    s = 0.9 + 0.1*(1.0-exp(-5.0*s)*sin(50.0*s));
    x *= s;
    y *= s;
    float a = atan(x,y)/3.141593;
    float r = sqrt(x*x+y*y);

    float h = abs(a);
    float d = (13.0*h - 22.0*h*h + 10.0*h*h*h)/(6.0-5.0*h);

    float f = smoothstep(d-0.02,d,r);
    float g = pow(1.0-clamp(r/d,0.0,1.0),0.25);
    return mix(vec3(0.5+0.5*g,0.2,0.1),vec3(1.0),f);
}


void main(void)
{
    vec2 p = (-1.0+2.0*gl_FragCoord.xy/resolution.xy);

    vec3 col = heart(2.0*p.x, 2.0*p.y );
    gl_FragColor = vec4(col,1.0);

}