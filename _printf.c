#include "main.h"
/**
 * print_buffer - Prints the buffer contents if they exist at all
 * @buffer: contains the array of characters
 * @buff_ind: the index where the next character is added
 * usually represents the length
 */
void print_buffer(char buffer[], int *buff_ind)
{
        if (*buff_ind > 0)
                write(1, &buffer[0], *buff_ind);
        *buff_ind = 0;
}
/**_printf - printf function that produces output to a format
 * @format: the format under consideration
 * Return: the characters being printed.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];
	
	if (format == NULL)
	{
		return (-1);
	}
	va_start(list, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind++ == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write (1, &format[i], 1) */
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			size = get_size(format, &i);
			precision = get_precision(format, &i, list);
			width = get_width(format, &i, list);
			++i;
			printed = handle_print(format, &i, list,
					buffer, precision, size, width, flags);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}
	print_buffer(buffer, &buff_ind);
	va_end(list);
	return (printed_chars);
}
