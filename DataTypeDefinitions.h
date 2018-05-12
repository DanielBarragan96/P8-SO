typedef struct {
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
}DATE;

typedef struct {
	int inuse;		// 0 cerrado, 1 abierto
	unsigned short inode;
	int currpos;
	int currbloqueenmemoria;
	char buffer[1024];
	unsigned short buffindirect[512]; //		
} OPENFILES;

typedef struct {
	char drive_status;	
	char chs_begin[3];
	char partition_type;
	char chs_end[3];
	int lba;
	int secs_partition;
}PARTITION;

typedef struct {
	char bootstrap_code[446];
	PARTITION partition[4];
	short boot_signature;
}MBR;

typedef struct {
	char name[18];
	unsigned int datetimecreat;	// 32 bits
	unsigned int datetimemodif;	// 32 bits
	unsigned int datetimelaacc; // 32 bits
	unsigned short uid;		// 16 bits
	unsigned short gid;		// 16 bits
	unsigned short perms;	// 16 bits
	unsigned int size;			// 32 bits
	unsigned short blocks[10];	// 10 x 16 bits = 20 bytes
	unsigned short indirect;	// 16 bits
	unsigned short indirect2;	// 16 bits
}INODE;

typedef struct {
	char jump[4];
	char nombre_particion[8];
	// Tabla de parámetros del bios
	// Están los datos sobre el formato de la partición
	unsigned short sec_inicpart;		// 1 sector
	unsigned char sec_res;		// 1 sector reservado para el sector de boot de la partición
	unsigned char sec_mapa_bits_area_nodos_i;// 1 sector
	unsigned char sec_mapa_bits_bloques;	// 6 sectores
	unsigned short sec_tabla_nodos_i;	// 3 sectores
	unsigned int sec_log_particion;		// 43199 sectores
	unsigned char sec_x_bloque;			// 2 sectores por bloque
	unsigned char heads;				// 8 superficies
	unsigned char cyls;				// 200 cilindros
	unsigned char secfis;				// 27 sectores por track
	char restante[484];	// Código de arranque
}SECBOOTPART;

OPENFILES openfiles[24] = {0};
MBR mbr;
INODE inode[24] = {0}, emptyinode = {0};
SECBOOTPART secboot;

char empty[512] = {0};
int sl_mb_nodosi;
int sl_mb_datos;
int sl_nodosi;
int sl_datos;
int sl_heads;
int sl_cyls;
int sl_secfis;
int SFIP;
int CIP;
int SIP;
int TAMBLOQUE;
char inodesmap[512] = {0};
char blocksmap[3072] = {0};
int openfiles_inicializada = 0;

int inicio_area_datos;
int secboot_en_memoria;
int mapa_bits_nodos_i;
int inodesmap_en_memoria;
int mapa_bits_nodos_i;
int sec_mapa_bits_bloques;
 //int TOTAL_NODOS_I = secboot.sec_tabla_nodos_i*8;


