#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "validation.h"

/* Return 1 if the ID is positive */
int validateID(int id)
{
    return id > 0;
}

/* Return 1 if the amount is non-negative (and not absurdly large / infinite) */
int validateMoney(double amount)
{
    return amount >= 0.0 && amount <= 1.0e12;
}

/* Reject NULL, empty text, or spaces only */
int validateText(const char *text)
{
    if (text == NULL)
        return 0;

    while (*text != '\0') {
        if (!isspace((unsigned char)*text))
            return 1;

        text++;
    }

    return 0;
}

/* Basic email format validation */
int validateEmail(const char *email)
{
    if (email == NULL)
        return 0;

    const char *at = strchr(email, '@');

    if (at == NULL || at == email ||
        strchr(at + 1, '@') != NULL)
        return 0;

    const char *dot = strchr(at + 1, '.');

    if (dot == NULL || dot == at + 1 ||
        dot[1] == '\0')
        return 0;

    return 1;
}

/* Allow digits and common phone number symbols */
int validatePhone(const char *phone)
{
    int digits = 0;

    if (phone == NULL)
        return 0;

    for (int i = 0; phone[i] != '\0'; i++) {
        if (isdigit((unsigned char)phone[i])) {
            digits++;
        } else if (phone[i] != '+' &&
                   phone[i] != ' ' &&
                   phone[i] != '-' &&
                   phone[i] != '(' &&
                   phone[i] != ')') {
            return 0;
        }
    }

    return digits >= 7 && digits <= 15;
}

/* ------------------------------------------------------------------ */
/* Input helpers                                                       */
/* ------------------------------------------------------------------ */

/* Throw away the rest of the current input line */
void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readLine(char *buffer, size_t size)
{
    size_t len;

    if (fgets(buffer, (int)size, stdin) == NULL)
        return -1;

    len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return 1;
    }

    if (len == size - 1) {
        /* buffer filled with no newline: the line was too long */
        clearInputBuffer();
        return 0;
    }

    return 1;   /* last line of input had no newline */
}

int readInt(int eofValue)
{
    char buffer[32];
    char *end;
    long value;
    int status = readLine(buffer, sizeof(buffer));

    if (status == -1)
        return eofValue;
    if (status == 0)
        return -1;

    value = strtol(buffer, &end, 10);
    if (end == buffer)
        return -1;

    while (isspace((unsigned char)*end))
        end++;

    if (*end != '\0' || value <= INT_MIN || value > INT_MAX)
        return -1;

    return (int)value;
}

int readDouble(double *value)
{
    char buffer[64];
    char *end;
    double result;
    int status = readLine(buffer, sizeof(buffer));

    if (status == -1)
        return -1;
    if (status == 0)
        return 0;

    result = strtod(buffer, &end);
    if (end == buffer)
        return 0;

    while (isspace((unsigned char)*end))
        end++;

    if (*end != '\0')
        return 0;

    *value = result;
    return 1;
}

int promptText(const char *prompt, char *buffer, size_t size)
{
    int status;

    for (;;) {
        printf("%s", prompt);
        status = readLine(buffer, size);

        if (status == -1)
            return 0;
        if (status == 1 && validateText(buffer))
            return 1;

        printf("Invalid input. It cannot be blank or longer than %d characters.\n",
               (int)size - 2);
    }
}

int promptMoney(const char *prompt, double *value)
{
    int status;

    for (;;) {
        printf("%s", prompt);
        status = readDouble(value);

        if (status == -1)
            return 0;
        if (status == 1 && validateMoney(*value))
            return 1;

        printf("Invalid amount. Enter a non-negative number (e.g. 1500.50).\n");
    }
}

int promptID(const char *prompt, int *value)
{
    int number;

    for (;;) {
        printf("%s", prompt);
        number = readInt(INT_MIN);

        if (number == INT_MIN)
            return 0;
        if (validateID(number)) {
            *value = number;
            return 1;
        }

        printf("Invalid ID. Enter a positive whole number.\n");
    }
}
