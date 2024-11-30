#include "get_next_line.h"

int ft_found_newline(char *str_buf)
{
    int i;

    if (!str_buf)
        return (0);
    i = 0;
    while (str_buf[i])
    {
        if (str_buf[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}
int ft_len_to_newline(char *str_buf)
{
    int len;

    if (!str_buf)
        return (0);
    len = 0;
    while (str_buf[len] && str_buf[len] != '\n')
        len++;
    if (str_buf[len] == '\n')
        len++;
    return (len);
}
char *ft_get_line(char * str_buf)
{
    int len;
    char *line;

    if (!str_buf)
        return (NULL);
    len = ft_len_to_newline(str_buf);
    line = malloc(len + 1); //!! 
    if (!line)
        return (NULL);
    ft_strlcpy(line, str_buf, len + 1);
    return (line);
}

void ft_read_join(char **str_buff, int fd)
{
    int bytes_read;
    char *buf;
    char *temp;

    while (!ft_found_newline (*str_buff))
    {
        buf = malloc(BUFFER_SIZE + 1); //!!
        if (!buf)
            return ;
        bytes_read = read(fd, buf, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(buf); //!! in nothing is read
            return ;
        }
        buf[bytes_read] = '\0';
        temp = ft_strjoined(*str_buff, buf);
        free(*str_buff);
        *str_buff = temp;
        free(buf); //!! end with buff
        if (bytes_read == 0)
            break;
    }
}

char *get_next_line(int fd)
{
    static char *str_buf;
    char *line;
    char *temp;

    //* checks: if fd = -1 or if nothing to read or if no access to read 
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
        return (NULL);
    ft_read_join(&str_buf, fd);
    if (!str_buf || !*str_buf)
    {
        free(str_buf);
        str_buf = NULL;
        return (NULL);
    }
    line = ft_get_line(str_buf);
    temp = ft_strdup(str_buf + ft_len_to_newline(str_buf));
    free(str_buf);
    str_buf = temp;
    return (line);
}
