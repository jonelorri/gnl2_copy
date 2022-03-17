#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str, int x)
{
	size_t	i;
	size_t nLocation;
	
	if (x == 1)
	{
		i = 0;
		if (!str)
			return (0);
		while (str[i])
			i++;
		return (i);
	}
	i = 0;
	nLocation = 0;
	while(i < ft_strlen(str, 1))
	{
		if(str[i] == '\n')
			return(i + 1);
		i++;
	}
	return(nLocation);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = ft_strlen(src, 1);
	if (dstsize)
	{
		while (src[++i] && --dstsize)
			dst[i] = src[i];
		dst[i] = '\0';
	}
	return (j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	s1_len;
	size_t 	dstl;
	char	*dst;
	size_t	dstsize;

	s1_len = ft_strlen(s1, 1);
	dest = (char *)malloc(sizeof(char) * (s1_len + ft_strlen(s2, 1) + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, s1_len + 1);
	dst = &dest[s1_len];
	dstl = ft_strlen(dst, 1);
	dstsize = ft_strlen(s2, 1) + 1;
	if (dstl < dstsize)
	{
		while (dstl < dstsize - 1 && *s2)
			*(dst + dstl++) = *s2++;
		*(dst + dstl) = '\0';
	}
	free((char *)s1);
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*srt;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s || len < 0)
		return (NULL);
	srt = (char *)malloc(len + 1 * (sizeof(char)));
	if (!srt)
		return (NULL);
	j = 0;
	while (s[j] != '\0')
		j++;
	while (start < j && i < len)
	{
		srt[i] = s[start];
		i++;
		start++;
	}
	srt[i] = '\0';
	return (srt);
}

char	*ft_strtrim(const char *s1, char *set)
{
	char	*ptr;

	ptr = (char *)s1;
	if (!s1 || !set)
		return (NULL);	
	while (*s1 != '\0' && *set == *s1)
		if(*s1 != '\n')
		{
			set++;
			s1++;
		}
		else
			break;
	if(*s1 == '\n')
		s1++;
	free(ptr);
	return (ft_substr(s1, 0, ft_strlen(s1, 1)));
}
