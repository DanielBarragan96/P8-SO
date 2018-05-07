



//////////////////////////////////////////////////
//												//
// Funciones para la gestión de los archivos	//
//												//
//////////////////////////////////////////////////
vdcreat()
{

}

vdopen()
{

}

vdread()
{

}

int vdwrite(int fd, char *buffer, int bytes)
{
  int currblock, currinode, cont =0, sector, i, result;
  unsigned shot *currptr;
  
  //Si no está abierto, regresa error
  if(openfiles[fd].inuse == 0)
    return (-1);
  
  currinode = openfiles[fd].inode;
  
  //Copiar byte por byte 
}

vdclose()
{

}

vdseek()
{

}

vdunlink()
{

}

//////////////////////////////////////////////////////////
//														//
// Funciones para el manejo de nodos i a bajo nivel.	//
//														//
//////////////////////////////////////////////////////////
setninode()
{

}

searchinode()
{

}

removeinode()
{

}

//////////////////////////////////////////////////////////////
//															//
// Funciones para el manejo de los mapas de bits, 			//
// tanto el de nodos i como el de mapa de bits de bloques	//
//															//
//////////////////////////////////////////////////////////////
Isinodefree()
{

}

nextinodefree()
{

}

assigninode()
{

}

unassiginode()
{

}

Isblockfree()
{

}

nextfreeblock()
{

}

assignblock()
{

}

uniassignblock()
{

}

//////////////////////////////////////////////////////
//													//
// Funciones para leer y escribir bloques del disco	//
//													//
//////////////////////////////////////////////////////
writeblock()
{

}

readblock()
{

}



//////////////////////////////////////////////////////
//													//
// Lectura y escritura de sectores lógicos			//
//													//
//////////////////////////////////////////////////////
vdreadsl(int unidad_lógica_o_partición,int sectorlog,char *buffer)
{

}

vdwritesl(int unidad_lógica_o_partición,int sectorlog,char *buffer)
{

}








