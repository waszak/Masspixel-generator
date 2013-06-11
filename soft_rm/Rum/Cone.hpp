#ifndef __OBJECT_CONE_HPP__
#define __OBJECT_CONE_HPP__
//c normalized
float sdCone( vec3 p, vec2 c )
{
    // c must be normalized
    float q = length(p.xy);
    return dot(c,vec2(q,p.z));
}

#endif //__OBJECT_CONE_HPP__
