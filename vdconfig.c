



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
    if(currblock == 0)//el bloque no existe
    {
     currblock = nextfreeblock();
      //El bloque encontrdo ponerlo donde apunta el apuntador al bloque actual
      *currptr = currblock;
      assignblock(currblock);//Asignarlo en el mapa de bits
      
      //Esccribir en el sector de la tabla de nodos i en el disco
      sector = (currinode/8);
      
      result = vdwriteseclog(inicio_nodos_i + sector, &inode[sect8]);
      
      //Si bloquee de pos actual no está en mem, lee el buffer del archivo
      if(openfiles[fd].currbloqueenmemoria!=currblock)
      {
       //Lee el bloque actual hasta el buffer que ***
        ****open
      }
      //Copia el caracter al buffer
      openfiles_[fd].buffer[openfiles[fd].curpos%TAMBLOQUE] = fer[cont];
      //incrementa posición actual del actual
      openfiles[fd].curpos++;
      //Si la posición es mayor que el tamaño, modifica el tamaño
      if(openfiles[fd].currpos > inode[currinode].size)
      {
       inode[openfiles[fd].inode].size = openfiles[fd].currpos;
      }
      cont++;
      //Si se llena el buff, escribelo
      if(openfiles[fd].currpos%TAMBLOQUE==0)
        writeblock(currblok, openfiles[fd].buffer);
      return(cont);
      //TODO en vdclose hay que escribir el archivo **********
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








