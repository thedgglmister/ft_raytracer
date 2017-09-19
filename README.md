# ft_raytracer
The 4th and 5th projects of the 42 Silicon Valley graphics branch

### --Project Description--

ft_raytracer is a 3D graphics renderer implementing a ray tracer algorithm. It currently supports phong lighting, parallel and point light sources, interactive shadows, recursive reflections and refractions, and adaptive super sampling. Supported objects include planes, spheres, cones, cylinders, and parabaloids, which can all be rotated and positioned using intrinsic angles and can be made finite or concave by bounding with planes.

#### --Ray Tracing--
The basic ray tracing model is as follows. A camera is placed in the world and rays are cast from the camera's position to points on an imaginary image plane. Each ray performs an intersection test with all objects in the scene to determine the closest intersection. From each intersection in the scene, additional rays are recursively cast in the directions of light sources and in the reflection/refraction directions. The final color of a pixel is calculated based on information gathered as these rays bounce around the scene.

##### --Diffuse Lighting--

Diffuse lighting is determined by computing the intensity of the light at a point on the sphere. If the angle is close to the normal at that point then the intensity will be increased. The intensity determines how much of the object's color to contribute.

<img src="/images/diffuse.png" width="400">

##### --Shadows--

Shadows are incorporated into lighting. To determine if a light source should contribute to the lighting at an intersection point a shadow ray is cast from the intersection point to the light source. If there is an intersection before the light source then this point is in the shadow of that light source.

<img src="/images/shadow.png" width="400">

##### --Specular Lighting--

Specular lighting is calculated by computing a reflection ray by reflecting the light vector about the normal at the intersection point. The view ray is compared to the reflection ray to determine how much specular lighting to contribute. The more parallel the vectors are the more specular lighting will be added.

<img src="/images/specular.png" width="400">

##### --Reflections--

Reflections are performed by casting rays originating from the intersection point directed along the reflection vector. A portion of the reflected ray's color will be contributed to the original intersection point based on how reflective the surface is. There is an arbitrary limit on how many reflections a ray can perform before stopping to improve performance and eliminate potential infinite loops.

<img src="/images/reflection.png" width="400">

##### --Refractions--

Refractions occur when rays intersect translucent objects. The light at the intersection point is determined by blending the reflected and refracted light at that point. A reflective ray is cast in the same way as described in the previous section. The refractive ray is calculated by bending the original ray based on the angle of incidence and the indices of refraction of the two materials. The amount of reflective and refractive light at the point is determined by the Fresnel equation.

<img src="/images/refraction.png" width="400">

##### --Final Renders--

<img src="/images/refraction_scene.png" width="800">
<img src="/images/reflection_scene.png" width="800">
<img src="/images/all_shapes_scene.png" width="800">

#### --Coding Style--

At 42, we follow a strict norm in order to teach us to follow style guides. This norm also prevents us from using many built-in functions. In this project, we are limited to using a barebones graphic library called minilibx. This library limits the functionality to creating windows and coloring specific pixels.

The allowed functions are : ```exit, open, close, read, malloc, free, and the functions of minilibx and math.h```.

The Project is written in C and in accordance with "The Norm".

#### --The Norm--

    • Functions must not exceed 25 lines
    • No more than 5 function-definitions in a .c file
    • One instruction per line
    • One single variable declaration per line; cannot stick declaration and initialisation on the same line
    • No more than 5 variables per block
    • No more than 4 parameters per function
    • Forbidden keywords are: [for] [do ... while] [switch] [case] [goto]
