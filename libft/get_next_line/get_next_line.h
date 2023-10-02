/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 22:49:47 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/25 20:07:40 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strdup_gnl(char *s);
size_t	ft_strlen_gnl(char *s);
char	*ft_strchr_gnl(char *s, int c);
void	*ft_calloc_gnl(size_t nmemb, size_t size);

#endif
