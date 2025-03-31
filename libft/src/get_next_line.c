#include "get_next_line.h"
#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2, size_t size)
{
	char	*result_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result_str = (char *)ft_calloc((s1_len +s2_len + 1), sizeof(char));
	if (!result_str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		result_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] && j < size)
		result_str[i++] = s2[j++];
	free(s1);
	return (result_str);
}

static char	*read_and_store(int fd, char *buffered_data)
{
	char		*buffer;
	ssize_t		bytes_read;

	// Allocate memory to the temp buffer
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1; // Initialize to a non-zero value
	while (!ft_strchr(buffered_data, '\n') && bytes_read > 0) // continue whilst there is not a new line
	{
		// Read and store into the buffer
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1) // Check for error
		{
			free(buffer);
			perror("Error reading file"); // ? Can I use perror ?
			return (NULL);
		}
		if (bytes_read > 0) // If bytes were read
		{
			buffered_data = ft_strjoin_gnl(buffered_data, buffer, (size_t)bytes_read); // Join the buffer in buffered_data
		}
	}
	free(buffer); // Free the temp buffer before exiting the function
	return (buffered_data);
}

static char	*extract_line(char *buffered_data)
{
	char	*line;
	size_t	i;

	if (!buffered_data || !*buffered_data)
		return (NULL);
	// Find the length of the line up to '\n' or '\0'
	i = 0;
	while (buffered_data[i] && buffered_data[i] != '\n')
		i++;
	// Allocate memory for the line
	line = (char *)ft_calloc((i + 2), sizeof(char)); // +1 for the '\n’
	if (!line)
		return (NULL);
	// Copy the line
	i = 0;
	while (buffered_data[i] && buffered_data[i] != '\n')
	{
		line[i] = buffered_data[i];
		i++;
	}
	// Include the '\n' if present
	if (buffered_data[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*update_buffer(char *buffered_data)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;

	// Find where the first line ends
	i = 0;
	while (buffered_data[i] && buffered_data[i] != '\n')
		i++;
	// If it's EOF, free and return NULL
	if (!buffered_data[i])
	{
		free (buffered_data);
		return (NULL);
	}
	// Allocate memory for the remaining buffered data
	new_buffer = (char *)ft_calloc((ft_strlen(buffered_data) - i + 1), sizeof(char));
	if (!new_buffer)
		return (NULL);
	// Copy the remaining data
	i++; // skip the '\n'
	j = 0;
	while (buffered_data[i])
		new_buffer[j++] = buffered_data[i++];
	// Free the old buffer and return the new one
	free(buffered_data);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffered_data;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// Read and store in buffer
	buffered_data = read_and_store(fd, buffered_data);
	if (!buffered_data)
		return (NULL);
	// Extract last line
	line = extract_line(buffered_data);
	// Update the buffer by removing the last line
	buffered_data = update_buffer(buffered_data);
	// Return the line
	return (line);
}



