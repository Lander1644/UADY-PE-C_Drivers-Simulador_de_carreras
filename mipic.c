/*------------------------------------------------------------------------------------
Programa fuente: Race_algorithm
Compilador a utilizar: Zinjai (solo para prototipar)
Programador: <López Sansores Lander Antonio>
			 <Salazar De La Cruz Canul Javier Adrian>
Descripción: desarrollo del algoritmo principal de ejecución de las carreras simuladas
Fecha de creación: 10/05/2026
Versión: 1.0.
---------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
///leer este comentario
///No c de estos (lap_time y championship) el de championship esta implementado diferente pero está lo de add en lo de los puntos que no se para que es, entiendo que no hacen nada pero no los he quitado
///xdd le dejo lander lo de .add cuando los pilotos llaman a lo de puntos, para ver como lo implementa o si lo quita
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
	char name[20];
	char team[10];
	float race_time;
	
	///estadisticas específicas de pilotos:
	int level; //velocidad
	int agresividad; //probabilidad 1/x / IGUAL INDICARÁ QUE TAN PROBABLE ES QUE CHOQUEN
	int concentracion; //probabilidad 1/x
	int concentracion_activa;
	int concentracion_cooldown;
	int eliminado; //cada que se llame la funcion en los for ver si esta eliminado, si está eliminado imprime nombre y vale burguer de que ya fue ese vato en esa carrera
	int manejo; // probabilidad 1/x
	
	///estos son los que no se pa que son
	struct lap_time interval;
	struct lap_time gap;
	struct championship points;
	
	
}drivers[22];

struct circuit{
	float seconds;
	int rain_probability;
	int laps;
	int curvas; //1/x
	int profit; //1/x
	int prob_choque; //1/x
};

///funcion que inicializa los pilots, está hasta abajo
void inicializar_pilotos(struct driver* drivers);

///Hasta abajo, este es el modulo seria el modulo de informacion, lo hizo chat xdd
void mostrar_informacion();

///prototipo de lo que sería la función para cada corredor
void simular_piloto(struct circuit circ[][4], struct driver* drivers, int campeonato, int carrera)
{
	//posible ponerles asteriscos
	float lap = circ[campeonato][carrera].seconds;
	int laps  = circ[campeonato][carrera].laps;
	int curvas  = circ[campeonato][carrera].curvas;
	int profit  = circ[campeonato][carrera].profit;
	int riesgo  = circ[campeonato][carrera].prob_choque;
	
	
	//evaluamos velocidad de piloto
	//mayor separacion en los tiempos a comparacion de antes
	switch (drivers->level) {
	case 10: drivers->race_time += lap + (rand() % 301) / 1000.0; break;
	case 9:  drivers->race_time += lap + (rand() % 301 + 500) / 1000.0; break;
	case 8:  drivers->race_time += lap + (rand() % 301 + 1000) / 1000.0; break;
	case 7:  drivers->race_time += lap + (rand() % 301 + 1500) / 1000.0; break;
	case 6:  drivers->race_time += lap + (rand() % 301 + 2000) / 1000.0; break;
	case 5:  drivers->race_time += lap + (rand() % 301 + 2500) / 1000.0; break;
	case 4:  drivers->race_time += lap + (rand() % 301 + 3000) / 1000.0; break;
	case 3:  drivers->race_time += lap + (rand() % 301 + 3500) / 1000.0; break;
	case 2:  drivers->race_time += lap + (rand() % 301 + 4000) / 1000.0; break;
	case 1:  drivers->race_time += lap + (rand() % 301 + 4250) / 1000.0; break;
	}
	
	//concentracion
	if (drivers->concentracion_cooldown > 0) {
		drivers->concentracion_cooldown--;
	}
	else if (drivers->concentracion_activa == 0) {
		if ((rand() % (drivers->concentracion * 200)) == 0) {
			drivers->concentracion_activa = 5; // dura 7 vueltas
			drivers->concentracion_cooldown = 60; //no se puede volver a concentrar hasta en n vueltas
			printf("  >> %s se ha CONCENTRADO!\n", drivers->name);
		}
	} else {
		drivers->concentracion_activa--;
	}
	
	//manejo
	if((rand()% curvas) == 0)
	{
		int tiro_manejo = rand() % 100 + 1;
		int umbral_manejo = (int)((1.0 / drivers->manejo) * 100);
		
		if (drivers->concentracion_activa > 0) {
			// Concentrado: nunca pierde tiempo, solo ahorra o neutro
			if (tiro_manejo <= umbral_manejo)
				drivers->race_time -= (rand() % 400 + 100)/ 1000.0; //mismas razones que en las de profit
			// si falla es neutro, no pasa nada
		} else {
			if (tiro_manejo <= umbral_manejo)
				drivers->race_time -= (rand() % 400 + 100) / 1000.0; // ahorra
			else
				drivers->race_time += (rand() % 3000 + 1000) / 1000.0; 
		}
	}
	
	//profit
	if((rand()% profit) == 0)
	{
		// Activó profit/se prueba el de piloto individual
		if ((rand() % (int)(1.0/(drivers->agresividad) * 1000)) == 0) 
		{
			// Ahorra tiempo
			drivers->race_time -= (rand() % 600 + 200)/ 1000.0;  
			
			// Pero mientras más agresivo, más riesgo de chocar
			int riesgo_real = riesgo;
			if (drivers->concentracion_activa > 0) riesgo_real *= 2; // concentrado reduce riesgo en un x2
			
			if ((rand() % riesgo_real) == 0) {
				// CHOQUE
				printf("  >> %s ha CHOCADO y abandona esta carrera!\n", drivers->name);
				drivers->race_time = 999999.0; // lo manda al último lugar
				drivers->eliminado = 1; //ver que hacer para que si eliminado
			}
		}
	}
	
	///stats específicas de los piltos en docs PILOTOS & CIRCUITOS
	
}
///solo una funcion para todos los pilotos que se pondrán esta funcion 22 veces para ver los parámetros

/*
	Para hacer los tipos de circuitos hacemos 3 arreglos de structs, que cada uno tenga 4 structs que sean las carreras que pasarán
*/
/*<---------- Información de los circuitos ---------->*/

