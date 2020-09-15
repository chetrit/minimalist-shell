/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** game structure initialization header
*/

#ifndef MY_UTILS_H_
#define MY_UTILS_H_

//FUNCTION OF STRING.H RECODDED
int my_strlen(char const *str);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strcat(char *dest, char const *src);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strdup(char const *src);

//ATOI FUNCTION RECODDED
int my_atoi(char const *str);

//CHAR * TO CHAR ** FUNCTION
char **one_dim_to_two_dim(char *str, char delim);

//PRINTING FUNCTIONS RECODDED
void my_putchar(char c);
void my_putstr(char const *str);
void my_put_error(char const *str);

//OTHERS
int is_alphanum(char const c);

#endif /*MY_UTILS_H_*/
