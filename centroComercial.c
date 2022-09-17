/*
PRACTICA 02 "SIMULACION DE SUPERMERCADO"

DESCRIPCIÓN: Simula un supermercado utilizando colas, de tal forma que se muestra en consola cómo llegan los 
			 clientes y cómo son atendidos.
			 Dejan de llegar clientes cuando se alcanzan 100 y se atiende a los últimos que están formados en las
			 filas.

OBSERVACIONES: Se emplea la libreria TADColaDin.h implementada en clase.

INSTRUCCION DE COMPILACION: gcc centroComercial.c TADColaDin.c presentacionWin.c -o centroComercial
EJECUCIÓN: centroComercial.exe 

AUTORES:  

Ericka Ruiz López              (C) Marzo 2021

*/
#include<stdio.h>
#include "presentacion.h"
#include "TADColaDin.h"
#include <time.h>
#include <stdlib.h>
#include <windows.h>
//#include "TADColaEst.h"	

void proceso(int numCajeras, int tiempoBase, int tiempoCliente, int tiempoAtencion);	//Función con todo el proceso de simulación.
void dibujarCuadro(int x1,int y1,int x2,int y2);  //Función para dibujar el cuadro contorno. 
void cuadroDatos();	//Función para dibujar los datos que van a estar estáticos durante toda la simulación.
void dibujarClientes(int x, int y, cola * cajera);	//Función para dibujar los clientes en cola.
void dibujarAtendiendo(int atendiendo, int x, int y);	//Función para dibujar el cliente en proceso de atención.

//Funcion principal
int main()
{
	int i, opc;				//Variables auxiliares
	int numCajeras=10;		//Numero de cajeras 10
	int tiempoBase=300;		//Tiempo base en ms
	int tiempoCliente=1;	//Tiempo de llegada de clientes en ms * 1
	int tiempoAtencion=6;	//Tiempo de atención en ms * 6
	
	do{
		//Permite al usuario escoger entre los tiempos predeterminados o sus propios tiempos
		printf("\nContinuar con tiempos predeterminados? (si:1 no:2): ");
		scanf("%d", &opc);
	}while(opc!=1&&opc!=2);

	if(opc==2){
		//Lee los tiempos en caso de que así se desee
		printf("\nIngrese el numero de cajeras abiertas: ");
		scanf("%d", &numCajeras);
		printf("\nIngrese el tiempo base: ");
		scanf("%d", &tiempoBase);
		printf("\nIngrese el tiempo de llegada de los clientes: ");
		scanf("%d", &tiempoCliente);
		printf("\nIngrese el tiempo de atencion: ");
		scanf("%d", &tiempoAtencion);
	}

	//Prepara la pantalla para la simulación
	BorrarPantalla();
	system("mode con: cols=100 lines=38");
	system("COLOR 0B");
	//Dibuja el cuadro del contorno
	dibujarCuadro(1,1,95,30);
	dibujarCuadro(37,2,58,4);
	//Dibuja los datos estáticos durante toda la simulación
	cuadroDatos();
	//Inicia el proceso de simulación
    proceso(numCajeras, tiempoBase, tiempoCliente, tiempoAtencion);
	//Espaciado al finalizar simulación
    for(i=0;i<4;i++){
    	printf("\n");
    }
    return 0;
}

//Funciones

