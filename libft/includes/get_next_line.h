#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 128
#endif

char	*get_next_line(int fd);
char 	*ft_strjoin_gnl(char *s1, char *s2, size_t size);
// void	*ft_calloc(size_t nmemb, size_t size);
// char	*ft_strchr(const char *s, int c);
// size_t	ft_strlen(const char *s);

#endif