#include "../../includes/minishell.h"

char	*ft_strjoin_arena(char const *s1, char const *s2, t_arena *arena)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 || !s2)
		return (0);
	str = ft_alloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)), arena);
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
