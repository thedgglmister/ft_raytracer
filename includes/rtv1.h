/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:50:41 by biremong          #+#    #+#             */
/*   Updated: 2017/08/21 18:45:31 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H

# define RTV1_H

# include <stdio.h> ////////
# include <math.h>
# include "mlx.h"
# include "libft.h"

# define WIN_W   1000
# define WIN_H   700
# define SS_CNT  1 //needs to be a sqr
# define MAX_RECURSE 10
# define AIR_N1  1.00029

# define TO_RAD(x) (x * M_PI / 180)

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
	int			w;
}				t_vec;

typedef struct	s_rgb
{
	double		r;
	double		g;
	double		b;
}				t_rgb;

typedef struct	s_ray
{
	t_vec		o;
	t_vec		d;
}				t_ray;

typedef double	**t_mat;

typedef struct	s_camera
{
	t_ray		ray;
	double		plane_dist;
	double		fov;
	t_vec		translation;
	t_vec		target;
	double		roll;
	t_mat		transform;
}				t_camera;

typedef struct	s_window
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_str;
	int			bits_per_pix;
	int			bytes_per_row;
	int			endian;
}				t_window;

typedef struct	s_obj
{
	char		*type;
	t_vec		translation;
	double		scalar;
	double		x_rads;
	double		y_rads;
	double		z_rads;
	double		min_lim[3];
	double		max_lim[3];
	t_rgb		diffusion;
	t_mat		transform;
	t_mat		inv_transform;
	double		phong_exp; //limit this, cant be too small. neg? less than 1? uhh
	double		gloss;
	double		k_refl; //link phong_exp to this?
	double		k_refr;
	double		n2;
}				t_obj;

typedef struct	s_light
{
	char		*type;
	t_vec		pos;
	t_vec		dir;
	t_rgb		emission;
}				t_light;

typedef struct	s_scene
{
	int			light_cnt;
	t_light		*lights;
	t_rgb		amb_emission;
	int			obj_cnt;
	t_obj		*objs;
}				t_scene;

typedef struct	s_hit
{
	double		t;
	t_obj		obj;
	t_ray		ray;//incoming ray. be specific?
	t_ray		img_ray;
	t_ray		reflect_ray;
	t_ray		refract_ray;
	t_vec		isect;
	t_vec		img_isect;
	t_vec		img_normal;
	t_vec		normal;
	t_ray		shdw_ray;
	double		light_dist;
	int			inside;
	double		n1;
}				t_hit;

typedef struct	s_globals
{
	t_window	*win;
	t_camera	*cam;
	t_scene		*scene;
}				t_globals;

/*
**ft_cone.c
*/
double			*ft_cone_hit_dist(t_ray ray, double s);
t_vec			ft_cone_normal(t_hit *hit, double s);

/*
**ft_cylinder.c
*/
double			*ft_cylinder_hit_dist(t_ray ray, double r);
t_vec			ft_cylinder_normal(t_hit *hit);

/*
**ft_draw.c
*/
void			ft_draw_scene(t_globals *glob);
int				ft_get_color(t_ray ray, int row, int col, t_globals *glob);
t_rgb			ft_ray_trace(t_ray ray, t_scene *scene, int recurse_count, double n1);
void			ft_draw_pixel(char *img_str, int row, int col, int color);

/*
**ft_free.c
*/
void			ft_free(t_globals *glob);
void			ft_free_matrix(t_mat matrix);
void			ft_free_scene(t_scene *scene);

/*
**ft_hit.c
*/
t_vec			ft_get_normal(t_hit *hit);
void			ft_get_reflect_ray(t_hit *hit);
void			ft_get_refract_ray(t_hit *hit);
double			*ft_hit_dist(t_ray ray, t_obj obj);
void			ft_get_hit_data(t_hit *hit);
void			ft_hit_to_world(t_hit *hit);
double			ft_closest_hit(t_obj obj, t_ray ray, double *t, double prev_t);
int				ft_within_limits(t_obj obj, t_ray ray, double t);

