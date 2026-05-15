/*------------------------------------------------------------------------------------
Programa fuente: Race_algorithm
Compilador a utilizar: Zinjai (solo para prototipar)
Programador: <L�pez Sansores Lander Antonio>
Descripci�n: desarrollo del algoritmo principal de ejecuci�n de las carreras simuladas
Fecha de creaci�n: 10/05/2026
Versi�n: 1.0.
---------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

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
	char team[10];
	float race_time;
	struct lap_time interval;
	struct lap_time gap;
	struct championship points;
	
}drivers[22];

struct circuit{
	float seconds;
	int rain_probability;
	int laps;
};

/*<---------- Informaci�n de los circuitos ---------->*/
struct circuit monaco = {70,4,72}; // Circuito de prueba

int main() {
	
	/*<---------- Informaci�n de los pilotos ---------->*/
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
	
	
	srand(time(NULL));
	float lap = monaco.seconds;
	int rain = rand() % (monaco.rain_probability + 1) + 1;
	if (rain == monaco.rain_probability)
		lap += 8;
	for (int i = 0; i < monaco.laps; i++) {
		for (int j = 0; j < 22; j++) {
			switch (drivers[j].level) {
				case 10: drivers[j].race_time += lap + (rand() % 301) / 1000.0; break;
				case 9:  drivers[j].race_time += lap + (rand() % 251 + 200) / 1000.0; break;
				case 8:  drivers[j].race_time += lap + (rand() % 251 + 350) / 1000.0; break;
				case 7:  drivers[j].race_time += lap + (rand() % 251 + 500) / 1000.0; break;
				case 6:  drivers[j].race_time += lap + (rand() % 251 + 650) / 1000.0; break;
				case 5:  drivers[j].race_time += lap + (rand() % 251 + 800) / 1000.0; break;
				case 4:  drivers[j].race_time += lap + (rand() % 251 + 950) / 1000.0; break;
				case 3:  drivers[j].race_time += lap + (rand() % 251 + 1100) / 1000.0; break;
				case 2:  drivers[j].race_time += lap + (rand() % 251 + 1250) / 1000.0; break;
				case 1:  drivers[j].race_time += lap + (rand() % 251 + 1400) / 1000.0; break;
			}
		}
	}
	for (int i = 0; i < 22; i++) {
		drivers[i].race_time /= 60;
		printf("%s\t\t%.3f\n", drivers[i].name, drivers[i].race_time);
	}
	return 0;
}



