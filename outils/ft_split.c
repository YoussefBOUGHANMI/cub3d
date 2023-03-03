
#include"../cub3d.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}



int ft_count_word(char *str, int len)
{
    int word_count;
    int i;

    i = 0;
    word_count = 0;
    while (i < len) 
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')) 
            i++;
        if (str[i]) 
	    {
            word_count++;
            while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')) 
                i++;
        }
    }
    return(word_count);
}


char **ft_split(char *str) 
{
    int i;
    int j = 0;
    int k = 0;
    int len;

    len = ft_strlen(str);
    char **result = (char**)malloc(sizeof(char*) * (ft_count_word(str, len) + 1));
    if (result == NULL) 
        return NULL;
    i = 0;
    while (i < len) 
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')) 
            i++;
        if (str[i]) 
	    {
            j = i;
            while (str[j] && (str[j] != ' ' && str[j] != '\t' && str[j] != '\n')) 
                j++;
            result[k] = (char*)malloc(sizeof(char) * (j - i + 1));
            if (result[k] == NULL) 
                return NULL;
            ft_strncpy(result[k], str + i, j - i);
            result[k][j - i] = '\0';
            k++;
            i = j;
        }
    }
    result[k] = NULL;
    return result;
}

