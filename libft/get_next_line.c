/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:43:07 by rmrok             #+#    #+#             */
/*   Updated: 2025/03/10 13:53:08 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_buff(char **buff)
{
	free(*buff);
	*buff = NULL;
	return (NULL);
}

char	*read_buff(int fd, int *read_fd)
{
	char	*buff;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	*read_fd = read(fd, buff, BUFFER_SIZE);
	if (*read_fd < 0)
		return (free_buff(&buff));
	buff[*read_fd] = '\0';
	return (buff);
}

char	*handle_buff(int fd)
{
	char	*new_buff;
	char	*buff;
	char	*tmp;
	int		read_fd;

	buff = read_buff(fd, &read_fd);
	if (!buff || read_fd <= 0)
		return (free_buff(&buff));
	while (!ft_strchr(buff, '\n') && read_fd > 0)
	{
		new_buff = read_buff(fd, &read_fd);
		if (!new_buff)
			return (free_buff(&buff));
		tmp = ft_strjoin(buff, new_buff);
		free(buff);
		free(new_buff);
		if (!tmp)
			return (NULL);
		buff = tmp;
	}
	return (buff);
}

char	*create_res(char **buff)
{
	char	*res;
	char	*tmp;
	size_t	res_len;

	if (!(*buff) || (*buff)[0] == '\0')
		return (NULL);
	res_len = 0;
	while ((*buff)[res_len] != '\n' && (*buff)[res_len])
		res_len++;
	res = (char *)malloc((res_len + 2) * sizeof(char));
	if (!res)
		return (free_buff(buff));
	ft_strlcpy(res, *buff, res_len + 1);
	if ((*buff)[res_len] == '\n')
		res[res_len] = '\n';
	res[res_len + 1] = '\0';
	tmp = NULL;
	if ((*buff)[res_len] == '\n' && (*buff)[res_len + 1] != '\0')
		tmp = ft_strdup(*buff + res_len + 1);
	free(*buff);
	*buff = tmp;
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buff = NULL;
	char		*new_buff;
	char		*tmp;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = handle_buff(fd);
	new_buff = ft_strjoin(buff, tmp);
	if (!new_buff)
		return (NULL);
	free(tmp);
	free(buff);
	buff = new_buff;
	res = create_res(&buff);
	if (!res)
		return (NULL);
	return (res);
}

// void tester(char *file_name)
// {
// 	int fd = open(file_name, O_RDONLY | O_CREAT);
// 	char *res;
// 	int i = 1;
// 	char  *buff;
// 	printf("%d\n", BUFFER_SIZE);
// 	res = get_next_line(fd);
// 	while (res && i < 15)
// 	{
// 		// printf("\n<---------------%d---------------->\n", i);
// 		printf("%s", res);
// 		// printf("\n<------------------------------->\n");
// 		free(res);
// 		res = get_next_line(fd);
// 		i++;
// 	}
// 	res = get_next_line(fd);
// 	// printf("\n<---------------%d---------------->\n", i);
// 	printf("%s", res);
// 	// printf("\n<------------------------------->\n");
// 	free(res);
// 	close(fd);
// }
// int main(int argc, char *argv[])
// {	
// 	if (argc == 2)	
// 		tester(argv[1]);
// 	else
// 		printf("nothing happened\n");
// 	return (0);
// }