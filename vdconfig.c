



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
  
  //Copiar byte por byte del buffer que recibo com argumento al buffer del archivo
  while(cont < bytes)
  {
    //Obtener la direción de donde está el bloque que corresponde a la posición actual
    currptr = currpostoptr(fd);
    if(currptr == NULL)
      reutnr (-1);
    
    //Cuál es el bloque que en el que escribíamos
    currblock = *currptr;
    
    //Si el bloque está en blanco, dale uno
    if(currblock == 0)
    {
     currblock = nextfreeblock();
      //El bloque encontrdo ponerlo donde
      
    }
  }
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








