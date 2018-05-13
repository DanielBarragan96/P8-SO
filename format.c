#pragma pack(2)

#include <stdio.h>
#include "DataTypeDefinitions.h"
#include "vdisk.h"

// Datos sobre la geometría del disco
//#define CYLINDERS 200
//#define HEADS 8
//#define SECTORS 27

int main()
{
	SECBOOTPART sbp;
	int unidad = 0;
	int sfip = 2,sip = 0,cip = 0;
	
	char buffer[512] = {0};
	
	// Obtener de la tabla de particiones los valores de:
	// 	sfip = Sector físico inicial de la partición
	//	sip = Superficie inicial de la partición
	//	cip = Cilindro inicial de la partición
	
	sbp.sec_inicpart=1;
	sbp.sec_res=1;
	sbp.sec_mapa_bits_area_nodos_i=1;
	sbp.sec_mapa_bits_bloques=6;
	sbp.sec_tabla_nodos_i=3;
	sbp.sec_log_particion=43100;
	sbp.sec_x_bloque=2;
	sbp.heads=8;
	sbp.cyls=200;
	sbp.secfis=27;
	
	// Escribir el contenido de la estructura sbp en el sector físico inicial de la 
	// partición
	vdwritesector(unidad,cip,sip,sfip,1,(void *) &sbp);
	
	int limit = sbp.sec_log_particion +1;
	for(sfip = 3; sfip <= limit; sfip++)
	{
		if(sfip==4)
		{
			buffer[0] = 0x01;
			vdwritesector(unidad,cip,sip,sfip,1,(void *) &buffer);
			sfip++;
			buffer[0] = 0x00;
		}
		vdwritesector(unidad,cip,sip,sfip,1,(void *) &buffer);	
	}
}
