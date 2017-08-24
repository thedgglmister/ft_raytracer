#include "rtv1.h"
//refl_coef shoudl apply to bot h refl_light and diffuse lgiht...?
t_rgb	ft_combine_light(t_hit *hit, t_rgb refl_light, t_rgb refr_light, t_rgb hit_light)
{



	t_rgb combined;
	double r0;
	double refl_pcnt;
	double theta;

	r0 = (hit->n1 - hit->obj.n2) / (hit->n1 + hit->obj.n2);
	r0 = r0 * r0;
	theta = ft_vector_angle(hit->ray.d, ft_vec_scale(hit->normal, -1));
	refl_pcnt = r0 + (1 - r0) * pow(1 - cos(theta), 5);

	combined.r = (hit_light.r + hit->obj.k_refl * refl_light.r) * refl_pcnt +
				hit->obj.k_refr * (1 - refl_pcnt) * refr_light.r;
	combined.g = (hit_light.g + hit->obj.k_refl * refl_light.g) * refl_pcnt +
				hit->obj.k_refr * (1 - refl_pcnt) * refr_light.g;
	combined.b = (hit_light.b + hit->obj.k_refl * refl_light.b) * refl_pcnt +
				hit->obj.k_refr * (1 - refl_pcnt) * refr_light.b;


	return (combined);

}

