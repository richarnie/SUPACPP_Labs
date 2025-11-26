CC=g++
FLAGS=-std=c++20 -w
TARGET=AnalyseData
OBJECTS=AnalyseData.o CustomFunctions.o
METHODS=CustomFunctions.cxx

${TARGET}: ${OBJECTS}
	${CC} ${FLAGS} ${OBJECTS} -o ${TARGET}
	@make clean

AnalyseData.o : AnalyseData.cxx
	${CC} ${FLAGS} -c AnalyseData.cxx

CustomFunctions.o : CustomFunctions.cxx
	${CC} ${FLAGS} -c CustomFunctions.cxx

clean:
	@rm -f *.o *~

cleantarget:
	@rm -f ${TARGET}
