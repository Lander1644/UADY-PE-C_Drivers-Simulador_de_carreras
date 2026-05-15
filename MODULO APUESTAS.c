#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>

struct lap_time{ // Estructura para registrar los tiempos en las carreras
	int minuts;
	float seconds;
};
struct championship{ //Estructura para registrar los puntos de cada piloto
	int australia;
	int china;
	int japon;
	int miami;
	int canada;
	int monaco;
	int add;
};
struct driver{ //Estructura para registrar los datos de cada piloto
	int level;
	char name[20];
	char team[25];
	float race_time;
	float Apuesta;//Añadimos dos variables mas para la estructura drivers, cuales son Apuesta como lo apostado por el jugador y Victorias para definir cuantas victorias ha tenido durante el proceso.
	int Victorias;
	struct lap_time interval;
	struct lap_time gap;
	struct championship points;
	
}drivers[22];

struct circuit{
	float seconds;
	int rain_probability;
	int laps;
};

//Funcion para cancelar lo apostado en un piloto, directamente lo inicializa a 0.
void cancelar_apuesta(struct driver drive[22], int *PilotosApostados, float *Fondos){
	int op;
	
	puts("Mencioname que piloto quieres cancelar su apuesta");
	
	while(1){
		puts("<======================================================>");
		printf("Piloto: ");
		scanf("%d", &op);
		op -=1;
		
		if(op >= 0 && op <= 21){
			if(drive[op].Apuesta != 0.0){
				printf("Piloto seleccionado: %s\n", drive[op].name);
				puts("Descartando apuesta y regresando el dinero...");
				*Fondos += drive[op].Apuesta;
				drive[op].Apuesta = 0.0;
				*PilotosApostados -=1;
				
				printf("Saldo: %.2f \n", *Fondos);
				
				break;
				
			}else puts("Ese piloto no tiene ningun monto apostado, elija a uno con monto apostado");
		}else puts("Ese piloto no existe, vuelve a escribirlo");
	}
}

void proceso_apuesta(struct driver drive[22], int opc2, float *Fondos, int *PilotosApostados)
{
	float Apuesta2=0;
	int opc=0, opc3=-1;
	
	puts("<==================Caja de apuesta==================>");
	if(*PilotosApostados != 4){
		puts("Selecciona un jugador por apostar (-1 Para cerrar)");
		
	}else{
		//En dado caso de que la cantidad de los pilotos apostados ha llegado al máximo
		puts("Cantidad máxima de pilotos alcanzado elimina o modifica la apuesta algún piloto con monto apostado, o regresa al modulo");
		puts("(1.-eliminar apuesta)(2.-Regresar al modulo)");
		
		while(opc != 2){
			scanf("%d", &opc3);
			switch(opc3){
			case 1:
				cancelar_apuesta(drive, PilotosApostados, Fondos);
				proceso_apuesta(drive, opc2, Fondos, PilotosApostados);
				break;
			case 2:
				puts("Regresando al modulo...");
				break;
			default:
				puts("Esa opcion no existe, vuelve a elegir");
				break;
			}if(opc3 == 2 || opc3 == 1) break;
		}
	}
	
	while(opc != -1){
		if(*PilotosApostados != 4){
			printf("\n<>Jugador: ");
			scanf("%d", &opc);
		}else {
			printf("\nLIMITE DE PILOTOS ALCANZADO, REGRESANDO AL MENU DE APUESTAS...\n\n"); 
			break;
		}
		
		if(opc > 0 && opc <= 22){
			opc-=1;
			
			printf("Jugador seleccionado: %s \n", drive[opc].name);
			printf("Reduces la apuesta con '-'\n");
			printf("<=========================================>\n");
			
			while(1){
				printf("\nApuesta: ");
				scanf("%f", &Apuesta2);//Insertamos el valor de la apuesta en una variable con valor temporal: apuesta2
				
				if(Apuesta2 > *Fondos){//if para la excepción de cuando el saldo no es suficiente para la apuesta.
					printf("\n<==========================================================>");
					printf("\nFondos insuficiente, reduce tu apuesta o recarga dinero");
					
					while(opc2 != 1 && opc2 != 2){
						
						printf("\n(1.-Reducir apuesta)(2.-regresar al menú): "); 
						scanf("%d", &opc2);
						switch(opc2){
						case 1:
							break;
						case 2:
							printf("\nRegresando al menu...");
							break;
						default:
							printf("\nNo existe esa opción, vuelve a escribir");
							break;
						}
					}if(opc2 == 2) break;
					
				}else if((Apuesta2 <= 0 && (drive[opc].Apuesta + Apuesta2) < 0) || Apuesta2 == 0){
					printf("El monto debe ser positivo o mayor a cero, vuelve a escribir\n");
					printf("<===========================================================>");
					
				}else{
					if (drive[opc].Apuesta == 0.0 && Apuesta2 > 0) {
						*PilotosApostados += 1;
					}
					
					drive[opc].Apuesta += Apuesta2; 
					*Fondos -= Apuesta2;
					
					if(drive[opc].Apuesta == 0.0){
						*PilotosApostados -= 1;
					}
					
					printf("\n¡Apuesta realizada!\n");
					printf("<===========================>\n");
					printf("Saldo Sobrante: %.2f \n", *Fondos);
					printf("Pilotos apostados: %d de 4\n", *PilotosApostados);
					printf("<===========================>\n");
					
					break;
				}
				
			}
		}else if(opc != -1) puts("Esa opción no existe, vuelve a escribir... ");
		
		if(opc2 == 2) break;
	}
}

