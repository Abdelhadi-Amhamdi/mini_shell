/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:04:02 by aamhamdi          #+#    #+#             */
/*   Updated: 2023/05/29 16:27:14 by aamhamdi         ###   ########.fr       */
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

char *str_fill(char *str, char *condition)
{
    int j;
    int index;
    char *tmp;
    char current;

    j = 0;
    index = 0;
    tmp = strdup(str);
    while (condition[j])
    {
        while (condition[j] && condition[j] == '*')
            j++;
        current = condition[j];
        while (tmp[index] && tmp[index] != current)
        {
            tmp[index] = '*';
            index++;
        }
        if (!tmp[index] || !condition[j])
            break ;
        j++;
        index++;
    }
    return (tmp);
}

int reg_ex_(char *str, char *condition)
{
	int index;
	int j;
    char current;
    char *tmp;
    
    index = 0;
    j = 0;
    tmp = str_fill(str, condition);
    while (condition[j])
    {
        while (condition[j] && condition[j] == '*')
            j++;
        current = condition[j];
        while (tmp[index] && tmp[index] != current)
            index++;
        if ((!j && index) || (!index && j))
            return (free(tmp), 0);
        if (!tmp[index])
            break;
        j++;
        index++;
    }
    if (condition[j] == '\0')
	    return (free(tmp), 1);
    return (free(tmp), 0);
}

char *wildcard(char *path, char *cnd)
{
	DIR *dir;
    char *data;
    struct dirent *entry;

	(void)cnd;
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return (NULL);
    }
    data = calloc(1, 1);
    while ((entry = readdir(dir)) != NULL)
	{
		if (reg_ex_(entry->d_name, cnd))
			printf("%s\n", entry->d_name);
        	// data = ft_strjoin_entrys(data, entry->d_name);
	}

    // closedir(dir);
	return (NULL);
	// return (data);
}
