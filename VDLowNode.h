
#ifndef VDLOWNODE_H
#define VDLOWNODE_H


// Escribir en la tabla de nodos-I del directorio raíz, los datos de un archivo
int setninode(int num, char *filename,unsigned short atribs, int uid, int gid);

// Buscar en la tabla de nodos I, el nodo I que contiene el 
// nombre del archivo indicado en el apuntador a la cadena
// Regresa el número de nodo i encontrado
// Si no lo encuentra, regresa -1
int searchinode(char *filename);

// Eliminar un nodo I de la tabla de nodos I, y establecerlo 
// como disponible
int removeinode(int numinode);

#endif /* VDLOWNODE_H */
