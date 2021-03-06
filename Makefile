all:
	gcc -o dumpsec dumpsec.c vdisk.o
	gcc -c VDSecLogOperation.c
	gcc -c VDBlockOperation.c 
	gcc -c VDNodeOperation.c
	gcc -c VDLowNode.c
	gcc -c VDTopOperation.c
	gcc -o vdformat format.c vdisk.o
	gcc -o shellvd shell.c vdisk.o
	
	

clean:
	-f dumpsec
	-f VDSecLogOperation
	-f VDBlockOperation
	-f VDNodeOperation
	-f VDLowNode
	-f VDTopOperation
	-f vdformat
	-f shellvd
