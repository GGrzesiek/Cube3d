#include "cube.h"

t_map_line	*new_map_line(char *content)
{
	t_map_line	*node;

	node = malloc(sizeof(t_map_line));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	add_map_line_back(t_map_line **head, t_map_line *node)
{
	t_map_line	*cur;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}

void	free_map_lines(t_map_line **head)
{
	t_map_line	*cur;
	t_map_line	*next;

	if (!head || !*head)
		return ;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		free(cur->content);
		free(cur);
		cur = next;
	}
	*head = NULL;
}