//Funcion de impresion de los pilotos y lo que se ha apostado antes de la carrera.
void Impresion_de_pilotos(struct driver drive[22], float Fondos, float Record){
	puts("<=========================LISTA DE PILOTOS========================>");
	puts("|        PILOTO         |    APUESTA    |VICTORIAS|");
		
	for(int h = 0; h < 22; h++)
	{
		if(h > 8)printf("|(%d)%-19s|%-15.2f|%-9d|\n", h+1, drive[h].name, drive[h].Apuesta, drive[h].Victorias);
		else printf("|(%d)%-20s|%-15.2f|%-9d|\n", h+1, drive[h].name, drive[h].Apuesta, drive[h].Victorias);
	} 
	printf("\n<=================================================================>\n");
	printf("SALDO: %.2f \n", Fondos);
	printf("Record DE GANANCIA: %.2f \n\n\n", Record);
}

void Modulo_de_apuestas(struct driver drive[22], float *Fondos, float *Record, int *PilotosApostados){
	
	Impresion_de_pilotos(drive, *Fondos, *Record);
	int opc1 = -1, opc2=0;
	
	while(opc1 != 3 && opc2 != 2){
		opc1 = -1, opc2=0;
		puts("<====MENU DEL MODULO DE APUESTAS====>");
		puts("Digitaliza qué proceso quieres hacer: ");
		puts("(1.-Visualizar jugadores)(2.-Sumar - restar apuesta)(3.-Cerrar modulo)");
		
		while(opc1 <= 0 || opc1 > 3){
			printf("Opción: ");
			scanf("%d", &opc1);
		
			switch(opc1)//Las opciones del modulo contienen subfunciones.
			{
			case 1:
				Impresion_de_pilotos(drive, *Fondos, *Record);
				break;
			case 2:
				proceso_apuesta(drive, opc2, Fondos, PilotosApostados);
				break;
			case 3:
				puts("Cerrando Proceso...");
				break;
			default:
				puts("Esa opcion no existe, repitelo...");
			}
			
			if(opc1 > 0 && opc1 <= 3) break;
		}
	}
	
	puts("Presiona cualquier tecla para continuar...");
	getch();
	
}
	
