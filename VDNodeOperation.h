#ifndef VDNODEOPERATION_H
#define VDNODEOPERATION_H

// *************************************************************************
// Para el mapa de bits del área de nodos i
// *************************************************************************

// Usando el mapa de bits, determinar si un nodo i, está libre u ocupado.
int isinodefree(int inode);

// Buscar en el mapa de bits, el primer nodo i que esté libre, es decir, que su bit está en 0, me regresa ese dato
int nextfreeinode();

// Poner en 1, el bit que corresponde al número de inodo indicado
int assigninode(int inode);

// Poner en 0, el bit que corresponde al número de inodo indicado
int unassigninode(int inode);

// Usando la información del mapa de bits del area de datos, saber si un bloque está libre o no
int isblockfree(int block);

// Usando el mapa de bits, buscar el siguiente bloque libre
int nextfreeblock();

// Asignar un bloque en 1 en el mapa de bits, lo cual significa que estaría ya ocupado.
int assignblock(int block);

// Poner en 0 el bit que corresponde a un bloque en el mapa de bits, esto equivale a decir que el bloque está libre
int unassignblock(int block);

unsigned short *postoptr(int fd,int pos);

short* currpostoptr(int fd);

#endif /* VDNODEOPERATION_H */
