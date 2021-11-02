/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:00:20 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/02 18:39:37 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_exit_code	g_exit;

static t_ll	save_number(const char *str, int *idx, int *digit_len, int *plus)
{
	int					minus;
	unsigned long long	num;

	minus = 1;
	num = 0;
	while ((str[*idx] >= 9 && str[*idx] <= 13) || str[*idx] == ' ')
		(*idx)++;
	if (str[*idx] == '-' || str[*idx] == '+')
	{
		if (str[(*idx)++] == '-')
			minus = -1;
	}
	while (str[*idx] >= '0' && str[*idx] <= '9')
	{
		num = num * 10 + ft_absol(str[(*idx)++] - '0');
		(*digit_len)++;
	}
	while ((str[*idx] >= 9 && str[*idx] <= 13) || str[*idx] == ' ')
		(*idx)++;
	*plus = minus;
	return (num * minus);
}

static int	ft_atolong(const char *str, t_ll *val)
{
	int		i;
	int		digit_len;
	int		is_plus;

	i = 0;
	digit_len = 0;
	if (str == NULL)
		return (FALSE);
	*val = save_number(str, &i, &digit_len, &is_plus);
	if (str[i] != '\0')
		return (FALSE);
	if (digit_len > 19 || is_plus != check_sign(*val))
		return (FALSE);
	return (TRUE);
}

static int	is_digit_string(char *str)
{
	int	i;
	int	digit_cnt;

	i = 0;
	digit_cnt = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i + digit_cnt] && ft_isdigit(str[i + digit_cnt]))
		digit_cnt++;
	while (is_space(str[i + digit_cnt]))
		i++;
	if (str[i + digit_cnt] == 0 && digit_cnt <= 19)
		return (TRUE);
	return (FALSE);
}

int	execute_exit(char **cmd, t_info *info)
{
	t_exit	tmp;

	if (info->n_cmd <= 1)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd[1] == NULL)
		exit(0);
	if (is_digit_string(cmd[1]) && ft_atolong(cmd[1], &(tmp.num)))
	{
		if (cmd[2] == NULL)
		{
			g_exit.code = tmp.c[0];
			exit(g_exit.code);
		}
		return (error_msg(cmd[0], NULL, "too many arguments"));
	}
	error_msg("exit", cmd[1], "numeric argument required");
	exit(255);
}