int main(int argc, char *argv[]) {
	float Record = 0;
	int PilotosApostados = 0;
	float Fondos = 10000;
	for(int i = 0; i < 22; i++)//Inicialización de las cantidades de las apuestas
	{
		drivers[i].Apuesta = 0;
	}
	
	
	/*<---------- Información de los pilotos ---------->*/
	drivers[0].level = 10;
	strcpy(drivers[0].name, "George Russel");
	strcpy(drivers[0].team, "Mercedes AMG");
	drivers[0].race_time = 0;
	drivers[0].points.add = 0;
	
	drivers[1].level = 10;
	strcpy(drivers[1].name, "Kimi Antonelli");
	strcpy(drivers[1].team, "Mercedes AMG");
	drivers[1].race_time = 0;
	drivers[1].points.add = 0;
	
	drivers[2].level = 10;
	strcpy(drivers[2].name, "Charles Leclerc");
	strcpy(drivers[2].team, "Scuderia Ferrari");
	drivers[2].race_time = 0;
	drivers[2].points.add = 0;
	
	drivers[3].level = 10;
	strcpy(drivers[3].name, "Lewis Hamilton");
	strcpy(drivers[3].team, "Scuderia Ferrari");
	drivers[3].race_time = 0;
	drivers[3].points.add = 0;
	
	drivers[4].level = 9;
	strcpy(drivers[4].name, "Lando Norris");
	strcpy(drivers[4].team, "McLaren Mastercard");
	drivers[4].race_time = 0;
	drivers[4].points.add = 0;
	
	drivers[5].level = 9;
	strcpy(drivers[5].name, "Oscar Piastri");
	strcpy(drivers[5].team, "McLaren Mastercard");
	drivers[5].race_time = 0;
	drivers[5].points.add = 0;
	
	drivers[6].level = 8;
	strcpy(drivers[6].name, "Max Verstappen");
	strcpy(drivers[6].team, "Red Bull Racing");
	drivers[6].race_time = 0;
	drivers[6].points.add = 0;
	
	drivers[7].level = 8;
	strcpy(drivers[7].name, "Isaac Hadjar");
	strcpy(drivers[7].team, "Red Bull Racing");
	drivers[7].race_time = 0;
	drivers[7].points.add = 0;
	
	drivers[8].level = 7;
	strcpy(drivers[8].name, "Pierre Gasly");
	strcpy(drivers[8].team, "BWT Alpine");
	drivers[8].race_time = 0;
	drivers[8].points.add = 0;
	
	drivers[9].level = 7;
	strcpy(drivers[9].name, "Franco Colapinto");
	strcpy(drivers[9].team, "BWT Alpine");
	drivers[9].race_time = 0;
	drivers[9].points.add = 0;
	
	drivers[10].level = 6;
	strcpy(drivers[10].name, "Oliver Bearman");
	strcpy(drivers[10].team, "TGR Haas");
	drivers[10].race_time = 0;
	drivers[10].points.add = 0;
	
	drivers[11].level = 6;
	strcpy(drivers[11].name, "Esteban Ocon");
	strcpy(drivers[11].team, "TGR Haas");
	drivers[11].race_time = 0;
	drivers[11].points.add = 0;
	
	drivers[12].level = 5;
	strcpy(drivers[12].name, "Liam Lawson");
	strcpy(drivers[12].team, "Racin Bulls");
	drivers[12].race_time = 0;
	drivers[12].points.add = 0;
	
	drivers[13].level = 5;
	strcpy(drivers[13].name, "Arvid Lindblad");
	strcpy(drivers[13].team, "Racing Bulls");
	drivers[13].race_time = 0;
	drivers[13].points.add = 0;
	
	drivers[14].level = 4;
	strcpy(drivers[14].name, "Carlos Sainz");
	strcpy(drivers[14].team, "Atlassian Williams");
	drivers[14].race_time = 0;
	drivers[14].points.add = 0;
	
	drivers[15].level = 4;
	strcpy(drivers[15].name, "Alex Albon");
	strcpy(drivers[15].team, "Atlassian Williams");
	drivers[15].race_time = 0;
	drivers[15].points.add = 0;
	
	drivers[16].level = 3;
	strcpy(drivers[16].name, "Nico Hulkenberg");
	strcpy(drivers[16].team, "Audi Revolut");
	drivers[16].race_time = 0;
	drivers[16].points.add = 0;
	
	drivers[17].level = 3;
	strcpy(drivers[17].name, "Garbiel Bortoleto");
	strcpy(drivers[17].team, "Audi Revolut");
	drivers[17].race_time = 0;
	drivers[17].points.add = 0;
	
	drivers[18].level = 2;
	strcpy(drivers[18].name, "Sergio Perez");
	strcpy(drivers[18].team, "Cadillac F1");
	drivers[18].race_time = 0;
	drivers[18].points.add = 0;
	
	drivers[19].level = 2;
	strcpy(drivers[19].name, "Valteri Bottas");
	strcpy(drivers[19].team, "Cadillac F1");
	drivers[19].race_time = 0;
	drivers[19].points.add = 0;
	
	drivers[20].level = 1;
	strcpy(drivers[20].name, "Fernando Alonso");
	strcpy(drivers[20].team, "Aston Martin");
	drivers[20].race_time = 0;
	drivers[20].points.add = 0;
	
	drivers[21].level = 1;
	strcpy(drivers[21].name, "Lance Stroll");
	strcpy(drivers[21].team, "Aston Martin");
	drivers[21].race_time = 0;
	drivers[21].points.add = 0;
	
	//Funcion del modulo de apuestas.
	Modulo_de_apuestas(drivers, &Fondos, &Record, &PilotosApostados);
	
	
	return 0;
}

