/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 20:54:27 by lnicosia          #+#    #+#             */
/*   Updated: 2021/01/11 19:01:39 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_POOL_H
# define THREAD_POOL_H
# include <pthread.h>

typedef struct			s_work
{
	void				*param;
	int					(*func)(void *);
	struct s_work		*next;
}						t_work;

typedef struct			s_tpool
{
	pthread_cond_t		worker_cond;
	pthread_cond_t		main_cond;
	pthread_mutex_t		mutex;
	t_work				*works;
	pthread_t			*threads;
	int					stop;
	int					nb_threads;
	int					nb_alive_threads;
	int					nb_working_threads;
	int					err;
	char				padding[4];
}						t_tpool;

int						init_tpool(t_tpool *tpool, int nb_threads);
int						free_tpool(t_tpool *tpool);
t_work					*create_work(int (*func)(void *), void *param);
t_work					*get_work(t_tpool *tpool);
void					destroy_work(t_work *work);
void					*tpool_worker(void *param);
void					*tpool_work(t_tpool *tpool,
int (*func)(void *), void *param);
int						tpool_wait(t_tpool *tpool);

#endif
