Import('env')
env.Replace(FUSECMD="avrdude $UPLOADERFLAGS -e -Uefuse:w:0xFD:m -Ulfuse:w:0xFF:m -Uhfuse:w:0xDA:m")