struct circuit circuitos [3][4] = 
{
	{
		//{tiempo x vuelta, prob lluvia 1/x, laps, curvas, profit,riesgo}
		{87,3,52,14,4,550}, ///Silverstonce Circuit, riesgo
		{106, 2, 44,13,3,420}, ///Circuit de Spa-Francorchamps
		{90,4,53,9,9,360}, ///Suzuka Circuit
		{76,10,66,13,7,800} ///Circuit de Barcelona-Catalunya
	},
	
	{
		{81,9,53,8,3,500}, ///Autódromo Nazionale Monza
		{75,5,71,10,3,600}, ///Red Bull Ring
		{90,99,50,27,5,220}, ///Jeddah Corniche Circuit
		{91,149,57,14,2,950} ///Bahrain international circuit
	},
	
	{
		{70,9,72,13,33,150}, ///circuito MONACO de PRUEBA
		{95,11,62,23,6,300}, ///Marina bay street circuit
		{76,6,70,15,11,1000}, ///Hungaroring
		{70,3,71,10,3,380} ///Autódromo Jose Carlos Pace
	}
};


int main() {
	
	///funcion para inicializar todos lo pilotos como está abajo
	inicializar_pilotos(drivers);
	
	///PRIMERO LO PRIMERO pregunta para escanear opción del campeonato
	printf("\nEscoge el CAMPEONATO que quieras simular (opciones 1-3)\n");
	printf("\nMENU CAMPEONATO");
	printf("\nCAMPEONATO NE -- 1");
	printf("\nCAMPEONATO NI -- 2");
	printf("\nCAMPEONATO NO -- 3\n");
	
	//variables para asignar el num de circuito
	int opcion_campeonato;
	int indicador_campeonato;
	
	//proceso para escanear la varibale y no sea menor a 1 y mayor a 3
	printf("\nCAMPEONATO: ");
	scanf("%d", &opcion_campeonato);
	while(opcion_campeonato > 3 || opcion_campeonato < 1)
	{
		printf("\nNUM. ERRONEO (opciones 1-3)");
		printf("\nCAMPEONATO: ");
		scanf("%d", &opcion_campeonato);
	};
	fflush(stdin);

	if(opcion_campeonato == 1)
	{
		indicador_campeonato = 0;
		printf("\nCAMPEONATO 1 Preparado para la carrera (pulsa para continuar)\n");
		getchar();
	}
	else if(opcion_campeonato == 2)
	{
		indicador_campeonato = 1;
		printf("\nCAMPEONATO 2 Preparado para la carrera (pulsa para continuar)\n");
		getchar();
	}
	else
	{
		indicador_campeonato = 2;
		printf("\nCAMPEONATO 3 Preparado para la carrera (pulsa para continuar)\n");
		getchar();
	}
	
	srand(time(NULL));
	for(int carrera = 0; carrera<4; carrera++)
	{
		//para reiniciar los tiempos de los pilotos y los indices si están eliminados
		for (int j = 0; j < 22; j++) 
		{
			drivers[j].race_time = 0;
			drivers[j].eliminado = 0;
			drivers[j].concentracion_activa = 0;
			drivers[j].concentracion_cooldown = 0;
		}
		
		float lap = circuitos[indicador_campeonato][carrera].seconds;
		int rain = rand() % (circuitos[indicador_campeonato][carrera].rain_probability + 1) + 1;
		if (rain == circuitos[indicador_campeonato][carrera].rain_probability){
			printf("\nAVISO: Llovera en esta carrera, tiempos aumentaran!");
			printf("\n(Pulsa para continuar)\n");
			circuitos[indicador_campeonato][carrera].seconds += 8;
			fflush(stdin);
			getchar();
		}
		for (int i = 0; i < circuitos[indicador_campeonato][carrera].laps; i++) {
			for (int j = 0; j < 22; j++) {
				//void simular_piloto(const struct circuit circ[][4], struct driver* drivers, int campeonato, int carrera)
				simular_piloto(circuitos, &drivers[j], indicador_campeonato, carrera);
			}
			
		}
		for (int i = 0; i < 22; i++) {
			drivers[i].race_time /= 60;
			printf("%s\t\t%.3f\n", drivers[i].name, drivers[i].race_time);
		}
		circuitos[indicador_campeonato][carrera].seconds -= 8; //para quitar el efecto de lluvia en cada carrera
		getchar();
	}
	return 0;
}

