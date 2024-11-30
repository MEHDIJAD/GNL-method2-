
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
	{
		len++;
	}
	return (len);
}
char	*ft_filljoin(char *tofill, const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		tofill[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		tofill[i] = s2[j];
		i++;
		j++;
	}
	tofill[i] = '\0';
	return (tofill);
}

char	*ft_strjoined(char const *s1, char const *s2)
{
	char	*strjn;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2)); //!!
	if (!s2)
		return (ft_strdup(s1)); //!!
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	strjn = (char *)malloc((len + 1) * sizeof(char)); //!!
	if (!strjn)
		return (NULL);
	strjn = ft_filljoin(strjn, s1, s2);
	return (strjn);
}

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*cpy;
    int i;

	size = ft_strlen((char *)s1);
	cpy = malloc(sizeof(char) * (size + 1));
	if (!cpy)
		return (NULL);
    i = 0;
	while (s1[i])
    {
        cpy[i] = s1[i];
        i++;
    }
	cpy[size] = '\0';
	return (cpy);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t			len;
	size_t			i;

	len = ft_strlen(src);
	if (dstsize != 0)
	{
		i = 0;
		while (src[i] && i < dstsize - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (len);
}
