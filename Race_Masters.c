/*-----------------------------------------------------------------------------------------------------------------------------
Programa fuente: Race_Masters.c
Compilador a utilizar: Zinjai
Programadores: <Alvarez Abel, Mis Elliot, Lopez Lander, Ruiz Pedro, Salazar Javier>
Descripciï¿½n: Programa que simula computacionalmente carreras de formula 1, y que contiene un mï¿½dulo de apuestas para el usuario
Fecha de creacion: 10/05/2026
Version: 1.0.
-------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int log_in(char user[10], char password[10]);
int  verificacionNombre(char *name);
void menu_inicio();
void simulacion();

int main() {
	int access = 0; //Variable de acceso
	int rol; //Variable de tipo de usuario
	char user[10], password[10]; //Strings para el usuario y contrasena
	printf("==================================================================\n");
	printf("                           RACE MASTERS\n");
	printf("==================================================================\n");
	while (access == 0) {
		access = log_in(user,password);
		if (!(verificacionNombre(user))) {
			access = 0;
			printf("\n Usuario solo puede contener numeros y letras ");
		}
	}
	printf("\nHola %s :)\nRace Masters es un programa que simula computacionalmente carreras de formula uno, y onde tu puedes elegir entre simplementa verlas, o apostar en ellas\n", user);
	menu_inicio();
	return 0;
}

int log_in(char user[10], char password[10]) { //Funcion para iniciar sesion
	int x; //Variable de salida
	char login_user[10], login_password[10];
	printf("¡Bienvenido al programa Race Masters!\nPara comenzar con la experiencia, requiere crear su usuario\n");
	printf("\nIngrese un nombre de usuario (minimo 5, maximo 10 caracteres): ");	fflush(stdin);	gets(user);
	/* Construir validacion del string */
	printf("\nCree una contrasena (minimo 5, maximo 10 caracteres): ");	fflush(stdin);	gets(password);
	/*Construir validacion del string*/
	printf("¡Bienvenido al programa Race Masters!\nPor favor, inicie sesion\n");
	printf("\nUsuario: ");	fflush(stdin);	gets(login_user);
	printf("Contrasena: ");	fflush(stdin);	gets(login_password);
	if (strcmp(user,login_user) == 0 && strcmp(password,login_password) == 0)
		x = 1;
	return x;
}

int  verificacionNombre(char *name) {
	for (int i = 0; name[i] != '\0'; i++) {
		if (!(isalnum(name[i]))) return 0;
	}
	return 1;
}

void menu_inicio() { // Funcion para el menu de inicio
	int x; // Variable de entrada
	printf("Ahora puede visualizar lo siguiente\n1) Simulacion\n2) Info. Pilotos\n3) Info. circuitos\n4) Transferir saldo\n5) Salir\n");
	printf("Seleccione una opcion: ");	scanf("%d", &x);
	while (x > 5 || x < 1) {
		printf("¡El dato ingresado es invalido! Ingreselo nuevamente: ");	scanf("%d", &x);
	}
	return;
	switch (x) {
	case 1: simulacion(); break;
	default: printf("\nGracias por usar Race Masters ¡Vuelve pronto!");	break;
	}
}

void simulacion() {
	//Integracion del menu de circuitos
	//INtegracion del modulo de apuestas
	//Integracion del algoritumo de carreras
	return;
}
