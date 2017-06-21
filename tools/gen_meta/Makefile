topdir=../../

include $(topdir)makefile_tools.inc

HOSTCFLAGS+=-Wno-format

EXES=gen_meta_software$(EXE) #gen_meta_modules$(EXE)

all: $(EXES)

gen_meta_software$(EXE): gen_meta_software.o gen_meta.o sha256.o
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

#gen_meta_modules$(EXE): gen_meta_modules.o gen_meta.o sha256.o
#	@echo $< \-\> $@
#	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

gen_meta_software.o: gen_meta_software.c gen_meta.h
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -I$(topdir)tools -c -o $@ $<

#gen_meta_modules.o: gen_meta_modules.c gen_meta.h
#	@echo $< \-\> $@
#	$(HOSTCC) $(HOSTCFLAGS) -c -o $@ $<

gen_meta.o: gen_meta.c gen_meta.h sha256.h
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -c -o $@ $<

sha256.o: sha256.c sha256.h
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(EXES)

distclean: clean

include $(topdir)bottom.inc
