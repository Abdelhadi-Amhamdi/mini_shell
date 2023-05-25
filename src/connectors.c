/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:04:02 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/25 10:31:21 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"
#include <dirent.h>

int run_connectors(t_tree *root)
{
	int status;
	
	if (!ft_strncmp(root->str, "&&", ft_strlen(root->str)))
	{
		status = executer(root->left, NULL);
		if (!status)
			return (executer(root->right, NULL));
	}
	else
	{
		status = executer(root->left, NULL);
		if (status)
			status = executer(root->right, NULL);
		return (status);
	}
	return (-11);
}

char	*ft_strjoin_entrys(char const *s1, char const *s2)
{
	char	*p;
	size_t	size1;
	size_t	size2;

	if (!s1 || !s2)
		return (0);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	p = (char *)malloc((size1 + size2 + 2) * sizeof(char));
	if (!p)
		return (0);
	ft_memcpy(p, s1, size1);
	ft_memcpy(p + size1, s2, size2);
    p[size1 + size2] = ' ';
	p[size1 + size2 + 1] = '\0';
	return (p);
}

void wildcard(t_lexer *node)
{
	DIR *dir;
    char *data;
    struct dirent *entry;

    dir = opendir("./");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    data = calloc(1, 1);
    while ((entry = readdir(dir)) != NULL)
        data = ft_strjoin_entrys(data, entry->d_name);

    closedir(dir);
	node->str = data;
    return 0;
}
