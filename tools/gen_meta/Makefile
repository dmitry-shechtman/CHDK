topdir=../../

include $(topdir)makefile_tools.inc

HOSTCFLAGS+=-Wno-format

EXES=gen_meta_software$(EXE) gen_meta_modules$(EXE)

all: $(EXES)

gen_meta_software$(EXE): gen_meta_software.o cli.o meta.o sha256.o json.o
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

gen_meta_modules$(EXE): gen_meta_modules.o meta_modules.o cli.o meta.o sha256.o json.o
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

gen_meta_software.o: gen_meta_software.c cli.h $(modules)/meta.h $(modules)/json.h
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -I$(topdir)tools -c -o $@ $<

gen_meta_modules.o: gen_meta_modules.c cli.h $(modules)/meta_modules.h $(modules)/meta.h $(modules)/json.h
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -c -o $@ $<

cli.o: cli.c cli.h
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -c -o $@ $<

meta_modules.o: $(modules)/meta_modules.c $(modules)/meta.h $(modules)/sha256.h $(modules)/json.h
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -I$(include) -DGEN_META -c -o $@ $<

meta.o: $(modules)/meta.c $(modules)/meta.h $(modules)/sha256.h $(modules)/json.h
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -DGEN_META -c -o $@ $<

json.o: $(modules)/json.c $(modules)/json.h
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -c -o $@ $<

sha256.o: $(modules)/sha256.c $(modules)/sha256.h
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(EXES)

distclean: clean

include $(topdir)bottom.inc
