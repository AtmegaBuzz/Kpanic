obj-m += kpanic.o

all:
	make -C /lib/modules/6.1.39-1-lts/build M=. modules

clean:
	make -C /lib/modules/6.1.39-1-lts/build M=. clean
