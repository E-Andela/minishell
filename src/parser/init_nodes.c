#include "../../inc/minishell.h"

t_command	*init_command_node(void)
{
	t_command	*cmd_node;

	cmd_node = (t_command *)malloc(sizeof(t_command));
	if (cmd_node == NULL)
		return (NULL);
	cmd_node->args = NULL;
	cmd_node->redirections = NULL;
	cmd_node->next = NULL;
	cmd_node->prev = NULL;
	return (cmd_node);
}

t_redirections	*init_redirection_node(char *file, t_token_type type)
{
	t_redirections	*redir;

	redir = (t_redirections *)malloc(sizeof(t_redirections));
	if (redir == NULL)
		return (NULL);
	redir->file = ft_strdup(file);
	redir->type = type;
	redir->next = NULL;
	return (redir);
}
