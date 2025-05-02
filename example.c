#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harper.h"

void
help()
{
	puts("harper-c example program");
	printf("built with harper-c v%s\n", HARPER_C_VERSION);
	puts("usage: ./example 'SENTENCE'");
	puts("parse SENTENCE and print any lints");
	puts("");
	puts("exit 0 on no mistake, 1 on mistake, and 127 on error");
}

int
main(int argc, char* argv[])
{
	int mistakes = 0;

	if ((argc == 1) || !strcmp(argv[1], "-h") ||  !strcmp(argv[1], "--help"))
	{
		help();
		return 0;
	}

	Document* sentence = harper_create_document(argv[1]);
	if (sentence == NULL)
		return 127;

	LintGroup* linter = harper_create_lint_group();
	if (linter == NULL)
	{
		harper_free_document(sentence);
		return 127;
	}

	int num_lints;
	Lint** lints = harper_get_lints(sentence, linter, &num_lints);
	if (lints == NULL)
	{
		harper_free_lint_group(linter);
		harper_free_document(sentence);
		return 127;
	}

	for (int i=0; i < num_lints; i++)
	{
		char* lint_message = harper_get_lint_message(lints[i]);
		if (lint_message != NULL)
		{
			printf("%s\n", lint_message);
			free(lint_message);
			mistakes = 1;
		}
	}

	harper_free_lint_group(linter);
	harper_free_document(sentence);
	return mistakes ? 1 : 0;
}