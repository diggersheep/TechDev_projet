#include <stdio.h>

int clavier (void)
{
	int x;
	scanf(" %d", &x);
	return x;
}

// 1 -> jeu + SDL
// 2 -> jeu + SDL + fog
// 3 -> jeu + console

int menu (void)
{
	printf("========================\n");
	printf("=      Space Al'Ka     =\n");
	printf("========================\n");
	printf("\n");
	printf("    1. Jeu SDL\n");
	printf("    2. Jeu SDL + brouillard\n");
	printf("\n");
	printf("> ");
	int code = clavier();

	if (code < 1 && code > 2)
		menu();
	else
		return code;
}