void inicializar_pilotos(struct driver *drivers)
{
	/*<---------- Información de los pilotos ---------->*/
	drivers[0].level = 9;
	strcpy(drivers[0].name, "George Russell");
	strcpy(drivers[0].team, "Mercedes AMG");
	drivers[0].agresividad = 5;
	drivers[0].manejo = 5;
	drivers[0].concentracion = 5;
	drivers[0].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[1].level = 6;
	strcpy(drivers[1].name, "Kimi Antonelli");
	strcpy(drivers[1].team, "Mercedes AMG");
	drivers[1].agresividad = 3;
	drivers[1].manejo = 9;
	drivers[1].concentracion = 5;
	drivers[1].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[2].level = 10;
	strcpy(drivers[2].name, "Charles Leclerc");
	strcpy(drivers[2].team, "Scuderia Ferrari");
	drivers[2].agresividad = 5;
	drivers[2].manejo = 5;
	drivers[2].concentracion = 4;
	drivers[2].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[3].level = 9;
	strcpy(drivers[3].name, "Lewis Hamilton");
	strcpy(drivers[3].team, "Scuderia Ferrari");
	drivers[3].agresividad = 7;
	drivers[3].manejo = 3;
	drivers[3].concentracion = 3;
	drivers[3].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[4].level = 10;
	strcpy(drivers[4].name, "Lando Norris");
	strcpy(drivers[4].team, "McLaren Mastercard");
	drivers[4].agresividad = 5;
	drivers[4].manejo = 5;
	drivers[4].concentracion = 4;
	drivers[4].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[5].level = 9;
	strcpy(drivers[5].name, "Oscar Piastri");
	strcpy(drivers[5].team, "McLaren Mastercard");
	drivers[5].agresividad = 8;
	drivers[5].manejo = 3;
	drivers[5].concentracion = 4;
	drivers[5].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[6].level = 10;
	strcpy(drivers[6].name, "Max Verstappen");
	strcpy(drivers[6].team, "Red Bull Racing");
	drivers[6].agresividad = 4;
	drivers[6].manejo = 3;
	drivers[6].concentracion = 3;
	drivers[6].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[7].level = 4;
	strcpy(drivers[7].name, "Isaac Hadjar");
	strcpy(drivers[7].team, "Red Bull Racing");
	drivers[7].agresividad = 3;
	drivers[7].manejo = 11;
	drivers[7].concentracion = 6;
	drivers[7].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[8].level = 8;
	strcpy(drivers[8].name, "Pierre Gasly");
	strcpy(drivers[8].team, "BWT Alpine");
	drivers[8].agresividad = 6;
	drivers[8].manejo = 6;
	drivers[8].concentracion = 5;
	drivers[8].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[9].level = 5;
	strcpy(drivers[9].name, "Franco Colapinto");
	strcpy(drivers[9].team, "BWT Alpine");
	drivers[9].agresividad = 3;
	drivers[9].manejo = 11;
	drivers[9].concentracion = 6;
	drivers[9].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[10].level = 5;
	strcpy(drivers[10].name, "Oliver Bearman");
	strcpy(drivers[10].team, "TGR Haas");
	drivers[10].agresividad = 3;
	drivers[10].manejo = 10;
	drivers[10].concentracion = 6;
	drivers[10].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[11].level = 7;
	strcpy(drivers[11].name, "Esteban Ocon");
	strcpy(drivers[11].team, "TGR Haas");
	drivers[11].agresividad = 4;
	drivers[11].manejo = 8;
	drivers[11].concentracion = 6;
	drivers[11].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[12].level = 5;
	strcpy(drivers[12].name, "Liam Lawson");
	strcpy(drivers[12].team, "Racin Bulls");
	drivers[12].agresividad = 4;
	drivers[12].manejo = 10;
	drivers[12].concentracion = 6;
	drivers[12].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[13].level = 2;
	strcpy(drivers[13].name, "Arvid Lindblad");
	strcpy(drivers[13].team, "Racing Bulls");
	drivers[13].agresividad = 2;
	drivers[13].manejo = 13;
	drivers[13].concentracion = 7;
	drivers[13].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[14].level = 8;
	strcpy(drivers[14].name, "Carlos Sainz");
	strcpy(drivers[14].team, "Atlassian Williams");
	drivers[14].agresividad = 7;
	drivers[14].manejo = 5;
	drivers[14].concentracion = 5;
	drivers[14].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[15].level = 7;
	strcpy(drivers[15].name, "Alex Albon");
	strcpy(drivers[15].team, "Atlassian Williams");
	drivers[15].agresividad = 5;
	drivers[15].manejo = 6;
	drivers[15].concentracion = 6;
	drivers[15].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[16].level = 6;
	strcpy(drivers[16].name, "Nico Hulkenberg");
	strcpy(drivers[16].team, "Audi Revolut");
	drivers[16].agresividad = 9;
	drivers[16].manejo = 5;
	drivers[16].concentracion = 6;
	drivers[16].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[17].level = 4;
	strcpy(drivers[17].name, "Gabriel Bortoleto");
	strcpy(drivers[17].team, "Audi Revolut");
	drivers[17].agresividad = 5;
	drivers[17].manejo = 9;
	drivers[17].concentracion = 7;
	drivers[17].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[18].level = 7;
	strcpy(drivers[18].name, "Sergio Perez");
	strcpy(drivers[18].team, "Cadillac F1");
	drivers[18].agresividad = 7;
	drivers[18].manejo = 7;
	drivers[18].concentracion = 6;
	drivers[18].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[19].level = 6;
	strcpy(drivers[19].name, "Valteri Bottas");
	strcpy(drivers[19].team, "Cadillac F1");
	drivers[19].agresividad = 10;
	drivers[19].manejo = 6;
	drivers[19].concentracion = 7;
	drivers[19].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[20].level = 8;
	strcpy(drivers[20].name, "Fernando Alonso");
	strcpy(drivers[20].team, "Aston Martin");
	drivers[20].agresividad = 8;
	drivers[20].manejo = 2;
	drivers[20].concentracion = 2;
	drivers[20].points.add = 0;
	/*<----------------------------------------------->*/
	drivers[21].level = 1;
	strcpy(drivers[21].name, "Lance Stroll");
	strcpy(drivers[21].team, "Aston Martin");
	drivers[21].agresividad = 4;
	drivers[21].manejo = 14;
	drivers[21].concentracion = 10;
	drivers[21].points.add = 0;
	/*<----------------------------------------------->*/
}

