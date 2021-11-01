/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:26:07 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/01 15:26:15 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_absol(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

int	check_sign(t_ll num)
{
	if (num >= 0)
		return (1);
	return (-1);
}
