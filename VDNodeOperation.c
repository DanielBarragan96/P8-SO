
#include "VDNodeOperation.h"
#include "vdisk.h"
#include "VDBlockOperation.h"
#include "VDSecLogOperation.h"

#include "DataTypeDefinitions.h"

// *************************************************************************
// Para el mapa de bits del área de nodos i
// *************************************************************************

//extern int secboot_en_memoria;
//extern SECBOOTPART secboot;

//int mapa_bits_nodos_i = 0;
//int inodesmap_en_memoria = 0;

// Usando el mapa de bits, determinar si un nodo i, está libre u ocupado.
int isinodefree(int inode)
{
	int offset=inode/8;
	int shift=inode%8;
	int result;

	// Checar si el sector de boot de la partición está en memoria
	if(!secboot_en_memoria)
	{
		// Si no está en memoria, cárgalo
		result=vdreadseclog(0, 0,(char *) &secboot);
		secboot_en_memoria=1;
	}
	mapa_bits_nodos_i= secboot.sec_inicpart +secboot.sec_res; 	
//Usamos la información del sector de boot de la partición para 
						//determinar en que sector inicia el 
						// mapa de bits de nodos i 
					
	// Ese mapa está en memoria
	if(!inodesmap_en_memoria)
	{
		// Si no está en memoria, hay que leerlo del disco
		result=vdreadseclog(0, mapa_bits_nodos_i,inodesmap);
		inodesmap_en_memoria=1;
	}


	if(inodesmap[offset] & (1<<shift))
		return(0); // El nodo i ya está ocupado
	else
		return(1); // El nodo i está libre
}	

// Buscar en el mapa de bits, el primer nodo i que esté libre, es decir, que su bit está en 0, me regresa ese dato
int nextfreeinode()
{
	int i,j;
	int result;

	// Checar si el sector de boot de la partición está en memoria
	if(!secboot_en_memoria)
	{
		// Si no está en memoria, cárgalo
		result=vdreadseclog(1,(char *) &secboot);
		secboot_en_memoria=1;
	}
	mapa_bits_nodos_i= secboot.sec_inicpart +secboot.sec_res; 	
//Usamos la información del sector de boot de la partición para 
						//determinar en que sector inicia el 
						// mapa de bits de nodos i 
					
	// Ese mapa está en memoria
	if(!inodesmap_en_memoria)
	{
		// Si no está en memoria, hay que leerlo del disco
		result=vdreadseclog(mapa_bits_nodos_i,inodesmap);
		inodesmap_en_memoria=1;
	}

	// Recorrer byte por byte mientras sea 0xFF sigo recorriendo
	i=0;
	while(inodesmap[i]==0xFF && i<3)
		i++;

	if(i<3)
	{
		// Recorrer los bits del byte, para encontrar el bit
		// que está en cero
		j=0;
		while(inodesmap[i] & (1<<j) && j<8)
			j++;

		return(i*8+j); // Regresar el bit del mapa encontrado en cero
	}
	else // Todos los bits del mapa de nodos i están en 1
		return(-1); // -1 significa que no hay nodos i disponibles		
}

// Poner en 1, el bit que corresponde al número de inodo indicado
int assigninode(int inode)
{
	int offset=inode/8;
	int shift=inode%8;
	int result;

	// Checar si el sector de boot de la partición está en memoria
	if(!secboot_en_memoria)
	{
		// Si no está en memoria, cárgalo
		result=vdreadseclog(0, 0,(char *) &secboot);
		secboot_en_memoria=1;
	}
	mapa_bits_nodos_i= secboot.sec_inicpart +secboot.sec_res; 	
//Usamos la información del sector de boot de la partición para 
						//determinar en que sector inicia el 
						// mapa de bits de nodos i 
					
	// Ese mapa está en memoria
	if(!inodesmap_en_memoria)
	{
		// Si no está en memoria, hay que leerlo del disco
		result=vdreadseclog(0, mapa_bits_nodos_i,inodesmap);
		inodesmap_en_memoria=1;
	}

	inodesmap[offset]|=(1<<shift); // Poner en 1 el bit indicado
	vdwriteseclog(0,mapa_bits_nodos_i,inodesmap);
	return(1);
}

// Poner en 0, el bit que corresponde al número de inodo indicado
int unassigninode(int inode)
{
	int offset=inode/8;
	int shift=inode%8;
	int result;

	// Checar si el sector de boot de la partición está en memoria
	if(!secboot_en_memoria)
	{
		// Si no está en memoria, cárgalo
		result=vdreadseclog(0, 0, (char *) &secboot);
		secboot_en_memoria=1;
	}
	mapa_bits_nodos_i= secboot.sec_inicpart +secboot.sec_res; 	
//Usamos la información del sector de boot de la partición para 
						//determinar en que sector inicia el 
						// mapa de bits de nodos i 
					
	// Ese mapa está en memoria
	if(!inodesmap_en_memoria)
	{
		// Si no está en memoria, hay que leerlo del disco
		result=vdreadseclog(0, mapa_bits_nodos_i,inodesmap);
		inodesmap_en_memoria=1;
	}

	inodesmap[offset]&=(char) ~(1<<shift); // Poner en cero el bit que corresponde al inodo indicado
	vdwriteseclog(0, mapa_bits_nodos_i,inodesmap);
	return(1);
}

