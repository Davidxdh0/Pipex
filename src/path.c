/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:21:57 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/10/26 11:05:46 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	relat_path(t_data *data, int cmd)
{
	char	*temp;
	char	*path;

	if (cmd == 0)
		temp = ft_strdup(data->cmd1[0]);
	else
		temp = ft_strdup(data->cmd2[0]);
	if (!temp)
		return ;
	if (temp[0] == '.')
	{
		path = ft_strjoin("./", temp);
		if (!path)
			return ;
		if (access(path, X_OK))
		{
			free(data->path);
			data->path = ft_strdup(path);
		}
		free(path);
	}
	free(temp);
}

void	path_splitter(t_data *data)
{
	data->paths = ft_split(data->path, ':');
	if (!data->paths)
		message("perror_exit(1, data->paths);");
}

char	*path_split(t_data *data, int cmd)
{
	int		i;
	char	*temp;

	path_splitter(data);
	i = -1;
	while (data->paths[++i])
	{
		temp = ft_strjoin(data->paths[i], "/");
		if (!temp)
			return (NULL);
		data->path = ft_strjoin(temp, data->cmd1[0]);
		if (!data->path)
			message("(perror_exit(1, data->path, 5000);");
		if (!access(data->path, X_OK))
		{
			relat_path(data, cmd);
			return (data->path);
		}
		free(data->path);
		free(temp);
	}
	free_arr(data->paths);
	data->path = NULL;
	return (NULL);
}

char	*env_var(char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	data->envps++;
	return (NULL);
}

void	input_parse(t_data *data, char **argv, char **envp, int cmd)
{
	int	i;

	i = 0;
	data->path = env_var(envp, data);
	if (!data->path && cmd == 0)
		clean_exit("Couldn't find PATH variable", 127);
	else if (!data->path && cmd == 1)
		exit(127);
	data->cmd1 = ft_split(argv[cmd + 2], ' ');
	if (!data->cmd1[0])
	{
		data->cmd1[0] = " ";
		data->flag++;
	}
	data->cmd2 = ft_split(argv[cmd + 2], ' ');
	if (!data->cmd2[0])
		data->flag++;
	data->envps = *envp + 5;
}
