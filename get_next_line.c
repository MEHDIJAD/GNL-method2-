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
    int i;
    int len;

    if (!str_buf)
        return (0);
    i = 0;
    len = 0;
    while (str_buf[i])
    {
        if (str_buf[i] == '\n')
            return (++len);
        i++;
        len++;  
    }
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
    free(str_buf); //!! end wiht str_buff
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
        if (!bytes_read)
        {
            free(buf); //!! in nothing is read
            return ;
        }
        buf[bytes_read] = '\0';
        temp = ft_strjoined(*str_buff, buf);
        free(*str_buff);
        *str_buff = temp;
        free(buf); //!! end with buff
    }
}

char *get_next_line(int fd)
{
    static char *str_buf;
    char *line;
    //* checks: if fd = -1 or if nothing to read or if no access to read 
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return (NULL);
    ft_read_join(&str_buf, fd);
    if (!str_buf)
        return (free(str_buf), NULL); //!!
    line = ft_get_line(str_buf);
    str_buf = ft_strdup(str_buf + ft_len_to_newline(str_buf));
    if (!str_buf[0])
    {
        free (str_buf);
        str_buf = NULL;
    }
    return (line);
}
