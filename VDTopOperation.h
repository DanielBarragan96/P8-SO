int vdopen(char *filename,unsigned short mode); //ustedes

int vdread(int fd, char *buffer, int bytes); //ustedes

int vdclose(int fd); //ustedes


// Esta función se va a usar para crear una función en el 
// sistema de archivos
int vdcreat(char *filename,unsigned short perms);

// Esta es la función más difícil, 
int vdwrite(int fd, char *buffer, int bytes);

int vdseek(int fd, int offset, int whence);

// Borrar un archivo del sistema de archivos
int vdunlink(char *filename);
