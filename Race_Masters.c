/*-----------------------------------------------------------------------------------------------------------------------------
Programa fuente: Race_Masters.c
Compilador a utilizar: Zinjai
Programadores: <Alvarez Abel, Mis Elliot, Lopez Lander, Ruiz Pedro, Salazar Javier>
Descripcion: Programa que simula computacionalmente carreras de formula 1, y que contiene un modulo de apuestas para el usuario
Fecha de creacion: 10/05/2026
Version: 1.5 (Integracion de modulos)
-------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <windows.h>

/* ================================================================
ESTRUCTURAS (unificadas desde simulacion.c y MODULO_APUESTAS.c)
================================================================ */

struct tiempo_vuelta {
	int minutos;
	float segundos;
};

struct campeonato {
	/*Nota importante: al final ninguna variable de esta estructura se utilizo debido a un cambio en la forma de manejar el campeonato.
	Sin embargo, como se usa la variable add para la sumatoria del campeonato, y se le llama como .add en todo el algoritmo, por cuuestiones de tiempo se dejo*/
	int australia;
	int china;
	int japon;
	int miami;
	int canada;
	int monaco;
	int add;
};

struct piloto {
	char nombre_p[20];
	char scuderia[25];
	float tiempo_carrera;
	int nivel;
	int agresividad;
	int concentracion;
	int concentracion_activa;
	int concentracion_cooldown;
	int eliminado;
	int manejo;
	float Apuesta;      /* monto apostado por el jugador */
	int Victorias;      /* victorias acumuladas en el campeonato */
	struct tiempo_vuelta intervalo;
	struct tiempo_vuelta brecha;
	struct campeonato puntos;
} pilotos[22];

struct circuito {
	float segundos;
	int probabilidad_lluvia;
	int vueltas;
	int curvas;
	int profit;
	int prob_choque;
};

/* ================================================================
DATOS GLOBALES DE CIRCUITOS (desde simulacion.c)
================================================================ */

struct circuito circuitos[3][4] = {
	{
	/* {segundos x vuelta, prob lluvia 1/x, vueltas, curvas, profit, riesgo} */
		{87,  3,  52, 14,  4, 550},  /* Silverstone */
	{106, 2,  44, 13,  3, 420},  /* Spa */
		{90,  4,  53,  9,  9, 360},  /* Suzuka */
	{76, 10,  66, 13,  7, 800}   /* Barcelona */
},
{
	{81,   9, 53,  8,  3, 500},  /* Monza */
{75,   5, 71, 10,  3, 600},  /* Red Bull Ring */
	{90,  99, 50, 27,  5, 220},  /* Jeddah */
{91, 149, 57, 14,  2, 950}   /* Bahrain */
},
		{
			{70,  9, 72, 13, 33, 150},   /* Monaco */
		{95, 11, 62, 23,  6, 300},   /* Marina Bay */
			{76,  6, 70, 15, 11,1000},   /* Hungaroring */
		{70,  3, 71, 10,  3, 380}    /* Interlagos */
		}
};

/* ================================================================
PROTOTIPOS
================================================================ */

/* --- Login y verificacion --- */
int    log_in(char usuario[50], char contrasena[50]);
int    verificacionNombre(char *nombre);

/* --- Menus --- */
void   menu_inicio(char usuario[50]);

/* --- Modulo de informacion --- */
void   info_pilotos(void);
void   info_circuitos(void);

/* --- Modulo de transferencia de saldo --- */
void   transferir_saldo(float *Fondos);

/* --- Algoritmo de validacion --- */
void capturar_tarjeta(char tarjeta[20]);

/* --- Modulo de apuestas (desde MODULO_APUESTAS.c) --- */
void   cancelar_apuesta(int *PilotosApostados, float *Fondos);
void   proceso_apuesta(int opc2, float *Fondos, int *PilotosApostados);
void   Impresion_de_pilotos(float Fondos, float Record);
void   Modulo_de_apuestas(float *Fondos, float *Record, int *PilotosApostados);

/* --- Modulo de simulacion (desde simulacion.c) --- */
void   inicializar_pilotos(void);
void   ordenar(int orden[22]);
void   simular_piloto(int campeonato, int carrera, int piloto_idx);
void   mostrar_clasificacion(void);
void   ejecutar_carrera(int indicador_campeonato, int carrera, float *Fondos, float *Record, int *PilotosApostados);
void   simulacion(float *Fondos, float *Record, int *PilotosApostados);

/* ================================================================
MAIN
================================================================ */

int main(void) {
	int   acceso = 0;
	char  usuario[50], contrasena[50];
	
	inicializar_pilotos();
	
	printf("==================================================================\n");
	printf("                           RACE MASTERS\n");
	printf("==================================================================\n");
	
	/* --- LOGIN --- */
	while (acceso == 0) {
		acceso = log_in(usuario, contrasena);
		if (!verificacionNombre(usuario)) {
			acceso = 0;
			printf("\n Usuario solo puede contener numeros y letras.\n");
		}
	}
	
	printf("\nHola %s :)\n", usuario);
	printf("Race Masters es un programa que simula computacionalmente carreras de\n");
	printf("formula uno, donde tu puedes elegir entre simplemente verlas, o apostar en ellas.\n");
	printf("Tambien, durante cada carrera, cada 3 segundos se imprimirá el progreso de esta cada 10 vueltas, para que no te pierdas de la accion :0\n");
	printf("Inicias con un saldo de $0.00 - ve al modulo de Transferir Saldo para recargar.\n");
	
	menu_inicio(usuario);   /* pasa el control al menu principal */
	
	return 0;
}

/* ================================================================
LOGIN Y VERIFICACION
================================================================ */

