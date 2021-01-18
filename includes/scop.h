/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:56:35 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/18 14:33:04 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
# include "env.h"

int				scop(int ac, char **av);
int				init_opengl(t_env *env);
void			free_all(t_env *env);
void			ft_fatal_error(const char *str, t_env *env);
void			viewport_update_callback(GLFWwindow *window, int width,
int height);
void			key_callback(GLFWwindow *window, int key, int scancode,
int action,
int mods);
int				draw_triangle(t_env *env);
int				init_triangle_shaders_program(t_env *env);
unsigned int	init_pipeline_shader(GLenum type, const char *source,
t_env *env);
char			*read_shader(const char *file);
int				init_shader(const char *vertex_shader,
const char *fragment_shader, t_env *env);
int				init_object(const char *source_file, unsigned int *textures,
unsigned int nb_textures, t_env *env);
int				add_object(size_t id, t_env *env);
int				move_object(t_instance *object, t_v3 move);
int				rotate_object(t_instance *object, t_v3 rotate);
int				scale_object(t_instance *object, t_v3 scale);
int				draw_object(t_object *object, unsigned int shader, t_env *env);
void			projection_matrix(t_camera *camera, float matrix[16]);

#endif
