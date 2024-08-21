/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlourenc <xlourenc@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:23:06 by xaviermonte       #+#    #+#             */
/*   Updated: 2024/08/21 17:30:49 by xlourenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *grab_rest(char *buffer)
{
    int i = 0;
    int j = 0;

    while(buffer[i] != '\n' && buffer[i] != '\0') {
        i++;
    }
    char *temp = malloc(ft_strlen(buffer) - i + 1);
    //printf("BUFFER %s\n", buffer);
    if(buffer[i] == '\0')
        return NULL;
    else
    {
        i++;
        while(buffer[i])
        {
                temp[j] = buffer[i];
                i++;
                j++;
        }
    }
    temp[j] = '\0';
    //printf("temp %s\n", temp);
    return temp;
}
static char *grab_line( char *buffer)
{
        char *temp;
        int i;
        int j;

        i = 0;
        j = 0;

        temp = malloc(sizeof(char)*ft_strlen(buffer) + 1);
        if(!temp)
                return NULL;
        while(buffer[i] != '\n' && buffer[i] != '\0')
        {      
                temp[i] = buffer[j];
                i++;
                j++;        
        }
        if(buffer[i] == '\n')
        {
                temp[i] = buffer[j];
                j++;
        }
        temp[j] = '\0';
        //printf("temp %s",temp);
        return (temp);
}
static char *read_file(int fd, char *buffer)
{
        char *temp;
        int bytes;
        int i;        
        int flag;

        flag = 0;
        temp = malloc((BUFFER_SIZE + 1) *(sizeof (char)));
        if(!temp){
                free(temp);
                return(NULL);               
        }
        temp[0] = '\0';
        bytes = 1;
        
        while(flag == 0 && bytes > 0)
        {
                bytes = read(fd,temp,BUFFER_SIZE);
                if(bytes < 0){
                        free(temp);
                        return (NULL);
                }
                buffer = ft_strjoin(buffer,temp);
                flag = ft_strchr(temp,'\n');
        }
        return(buffer);
}


char *get_next_line(int fd)
{
        static char *buffer;
        char *line;
        int i;
        
        i = 0;
        if(fd < 0 || BUFFER_SIZE <= 0)
                return (NULL);
        buffer = read_file(fd ,buffer);
        if(buffer == NULL)    
                return (NULL);
        //printf("buffer %s\n", buffer);
        line = grab_line(buffer);
        buffer = grab_rest(buffer);
        if(buffer == NULL)
                return (NULL);
        return(line);
}

 int main(void)
{
        int fd;
        char *line;

        fd = open("text.txt",O_RDONLY);
        line = get_next_line(fd);
/*         printf("line %s\n", line);
        free(line);
        line = get_next_line(fd);
        printf("line %s\n", line);
        free(line);
        line = get_next_line(fd);
        printf("line %s\n", line);
        free(line);
        line = get_next_line(fd);
        printf("line %s\n", line);
        free(line); */
        while(line != NULL)
        {
                printf("line %s\n",line);
                if(!line)
                        free(line);
                line = get_next_line(fd);
        }
        free(line);
        close(fd);
}
