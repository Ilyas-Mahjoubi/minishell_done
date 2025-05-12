/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:00:49 by tkurukul          #+#    #+#             */
/*   Updated: 2024/11/29 00:33:37 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define malloc(size) custom_malloc(size)

//static int malloc_counter = 0;

/*void *custom_malloc(size_t size)
{
    malloc_counter++;
    if (malloc_counter == 3) // Simulate failure on the third allocation
    {
        return NULL;
    }
    return malloc(size);
}*/

static int	ft_skip(char c, const char *s, size_t f)
{
	size_t	i;

	i = f;
	while (s[i] != '\0' && s[i] == c)
		i++;
	return (i);
}

static int	ft_strlen(char c, char *s, size_t g)
{
	size_t	i;

	i = g;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i - g);
}

static int	ft_count_words(char c, const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_copy( char *src, size_t start, size_t len, char **arr)
{
	size_t			i;
	char			*dest;
	size_t			j;

	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == NULL)
	{
		j = 0;
		while (arr[j] != NULL)
		{
			free(arr[j]);
			j++;
		}
		free(arr);
		return (NULL);
	}
	i = 0;
	while (i < len && src[start + i] != '\0')
	{
		dest[i] = src[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char			**arr;
	size_t			len;
	size_t			i;
	size_t			skipstart;
	size_t			count;

	if (s == NULL)
		return (NULL);
	count = ft_count_words(c, s);
	arr = (char **)malloc((count + 1) * (sizeof(char *)));
	if (arr == NULL)
		return (NULL);
	i = 0;
	len = 0;
	skipstart = 0;
	while (i < count)
	{
		skipstart = ft_skip(c, s, skipstart);
		len = ft_strlen(c, (char *)s, skipstart);
		arr[i] = ft_copy((char *)s, skipstart, len, arr);
		skipstart += len;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
/*
int main(void)
{
    char **result;

    // Test string with three words
    char *test_str = "word1 word2 word3";
    char delimiter = ' ';

    // Run the function
    result = ft_split(test_str, delimiter);

    // Check the result
    if (result == NULL)
    {
        printf("Allocation failed as expected. Checking for memory leaks.\n");
    }
    else
    {
        printf("Error: Allocation did not fail when it should have.\n");
    }

    return 0;
}

int	main(void)
{
	char	**arr =(char **)ft_split("hello!",' ');
	int	i = 0;

	while (arr[i] != NULL)
	{
		if (arr[i] != NULL)
		{
			printf("%s\n", arr[i]);
			free(arr[i]);
		}
		i++;
	}
	free(arr);
	return (0);
}

 * check char
 * count words;
 * strcpy
 * ccreate malloc for char **
 * have a while that creates malloc * for malloc ** whith [i];
 * create a scroller for src, cpy until delimiter
 *
 */
