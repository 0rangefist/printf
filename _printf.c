#include "main.h"

/**
 * print_specified_data - Prints an argument from a list
 * of arguments in a way determined by a given specifier
 *
 * @specifier_char: The specifier to determine how
 * printing should be done
 *
 * @args: The list of arguments from which our
 * argument of interest can be found
 *
 * Return: The number of characters printed
 */
int print_specified_data(va_list args, const char specifier_char)
{
	/* check if the specifier_char matches any pre-defined */
	switch (specifier_char)
	{
		case 'c':
			return (print_char(args));
		case 's':
			return (print_string(args));
		case 'd':
		case 'i':
			return (print_integer(args));
		case '%':
			return (write(STDOUT_FILENO, "%", 1));
		default:
			/* print the % char & unidentified specifier_char */
			return (write(STDOUT_FILENO, "%", 1)
				   + write(STDOUT_FILENO, &specifier_char, 1));
	}
}

/**
 * print_escape_sequence - Prints an escape sequence
 *
 * @special_char: The special character that determines
 * what the escape sequence is
 *
 * Return: The number of characters printed
 */
int print_escape_sequence(const char special_char)
{
	/* check if the special_char matches any pre-defined */
	switch (special_char)
	{
		case 't': /* tab character */
			return (write(STDOUT_FILENO, "\t", 1));
		case 'r': /* carriage return character */
			return (write(STDOUT_FILENO, "\r", 1));
		case 'n': /* newline character */
			return (write(STDOUT_FILENO, "\n", 1));
		default:
			/* print the unidentified special_char */
			return (write(STDOUT_FILENO, &special_char, 1));
	}
}

/**
 * _printf - Prints a formatted string to stdout
 *
 * @format: The format string
 * @...: The arguments to be printed
 *
 * Return: The number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	char	specifier_char;
	char	special_char;
	/* pointer to the current character in the format string */
	const char *format_ptr		= format;
	int	  num_chars_printed = 0;

	if (!format) /* check if format is NULL pointer */
	{
		return (-1);
	}

	/* initialize the args pointer to start at the beginning */
	va_start(args, format);

	while (*format_ptr)
	{
		switch (*format_ptr)
		{
			case '%': /* if the format specifier % is encountered */
				/* save the next character after the specifier */
				specifier_char = *(++format_ptr);
				num_chars_printed += print_specified_data(args, specifier_char);
				break;
			case '\\': /* if the escape character is encountered */
				/* save the next character after the escape char */
				special_char = *(++format_ptr);
				num_chars_printed += print_escape_sequence(special_char);
				break;
			default: /* if any ordinary character is encountered */
				num_chars_printed += write(STDOUT_FILENO, format_ptr, 1);
				break;
		}
		format_ptr++;
	}
	va_end(args);
	return (num_chars_printed);
}
