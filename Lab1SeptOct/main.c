#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORD_LENGTH 30

int hasDoubleConsonants(const char* word) {
	int length = strlen(word);
	char consonants[] = "bcdfghjklmnpqrstvwxyz";

	for (int i = 0; i < length - 1; i++) {
		char current = tolower(word[i]);
		char next = tolower(word[i + 1]);

		if (isalpha(current) && isalpha(next) && strchr(consonants, current) && current == next) {
			return 1;
		}
	}
	return 0;
}

int main() {
	FILE* file;
	char filepath[] = "C:\\Users\\yanam\\Desktop\\Lab1SP.txt";
	char word[MAX_WORD_LENGTH + 1];
	char printedWords[MAX_WORD_LENGTH + 1][MAX_WORD_LENGTH + 1];
	int printedWordsCount = 0;

	if (fopen_s(&file, filepath, "r") != 0) {
		printf("Error while opening the file\n");
		return 1;
	}

	printf("Words with double consonants: \n");

	while (fscanf_s(file, "%30s", word, (unsigned)_countof(word)) != EOF) {
		// Видаляємо коми зі слова
		char* context;
		char* token = strtok_s(word, ",", &context);
		while (token != NULL) {
			if (hasDoubleConsonants(token)) {
				int isDuplicate = 0;
				for (int i = 0; i < printedWordsCount; i++) {
					if (strcmp(token, printedWords[i]) == 0) {
						isDuplicate = 1;
						break;
					}
				}
				if (!isDuplicate) {
					printf("%s\n", token);
					strncpy_s(printedWords[printedWordsCount], _countof(printedWords[printedWordsCount]), token, _TRUNCATE);
					printedWordsCount++;
				}
			}
			token = strtok_s(NULL, ",", &context);
		}
	}

	fclose(file);

	return 0;
}
