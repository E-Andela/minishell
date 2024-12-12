#include "../inc/minishell.h"

void	print_linked_list(t_env_list *linked_list)
{
	t_env_list	*temp;

	if (linked_list == NULL)
	{
		printf("environment list is empty\n");
		return ;
	}
	else
	{
		printf("environment list : \n");
		temp = linked_list;
		while (temp->next != NULL)
		{
			printf("%sname	= %s%s\n", YELLOW, DEFAULT, temp->key);
			printf("%svalue	= %s%s\n", YELLOW, DEFAULT, temp->key_value);
			temp = temp->next;
		}
		if (temp->next == NULL)
		{
			printf("%sname	= %s%s\n", YELLOW, DEFAULT, temp->key);
			printf("%svalue	= %s%s\n", YELLOW, DEFAULT, temp->key_value);
		}
	}
}


const char *get_token_type_string(t_token_type type)
{
    switch (type)
    {
        case WORD: return "WORD";
        case SINGLE_QUOTED: return "SINGLE_QUOTED";
        case DOUBLE_QUOTED: return "DOUBLE_QUOTED";
        case PIPE: return "PIPE";
        case OUT_APPEND: return "OUT_APPEND";
        case IN_REDIRECT: return "IN_REDIRECT";
        case OUT_REDIRECT: return "OUT_REDIRECT";
        case HERE_DOC: return "HERE_DOC";
		case UNSET: return "UNSET";
        default: return "UNKNOWN";
    }
}


void	print_tokens(t_tokens *token_list)
{
	t_tokens *temp;

	if (!token_list)
	{
		printf("token list is empty\n");
		return ;
	}
	else
	{
		temp = token_list;
		while (temp != NULL)
		{
			printf("%sindex:		%d\n", GREEN, temp->index);
			// printf("token index:	%d\n", temp->index);
			printf("value:		%s\n", temp->value);
			printf("type:		%s (%d)\n", get_token_type_string(temp->type), temp->type);
			// printf("expandable?:	%d\n", temp->expandable);
			printf("%s----------------------------------%s\n", BLUE, DEFAULT);
			temp = temp->next;
		}
	}
}



void print_cmd_list(t_command *head_cmd_node)
{
    t_command *current_cmd;
	t_redirections *current_redir;
	int i;

	if (!head_cmd_node)
	{
	    printf("No commands to print.\n");
	    return;
	}
    current_cmd = head_cmd_node;
    while (current_cmd != NULL)
    {
		printf("%s----------------------------------%s\n", BLUE, DEFAULT);
        // printf("%sCommand Node:\n%s", YELLOW, GREEN);

        // Print arguments
        printf("%sArguments:	%s", YELLOW, DEFAULT);
        if (current_cmd->args)
        {
            i = 0;
			while (current_cmd->args[i] != NULL)
        	{
				printf("%s  ", current_cmd->args[i]);
				i++;
			}             
			printf("\n");
        }
        else
        {
            printf("None\n");
        }

        // Print redirections
        printf("%sRedirections:	", YELLOW);
        if (current_cmd->redirections)
        {
            current_redir = current_cmd->redirections;
            while (current_redir != NULL)
            {
                printf("\n%s    Type:	%s%s\n", YELLOW, DEFAULT, get_token_type_string(current_redir->type));
                
				if (current_redir->type == HERE_DOC)
					printf("%s    Dilimiter:	%s%s\n", YELLOW, DEFAULT, current_redir->file);
				else 
					printf("%s    File:	%s%s\n", YELLOW, DEFAULT, current_redir->file);
                current_redir = current_redir->next;
            }
        }
        else
            printf("%sNone\n", DEFAULT);
        printf("\n");
        current_cmd = current_cmd->next;
    }
}