obj-m += kpanic.o

all:
	make -C /lib/modules/6.4.7-arch1-1/build M=. modules

clean:
	make -C /lib/modules/6.4.7-arch1-1/build M=. clean