//Función con todo el proceso de simulación.
//Recibe el número de cajeras abiertas, el tiempo base, el tiempo de llegada de los clientes y el tiempo de atención en caja
void proceso(int numCajeras, int tiempoBase, int tiempoCliente, int tiempoAtencion)
{
	//Arreglo de 10 colas para representar las 10 cajeras
    cola cajera[10];
	//Elemento auxiliar
    elemento e;
	//Contadores auxiliares
    int cliente = 0;
    int tiempo,fila,i,fin=0, atendiendo=0;
	int cuentaAtendidos=0;
	
    srand(time(NULL));
	
	//Inicializa las 10 colas
	Initialize(&cajera[0]);
	Initialize(&cajera[1]);
    Initialize(&cajera[2]);
    Initialize(&cajera[3]);
    Initialize(&cajera[4]);
    Initialize(&cajera[5]);
    Initialize(&cajera[6]);
    Initialize(&cajera[7]);
    Initialize(&cajera[8]);
    Initialize(&cajera[9]);

	//Bucle infinito 
    while(1)
	{
        Sleep(tiempoBase);		//Esperar el tiempo base
		tiempo++;				//Incrementar el contador de tiempo

		//Instrucciones para atender a los clientes
		//Si el tiempo es múltipli del tiempo atención
        if (tiempo % tiempoAtencion == 0)
		{	
			//Contador auxiliar para la terminación del proceso
			fin=0;
			//Recorre el número de cajas abiertas
            for(i=0;i<numCajeras;i++)
			{
				//Si la caja no está vacía
                if (!Empty(&cajera[i]))
                {
					//Desencola un cliente para su atención
                    e = Dequeue(&cajera[i]);
					atendiendo = e.n;
					//Incrementa el contador de clientes atendidos
					cuentaAtendidos++;
					//Imprime el número de clientes atendidos
					MoverCursor(85,3);
					printf("    "); 
					MoverCursor(85,3);
					printf("%d",cuentaAtendidos); 
					//Si el número de clientes atendidos llega a 100, imprime 
					if(cuentaAtendidos==100){
						MoverCursor(30,5);
						printf("Meta de clientes alcanzada. Tienda cerrada.");
					}
                }
				//Si la caja está vacía
                else
                {
					//Incrementa contador auxiliar para término de proceso
					fin++;
					//Indicador de que no se atiende a nadie
					atendiendo = -1;
				}

				//Dibuja el cliente en atención de cada caja
				if(i==0)
				{
					dibujarAtendiendo(atendiendo, 35, 7);
				}
				if(i==1)
				{
					dibujarAtendiendo(atendiendo, 35, 12);
				}
				if(i==2)
				{
					dibujarAtendiendo(atendiendo, 35, 17);
				}
				if(i==3)
				{
					dibujarAtendiendo(atendiendo, 35, 22);
				}
				if(i==4)
				{
					dibujarAtendiendo(atendiendo, 35, 27);
				}
				if(i==5)
				{
					dibujarAtendiendo(atendiendo, 85, 7);
				}
				if(i==6)
				{
					dibujarAtendiendo(atendiendo, 85, 12);
				}
				if(i==7)
				{
					dibujarAtendiendo(atendiendo, 85, 17);
				}
				if(i==8)
				{
					dibujarAtendiendo(atendiendo, 85, 22);
				}
				if(i==9)
				{
					dibujarAtendiendo(atendiendo, 85, 27);
				}            
            }

			//Si el contador auxiliar es igual al número de cajas, quiere decir que todas están vacías
			if(fin==numCajeras)
			{	
				//Finaliza proceso
				break;
			}
		}

		//Instrucciones para la llegada de clientes a las colas
		//Si el tiempo es múltiplo del tiempo de llegada de clientes y el número de clientes atendidos es menor o igual a 100
        if (tiempo % tiempoCliente == 0 && cuentaAtendidos<=100)
        {
            cliente++;					//Incrementar el numero de clientes
            e.n = cliente;				//Dar el numero que identifica al cliente
            fila=rand()%numCajeras;		//Escoger la fila para formarse aleatoriamente								
            Queue(&cajera[fila], e);	//Formarse en la fila seleccionada
        }

		//Dibuja los clientes en cola de cada caja
		dibujarClientes(30, 9, &cajera[0]);
		dibujarClientes(30, 14, &cajera[1]);
		dibujarClientes(30, 19, &cajera[2]);
		dibujarClientes(30, 24, &cajera[3]);
		dibujarClientes(30, 29, &cajera[4]);
		dibujarClientes(80, 9, &cajera[5]);
		dibujarClientes(80, 14, &cajera[6]);
		dibujarClientes(80, 19, &cajera[7]);
		dibujarClientes(80, 24, &cajera[8]);
		dibujarClientes(80, 29, &cajera[9]);
    }
}


/*
Función para dibujar el cuadro contorno. 
Recibe posicon incial en x, posicion incial en y, posiscion final en x , posicion final en y 
*/
void dibujarCuadro(int x1,int y1,int x2,int y2){
	int i;

    for (i=x1;i<x2;i++){
		MoverCursor(i,y1); 
		printf("\304"); //linea horizontal superior
		MoverCursor(i,y2); 
		printf("\304"); //linea horizontal inferior
    }
    for (i=y1;i<y2;i++){
		MoverCursor(x1,i); 
		printf("\263"); //linea vertical izquierda
		MoverCursor(x2,i); 
		printf("\263"); //linea vertical derecha
	}
  	MoverCursor(x1,y1); 
  	printf("\332");
    MoverCursor(x1,y2); 
    printf("\300");
    MoverCursor(x2,y1); 
    printf("\277");
    MoverCursor(x2,y2); 
    printf("\331");
}

