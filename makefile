CXX = g++
CXXFLAGS = -MMD -L/usr/X11R6/lib -lX11 -lstdc++
EXEC = mario
OBJECTS = main.cpp canvas.cpp displayable.cpp mario.cpp block.cpp character.cpp sun.cpp eventListener.cpp  static.cpp grid.cpp cell.cpp utils.cpp canvasUnderlay.cpp introText.cpp enemy.cpp

${EXEC}:
	${CXX} -o ${EXEC} ${OBJECTS} ${CXXFLAGS} 

run:
	make; ./${EXEC}

clean:
	rm *.d ${EXEC}
