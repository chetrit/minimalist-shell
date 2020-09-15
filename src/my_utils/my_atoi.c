/*
** EPITECH PROJECT, 2019
** my_atoi
** File description:
** transforms string into int
*/

int my_strlen(char const *str);

int less_counter(const char *str, int i, int condition)
{
    if ((str[i] == '-' || i == 0) && condition == 1) {
        return (1);
    } else {
        return (0);
    }
}

int my_atoi(char const *str)
{
    int len = my_strlen(str);
    long nb = 0;
    int less_count = 0;

    for (int i = 0, condition_less = 1; i != len; i++) {
        if ((str[i] < 48 || str[i] > 57) && (str[i] != '-' && str[i] != '+')) {
            i = len - 1;
        } else if (str[i] >= '0' && str[i] <= '9') {
            condition_less = 0;
            nb = nb * 10;
            nb = nb + (str[i] - 48);
        } else
            less_count = less_counter(str, i, condition_less) + less_count;
        if (nb == 2147483648)
            return (less_count % 2  == 1 ? -2147483648 : 0);
    }
    less_count % 2 == 1 ? nb = -nb : 0;
    return (nb);
}
