#include "VDTopOperation.h"
#include "DataTypeDefinitions.h"


int vdopen(char *filename,unsigned short mode)
{
	int numinode;
	int i;
	
	// Poner el archivo en la tabla de archivos abiertos
	// Establecer el archivo como abierto
	if(!openfiles_inicializada)
	{
		// La primera vez que abrimos un archivo, necesitamos
		// inicializar la tabla de archivos abiertos
		for(i=0;i<24;i++)
		{
			openfiles[i].inuse=0;
			openfiles[i].currbloqueenmemoria=-1;
		}
		openfiles_inicializada=1;
	}
	
	numinode=searchinode(filename);
	
	i=0;
	while(openfiles[i].inuse && i<24)
		i++;

	if(i>=24)			// Llegamos al final y no hay lugar
		return(-1);

	openfiles[i].inuse=1;		// Poner el archivo en uso
	openfiles[i].inode=numinode; 	// Indicar que inodo es el del archivo abierto
	openfiles[i].currpos=0; 	// Y la posición inicial del archivo es 0
	
	return(i);
}

int vdread(int fd, char *buffer, int bytes)
{	//return: -1 -> error; 1 -> OK; 2 -> NO BLOCKS
	int currblock;
	int currinode;
	int cont=0;
	int sector;
	int i,j;
	int result;
	unsigned short *currptr;
		
	// Si no está abierto, regresa error
	if(openfiles[fd].inuse==0)
		return(-1);

	currinode=openfiles[fd].inode;
	
	// Copiar byte por byte del buffer que recibio como argumento al buffer del archivo
	while(cont<bytes)
	{
		// Obtener la direccion de donde esta el bloque que corresponde a la posicion actual
		currptr=currpostoptr(fd);
		if(currptr==NULL)
			return(-1);
	
		// Cual es el bloque en el que escibiriamos
		currblock=*currptr;

		// Si el bloque está en blanco, se regresa
		if(currblock==0)
		{
			return(0);
		}
		// Si el bloque de la posición actual no está en memoria
		// Lee el bloque al buffer del archivo
		if(openfiles[fd].currbloqueenmemoria!=currblock)
		{
			// Leer el bloque actual hacia el buffer que
			// está en la tabla de archivos abiertos
			readblock(currblock,openfiles[fd].buffer);			
			// Actualizar en la tabla de archivps abiertos
			// el bloque actual
			openfiles[fd].currbloqueenmemoria=currblock;
		}

		// Copia el caracter al buffer
		buffer[cont]=openfiles[fd].buffer[openfiles[fd].currpos%TAMBLOQUE];

		// Incrementa posición actual del actual
		openfiles[fd].currpos++;

		// Incrementa el contador
		cont++;
	}
	
	return(cont);
}

int vdclose(int fd)
{
	if(fd < 0 || fd > 23)
		return(-1);
	
	openfiles[fd].inuse=-1;	   // poner el iNODE como libre
	openfiles[fd].inode=NULL;  // el nodo ahora no apunta a nada
	
	return(1);
}



// Esta función se va a usar para crear una función en el sistema de archivos
int vdcreat(char *filename,unsigned short perms)
{
	int numinode;
	int i;

	// Ver si ya existe el archivo
	numinode=searchinode(filename);
	if(numinode==-1) // Si el archivo no existe
	{
		// Buscar un inodo en blanco en el mapa de bits (nodos i)
		numinode=nextfreeinode(); // Recorrer la tabla de nodos i buscando
					  // un inodo que esté libre
		if(numinode==-1) // La tabla de nodos-i está llena
		{
			return(-1); // No hay espacio para más archivos
		}
	} else{	// Si el archivo ya existe, elimina el inodo
		removeinode(numinode);
	}

// Escribir el archivo en el inodo encontrado en un inodo de la tabla, y los datos del archivo
	setninode(numinode,filename,perms,getuid(),getgid());
		
	assigninode(numinode);

	// Poner el archivo en la tabla de archivos abiertos
	// Establecer el archivo como abierto
	if(!openfiles_inicializada)
	{
		// La primera vez que abrimos un archivo, necesitamos
		// inicializar la tabla de archivos abiertos
		for(i=0;i<24;i++)
		{
			openfiles[i].inuse=0;
			openfiles[i].currbloqueenmemoria=-1;
		}
		openfiles_inicializada=1;
	}

	// Buscar si hay lugar en la tabla de archivos abiertos; si no hay lugar, regresa -1
	i=0;
	while(openfiles[i].inuse && i<24)
		i++;

	if(i>=24)		// Llegamos al final y no hay lugar
		return(-1);

	openfiles[i].inuse=1;	// Poner el archivo en uso
	openfiles[i].inode=numinode;  // Indicar que inodo es del archivo abierto
	openfiles[i].currpos=0; // Y la posición inicial del archivo es 0
	return(i);
}

