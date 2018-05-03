
#define HEADS 8
#define SECTORS 27
#define CYLINDERS 200 
#define TOTAL_SECTORS (HEADS*SECTORS*CYLINDERS)

//////////////////////////////////////////////////
//												//
// Funciones para la gestión de los archivos	//
//												//
//////////////////////////////////////////////////
vdcreat();

vdopen();

vdread();

vdwrite();

vdclose();

vdseek();

vdunlink();

//////////////////////////////////////////////////////////
//														//
// Funciones para el manejo de nodos i a bajo nivel.	//
//														//
//////////////////////////////////////////////////////////
setninode();

searchinode();

removeinode();

//////////////////////////////////////////////////////////////
//															//
// Funciones para el manejo de los mapas de bits, 			//
// tanto el de nodos i como el de mapa de bits de bloques	//
//															//
//////////////////////////////////////////////////////////////
Isinodefree();

nextinodefree();

assigninode();

unassiginode();

Isblockfree();

nextfreeblock();

assignblock();

uniassignblock();

//////////////////////////////////////////////////////////
//														//
// Funciones para leer y escribir bloques del disco		//
//														//
// Requiere datos de la donde inician y terminan 		//
// los mapas de bits, estos están en el sector de boot  //
// de la partición Se requiere también el tamaño de los //
// bloques y dónde inicia el área de datos o bloque		//
//////////////////////////////////////////////////////////
writeblock();

readblock();

//////////////////////////////////////////////////////
//													//
// Lectura y escritura de sectores lógicos			//
//													//
// Requiere datos de la geometría de la partición.	//
// Obtener de la tabla de particiones del MBR		//
//////////////////////////////////////////////////////

vdreadsl(int unidad_lógica_o_partición,int sectorlog,char *buffer);

vdwritesl(int unidad_lógica_o_partición,int sectorlog,char *buffer);




