/*-----------------------------------------------------------------------------------------------------------------------------
Programa fuente: Race_Masters.c
Compilador a utilizar: Zinjai
Programadores: <�lvarez Abel, Mis Elliot, L�pez Lander, Ruiz Pedro, Salazar Javier>
Descripci�n: Programa que simula computacionalmente carreras de f�rmula 1, y que contiene un m�dulo de apuestas para el usuario
Fecha de creaci�n: 10/05/2026
Versi�n: 1.0.
-------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int log_in(char user[10], char password[10]);
int user_type(char user[10]);
int  verificacionNombre(char *name);


int main() {
	int access = 0; //Variable de acceso
	int rol; //Variable de tipo de usuario
	char user[10], password[10]; //Strings para el usuario y contrase�a
	printf("==================================================================\n");
	printf("                           RACE MASTERS\n");
	printf("==================================================================\n");
	while (access == 0)
		access = log_in(user,password);
		if (!(verificacionNombre(user))) {
			access = 0;
			printf("\n Usuario solo puede contener numeros y letras ");
		}
	rol = user_type(user);
	return 0;
}

int log_in(char user[10], char password[10]) { //Funci�n para iniciar sesi�n
	int x; //Variable de salida
	char login_user[10], login_password[10];
	printf("�Bienvenido al programa Race Masters!\nPara comenzar con la experiencia, requiere crear su usuario\n");
	printf("\nIngrese un nombre de usuario (m�nimo 5, m�ximo 10 caracteres): ");	fflush(stdin);	gets(user);
	/* Construir validaci�n del string */
	printf("\nCree una contrase�a (m�nimo 5, m�ximo 10 caracteres): ");	fflush(stdin);	gets(password);
	/*Construir validaci�n del string*/
	printf("�Bienvenido al programa Race Masters!\nPor favor, inicie sesi�n\n");
	printf("\nUsuario: ");	fflush(stdin);	gets(login_user);
	printf("Contrase�a: ");	fflush(stdin);	gets(login_password);
	if (strcmp(user,login_user) == 0 && strcmp(password,login_password) == 0)
		x = 1;
	return x;
}

int user_type(char user[10]) {
	int x;
	printf("\nHola %s :)\n�Qu� deseas hacer en el programa?\n", user);
	printf("1) Visualizar simulaciones de carreras\n2) Apostar en las carreras\nIngrese una opci�n: ");
	scanf("%d", &x);
	while (x != 1 && x != 2) {
		printf("�El valor ingresado es inv�lido! Ingreselo nuevamente: ");	scanf("%d", &x);
	}
	switch (x) {
		case 1: printf("Usted ha seleccionado ser espectador"); break;
		case 2: printf("Usted ha seleccionado ser apostador"); break;
	}
	return x;
}


int  verificacionNombre(char *name) {
	for (int i = 0; name[i] != '\0'; i++) {
		if (!(isalnum(name[i]))) return 0;
	}
	return 1;
}