//Función para dibujar los datos estáticos durante toda la simulación
void cuadroDatos(){
	//Mueve el cursor a una posición específica
	MoverCursor(38,3);
	//Imprime
	printf("------ B &n L ------");
	MoverCursor(2,8);
	printf("--- Cola 1: ---");
	MoverCursor(20,7);
    printf("Atendiendo a: "); 
	MoverCursor(20,9);
    printf("En fila: ");
	MoverCursor(2,13);
	printf("--- Cola 2: ---");
	MoverCursor(20,12);
    printf("Atendiendo a: "); 
	MoverCursor(20,14);
    printf("En fila: ");
	MoverCursor(2,18);
	printf("--- Cola 3: ---");
	MoverCursor(20,17);
    printf("Atendiendo a: "); 
	MoverCursor(20,19);
    printf("En fila: ");
	MoverCursor(2,23);
	printf("--- Cola 4: ---");
	MoverCursor(20,22);
    printf("Atendiendo a: "); 
	MoverCursor(20,24);
    printf("En fila: ");
	MoverCursor(2,28);
	printf("--- Cola 5: ---");
	MoverCursor(20,27);
    printf("Atendiendo a: "); 
	MoverCursor(20,29);
    printf("En fila: ");
	MoverCursor(50,8);
	printf("--- Cola 6: ---");
	MoverCursor(65,3);
    printf("Clientes atendidos:"); 
	MoverCursor(70,7);
    printf("Atendiendo a: "); 
	MoverCursor(70,9);
    printf("En fila: ");
	MoverCursor(50,13);
	printf("--- Cola 7: ---");
	MoverCursor(70,12);
    printf("Atendiendo a: "); 
	MoverCursor(70,14);
    printf("En fila: ");
	MoverCursor(50,18);
	printf("--- Cola 8: ---");
	MoverCursor(70,17);
    printf("Atendiendo a: "); 
	MoverCursor(70,19);
    printf("En fila: ");
	MoverCursor(50,23);
	printf("--- Cola 9: ---");
	MoverCursor(70,22);
    printf("Atendiendo a: "); 
	MoverCursor(70,24);
    printf("En fila: ");
	MoverCursor(50,28);
	printf("--- Cola 10: ---");
	MoverCursor(70,27);
    printf("Atendiendo a: "); 
	MoverCursor(70,29);
    printf("En fila: ");
}

//Función para dibujar los clientes en cola.
void dibujarClientes(int x, int y, cola * cajera){
	//Contadores auxiliares
	int j=0;
	int i=0;
	int tam = Size(cajera);
	//Si la cola tiene más de 3 elementos
	if(tam>3){
		//Imprime hasta tres elementos
		for(i=0;i<3;i++){
			MoverCursor(x+j,y); printf("%d",Element(cajera,i+1).n);
			j+=4;
		}
		//Imprime el número de elementos restantes
		MoverCursor(x+13,y); printf("    ");
		MoverCursor(x+13,y); printf("+%d",tam-3);
	}
	//Si la cola tiene menos de 3 o 3 elementos
	else{
		//Inicializa el contador auxiliar
		i=0;
		//Limpia los elementos que resten 
		MoverCursor(x,y); printf("            ");
		//Imprime los elementos que hay en la cola
		while(i<tam){
			printf("   ");
			MoverCursor(x+j,y); printf("%d",Element(cajera,i+1).n);
			j+=4;	//Contador para posicionamiento
			i++;
		}
	}
}

//Función para dibujar el cliente en proceso de atención
void dibujarAtendiendo(int atendiendo, int x, int y)
{
	//Si no se está atendiendo a ningún cliente
	if(atendiendo == -1)
	{
		//Imprime Nadie
		MoverCursor(x,y);
		printf("Nadie");
	}
	//Si se está atendiendo a un cliente
	else
	{
		//Imprime el cliente 
		MoverCursor(x,y);//posicion atendiendo
		printf("       ");
		MoverCursor(x,y);
		printf("%d",atendiendo);
	}
}
