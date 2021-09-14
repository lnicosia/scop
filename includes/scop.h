/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:56:35 by lnicosia          #+#    #+#             */
/*   Updated: 2021/09/14 18:09:44 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
# include "env.h"
# include "inputs.h"

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
int				init_object(const char *source_file, t_env *env);
int				set_object_texture(t_instance *mesh, int id, unsigned int text);
int				add_object(size_t id, t_env *env);
int				move_object(t_instance *mesh, t_v3 move);
int				rotate_object(t_instance *mesh, t_v3 rotate);
int				scale_object(t_instance *mesh, t_v3 scale);
int				update_object(t_instance *mesh);
int				draw_mesh(t_object *object, t_mesh *mesh, unsigned int instance,
unsigned int shader, t_env *env);
int				draw_object(t_object *object, unsigned int instance,
unsigned int shader, t_env *env);
void			projection_matrix(t_camera *camera, float matrix[16]);
int				parse_object(const char *source_file, int mode, t_object *object,
t_env *env);
int             process_inputs(t_input *inputs, t_env *env);
int             init_inputs(t_input *inputs);
void			init_camera(t_env *env);
void			free_object(t_object *object);
int				init_cubemap(char *files[6], int flip[6], GLenum format, t_env *env);
int				draw_skybox(unsigned int cubemap, unsigned int shader, t_env *env);
int				init_mesh_buffers(t_mesh *mesh);
void			print_mesh(t_mesh *mesh);
void			print_object(t_object *object);
int				set_mesh_texture(t_mesh *mesh, size_t instance, int id, unsigned int text);

#endif