int log_in(char usuario[50], char contrasena[50]) {
	char login_usuario[50], login_contrasena[50];
	
	printf("\n--- REGISTRO ---\n");
	printf("Cree un nombre de usuario (5-10 caracteres, solo letras y numeros): ");
	fflush(stdin);
	fgets(usuario, 50, stdin);
	usuario[strcspn(usuario, "\n")] = '\0';
	
	printf("Cree una contrasena (5-10 caracteres): ");
	fflush(stdin);
	fgets(contrasena, 50, stdin);
	contrasena[strcspn(contrasena, "\n")] = '\0';
	
	/* Validacion basica de longitud */
	if (strlen(usuario) < 5 || strlen(usuario) > 10) {
		printf("El usuario debe tener entre 5 y 10 caracteres.\n");
		return 0;
	}
	if (strlen(contrasena) < 5 || strlen(contrasena) > 10) {
		printf("La contrasena debe tener entre 5 y 10 caracteres.\n");
		return 0;
	}
	
	printf("\n--- INICIO DE SESION ---\n");
	printf("Usuario: ");
	fflush(stdin);
	fgets(login_usuario, 50, stdin);
	login_usuario[strcspn(login_usuario, "\n")] = '\0';
	
	printf("Contrasena: ");
	fflush(stdin);
	fgets(login_contrasena, 50, stdin);
	login_contrasena[strcspn(login_contrasena, "\n")] = '\0';
	
	if (strcmp(usuario, login_usuario) == 0 && strcmp(contrasena, login_contrasena) == 0)
		return 1;
	
	printf("Usuario o contrasena incorrectos. Intente de nuevo.\n");
	return 0;
}

int verificacionNombre(char *nombre) {
	for (int i = 0; nombre[i] != '\0'; i++) {
		if (!isalnum((unsigned char)nombre[i])) return 0;
	}
	return 1;
}

/* ================================================================
MENU DE INICIO
================================================================ */

