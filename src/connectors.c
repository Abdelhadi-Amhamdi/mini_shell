/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:04:02 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/06/06 15:57:21 by aamhamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"
#include <dirent.h>

int run_connectors(t_tree *root)
{
	int status;
	
	if (!ft_strncmp(root->str, "&&", ft_strlen(root->str)))
	{
		status = executer(root->left);
		if (status >= 0 && status <= 127)
			return (executer(root->right));
	}
	else
	{
		status = executer(root->left);
		if (status < 0 || status > 127)
			status = executer(root->right);
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
    free((char *)s1);
	return (p);
}

int is_match(char *str, char *cnd)
{
    int index;
    int j;
    int last_wild_index;
    int next_wild_index;
    int backtracking_index;

    index = 0;
    j = 0;
    last_wild_index = -1;
    next_wild_index = -1;
    backtracking_index = -1;
    while (str[index])
    {
        if (cnd[j] == str[index])
        {
            index++;
            j++;
        }
        else if (cnd[j] == '*')
        {
            last_wild_index = j;
            next_wild_index = ++j;
            backtracking_index = index;
        }
        else if (last_wild_index == -1)
            return (0);
        else
        {
            j = next_wild_index;
            index = ++backtracking_index;
        }
    }
    while (j < (int)ft_strlen(cnd))
    {
        if (cnd[j++] != '*')
            return (0);
    }
    return (1);
}

int allow_hidden(char *file_name, char *cnd)
{
    if ((cnd[0] == '.' && file_name[0] == '.') || file_name[0] != '.')
        return (1);
    return (0);
}

char *wildcard(char *condition)
{
	DIR *dir;
    char *data;
    struct dirent *entry;

    (void)condition;
    dir = opendir("./");
    if (dir == NULL) {
        perror("opendir");
        return (NULL);
    }
    data = calloc(1, 1);
    while ((entry = readdir(dir)) != NULL)
	{
		if (is_match(entry->d_name, condition) && allow_hidden(entry->d_name, condition))
            data = ft_strjoin_entrys(data, entry->d_name);
	}
    closedir(dir);
	return (data);
}
