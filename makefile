# -lXi -lXmu assuming these were needed for WSL?

LIBS = -lglut -lGLEW -lGLU -lm -lGL

lab6: lab6.c myLib.o initShader.o
	gcc -o lab_6 lab6.c myLib.o initShader.o $(LIBS)

lab6_ctm: lab6_ctm.c initShader.o
	gcc -o lab6_ctm lab6_ctm.c initShader.o $(LIBS)

initShader.o: initShader.c initShader.h
	gcc -c initShader.c

myLib.o: myLib.c myLib.h
	gcc -c myLib.c