// Esta es la función más difícil, 
int vdwrite(int fd, char *buffer, int bytes)
{
	int currblock;
	int currinode;
	int cont=0;
	int sector;
	int i;
	int result;
	unsigned short *currptr;

	// Si no está abierto, regresa error
	if(openfiles[fd].inuse==0)
		return(-1);

	currinode=openfiles[fd].inode;

	// Copiar byte por byte del buffer que recibo como argumento al buffer del archivo
	while(cont<bytes)
	{
		// Obtener la dirección de donde está el bloque que corresponde
		// a la posición actual
		currptr=currpostoptr(fd);
		if(currptr==NULL)
			return(-1);
	
		// Cuál es el bloque en el que escibiríamos
		currblock=*currptr;

		// Si el bloque está en blanco, dale uno
		if(currblock==0)
		{
			currblock=nextfreeblock();
			// El bloque encontrado ponerlo en donde
			// apunta el apuntador al bloque actual
			*currptr=currblock;
			assignblock(currblock);	// Asignarlo en el mapa de bits
			
			// Escribir el sector de la tabla de nodos i
			// En el disco
			sector=(currinode/8);
			result=vdwriteseclog(0,inicio_nodos_i+sector,&inode[sector*8]);
		}

		// Si el bloque de la posición actual no está en memoria
		// Lee el bloque al buffer del archivo
		if(openfiles[fd].currbloqueenmemoria!=currblock)
		{
			// Leer el bloque actual hacia el buffer que
			// está en la tabla de archivos abiertos
			readblock(currblock,openfiles[fd].buffer);			
			// Actualizar en la tabla de archivps abiertos
			// el bloque actual
			openfiles[fd].currbloqueenmemoria=currblock;
		}

		// Copia el caracter al buffer
		openfiles[fd].buffer[openfiles[fd].currpos%TAMBLOQUE]=buffer[cont];

		// Incrementa posición actual del cursor del archivo
		openfiles[fd].currpos++;

		// Si la posición es mayor que el tamaño, modifica el tamaño
		if(openfiles[fd].currpos>inode[currinode].size)
			inode[openfiles[fd].inode].size=openfiles[fd].currpos;

		// Incrementa el contador
		cont++;

		// Si se llena el buffer, escríbelo
		if(openfiles[fd].currpos%TAMBLOQUE==0)
			writeblock(currblock,openfiles[fd].buffer);
	}
	if(openfiles[fd].currpos%TAMBLOQUE!=0)
		writeblock(currblock, openfiles[fd].buffer);
		
	return(cont);
}

int vdseek(int fd, int offset, int whence)
{
	unsigned short oldblock,newblock;
	short* temp;

	// Si no está abierto regresa error
	if(openfiles[fd].inuse==0)
		return(-1);  // Regresar ERROR

	/* La función currpostoptr es una función que a partir de 
	la posición actual del apuntador del archivo, 
	regresa la dirección de memoria en el nodo i o 
	el bloque de apuntadores que contiene el bloque
	donde está el puntero del archivo */
	temp = (currpostoptr(fd));
	oldblock = *temp;
		
	if(whence==0) // A partir del inicio
	{
		// Si el offset está antes del inicio, o después del final, regresar un error
		if(offset<0||offset>inode[openfiles[fd].inode].size)
			return(-1);
		openfiles[fd].currpos=offset;

	} else if(whence==1) // A partir de la posición actual
	{

		// Validar posiciones dentro de los arreglos para evitar segmentation fault
		if(openfiles[fd].currpos+offset>inode[openfiles[fd].inode].size || openfiles[fd].currpos+offset<0)
		return(-1);
		openfiles[fd].currpos+=offset;

	} else if(whence==2) // A partir del final
	{
		if(offset>inode[openfiles[fd].inode].size ||
		   openfiles[fd].currpos-offset<0)
			return(-1);
		openfiles[fd].currpos=inode[openfiles[fd].inode].size-offset;
	} else
		return(-1);

	// Verificamos si la nueva posición del puntero es un
	// bloque diferente al que estábamos,si es así hay que
	// cargar ese bloque a memoria
	temp = currpostoptr(fd);
	newblock = *temp;
	
	// Después de mover el puntero, se cambia a otro bloque
	if(newblock!=oldblock)
	{
		// Escribir el bloque viejo
		writeblock(oldblock,openfiles[fd].buffer);
		// Leer el bloque nuevo
		readblock(newblock,openfiles[fd].buffer);
		// Indicar el nuevo bloque como bloque actual en la tabla de archivos abiertos
		openfiles[fd].currbloqueenmemoria=newblock;
	}

	// Regresamos la posición actual del archivo
	return(openfiles[fd].currpos);
}

// Borrar un archivo del sistema de archivos
int vdunlink(char *filename)
{
	int numinode;
	int i;

	// Busca el inodo del archivo
	numinode=searchinode(filename);
	if(numinode==-1)
		return(-1); // No existe

	removeinode(numinode);
	
	inode[numinode] = emptyinode; // = &emptynode[0]
	
	for(i=0;i<secboot.sec_tabla_nodos_i;i++){
		vdwriteseclog(0, sl_nodosi+i,&inode[i*8]);
	}
}

