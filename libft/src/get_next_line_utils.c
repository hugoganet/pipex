#include <stdlib.h>
//#include "get_next_line.h"

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	size_t 	total_size;
// 	char	*ptr;
// 	size_t	i;

// 	if (nmemb == 0 ||size == 0)
// 		return (malloc(0));
// 	if (size > SIZE_MAX / size)
// 		return (NULL);
// 	total_size = size * nmemb;
// 	ptr = (char *)malloc(total_size);
// 	if (!ptr)
// 		return (NULL);
// 	i = 0;	
// 	while(i < total_size)
// 		ptr[i++] = '\0';
// 	return (ptr); 
// }
// int		ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s && s[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	if (!s)
// 		return (NULL);
// 	while (*s)
// 	{
// 		if (*s == (char)c)
// 		{
// 			//printf("\nfound\n");
// 			return ((char *)s);
// 		}
// 		s++;
// 	}
// 	if ((char)c == '\0')
// 		return ((char *)s);
// 	return (NULL);
// }

// char	*ft_strjoin(char *s1, char *s2, size_t size)
// {
// 	char	*result_str;
// 	size_t	s1_len;
// 	size_t	s2_len;
// 	size_t	i;
// 	size_t	j;

// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	result_str = (char *)ft_calloc((s1_len +s2_len + 1), sizeof(char));
// 	if (!result_str)
// 		return (NULL);
// 	i = 0;
// 	while (s1 && s1[i])
// 	{
// 		result_str[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2 && s2[j] && j < size)
// 		result_str[i++] = s2[j++];
// 	free(s1);
// 	return (result_str);
// }
