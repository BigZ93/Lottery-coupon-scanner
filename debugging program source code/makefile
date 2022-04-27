default: main.cpp
	g++ -std=c++11 -c distance.cpp -o distance.o
	g++ -std=c++11 -c ccomponent.cpp -o ccomponent.o
	g++ -std=c++11 -c parameters.cpp -o parameters.o
	g++ -std=c++11 -c wager.cpp -o wager.o
	g++ -std=c++11 -c report.cpp -o report.o
	g++ -std=c++11 -c modes.cpp -o modes.o
	g++ -std=c++11 -c basecoupon.cpp -o basecoupon.o
	g++ -std=c++11 -c photo.cpp `pkg-config opencv --cflags --libs` -o photo.o
	g++ -std=c++11 -c mycoupon.cpp -o mycoupon.o
	g++ -std=c++11 -c controllines.cpp `pkg-config opencv --cflags --libs` -o controllines.o
	g++ -std=c++11 -c markings.cpp `pkg-config opencv --cflags --libs` -o markings.o
	g++ -std=c++11 -c scanner.cpp `pkg-config opencv --cflags --libs` -o scanner.o
	g++ -std=c++11 -c main.cpp `pkg-config opencv --cflags --libs` -o main.o
	g++ -std=c++11 main.o distance.o ccomponent.o parameters.o wager.o report.o modes.o basecoupon.o photo.o mycoupon.o controllines.o markings.o scanner.o `pkg-config opencv --cflags --libs`
