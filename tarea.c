/* Carolina Dorado Ruiz
*  cod. 1522589
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


main(int argc, char* argv[] )
{

	//Toma el tiempo
	clock_t start = clock();
   
	//Nombre de archivo
  	 char *nombreArchivos[60] ;	

	//Funcion
	 infoDirectorio(nombreArchivos, argv[1]);
		
	//Toma el tiempo transcurrido al finalizar y lo imprime
	printf("Tiempo transcurrido: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
	
}
	//Funcion que recibe el nombre del directorio y matriz con nombre de archivos vacía
	// e imprime los nombres de los archivos no directorios que hay en el directorio y el peso total de 
	//los archivos
	void infoDirectorio(char *nombreArchivos[], char nombreDirectorio[100])
	{

		struct dirent **entradas= NULL;

		int numeroArchivos = scandir (nombreDirectorio, &entradas, NULL, NULL);
		char ruta[120];
		char slash = "/";
		int pesoTotal = 0;

		for (int i=0; i<numeroArchivos; i++)
		{
			if(entradas[i]->d_type == DT_REG)
			{	
				strcat(ruta,nombreDirectorio);
				strcat(ruta,"/");
				nombreArchivos[i] = entradas[i]->d_name;
				printf ("Nombre archivo: %s\n", nombreArchivos[i]);
				strcat(ruta,nombreArchivos[i]);
				pesoTotal += filesize(ruta);
				//printf ("%d\n",filesize(ruta));
				ruta[0] = '\0';
				//Liberar memoria
				free (entradas[i]);
				entradas[i] = NULL;
			}			
		}
		printf ("Peso Total: %d\n",pesoTotal);
		free (entradas);
		entradas = NULL;
	}

	int filesize(char *filename) 
	{
       		 // Definicion e inicializacion de variables
       		 FILE *fp;
       		 int count = 0;

        	// Se abre el archivo y se contara caracter por caracter el numero 
    		// de bytes del archivo
       		 fp = fopen(filename,"r");
        	if (fp == NULL) 
		{
               		 perror("filesize - No se pudo abrir archivo\n");
               		 return -1;
       		 }

      		 while (fgetc(fp) != EOF) 
		{
               		 count++;
       		 }
        	fclose(fp);
       		return count;
	}
