CC = cl
L = link
CFLAGS = /nologo /W4 /EHsc /DWIN /D_CRT_SECURE_NO_DEPRECATE

build: tema1.exe

tema1.exe: fctAux.obj main.obj opElem.obj opHash.obj hash.lib
	$(L) /nologo /out:$@ $**

hash.lib: hash.dll

main.obj: main.c
	$(CC) $(CFLAGS) /c $**
fctAux.obj: fctAux.c
	$(CC) $(CFLAGS) /c $**
opElem.obj: opElem.c
	$(CC) $(CFLAGS) /c $**
opHash.obj: opHash.c
	$(CC) $(CFLAGS) /c $**

clean:
	del /Q /F *.obj *.lib *.dll *.exe  *.exp