void menu_inicio(char usuario[50]) {
	int x = 0;
	float Fondos          = 0.0;
	float Record          = 0.0;
	int   PilotosApostados = 0;
	
	do {
		printf("\n==================================================================\n");
		printf("  MENU PRINCIPAL - Hola, %s | Saldo: $%.2f\n", usuario, Fondos);
		printf("==================================================================\n");
		printf("Recomendacion: selecciona transferir saldo primero para poder apostar mas adelante\n");
		printf("  1) Simulacion\n");
		printf("  2) Info. Pilotos\n");
		printf("  3) Info. Circuitos\n");
		printf("  4) Transferir Saldo\n");
		printf("  5) Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &x);
		fflush(stdin);
		
		while (x < 1 || x > 5) {
			printf("Opcion invalida. Ingresela nuevamente: ");
			scanf("%d", &x);
			fflush(stdin);
		}
		
		switch (x) {
		case 1:
			simulacion(&Fondos, &Record, &PilotosApostados);
			break;
		case 2:
			info_pilotos();
			break;
		case 3:
			info_circuitos();
			break;
		case 4:
			transferir_saldo(&Fondos);
			break;
		case 5:
			printf("\nGracias por usar Race Masters. Vuelve pronto!\n");
			break;
		}
	} while (x != 5);
}

/* ================================================================
MODULO: INFO PILOTOS
(TODO: pendiente de implementacion segun especificaciones)
================================================================ */

void info_pilotos(void) {
	printf("\n========== INFO PILOTOS ==========\n");
	for (int i = 0; i < 22; i++) {
		printf("\n(%d) %-20s | Equipo: %-25s | Nivel: %d\n",
			   i+1, pilotos[i].nombre_p, pilotos[i].scuderia, pilotos[i].nivel);
		printf("    Agresividad: %d | Manejo: %d | Concentracion: %d\n",
			   pilotos[i].agresividad, pilotos[i].manejo, pilotos[i].concentracion);
	}
	printf("\n");
}

/* ================================================================
MODULO: INFO CIRCUITOS
(TODO: pendiente de implementacion segun especificaciones)
================================================================ */

void info_circuitos(void) {
	printf("\n========== INFO CIRCUITOS ==========\n");
	printf("Formato: vueltas | seg/vuelta | lluvia 1/x | curvas 1/x | peligro 1/x\n\n");
	
	printf("--- CAMPEONATO NE ---\n");
	printf("Silverstone:    %d vueltas | %.0f s/v | lluvia 1/%d | curvas 1/%d | peligro 1/%d\n",
		   circuitos[0][0].vueltas, circuitos[0][0].segundos, circuitos[0][0].probabilidad_lluvia, circuitos[0][0].curvas, circuitos[0][0].prob_choque);
	printf("Spa:            %d vueltas | %.0f s/v | lluvia 1/%d | curvas 1/%d | peligro 1/%d\n",
		   circuitos[0][1].vueltas, circuitos[0][1].segundos, circuitos[0][1].probabilidad_lluvia, circuitos[0][1].curvas, circuitos[0][1].prob_choque);
	printf("Suzuka:         %d vueltas | %.0f s/v | lluvia 1/%d | curvas 1/%d | peligro 1/%d\n",
		   circuitos[0][2].vueltas, circuitos[0][2].segundos, circuitos[0][2].probabilidad_lluvia, circuitos[0][2].curvas, circuitos[0][2].prob_choque);
	printf("Barcelona:      %d vueltas | %.0f s/v | lluvia 1/%d | curvas 1/%d | peligro 1/%d\n",
		   circuitos[0][3].vueltas, circuitos[0][3].segundos, circuitos[0][3].probabilidad_lluvia, circuitos[0][3].curvas, circuitos[0][3].prob_choque);
	
	printf("\n--- CAMPEONATO NI ---\n");
	printf("Monza:          %d vueltas | %.0f s/v | lluvia 1/%d | curvas 1/%d | peligro 1/%d\n",
		   circuitos[1][0].vueltas, circuitos[1][0].segundos, circuitos[1][0].probabilidad_lluvia, circuitos[1][0].curvas, circuitos[1][0].prob_choque);
	printf("Red Bull Ring:  %d vueltas | %.0f s/v | lluvia 1/%d | curvas 1/%d | peligro 1/%d\n",
		   circuitos[1][1].vueltas, circuitos[1][1].segundos, circuitos[1][1].probabilidad_lluvia, circuitos[1][1].curvas, circuitos[1][1].prob_choque);
	printf("Jeddah:         %d vueltas | %.0f s/v | lluvia 1/%d | curvas 1/%d | peligro 1/%d\n",
		   circuitos[1][2].vueltas, circuitos[1][2].segundos, circuitos[1][2].probabilidad_lluvia, circuitos[1][2].curvas, circuitos[1][2].prob_choque);
	printf("Bahrain:        %d vueltas | %.0f s/v | lluvia 1/%d | curvas 1/%d | peligro 1/%d\n",
		   circuitos[1][3].vueltas, circuitos[1][3].segundos, circuitos[1][3].probabilidad_lluvia, circuitos[1][3].curvas, circuitos[1][3].prob_choque);
	
	printf("\n--- CAMPEONATO NO ---\n");
	printf("Monaco:         %d vueltas | %.0f s/v | lluvia 1/%d | curvas 1/%d | peligro 1/%d\n",
		   circuitos[2][0].vueltas, circuitos[2][0].segundos, circuitos[2][0].probabilidad_lluvia, circuitos[2][0].curvas, circuitos[2][0].prob_choque);
	printf("Marina Bay:     %d vueltas | %.0f s/v | lluvia 1/%d | curvas 1/%d | peligro 1/%d\n",
		   circuitos[2][1].vueltas, circuitos[2][1].segundos, circuitos[2][1].probabilidad_lluvia, circuitos[2][1].curvas, circuitos[2][1].prob_choque);
	printf("Hungaroring:    %d vueltas | %.0f s/v | lluvia 1/%d | curvas 1/%d | peligro 1/%d\n",
		   circuitos[2][2].vueltas, circuitos[2][2].segundos, circuitos[2][2].probabilidad_lluvia, circuitos[2][2].curvas, circuitos[2][2].prob_choque);
	printf("Interlagos:     %d vueltas | %.0f s/v | lluvia 1/%d | curvas 1/%d | peligro 1/%d\n",
		   circuitos[2][3].vueltas, circuitos[2][3].segundos, circuitos[2][3].probabilidad_lluvia, circuitos[2][3].curvas, circuitos[2][3].prob_choque);
	printf("\n");
}

/* ================================================================
MODULO: TRANSFERIR SALDO
================================================================ */

void transferir_saldo(float *Fondos) {
	float monto;
	char tarjeta[16];
	printf("\n========== TRANSFERIR SALDO ==========\n");
	printf("Saldo actual: $%.2f\n", *Fondos);
	printf("Ingrese el monto a depositar: $");
	scanf("%f", &monto);
	printf("Ingrese su número de tarjeta de débito/crédito: ");
	capturar_tarjeta(tarjeta);
	printf("Tarjeta aceptada. Procediendo con el deposito...\n");
	fflush(stdin);
	if (monto > 0) {
		*Fondos += monto;
		printf("Deposito exitoso. Nuevo saldo: $%.2f\n", *Fondos);
	} else {
		printf("Monto invalido.\n");
	}
}

/*=================================================================
ALGORITMO PARA VALIDAR LA TARJETA
===================================================================*/
void capturar_tarjeta(char tarjeta[16]) {
	int valida = 0;
	while (!valida) {
		printf("Ingrese su numero de tarjeta (16 digitos): ");
		fgets(tarjeta, 20, stdin);
		tarjeta[strcspn(tarjeta, "\n")] = '\0';
		
		int len = strlen(tarjeta);
		valida = 1;
		
		if (len != 16) {
			printf("La tarjeta debe tener 16 digitos. Intente de nuevo.\n");
			valida = 0;
			continue;
		}
		
		for (int i = 0; i < len; i++) {
			if (!isdigit(tarjeta[i])) {
				printf("La tarjeta solo debe contener numeros. Intente de nuevo.\n");
				valida = 0;
				break;
			}
		}
	}
}

/* ================================================================
MODULO DE APUESTAS (integrado desde MODULO_APUESTAS.c)
Adaptado para usar el arreglo global pilotos[]
================================================================ */

void cancelar_apuesta(int *PilotosApostados, float *Fondos) {
	int op;
	puts("Indica que piloto quieres cancelar su apuesta (numero de piloto):");
	
	while (1) {
		puts("<======================================================>");
		printf("Piloto: ");
		scanf("%d", &op);
		op -= 1;
		
		if (op >= 0 && op <= 21) {
			if (pilotos[op].Apuesta != 0.0) {
				printf("Piloto seleccionado: %s\n", pilotos[op].nombre_p);
				puts("Descartando apuesta y regresando el dinero...");
				*Fondos += pilotos[op].Apuesta;
				pilotos[op].Apuesta = 0.0;
				*PilotosApostados -= 1;
				printf("Saldo: %.2f\n", *Fondos);
				break;
			} else {
				puts("Ese piloto no tiene ningun monto apostado.");
			}
		} else {
			puts("Ese piloto no existe, vuelve a escribirlo.");
		}
	}
}

void proceso_apuesta(int opc2, float *Fondos, int *PilotosApostados) {
	float Apuesta2 = 0;
	int   opc = 0, opc3 = -1;
	
	puts("<==================Caja de apuesta==================>");
	
	if (*PilotosApostados == 4) {
		puts("Cantidad maxima de pilotos alcanzada. Elimina o modifica alguna apuesta.");
		puts("(1.-Eliminar apuesta) (2.-Regresar al modulo)");
		
		while (1) {
			scanf("%d", &opc3);
			fflush(stdin);
			switch (opc3) {
			case 1:
				cancelar_apuesta(PilotosApostados, Fondos);
				proceso_apuesta(opc2, Fondos, PilotosApostados);
				return;
			case 2:
				puts("Regresando al modulo...");
				return;
			default:
				puts("Opcion no valida, vuelve a elegir.");
				break;
			}
		}
	}
	
	puts("Selecciona un piloto para apostar (-1 para cerrar):");
	
	while (opc != -1) {
		if (*PilotosApostados == 4) {
			printf("\nLIMITE DE PILOTOS ALCANZADO, REGRESANDO AL MENU DE APUESTAS...\n\n");
			break;
		}
		
		printf("\n<> Piloto #: ");
		scanf("%d", &opc);
		fflush(stdin);
		
		if (opc > 0 && opc <= 22) {
			opc -= 1;
			
			printf("Piloto seleccionado: %s\n", pilotos[opc].nombre_p);
			printf("Usa un valor negativo para reducir la apuesta.\n");
			printf("<=========================================>\n");
			
			while (1) {
				printf("\nApuesta: ");
				scanf("%f", &Apuesta2);
				fflush(stdin);
				
				if (Apuesta2 > *Fondos) {
					printf("\nFondos insuficientes. Reduce tu apuesta o recarga dinero.\n");
					printf("(1.-Reducir apuesta) (2.-Regresar al menu): ");
					opc2 = 0;
					while (opc2 != 1 && opc2 != 2) {
						scanf("%d", &opc2);
						fflush(stdin);
					}
					if (opc2 == 2) break;
					
				} else if ((Apuesta2 <= 0 && (pilotos[opc].Apuesta + Apuesta2) < 0) || Apuesta2 == 0) {
					printf("El monto debe ser distinto de cero y no dejar apuesta negativa.\n");
					
				} else {
					if (pilotos[opc].Apuesta == 0.0 && Apuesta2 > 0)
						*PilotosApostados += 1;
					
					pilotos[opc].Apuesta += Apuesta2;
					*Fondos -= Apuesta2;
					
					if (pilotos[opc].Apuesta == 0.0)
						*PilotosApostados -= 1;
					
					printf("\nApuesta realizada!\n");
					printf("Saldo sobrante: $%.2f\n", *Fondos);
					printf("Pilotos apostados: %d de 4\n", *PilotosApostados);
					break;
				}
			}
			
		} else if (opc != -1) {
			puts("Opcion no valida, vuelve a escribir.");
		}
		
		if (opc2 == 2) break;
	}
}

void Impresion_de_pilotos(float Fondos, float Record) {
	puts("<=========================LISTA DE PILOTOS========================>");
	puts("|        PILOTO         |    APUESTA    |VICTORIAS|");
	
	for (int h = 0; h < 22; h++) {
		if (h > 8)
			printf("|(%d)%-19s|%-15.2f|%-9d|\n", h+1, pilotos[h].nombre_p, pilotos[h].Apuesta, pilotos[h].Victorias);
		else
			printf("|(%d)%-20s|%-15.2f|%-9d|\n", h+1, pilotos[h].nombre_p, pilotos[h].Apuesta, pilotos[h].Victorias);
	}
	printf("\n<=================================================================>\n");
	printf("SALDO: $%.2f\n", Fondos);
	printf("RECORD DE GANANCIA: $%.2f\n\n", Record);
}

void Modulo_de_apuestas(float *Fondos, float *Record, int *PilotosApostados) {
	int opc1 = -1, opc2 = 0;
	
	Impresion_de_pilotos(*Fondos, *Record);
	
	while (opc1 != 3) {
		opc1 = -1; opc2 = 0;
		puts("<====MENU DEL MODULO DE APUESTAS====>");
		puts("(1.-Visualizar pilotos) (2.-Apostar/modificar) (3.-Cerrar modulo)");
		
		while (opc1 <= 0 || opc1 > 3) {
			printf("Opcion: ");
			scanf("%d", &opc1);
			fflush(stdin);
			
			switch (opc1) {
			case 1:
				Impresion_de_pilotos(*Fondos, *Record);
				break;
			case 2:
				proceso_apuesta(opc2, Fondos, PilotosApostados);
				break;
			case 3:
				puts("Cerrando modulo de apuestas...");
				break;
			default:
				puts("Opcion no valida, repitelo.");
			}
			
			if (opc1 >= 1 && opc1 <= 3) break;
		}
	}
}

/* ================================================================
MODULO DE SIMULACION (integrado desde simulacion.c)
================================================================ */

void simular_piloto(int campeonato, int carrera, int idx) {
	struct piloto *p = &pilotos[idx];
	
	if (p->eliminado) return;
	
	float vuelta = circuitos[campeonato][carrera].segundos;
	int   curvas = circuitos[campeonato][carrera].curvas;
	int   profit = circuitos[campeonato][carrera].profit;
	int   riesgo = circuitos[campeonato][carrera].prob_choque;
	
	/* Velocidad segun nivel */
	switch (p->nivel) {
	case 10: p->tiempo_carrera += vuelta + (rand() % 301) / 1000.0;         break;
	case 9:  p->tiempo_carrera += vuelta + (rand() % 301 + 500)  / 1000.0;  break;
	case 8:  p->tiempo_carrera += vuelta + (rand() % 301 + 1000) / 1000.0;  break;
	case 7:  p->tiempo_carrera += vuelta + (rand() % 301 + 1500) / 1000.0;  break;
	case 6:  p->tiempo_carrera += vuelta + (rand() % 301 + 2000) / 1000.0;  break;
	case 5:  p->tiempo_carrera += vuelta + (rand() % 301 + 2500) / 1000.0;  break;
	case 4:  p->tiempo_carrera += vuelta + (rand() % 301 + 3000) / 1000.0;  break;
	case 3:  p->tiempo_carrera += vuelta + (rand() % 301 + 3500) / 1000.0;  break;
	case 2:  p->tiempo_carrera += vuelta + (rand() % 301 + 4000) / 1000.0;  break;
	case 1:  p->tiempo_carrera += vuelta + (rand() % 301 + 4250) / 1000.0;  break;
	}
	
	/* Concentracion */
	if (p->concentracion_cooldown > 0) {
		p->concentracion_cooldown--;
	} else if (p->concentracion_activa == 0) {
		if ((rand() % (p->concentracion * 200)) == 0) {
			p->concentracion_activa   = 5;
			p->concentracion_cooldown = 60;
			printf("  >> %s se ha CONCENTRADO!\n", p->nombre_p);
		}
	} else {
		p->concentracion_activa--;
	}
	
	/* Manejo en curvas */
	if ((rand() % curvas) == 0) {
		int tiro   = rand() % 100 + 1;
		int umbral = (int)((1.0 / p->manejo) * 100);
		
		if (p->concentracion_activa > 0) {
			if (tiro <= umbral)
				p->tiempo_carrera -= (rand() % 400 + 100) / 1000.0;
		} else {
			if (tiro <= umbral)
				p->tiempo_carrera -= (rand() % 400 + 100) / 1000.0;
			else
				p->tiempo_carrera += (rand() % 3000 + 1000) / 1000.0;
		}
	}
	
	/* Profit / riesgo de choque */
	if ((rand() % profit) == 0) {
		if ((rand() % (int)(1.0 / p->agresividad * 1000)) == 0) {
			p->tiempo_carrera -= (rand() % 600 + 200) / 1000.0;
			
			int riesgo_real = riesgo;
			if (p->concentracion_activa > 0) riesgo_real *= 2;
			
			if ((rand() % riesgo_real) == 0) {
				printf("  >> %s ha CHOCADO y abandona la carrera!\n", p->nombre_p);
				p->tiempo_carrera = 999999.0;
				p->eliminado = 1;
			}
		}
	}
}

void ordenar(int orden[22]) {
	int i, j, tmp;
	for (i = 0; i < 21; i++) {
		j = i + 1;
		while (j < 22) {
			if (pilotos[orden[i]].tiempo_carrera > pilotos[orden[j]].tiempo_carrera) {
				tmp      = orden[j];
				orden[j] = orden[i];
				orden[i] = tmp;
			}
			j++;
		}
	}
}

void mostrar_clasificacion(void) {
	/* Clasificacion acumulada del campeonato por puntos */
	int orden_pts[22];
	for (int i = 0; i < 22; i++) orden_pts[i] = i;
	
	/* Ordenar por puntos (burbuja descendente) */
	for (int i = 0; i < 21; i++) {
		int j = i + 1;
		while (j < 22) {
			if (pilotos[orden_pts[i]].puntos.add < pilotos[orden_pts[j]].puntos.add) {
				int tmp = orden_pts[j];
				orden_pts[j] = orden_pts[i];
				orden_pts[i] = tmp;
			}
			j++;
		}
	}
	
	printf("\n========== CLASIFICACION DEL CAMPEONATO ==========\n");
	printf("%-4s %-20s %-25s %-6s\n", "POS", "PILOTO", "EQUIPO", "PTS");
	printf("----------------------------------------------------------\n");
	for (int i = 0; i < 22; i++) {
		int idx = orden_pts[i];
		printf("%-4d %-20s %-25s %-6d\n",
			   i+1, pilotos[idx].nombre_p, pilotos[idx].scuderia, pilotos[idx].puntos.add);
	}
	printf("\n");
}

/* --- Logica de resolucion de apuestas al terminar una carrera --- */
/* TODO: definir multiplicadores de pago con el equipo */
static void resolver_apuestas(int orden[22], float *Fondos, float *Record) {
	printf("\n========== RESULTADO DE APUESTAS ==========\n");
	
	for (int i = 0; i < 22; i++) {
		if (pilotos[i].Apuesta > 0.0) {
			/* Buscar posicion del piloto en el orden */
			int pos = -1;
			for (int k = 0; k < 22; k++) {
				if (orden[k] == i) { pos = k; break; }
			}
			if (pos == 0) {
				/* Gano: pago simple 2x (TODO: ajustar segun nivel/cuota) */
				float ganancia = pilotos[i].Apuesta * 2.0;
				printf("  %s GANO! Recuperas $%.2f\n", pilotos[i].nombre_p, ganancia);
				*Fondos += ganancia;
				if (ganancia > *Record) *Record = ganancia;
			} else {
				printf("  %s no gano (posicion %d). Pierdes $%.2f\n",
					   pilotos[i].nombre_p, pos+1, pilotos[i].Apuesta);
			}
			pilotos[i].Apuesta = 0.0; /* limpiar apuesta para la siguiente carrera */
		}
	}
}

void ejecutar_carrera(int indicador_campeonato, int carrera,
					  float *Fondos, float *Record, int *PilotosApostados) {
	/* Reiniciar tiempos y estado de pilotos */
	for (int j = 0; j < 22; j++) {
		pilotos[j].tiempo_carrera       = 0;
		pilotos[j].eliminado            = 0;
		pilotos[j].concentracion_activa = 0;
		pilotos[j].concentracion_cooldown = 0;
	}
	
	/* Lluvia */
	int lluvia = rand() % (circuitos[indicador_campeonato][carrera].probabilidad_lluvia + 1) + 1;
	if (lluvia == circuitos[indicador_campeonato][carrera].probabilidad_lluvia) {
		printf("\nAVISO: Llovera en esta carrera - tiempos aumentaran!\n");
		printf("(Pulsa Enter para continuar)\n");
		circuitos[indicador_campeonato][carrera].segundos += 8;
		fflush(stdin);
		getchar();
	}
	
	int orden[22];
	for (int i = 0; i < 22; i++) orden[i] = i;
	
	int total_vueltas = circuitos[indicador_campeonato][carrera].vueltas;
	
	/* --- Bucle de vueltas --- */
	for (int i = 0; i < total_vueltas; i++) {
		for (int j = 0; j < 22; j++) {
			simular_piloto(indicador_campeonato, carrera, j);
		}
		
		/* Impresion parcial cada 10 vueltas */
		if (i % 10 == 0) {
			ordenar(orden);
			pilotos[orden[0]].intervalo.minutos  = 0;
			pilotos[orden[0]].intervalo.segundos = 0.0;
			pilotos[orden[0]].brecha.minutos     = 0;
			pilotos[orden[0]].brecha.segundos    = 0.0;
			
			for (int k = 1; k < 22; k++) {
				float dif_i = pilotos[orden[k]].tiempo_carrera - pilotos[orden[k-1]].tiempo_carrera;
				pilotos[orden[k]].intervalo.minutos  = (int)(dif_i / 60);
				pilotos[orden[k]].intervalo.segundos = dif_i - pilotos[orden[k]].intervalo.minutos * 60;
				
				float dif_b = pilotos[orden[k]].tiempo_carrera - pilotos[orden[0]].tiempo_carrera;
				pilotos[orden[k]].brecha.minutos  = (int)(dif_b / 60);
				pilotos[orden[k]].brecha.segundos = dif_b - pilotos[orden[k]].brecha.minutos * 60;
			}
			
			printf("\n--- VUELTA %d DE %d ---\n", i+1, total_vueltas);
			printf("%-4s %-20s %-15s %-15s\n", "POS", "PILOTO", "INTERVALO", "BRECHA");
			printf("------------------------------------------------------------\n");
			for (int k = 0; k < 22; k++) {
				int idx = orden[k];
				if (k == 0)
					printf("%-4d %-20s %-15s %-15s\n", k+1, pilotos[idx].nombre_p, "LIDER", "LIDER");
				else
					printf("%-4d %-20s +%d:%06.3f       +%d:%06.3f\n",
						   k+1, pilotos[idx].nombre_p,
						   pilotos[idx].intervalo.minutos, pilotos[idx].intervalo.segundos,
						   pilotos[idx].brecha.minutos,    pilotos[idx].brecha.segundos);
			}
			Sleep(4000); // Detiene el programa por dos segundos para no arrojarle todas las impresiones al usuario
		}
	}
	
	/* --- Resultado final de la carrera --- */
	ordenar(orden);
	pilotos[orden[0]].intervalo.minutos  = 0;
	pilotos[orden[0]].intervalo.segundos = 0.0;
	pilotos[orden[0]].brecha.minutos     = 0;
	pilotos[orden[0]].brecha.segundos    = 0.0;
	
	for (int i = 1; i < 22; i++) {
		float dif_i = pilotos[orden[i]].tiempo_carrera - pilotos[orden[i-1]].tiempo_carrera;
		pilotos[orden[i]].intervalo.minutos  = (int)(dif_i / 60);
		pilotos[orden[i]].intervalo.segundos = dif_i - pilotos[orden[i]].intervalo.minutos * 60;
		
		float dif_b = pilotos[orden[i]].tiempo_carrera - pilotos[orden[0]].tiempo_carrera;
		pilotos[orden[i]].brecha.minutos  = (int)(dif_b / 60);
		pilotos[orden[i]].brecha.segundos = dif_b - pilotos[orden[i]].brecha.minutos * 60;
	}
	
	printf("\n========== RESULTADO FINAL - CARRERA %d ==========\n", carrera+1);
	printf("%-4s %-20s %-15s %-15s\n", "POS", "PILOTO", "INTERVALO", "BRECHA");
	printf("------------------------------------------------------------\n");
	for (int i = 0; i < 22; i++) {
		int idx = orden[i];
		if (i == 0)
			printf("%-4d %-20s %-15s %-15s\n", i+1, pilotos[idx].nombre_p, "LIDER", "LIDER");
		else
			printf("%-4d %-20s +%d:%06.3f       +%d:%06.3f\n",
				   i+1, pilotos[idx].nombre_p,
				   pilotos[idx].intervalo.minutos, pilotos[idx].intervalo.segundos,
				   pilotos[idx].brecha.minutos,    pilotos[idx].brecha.segundos);
	}
	
	/* Ganador */
	pilotos[orden[0]].Victorias++;
	
	/* Puntos F1 (top 10) */
	int pts_tabla[10] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
	for (int i = 0; i < 10; i++)
		pilotos[orden[i]].puntos.add += pts_tabla[i];
	
	/* Resolver apuestas si las hay */
	if (*PilotosApostados > 0)
		resolver_apuestas(orden, Fondos, Record);
	*PilotosApostados = 0;
	
	/* Quitar efecto lluvia */
	circuitos[indicador_campeonato][carrera].segundos -= 8;
	
	printf("\nPresiona Enter para continuar...\n");
	fflush(stdin);
	getchar();
}
					  
					  /* --- Simulacion: menu de campeonato y loop de carreras --- */
					  void simulacion(float *Fondos, float *Record, int *PilotosApostados) {
						  int opcion_campeonato, indicador_campeonato;
						  
						  printf("\n==================================================================\n");
						  printf("                        SIMULACION\n");
						  printf("==================================================================\n");
						  printf("Escoge el campeonato que quieres simular:\n");
						  printf("  1) CAMPEONATO NE  (Silverstone, Spa, Suzuka, Barcelona)\n");
						  printf("  2) CAMPEONATO NI  (Monza, Red Bull Ring, Jeddah, Bahrain)\n");
						  printf("  3) CAMPEONATO NO  (Monaco, Marina Bay, Hungaroring, Interlagos)\n");
						  printf("  4) Volver al menu principal\n");
						  printf("Opcion: ");
						  scanf("%d", &opcion_campeonato);
						  fflush(stdin);
						  
						  while (opcion_campeonato < 1 || opcion_campeonato > 4) {
							  printf("Opcion invalida. Ingresela nuevamente: ");
							  scanf("%d", &opcion_campeonato);
							  fflush(stdin);
						  }
						  
						  if (opcion_campeonato == 4) return;
						  
						  indicador_campeonato = opcion_campeonato - 1;
						  
						  /* Reiniciar puntos y victorias para el campeonato */
						  for (int i = 0; i < 22; i++) {
							  pilotos[i].puntos.add = 0;
							  pilotos[i].Victorias  = 0;
							  pilotos[i].Apuesta    = 0.0;
						  }
						  *PilotosApostados = 0;
						  
						  srand((unsigned int)time(NULL));
						  
						  /* --- Loop de las 4 carreras del campeonato --- */
						  for (int carrera = 0; carrera < 4; carrera++) {
							  printf("\n==================================================================\n");
							  printf("  CARRERA %d DE 4\n", carrera+1);
							  printf("==================================================================\n");
							  
							  /* 1.1.1 Desea apostar? */
							  int apostar = 0;
							  printf("Desea apostar antes de esta carrera? (1=Si / 2=No): ");
							  scanf("%d", &apostar);
							  fflush(stdin);
							  
							  if (apostar == 1) {
								  Modulo_de_apuestas(Fondos, Record, PilotosApostados);
							  }
							  
							  /* 1.1.2 y 1.1.3: Ejecucion + resultado */
							  ejecutar_carrera(indicador_campeonato, carrera, Fondos, Record, PilotosApostados);
							  
							  /* 1.1.4 Menu mini */
							  int mini = 0;
							  while (mini != 3) {
								  printf("\n--- MENU MINI ---\n");
								  printf("  1) Siguiente carrera\n");
								  printf("  2) Clasificacion de pilotos\n");
								  printf("  3) Salir al menu principal\n");
								  printf("Opcion: ");
								  scanf("%d", &mini);
								  fflush(stdin);
								  
								  switch (mini) {
								  case 1:
									  if (carrera == 3) {
										  printf("\nFin del campeonato. No hay mas carreras.\n");
										  mini = 3; /* fuerza salida del menu mini y del loop */
									  }
									  break;
								  case 2:
									  mostrar_clasificacion();
									  break;
								  case 3:
									  /* Salir rompe el loop de carreras tambien */
									  carrera = 4; /* valor centinela para salir del for externo */
									  break;
								  default:
									  printf("Opcion invalida.\n");
									  break;
								  }
								  
								  if (mini == 1 || mini == 3) break;
							  }
						  }
						  
						  /* 1.2 Resultado final del campeonato */
						  printf("\n==================================================================\n");
						  printf("          FIN DEL CAMPEONATO - CLASIFICACION FINAL\n");
						  printf("==================================================================\n");
						  mostrar_clasificacion();
						  
						  printf("\nPresiona Enter para volver al menu principal...\n");
						  fflush(stdin);
						  getchar();
					  }
					  
					  /* ================================================================
					  INICIALIZAR PILOTOS (desde simulacion.c, adaptado al struct unificado)
					  ================================================================ */
					  
					  void inicializar_pilotos(void) {
						  /* Inicializar apuestas y victorias a 0 */
						  for (int i = 0; i < 22; i++) {
							  pilotos[i].Apuesta  = 0.0;
							  pilotos[i].Victorias = 0;
							  pilotos[i].puntos.add = 0;
							  pilotos[i].eliminado  = 0;
							  pilotos[i].concentracion_activa   = 0;
							  pilotos[i].concentracion_cooldown = 0;
							  pilotos[i].tiempo_carrera = 0.0;
						  }
						  
						  pilotos[0].nivel = 9; strcpy(pilotos[0].nombre_p, "George Russell");    strcpy(pilotos[0].scuderia, "Mercedes AMG");        pilotos[0].agresividad=5;  pilotos[0].manejo=5;  pilotos[0].concentracion=5;
						  pilotos[1].nivel = 6; strcpy(pilotos[1].nombre_p, "Kimi Antonelli");    strcpy(pilotos[1].scuderia, "Mercedes AMG");        pilotos[1].agresividad=3;  pilotos[1].manejo=9;  pilotos[1].concentracion=5;
						  pilotos[2].nivel =10; strcpy(pilotos[2].nombre_p, "Charles Leclerc");   strcpy(pilotos[2].scuderia, "Scuderia Ferrari");    pilotos[2].agresividad=5;  pilotos[2].manejo=5;  pilotos[2].concentracion=4;
						  pilotos[3].nivel = 9; strcpy(pilotos[3].nombre_p, "Lewis Hamilton");    strcpy(pilotos[3].scuderia, "Scuderia Ferrari");    pilotos[3].agresividad=7;  pilotos[3].manejo=3;  pilotos[3].concentracion=3;
						  pilotos[4].nivel =10; strcpy(pilotos[4].nombre_p, "Lando Norris");      strcpy(pilotos[4].scuderia, "McLaren Mastercard"); pilotos[4].agresividad=5;  pilotos[4].manejo=5;  pilotos[4].concentracion=4;
						  pilotos[5].nivel = 9; strcpy(pilotos[5].nombre_p, "Oscar Piastri");     strcpy(pilotos[5].scuderia, "McLaren Mastercard"); pilotos[5].agresividad=8;  pilotos[5].manejo=3;  pilotos[5].concentracion=4;
						  pilotos[6].nivel =10; strcpy(pilotos[6].nombre_p, "Max Verstappen");    strcpy(pilotos[6].scuderia, "Red Bull Racing");    pilotos[6].agresividad=4;  pilotos[6].manejo=3;  pilotos[6].concentracion=3;
						  pilotos[7].nivel = 4; strcpy(pilotos[7].nombre_p, "Isaac Hadjar");      strcpy(pilotos[7].scuderia, "Red Bull Racing");    pilotos[7].agresividad=3;  pilotos[7].manejo=11; pilotos[7].concentracion=6;
						  pilotos[8].nivel = 8; strcpy(pilotos[8].nombre_p, "Pierre Gasly");      strcpy(pilotos[8].scuderia, "BWT Alpine");         pilotos[8].agresividad=6;  pilotos[8].manejo=6;  pilotos[8].concentracion=5;
						  pilotos[9].nivel = 5; strcpy(pilotos[9].nombre_p, "Franco Colapinto");  strcpy(pilotos[9].scuderia, "BWT Alpine");         pilotos[9].agresividad=3;  pilotos[9].manejo=11; pilotos[9].concentracion=6;
						  pilotos[10].nivel= 5; strcpy(pilotos[10].nombre_p,"Oliver Bearman");    strcpy(pilotos[10].scuderia,"TGR Haas");           pilotos[10].agresividad=3; pilotos[10].manejo=10;pilotos[10].concentracion=6;
						  pilotos[11].nivel= 7; strcpy(pilotos[11].nombre_p,"Esteban Ocon");      strcpy(pilotos[11].scuderia,"TGR Haas");           pilotos[11].agresividad=4; pilotos[11].manejo=8; pilotos[11].concentracion=6;
						  pilotos[12].nivel= 5; strcpy(pilotos[12].nombre_p,"Liam Lawson");       strcpy(pilotos[12].scuderia,"Racing Bulls");       pilotos[12].agresividad=4; pilotos[12].manejo=10;pilotos[12].concentracion=6;
						  pilotos[13].nivel= 2; strcpy(pilotos[13].nombre_p,"Arvid Lindblad");    strcpy(pilotos[13].scuderia,"Racing Bulls");       pilotos[13].agresividad=2; pilotos[13].manejo=13;pilotos[13].concentracion=7;
						  pilotos[14].nivel= 8; strcpy(pilotos[14].nombre_p,"Carlos Sainz");      strcpy(pilotos[14].scuderia,"Atlassian Williams"); pilotos[14].agresividad=7; pilotos[14].manejo=5; pilotos[14].concentracion=5;
						  pilotos[15].nivel= 7; strcpy(pilotos[15].nombre_p,"Alex Albon");        strcpy(pilotos[15].scuderia,"Atlassian Williams"); pilotos[15].agresividad=5; pilotos[15].manejo=6; pilotos[15].concentracion=6;
						  pilotos[16].nivel= 6; strcpy(pilotos[16].nombre_p,"Nico Hulkenberg");   strcpy(pilotos[16].scuderia,"Audi Revolut");       pilotos[16].agresividad=9; pilotos[16].manejo=5; pilotos[16].concentracion=6;
						  pilotos[17].nivel= 4; strcpy(pilotos[17].nombre_p,"Gabriel Bortoleto"); strcpy(pilotos[17].scuderia,"Audi Revolut");       pilotos[17].agresividad=5; pilotos[17].manejo=9; pilotos[17].concentracion=7;
						  pilotos[18].nivel= 7; strcpy(pilotos[18].nombre_p,"Sergio Perez");      strcpy(pilotos[18].scuderia,"Cadillac F1");        pilotos[18].agresividad=7; pilotos[18].manejo=7; pilotos[18].concentracion=6;
						  pilotos[19].nivel= 6; strcpy(pilotos[19].nombre_p,"Valtteri Bottas");   strcpy(pilotos[19].scuderia,"Cadillac F1");        pilotos[19].agresividad=10;pilotos[19].manejo=6; pilotos[19].concentracion=7;
						  pilotos[20].nivel= 8; strcpy(pilotos[20].nombre_p,"Fernando Alonso");   strcpy(pilotos[20].scuderia,"Aston Martin");      pilotos[20].agresividad=8; pilotos[20].manejo=2; pilotos[20].concentracion=2;
						  pilotos[21].nivel= 1; strcpy(pilotos[21].nombre_p,"Lance Stroll");      strcpy(pilotos[21].scuderia,"Aston Martin");      pilotos[21].agresividad=4; pilotos[21].manejo=14;pilotos[21].concentracion=10;
					  }
