/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:42:36 by livliege      #+#    #+#                 */
/*   Updated: 2024/12/12 15:02:38 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define VECTOR_INIT_CAPACITY 16

typedef struct s_vector
{
	char	*value;
	int		capacity;
	int		total;
}	t_vector;

typedef struct s_env_list
{
	char				*key;
	char				*key_value;
	struct s_env_list	*next;
}	t_env_list;

typedef enum s_token_type
{
	UNSET,
	CMD,
	WORD,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	PIPE,
	OUT_APPEND,
	OUT_REDIRECT,
	IN_REDIRECT,
	HERE_DOC
}	t_token_type;

typedef struct s_tokens
{
	char			*value;
	t_token_type	type;
	unsigned int	index;
	struct s_tokens	*prev;
	struct s_tokens	*next;
}	t_tokens;

// In case of an heredoc, *file will be the delimiter.
typedef struct s_redirection
{
	char					*file;
	t_token_type			type;
	struct s_redirection	*next;
}	t_redirections;

typedef struct s_command
{
	int					index;
	char				**args;
	t_redirections		*redirections;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

typedef struct s_data
{
	char			*user_input;
	t_env_list		*environment;
	t_tokens		*tokens_list;
	// unsigned int	pipe_count;
	t_command		*command_list;

}	t_data;

#endif