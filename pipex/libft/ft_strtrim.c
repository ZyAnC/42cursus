/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:48:06 by yzheng            #+#    #+#             */
/*   Updated: 2024/04/16 11:39:16 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	checkset(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	len;
	size_t	start;
	size_t	end;
	int		i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	start = 0;
	len = ft_strlen(s1);
	while (s1[start] && checkset(set, s1[start]))
		start++;
	if (start == len)
		return (ft_strdup(""));
	end = len - 1;
	while (end > start && checkset(set, s1[end]))
		end--;
	s2 = malloc ((end - start + 2) * sizeof(*s1));
	if (s2 == NULL)
		return (NULL);
	while (start <= end)
		s2[i++] = s1[start++];
	s2[i] = '\0';
	return (s2);
}

#include <stdio.h>
int main() {
    // 测试用例数据
    struct {
        char const *s1;
        char const *set;
    } test_cases[] = {
        {"   Hello World   ", ""},
        {"###Hello World###", "#"},
        {"abcHello Worldcba", "acb"},
        {"", " "},
        {"   ", " "},
        {NULL, " "}
    };

    // 测试用例名称
    char const *test_names[] = {
        "Test 1: Trimming spaces",
        "Test 2: Trimming hash",
        "Test 3: Trimming multiple characters",
        "Test 4: Empty string",
        "Test 5: Space only",
        "Test 6: NULL string"
    };

    // 执行测试并打印结果
    for (unsigned long i = 0;
	i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        char *result = ft_strtrim(test_cases[i].s1, test_cases[i].set);
        printf("%s\n", test_names[i]);
        printf("Original: [%s], Set: [%s]\n",
		test_cases[i].s1 ? test_cases[i].s1 : "NULL", test_cases[i].set);
        printf("Result: [%s]\n\n", result ? result : "NULL");
        free(result); // 释放由ft_strtrim分配的内存
    }

    return 0;
}
