#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s1_tmp;
	unsigned char	*s2_tmp;

	i = 0;
	s1_tmp = (unsigned char *)s1;
	s2_tmp = (unsigned char *)s2;
	while (s1_tmp[i] && s2_tmp[i])
	{
		if (s1_tmp[i] != s2_tmp[i])
			break ;
		i++;
	}
	return (s1_tmp[i] - s2_tmp[i]);
}

void	swap_str(char **str, int i, int j)
{
	char	*tmp;

	tmp = str[i];
	str[i] = str[j];
	str[j] = tmp;
}

void	sort_env_str(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i] != NULL)
	{
		j = i;
		while (ft_strcmp(str[j - 1], str[j]) > 0)
		{
			swap_str(str, j - 1, j);
			j--;
			if (j <= 0)
				break;
		}
		i++;
	}
}

void	print_env_str(char **str, int *fd)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		ft_putendl_fd(str[i], fd[WRITE]);
		i++;
	}
}

void	print_export(t_info *info, int *fd)
{
	int		i;
	t_env	*cur;
	char	*tmp;
	char	**str;

	i = 0;
	cur = info->env_deq->head;
	str = (char **)malloc(sizeof(char *) * (info->env_deq->size + 1));
	merror(str);
	str[info->env_deq->size] = NULL;
	while (cur != NULL)
	{
		if (cur->env_flag == TRUE)
		{
			tmp = ft_strjoin(cur->key, "=");
			merror(tmp);
			str[i] = ft_strjoin(tmp, cur->value);
			merror(str[i++]);
			free(tmp);
			tmp = NULL;
		}
		cur = cur->next;
	}
	sort_env_str(str);
	print_env_str(str, fd);
	free_double_string(str);
}

void	add_env_value(char **env, t_env *cur, int add)
{
	char	*del;
	char	*new;

	if (env[VALUE][0] == '\0')
	{
		if (cur != NULL)
			cur->env_flag = TRUE;
		return ;
	}
	if (add == TRUE)
	{
		del = cur->value;
		new = ft_strjoin(cur->value, env[VALUE]);
		merror(new);
		cur->value = new;
		free(del);
	}
	else
	{
		if (cur->value)
			free(cur->value);
		cur->value = ft_strdup(env[VALUE]);
		merror(cur->value);
	}
	cur->env_flag = TRUE;
}

void	add_new_env(char **env, t_info *info)
{
	t_env	*end;
	t_env	*tmp;

	end = info->env_deq->last;
	tmp = create_env_node();
	link_env_node(end, tmp);
	end = end->next;
	end->key = ft_strdup(env[KEY]);
	merror(end->key);
	info->env_deq->last = end;
	end->env_flag = TRUE;
	info->env_deq->size += 1;
	if (env[VALUE] == NULL || env[VALUE][0] == '\0')
		return ;
	end->value = ft_strdup(env[VALUE]);
	merror(end->value);
}

int	incorrect_env_key(char *env_key)
{
	int	i;

	i = 0;
	if (ft_isdigit(env_key[i]))
		return (TRUE);
	while (env_key[i] && !is_special(env_key[i]))
		i++;
	if (env_key[i] == 0)
		return (FALSE);
	return (TRUE);
	//특수문자 말고 확인할거 있는지 체크하기
	// + 첫글자가 숫자인지도 체크
}

int	check_add_value(char **env)
{
	int		len;
	char	*tmp;

	len = (int)ft_strlen(env[KEY]);
	if (env[KEY][len - 1] == '+')//맨뒤에 +가 있으면 그거 지워줌.
	{
		tmp = (char *)malloc(sizeof(char) * len);
		merror(tmp);
		ft_strlcpy(tmp, env[KEY], len);
		free(env[KEY]);
		env[KEY] = tmp;
		return (TRUE);
	}
	return (FALSE);
}

void	export(char **cmd, t_info *info, int *fd)
{
	int		i;
	int		add_flag;
	char	**env;
	t_env	*cur_env;

	i = 0;
	add_flag = FALSE;
	if (cmd[1] == NULL)
	{
		print_export(info, fd);
		return ;
	}
	while (cmd[++i] != NULL)
	{
		env = env_split(cmd[i]);//==이 2개인 경우도 인식하는데 이거 처리 어떻게? => 무조건 첫번째 =으로 처리
		add_flag = check_add_value(env);
		if (incorrect_env_key(env[KEY]))//문자열의 양식 판단
		{
			error_message("export", env[KEY], "not a valid identifier");
			free_double_string(env);
			env = 0;
			continue ;
		}
		cur_env = check_listin(env[KEY], info);//리스트 안에 있는지
		if (cur_env)
			add_env_value(env, cur_env, add_flag);//그 변수 값을 새로이
		else
			add_new_env(env, info);//변수 자체를 새로 추가
		free_double_string(env);
		env = 0;
	}
	free_double_string(info->env_list);
	make_env_double_string(info);
	reset_env_path(info);
}

/*
cmd[0] = export
cmd[1] = QQ or QQ=asd
1. =앞의 변수 이름 QQ가 이미 환경변수에 있는지 확인
	환경변수list마다 변수 길이만큼 strncmp
		-> 통과하면 변수길이 다음 문자가 =인지 확인
			-> 있으면 그 값만 추가하거나 변경
2. 없으면 그냥 추가
	1. 환경변수 리스트 확장
	2. QQ=~~그대로 추가.
*/
// ++export qq+=asd -> value값에 이어붙이는 로직
