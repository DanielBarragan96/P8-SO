all:
	gcc -o dumpsec dumpsec.c vdisk.o
	gcc -c VDSecLogOperation.c
	gcc -c VDBlockOperation.c 
	gcc -c VDNodeOperation.c


clean:
	-f dumpsec
	-f VDSecLogOperation
	-f VDBlockOperation
	-f VDNodeOperation
	-f VDLowNode
	-f VDTopOperation
	-f shellvd
