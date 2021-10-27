#include "minishell.h"

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

void	export(char **cmd, t_info *info, int *fd)
{
	int		i;
	int		add_flag;
	char	**env;
	t_env	*cur_env;

	i = 0;
	add_flag = FALSE;
	if (cmd[1] == NULL)
		return (print_export(info, fd));
	while (cmd[++i] != NULL)
	{
		env = env_split(cmd[i]);//==이 2개인 경우도 인식하는데 이거 처리 어떻게? => 무조건 첫번째 =으로 처리
		add_flag = check_add_value(env);
		if (incorrect_env_key(env[KEY]))//문자열의 양식 판단
			error_message("export", env[KEY], "not a valid identifier");
		else
		{
			cur_env = check_listin(env[KEY], info);//리스트 안에 있는지
			if (cur_env)
				add_env_value(env, cur_env, add_flag);//그 변수 값을 새로이
			else
				add_new_env(env, info);//변수 자체를 새로 추가
		}
		free_double_string(env);
	}
	reset_env_info(info);
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
