/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:07:08 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/01 15:07:08 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(int *fd, t_info *info)
{
	ft_putendl_fd(info->pwd_path, fd[WRITE]);
	return (NORMAL);
}