void mostrar_informacion()
{
	printf("\n========== PILOTOS ==========\n");
	for (int i = 0; i < 22; i++)
	{
		printf("\nPiloto: %s\n", drivers[i].name);
		printf("Equipo: %s\n", drivers[i].team);
		printf("Nivel: %d\n", drivers[i].level);
		printf("Manejo: %d\n", drivers[i].manejo);
		printf("Agresividad: %d\n", drivers[i].agresividad);
		printf("Concentracion: %d\n", drivers[i].concentracion);
		printf("-----------------------------\n");
	}
	
	printf("\n========== CAMPEONATOS ==========\n");
	
	printf("\nCAMPEONATO NE");
	printf("\nLLUVIA, CURVAS Y PELIGRO son probabilidades, en curva se pone a prueba al piloto, PELIGRO es prob. de riesgo.\n\n");
	printf("Silverstone:   laps: %d | seg/vuelta: %.0f | lluvia: 1/%d | curvas: 1/%d | peligro: 1/%d\n", circuitos[0][0].laps, circuitos[0][0].seconds, circuitos[0][0].rain_probability, circuitos[0][0].curvas, circuitos[0][0].prob_choque);
	printf("Spa:           laps: %d | seg/vuelta: %.0f | lluvia: 1/%d | curvas: 1/%d | peligro: 1/%d\n", circuitos[0][1].laps, circuitos[0][1].seconds, circuitos[0][1].rain_probability, circuitos[0][1].curvas, circuitos[0][1].prob_choque);
	printf("Suzuka:        laps: %d | seg/vuelta: %.0f | lluvia: 1/%d | curvas: 1/%d | peligro: 1/%d\n", circuitos[0][2].laps, circuitos[0][2].seconds, circuitos[0][2].rain_probability, circuitos[0][2].curvas, circuitos[0][2].prob_choque);
	printf("Barcelona:     laps: %d | seg/vuelta: %.0f | lluvia: 1/%d | curvas: 1/%d | peligro: 1/%d\n", circuitos[0][3].laps, circuitos[0][3].seconds, circuitos[0][3].rain_probability, circuitos[0][3].curvas, circuitos[0][3].prob_choque);
	
	printf("\nCAMPEONATO NI\n");
	printf("Monza:         laps: %d | seg/vuelta: %.0f | lluvia: 1/%d | curvas: 1/%d | peligro: 1/%d\n", circuitos[1][0].laps, circuitos[1][0].seconds, circuitos[1][0].rain_probability, circuitos[1][0].curvas, circuitos[1][0].prob_choque);
	printf("Red Bull Ring: laps: %d | seg/vuelta: %.0f | lluvia: 1/%d | curvas: 1/%d | peligro: 1/%d\n", circuitos[1][1].laps, circuitos[1][1].seconds, circuitos[1][1].rain_probability, circuitos[1][1].curvas, circuitos[1][1].prob_choque);
	printf("Jeddah:        laps: %d | seg/vuelta: %.0f | lluvia: 1/%d | curvas: 1/%d | peligro: 1/%d\n", circuitos[1][2].laps, circuitos[1][2].seconds, circuitos[1][2].rain_probability, circuitos[1][2].curvas, circuitos[1][2].prob_choque);
	printf("Bahrain:       laps: %d | seg/vuelta: %.0f | lluvia: 1/%d | curvas: 1/%d | peligro: 1/%d\n", circuitos[1][3].laps, circuitos[1][3].seconds, circuitos[1][3].rain_probability, circuitos[1][3].curvas, circuitos[1][3].prob_choque);
	
	printf("\nCAMPEONATO NO\n");
	printf("Monaco:        laps: %d | seg/vuelta: %.0f | lluvia: 1/%d | curvas: 1/%d | peligro: 1/%d\n", circuitos[2][0].laps, circuitos[2][0].seconds, circuitos[2][0].rain_probability, circuitos[2][0].curvas, circuitos[2][0].prob_choque);
	printf("Marina Bay:    laps: %d | seg/vuelta: %.0f | lluvia: 1/%d | curvas: 1/%d | peligro: 1/%d\n", circuitos[2][1].laps, circuitos[2][1].seconds, circuitos[2][1].rain_probability, circuitos[2][1].curvas, circuitos[2][1].prob_choque);
	printf("Hungaroring:   laps: %d | seg/vuelta: %.0f | lluvia: 1/%d | curvas: 1/%d | peligro: 1/%d\n", circuitos[2][2].laps, circuitos[2][2].seconds, circuitos[2][2].rain_probability, circuitos[2][2].curvas, circuitos[2][2].prob_choque);
	printf("Interlagos:    laps: %d | seg/vuelta: %.0f | lluvia: 1/%d | curvas: 1/%d | peligro: 1/%d\n", circuitos[2][3].laps, circuitos[2][3].seconds, circuitos[2][3].rain_probability, circuitos[2][3].curvas, circuitos[2][3].prob_choque);
}
