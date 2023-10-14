include Makefile.inc

SAMPLE_DATA=0001-sampleDataModule.bin

all: utilsModule sampleDataModule

utilsModule:
	cd utils; make

sampleDataModule:
	printf "This is sample data." >> $(SAMPLE_DATA) && dd if=/dev/zero bs=1 count=1 >> $(SAMPLE_DATA)

clean:
	cd utils; make clean
	rm -rf *.bin


.PHONY: utilsModule all clean

