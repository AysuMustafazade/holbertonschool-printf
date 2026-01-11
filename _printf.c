#include <stdarg.h>
#include <unistd.h>

/**
 * print_number - prints an integer
 * @n: number to print
 *
 * Return: number of characters printed
 */
int print_number(int n)
{
	unsigned int num;
	int count = 0;
	char c;

	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		num = -n;
	}
	else
		num = n;

	if (num / 10)
		count += print_number(num / 10);

	c = (num % 10) + '0';
	write(1, &c, 1);
	count++;

	return (count);
}

/**
 * _printf - produces output according to a format
 * @format: format string
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	char c;
	char *str;

	if (format == NULL)
		return (-1);

	va_start(args, format);

	while (*format)
	{
		if (*format != '%')
		{
			write(1, format, 1);
			count++;
		}
		else
		{
			format++;
			if (*format == '\0')
			{
				va_end(args);
				return (-1);
			}

			if (*format == 'c')
			{
				c = (char)va_arg(args, int);
				write(1, &c, 1);
				count++;
			}
			else if (*format == 's')
			{
				str = va_arg(args, char *);
				if (!str)
					str = "(null)";
				while (*str)
				{
					write(1, str, 1);
					str++;
					count++;
				}
			}
			else if (*format == 'd' || *format == 'i')
			{
				count += print_number(va_arg(args, int));
			}
			else if (*format == '%')
			{
				write(1, "%", 1);
				count++;
			}
			else
			{
				write(1, "%", 1);
				write(1, format, 1);
				count += 2;
			}
		}
		format++;
	}

	va_end(args);
	return (count);
}
