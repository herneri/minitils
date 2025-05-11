/*
	nl.c: Print files with line numbers.

    Copyright 2025 Eric Hernandez

	This file is part of minitils.

	minitils is free software: you can redistribute it and/or modify it under the terms of the GNU General
	Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

	minitils is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
	the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with minitils. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *input_file = NULL;
	char *text_buffer = NULL;
	size_t text_size = 0;
	int line_number = 1;

	if (argc == 1) {
		while (getline(&text_buffer, &text_size, stdin) != -1) {
			if (text_buffer[0] == '\n') {
				printf("\n");
				continue;
			}

			printf("     %d  %s", line_number, text_buffer);
			line_number++;
		}

		free(text_buffer);
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		input_file = fopen(argv[i], "r");
		if (input_file == NULL) {
			fprintf(stderr, "nl: Failed to read file\n");
			return 1;
		}

		while (getline(&text_buffer, &text_size, input_file) != -1) {
			if (text_buffer[0] == '\n') {
				printf("\n");
				continue;
			}

			printf("     %d  %s", line_number, text_buffer);
			line_number++;
		}

		fclose(input_file);
		free(text_buffer);
	}

	return 0;
}
