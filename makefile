vdl: vdl.o logger.o serial.o nmea.o dlgps.o sensehat.o
	g++ -g -o vdl vdl.o logger.o serial.o nmea.o dlgps.o sensehat.o -lm -lRTIMULib
vdl.o: vdl.cpp vdl.h logger.h serial.h nmea.h dlgps.h
	g++ -g -c vdl.cpp
logger.o: logger.cpp logger.h serial.h nmea.h dlgps.h
	g++ -g -c logger.cpp
serial.o: serial.cpp serial.h
	g++ -g -c serial.cpp
dlgps.o: dlgps.cpp dlgps.h
	g++ -g -c dlgps.cpp
nmea.o: nmea.cpp nmea.h
	g++ -g -c nmea.cpp
sensehat.o: sensehat.cpp sensehat.h
	g++ -g -c sensehat.cpp
clean:
	touch *
	rm *.o