/*
**ft_hooks.c
*/
void			ft_set_hooks(t_globals *glob);
int				ft_on_keypress(int keycode, void *param);
int				ft_on_exit(void *param);

/*
**ft_initilize.c
*/
void			ft_init_window(t_globals *glob, int fd);
void			ft_init_camera(t_globals *glob, int fd);
void			ft_init_scene(t_globals *glob, int fd);

/*
**ft_intersect.c
*/
t_hit			ft_intersect(t_ray ray, t_scene *scene);

/*
**ft_light.c
*/
t_rgb			ft_get_light(t_hit hit, t_scene *scene);
t_rgb			ft_get_ambient_light(t_hit hit, t_rgb amb_emission);
t_rgb			ft_get_diffuse_light(t_hit hit, t_light light);
t_rgb			ft_get_specular_light(t_hit hit, t_light light);
int				ft_in_shadow(t_hit *hit, t_light light, t_scene *scene);

/*
**ft_light_corrections.c
*/
t_rgb			ft_gamma_correction(t_rgb light, double gamma);
t_rgb			ft_scale_white(t_rgb light);
int				ft_rgb_to_int(t_rgb light);
t_rgb			ft_combine_samples(t_rgb samples[SS_CNT]);

/*
**ft_matrix.c
*/
t_mat			ft_new_matrix(void);
t_vec			ft_mat_vec_mult(t_mat m, t_vec u);
void			ft_mat_mat_mult(t_mat m1, t_mat m2, t_mat *result);

/*
**ft_parabaloid.c
*/
double			*ft_parabaloid_hit_dist(t_ray ray, double s);
t_vec			ft_parabaloid_normal(t_hit *hit, double s);

/*
**ft_parse_scene_1.c
*/
void			ft_skip_empty_line(int fd);
char			*ft_parse_str(int fd, char *category);
t_vec			ft_parse_vec(int fd, char *category);
double			ft_parse_val(int fd, char *category);
t_rgb			ft_parse_rgb(int fd, char *category);

/*
**ft_parse_scene_2.c
*/
void			ft_parse_cam_info(int fd, t_camera *cam);
void			ft_parse_light_info(int fd, t_light *light);
t_rgb			ft_calc_amb_rgb(int t_rgb, t_light *lights, int light_cnt);
void			ft_parse_obj_info(int fd, t_obj *obj);
void			ft_parse_limits(int fd, double min_lim[3], double max_lim[3]);
void			ft_validate_obj_type(char *type);

/*
**ft_plane.c
*/
double			*ft_plane_hit_dist(t_ray ray);
t_vec			ft_plane_normal(t_hit *hit);

/*
**ft_quadratic.c
*/
double			*ft_solve_quadratic(double a, double b, double c);

/*
**ft_sphere.c
*/
double			*ft_sphere_hit_dist(t_ray ray, double r);
t_vec			ft_sphere_normal(t_hit *hit);

/*
**ft_transform.c
*/
t_mat			ft_get_transform(
						t_vec t, double x_rads, double y_rads, double z_rads);
t_mat			ft_inverse(t_mat transform);
t_mat			ft_get_rx_matrix(double x_rads);
t_mat			ft_get_ry_matrix(double y_rads);
t_mat			ft_get_rz_matrix(double z_rads);

/*
**ft_vector_1.c
*/
double			ft_dot_product(t_vec u, t_vec v);
double			ft_magnitude(t_vec v);
void			ft_normalize(t_vec *u);
double			ft_vector_angle(t_vec u, t_vec v);

/*
**ft_vector2.c
*/
t_vec			ft_cross_product(t_vec u, t_vec v);
t_vec			ft_ortho_vector(t_vec u);
t_vec			ft_vec_add(t_vec v, t_vec u);
t_vec			ft_vec_subtract(t_vec v, t_vec u);
t_vec			ft_vec_scale(t_vec v, double scalar);

/*
**ft_reflect.c
*/
t_rgb   ft_combine_light(t_hit *hit, t_rgb refl_light, t_rgb refr_light, t_rgb hit_light);

#endif
