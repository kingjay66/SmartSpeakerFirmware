obj-m += smart_speaker_driver.o

CC			:= /usr/bin/aarch64-linux-gnu-gcc-13

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

