hoc2:	hoc.o
		cc hoc.o -o hoc2

hoc.o:	y.tab.c
		cc -c y.tab.c -o hoc.o

y.tab.c:hoc2.y
		yacc hoc2.y
