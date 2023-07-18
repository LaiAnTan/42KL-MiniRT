# define BUFFER_SIZE 42

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

int    nlcheck(char *ev)
{
    int    i = 0;
    while (ev[i] != 0)
    {
        if (ev[i] == '\n')
            return (0);
        i++;
    }
    return (1);
}

char    *reallocbuff(char *buff, int rv)
{
    int i = 0;
    char *tmp = malloc(sizeof(char) * (rv +1));
    while (i < rv)
    {
        tmp[i] = buff[i];
        i++;
    }
    tmp[i] = 0;
    free(buff);
    return (tmp);
}

int    ft_strlen(char *str)
{
    int    i = 0;
	if (!str)
		return (0);
    while (str[i] != 0)
        i++;
    return (i);
}

char    *ft_strjoin(char    *ev, char *buff)
{
    char    *tmp = malloc(sizeof(char) * (ft_strlen(ev) + ft_strlen(buff) + 1));
    int    i = 0;
    int    j = 0;

    while (ev[i] != 0)
    {
        tmp[i] = ev[i];
        i++;
    }
    while (buff[j] != 0)
        tmp[i++] = buff[j++];
    free(ev);
    return (tmp);
}

char    *get_line(char *ev)
{
    int    i = 0;
    int    j = 0;
    char    *tmp;
    while (ev[i] != '\n' && ev[i] != 0)
        i++;
    if (ev[i] == '\n')
        tmp = malloc(sizeof(char) * (i+2));
    if (ev[i] == 0)
        tmp = malloc(sizeof(char) * (i+1));
    while (j < i)
    {
        tmp[j] = ev[j];
        j++;
    }
    if (ev[j] == '\n')
        tmp[j++] = '\n';
    tmp[j] = 0;
    return (tmp);
}

char    *trim(char *ev)
{
    char    *tmp;
    int    i = 0;
    int    j = ft_strlen(ev);

    while (ev[i] != '\n' && ev[i] != 0)
        i++;
    if (ev[i] == 0)
    {
        free(ev);
        return (NULL);
    }
    tmp = malloc(sizeof(char) * (j - i + 1));
    if (!tmp)
        return (NULL);
    j = 0;
    if (ev[i] == '\n')
        i++;
    while (ev[i] != 0)
        tmp[j++] = ev[i++];
    tmp[j] = 0;
    free(ev);
    return (tmp);
}


char    *reading(char *everything, int fd)
{
    int    rv = 1;
    char    *buff;
    while (rv)
    {
        buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        rv = read(fd, buff, BUFFER_SIZE);
        if (rv == -1)
            return (NULL);
		buff[rv] = '\0';
        buff = reallocbuff(buff, rv);
        everything = ft_strjoin(everything, buff);
        rv = nlcheck(buff);
        free(buff);
    }
    return (everything);
}


char    *get_next_line(int fd)
{
    static char    *everything;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!everything)
    {
        everything = malloc(sizeof(char) * 1);
        if (!everything)
            return (NULL);
        everything[0] = 0;
    }
    everything = reading(everything, fd);
    if (!everything)
        return (NULL);
    line = get_line(everything);
    if (!line)
        return (NULL);
    everything = trim(everything);
    return (line);
}

int    main()
{
    int    fd = open("./test.txt", O_RDONLY);
    for (int i = 0; i < 15; i++)
    {
        char *yes = get_next_line(fd);
        printf("%d= ", i);
        printf("yes = %s\n", yes);
        free(yes);
    }
}