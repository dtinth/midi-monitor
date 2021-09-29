mini-monitor:
	g++ -I/usr/include/rtmidi -lrtmidi --std=c++14 main.cpp -omidi-monitor
