#include "../../inc/minishell.h"

char	*ft_realloc_copy(char *str, unsigned int old_size, unsigned int new_size)
{
	char			*new_str;
	unsigned int	i;

	if (new_size == 0)
		return (NULL);
	new_str = malloc(new_size);
	if (new_str == NULL)
		return (NULL);
	if (str == NULL || old_size == 0)
		return (new_str);
	if (new_size < old_size)
		old_size = new_size;
	i = 0;
	while (i < old_size)
	{
		new_str[i] = str[i];
		i++;
	}
	free(str);
	return (new_str);
}

void	*ft_realloc(void *str, unsigned int old_size, unsigned int new_size)
{
	char	*new_str;

	if (str == NULL)
	{
		str = malloc(new_size);
		if (str == NULL)
			return (NULL);
		return (str);
	}
	if (new_size == old_size)
		return (str);
	if (new_size == 0 && str != NULL)
		return (free(str), NULL);
	new_str = ft_realloc_copy(str, old_size, new_size);
	if (new_str == NULL)
		return (free(str), NULL);
	return (new_str);
}

static void	vector_resize(t_vector *vector, int new_capacity)
{
	char	*resized_vector;

	resized_vector = ft_realloc(vector->value, vector->capacity, new_capacity);
	if (resized_vector == NULL)
		exit(EXIT_FAILURE);
	vector->value = resized_vector;
	vector->capacity = new_capacity;
}

void	vector_init(t_vector *vector)
{
	vector->capacity = VECTOR_INIT_CAPACITY;
	vector->total = 0;
	vector->value = malloc(sizeof(char) * vector->capacity);
}

void	vector_add_char(t_vector *vector, char c)
{
	if (vector->capacity == vector->total)
		vector_resize(vector, vector->capacity * 2);
	vector->value[vector->total] = c;
	vector->total++;
}
