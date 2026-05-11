/*-----------------------------------------------------------------------------------------------------------------------------
Programa fuente: Race_Masters.c
Compilador a utilizar: Zinjai
Programadores: <Álvarez Abel, Mis Elliot, López Lander, Ruiz Pedro, Salazar Javier>
Descripción: Programa que simula computacionalmente carreras de fórmula 1, y que contiene un módulo de apuestas para el usuario
Fecha de creación: 10/05/2026
Versión: 1.0.
-------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int log_in(char user[10], char password[10]);
int user_type(char user[10]);

int main() {
	int access = 0; //Variable de acceso
	int rol; //Variable de tipo de usuario
	char user[10], password[10]; //Strings para el usuario y contraseña
	printf("==================================================================\n");
	printf("                           RACE MASTERS\n");
	printf("==================================================================\n");
	while (access == 0)
		access = log_in(user,password);
	rol = user_type(user);
	return 0;
}

int log_in(char user[10], char password[10]) { //Función para iniciar sesión
	int x; //Variable de salida
	char login_user[10], login_password[10];
	printf("¡Bienvenido al programa Race Masters!\nPara comenzar con la experiencia, requiere crear su usuario\n");
	printf("\nIngrese un nombre de usuario (mínimo 5, máximo 10 caracteres): ");	fflush(stdin);	gets(user);
	/* Construir validación del string */
	printf("\nCree una contraseña (mínimo 5, máximo 10 caracteres): ");	fflush(stdin);	gets(password);
	/*Construir validación del string*/
	printf("¡Bienvenido al programa Race Masters!\nPor favor, inicie sesión\n");
	printf("\nUsuario: ");	fflush(stdin);	gets(login_user);
	printf("Contraseña: ");	fflush(stdin);	gets(login_password);
	if (strcmp(user,login_user) == 0 && strcmp(password,login_password) == 0)
		x = 1;
	return x;
}

int user_type(char user[10]) {
	int x;
	printf("\nHola %s :)\n¿Qué deseas hacer en el programa?\n", user);
	printf("1) Visualizar simulaciones de carreras\n2) Apostar en las carreras\nIngrese una opción: ");
	scanf("%d", &x);
	while (x != 1 && x != 2) {
		printf("¡El valor ingresado es inválido! Ingreselo nuevamente: ");	scanf("%d", &x);
	}
	switch (x) {
		case 1: printf("Usted ha seleccionado ser espectador"); break;
		case 2: printf("Usted ha seleccionado ser apostador"); break;
	}
	return x;
}