// Usando la información del mapa de bits del area de datos, saber si un bloque está libre o no
int isblockfree(int block)
{
	int offset=block/8; // Número de byte en el mapa
	int shift=block%8; // Número de bit en el byte
	int result;
	int i;

	// Determinar si tenemos el sector de boot de la partición en memoria
	if(!secboot_en_memoria)
	{
		result=vdreadseclog(0, 0, (char *) &secboot);
		secboot_en_memoria=1;
	}

	// Calcular el sector lógico donde está el mapa de bits de los bloques
	mapa_bits_bloques= secboot.sec_inicpart+secboot.sec_res+secboot.sec_mapa_bits_nodos_i;
	
	// Verificar si ya está en memoria, si no, cargarlo
	if(!blocksmap_en_memoria)
	{
		// Cargar todos los sectores que corresponden al 
		// mapa de bits
		for(i=0;i<secboot.sec_mapa_bits_bloques;i++)
			result=vdreadseclog(0, mapa_bits_bloques+i,blocksmap+i*512);
		blocksmap_en_memoria=1;
	}

	if(blocksmap[offset] & (1<<shift))
		return(0);	// Si el bit está en 1, regresar 0 (no está libre)
	else
		return(1);	// Si el bit está en 0, regresar 1 (si está libre)
}	

// Usando el mapa de bits, buscar el siguiente bloque libre
int nextfreeblock()
{
	int i,j;
	int result;

	// Determinar si tenemos el sector de boot de la partición en memoria
	if(!secboot_en_memoria)
	{
		result=vdreadseclog(0, 0, (char *) &secboot);
		secboot_en_memoria=1;
	}

	// Calcular el sector lógico donde está el mapa de bits de los bloques
	mapa_bits_bloques= secboot.sec_inicpart+secboot.sec_res+secboot.sec_mapa_bits_nodos_i;
	
	// Verificar si ya está en memoria, si no, cargarlo
	if(!blocksmap_en_memoria)
	{
		// Cargar todos los sectores que corresponden al 
		// mapa de bits
		for(i=0;i<secboot.sec_mapa_bits_bloques;i++)
			result=vdreadseclog(0, mapa_bits_bloques+i,blocksmap+i*512);
		blocksmap_en_memoria=1;
	}

	// Empezar desde el primer byte del mapa de bloques.
	i=0;
	// Si el byte tiene todos los bits en 1, y mientras no
// lleguemos al final del mapa de bits
	while(blocksmap[i]==0xFF && i<secboot.sec_mapa_bits_bloques*512)
		i++;

	// Si no llegué al final del mapa de bits, quiere decir
	// que aún hay bloques libres
	if(i<secboot.sec_mapa_bits_bloques*512)
	{
		j=0;
		while(blocksmap[i] & (1<<j) && j<8)
			j++;

		return(i*8+j);	// Retorno el número de bloque
						// que se encontró disponible
	}
	else
		// Si ya no hublo bloques libres, regresar -1 = Error
		return(-1);
}

// Asignar un bloque en 1 en el mapa de bits, lo cual significa que estaría ya ocupado.
int assignblock(int block)
{
	int offset=block/8;
	int shift=block%8;
	int result;
	int i;
	int sector;

	// Determinar si tenemos el sector de boot de la partición en memoria
	if(!secboot_en_memoria)
	{
		result=vdreadseclog(0, 0, (char *) &secboot);
		secboot_en_memoria=1;
	}

	// Calcular el sector lógico donde está el mapa de bits de los bloques
	mapa_bits_bloques= secboot.sec_inicpart+secboot.sec_res+secboot.sec_mapa_bits_nodos_i;
	
	// Verificar si ya está en memoria, si no, cargarlo
	if(!blocksmap_en_memoria)
	{
		// Cargar todos los sectores que corresponden al 
		// mapa de bits
		for(i=0;i<secboot.sec_mapa_bits_bloques;i++)
			result=vdreadseclog(0, mapa_bits_bloques+i,blocksmap+i*512);
		blocksmap_en_memoria=1;
	}

	blocksmap[offset]|=(1<<shift);

	// Determinar en que número de sector está el bit que 
	// modificamos 	
	sector=(offset/512);
	// Escribir el sector del mapa de bits donde está el bit
	// que modificamos
	vdwriteseclog(0, mapa_bits_bloques+sector,blocksmap+sector*512);
	//for(i=0;i<secboot.sec_mapa_bits_bloques;i++)
	//	vdwriteseclog(mapa_bits_bloques+i,blocksmap+i*512);
	return(1);
}

// Poner en 0 el bit que corresponde a un bloque en el mapa de bits, esto equivale a decir que el bloque está libre
int unassignblock(int block)
{
	int offset=block/8;
	int shift=block%8;
	int result;
	char mask;
	int sector;
	int i;

	// Determinar si tenemos el sector de boot de la partición en memoria
	if(!secboot_en_memoria)
	{
		result=vdreadseclog(0, 0, (char *) &secboot);
		secboot_en_memoria=1;
	}

	// Calcular el sector lógico donde está el mapa de bits de los bloques
	mapa_bits_bloques= secboot.sec_inicpart+secboot.sec_res+secboot.sec_mapa_bits_nodos_i;
	
	// Verificar si ya está en memoria, si no, cargarlo
	if(!blocksmap_en_memoria)
	{
		// Cargar todos los sectores que corresponden al 
		// mapa de bits
		for(i=0;i<secboot.sec_mapa_bits_bloques;i++)
			result=vdreadseclog(0, mapa_bits_bloques+i,blocksmap+i*512);
		blocksmap_en_memoria=1;
	}

	blocksmap[offset]&=(char) ~(1<<shift);

	// Calcular en que sector está el bit modificado
	// Escribir el sector en disco
	sector=(offset/512);
	vdwriteseclog(0, mapa_bits_bloques+sector,blocksmap+sector*512);
	result = vdwriteseclog(0, sl_datos+block-1, empty);
	// for(i=0;i<secboot.sec_mapa_bits_bloques;i++)
	//	vdwriteseclog(mapa_bits_bloques+i,blocksmap+i*512);
	return(1);
}
