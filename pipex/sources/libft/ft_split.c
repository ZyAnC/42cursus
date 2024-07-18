/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:50:46 by yzheng            #+#    #+#             */
/*   Updated: 2024/07/18 18:18:55 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	countstring(char *str, char charset)
{
	int	i;
	int	count;
	int	isprevsep;

	i = 0;
	count = 0;
	isprevsep = 1;
	while (str[i])
	{
		if (str[i] == charset)
		{
			isprevsep = 1;
		}
		else if (isprevsep)
		{
			count++;
			isprevsep = 0;
		}
		i++;
	}
	return (count);
}

static	void	free_result(char **result, int j)
{
	while (j--)
		free(result[j]);
	free(result);
}

static	char	*ftstrndup(const char *src, int n)
{
	char	*dest;
	int		i;

	if (!src)
		return (NULL);
	dest = malloc(n + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[n] = '\0';
	return (dest);
}

static int sp(char **result, char *str, char charset, int j)
{
    int start = 0;
    int i = 0;

    if (result == NULL || str == NULL)
        return -1;

    while (str[i])
    {
     
        if (str[i] == '"' || str[i] == '\'')
        {
            char quote = str[i];
            i++; 
            start = i; 
            while (str[i] && str[i] != quote)
                i++;
            if (str[i] == quote)
            {
                result[j] = ftstrndup(str + start, i - start);
                if (!result[j])
                {
                    free_result(result, j);
                    return 0;
                }
                j++;
            }

            if (str[i] == quote)
                i++;
        }
        else if (str[i] != charset)
        {
            start = i;
            while (str[i] && str[i] != charset)
                i++;
            result[j] = ftstrndup(str + start, i - start);
            if (!result[j])
            {
                free_result(result, j);
                return 0;
            }
            j++;
        }
        else
        {
            // Move past the separator
            i++;
        }
    }

    result[j] = NULL;
    return 1;
}


char	**ft_split(char *str, char charset)
{
	char	**result;
	int		size;

	if (!str)
		return (NULL);
	size = countstring(str, charset);
	result = malloc((size + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	if (sp(result, str, charset, 0))
		return (result);
	else
		return (NULL);
}
/*
#include <stdio.h>
int main() {
    char test_str[] = "hello!";
    char charset= ' ';

    // 调用 ft_split 函数得到结果
    char **result = ft_split(test_str, charset);
    if (result == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // 循环打印每个分割后的字符串
    for (int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
    }

    // 释放 ft_split 返回的结果内存
    for (int i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}*/
