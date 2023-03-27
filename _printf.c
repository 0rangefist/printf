#include "main.h"
/**
 * print_specified_data - Prints an argument from a list
 * of arguments in a way determined by a given specifier
 *
 * @args: The list of arguments from which our
 * argument of interest can be found
 *
 * @format_ptr_ptr: The ptr to the format string ptr
 *
 * Return: The number of characters printed
 */
int print_specified_data(va_list args, const char **format_ptr_ptr)
{
	/* check if the specifier_char matches any pre-defined */
	/* value of the next char in the format string */
	switch (*(*(format_ptr_ptr) + 1))
	{
		case 'c':
			/* dereference format_ptr & increment it by 1 */
			/* this moves format_ptr to the next character */
			*format_ptr_ptr = *(format_ptr_ptr) + 1;
			return (print_char(args));
		case 's':
			*format_ptr_ptr = *(format_ptr_ptr) + 1;
			return (print_string(args));
		case 'd':
		case 'i':
			*format_ptr_ptr = *(format_ptr_ptr) + 1;
			return (print_integer(args));
		default:
			/* when no specifier char */
			return (write(STDOUT_FILENO, "%%", 1));
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
	/* pointer to the current character in the format string */
	const char *format_ptr		  = format;
	int			num_chars_printed = 0;

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
				if (*(format_ptr + 1) == '%') /* if next char == % */
				{
					/*  print % */
					num_chars_printed += write(STDOUT_FILENO, format_ptr, 1);
					format_ptr++;
					break;
				}
				/* we have a potential specifier character */
				num_chars_printed += print_specified_data(args, &format_ptr);
				break;
			default: /* if any other character is encountered */
				num_chars_printed += write(STDOUT_FILENO, format_ptr, 1);
				break;
		}
		format_ptr++;
	}
	va_end(args);
	if (args == NULL)
	{
		return (-1);
	}
	return (num_chars_printed);
}

