/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:17:25 by yzheng            #+#    #+#             */
/*   Updated: 2024/04/19 15:17:26 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

#include <stdio.h>

// Helper function to print list contents for demonstration
void print_list(t_list *head) {
    while (head != NULL) {
        printf("%d -> ", *(int *)(head->content));
        head = head->next;
    }
    printf("NULL\n");
}

int main()
{
    int a = 10, b = 20, c = 30;

    // Create nodes
    t_list *head = NULL;
    t_list *first = malloc(sizeof(t_list));
    t_list *second = malloc(sizeof(t_list));
    t_list *third = malloc(sizeof(t_list));

    first->content = &a;
    first->next = NULL;
    second->content = &b;
    second->next = NULL;
    third->content = &c;
    third->next = NULL;

    // Add nodes to the list
    ft_lstadd_front(&head, third);
    ft_lstadd_front(&head, second);
    ft_lstadd_front(&head, first);

    // Print the list
    print_list(head);

    // Free allocated nodes
    free(first);
    free(second);
    free(third);

    return 0;
}
