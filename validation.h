#ifndef VALIDATION_H
#define VALIDATION_H

#include <stddef.h>

/* ---- validation checks: return 1 if valid, 0 if not ---- */
int validateID(int id);
int validateMoney(double amount);
int validateText(const char *text);
int validateEmail(const char *email);
int validatePhone(const char *phone);

/* ---- safe input helpers (line based, so bad input never repeats an old choice) ---- */
void clearInputBuffer(void);

/* Reads one line into buffer. Returns 1 = ok, 0 = line too long, -1 = input closed. */
int readLine(char *buffer, size_t size);

/* Reads a whole number. Returns -1 if the text is not a number, eofValue if input is closed. */
int readInt(int eofValue);

/* Reads a decimal number. Returns 1 = ok, 0 = not a number, -1 = input closed. */
int readDouble(double *value);

/* Ask again until valid. Each returns 1 on success, 0 if input was closed. */
int promptText(const char *prompt, char *buffer, size_t size);
int promptMoney(const char *prompt, double *value);
int promptID(const char *prompt, int *value);

#endif
