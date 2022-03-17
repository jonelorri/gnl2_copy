#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(const char *s1, char const *set);
int	ft_search_n(const char *s1);
char	*ft_strchr(const char *s, int c);

void	ft_free(char **buf, char **holder)
{
	free(*buf);
	free(*holder);
	*holder = NULL;
}

char	*end_line(char **holder2, char *buf)
{
	int n;
	char *line;

	n = ft_search_n(*holder2);
	line = (char *)malloc((n + 1) * sizeof(char));
	ft_strlcpy(line, *holder2, n + 1);
	*holder2 = ft_strtrim(*holder2, line);
	free(buf);
	return(line);
}

static char *update_holder(char **holder, char *buf, size_t a)
{
	char	*temp;

	if(a <= BUFFER_SIZE && a > 0)
	{
		if(ft_strlen(*holder) > 0)
		{
			temp = (char *)malloc(sizeof(char) * (a + 1));
			ft_strlcpy(temp, buf, a + 1);
			*holder = ft_strjoin(*holder, temp);
			free(temp);
		}
		else
		{
			free(*holder);
			*holder = (char *)malloc(sizeof(char) * (ft_strlen(*holder) + a + 1));
			ft_strlcpy(*holder, buf, a + 1);
		}
	}
	return(*holder);
}

char	*update_line(char **holder, char *buf)
{
	char *line;

	if(ft_strlen(*holder) > 0)
	{
		line = (char *)malloc(sizeof(char) * ft_strlen(*holder) + 1);
		ft_strlcpy(line, *holder, ft_strlen(*holder) + 1);
		ft_free(&buf, &*holder);
		return(line);
	}
	ft_free(&buf, &*holder);
	return(NULL);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*holder;
	size_t		a;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if(!holder)
		holder = ft_strdup("");
	while(ft_search_n(holder) == 0)
	{
		a = read(fd, buf, BUFFER_SIZE);
		if(a == 0 || (int)a == -1)
			return(update_line(&holder, buf));
		holder = update_holder(&holder, buf, a);
		if(!holder)
			return(NULL);
	}
	line = end_line(&holder, buf);
	return(line);
}
