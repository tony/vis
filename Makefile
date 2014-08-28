include config.mk

SRC += vis.c colors.c editor.c text.c text-motions.c text-objects.c
ALL = ${SRC} util.h editor.h text.h text-motions.h text-objects.h \
	config.def.h config.mk Makefile LICENSE README vis.1
OBJ = ${SRC:.c=.o}

all: clean options vis

options:
	@echo vis build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

config.h:
#TODO	cp config.def.h config.h
	ln -fs config.def.h config.h

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

vis: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}
	@ln -sf $@ nano

debug: clean
	@make CFLAGS='${DEBUG_CFLAGS}'

clean:
	@echo cleaning
	@rm -f vis nano ${OBJ} vis-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p vis-${VERSION}
	@cp -R ${ALL} vis-${VERSION}
	@tar -cf vis-${VERSION}.tar vis-${VERSION}
	@gzip vis-${VERSION}.tar
	@rm -rf vis-${VERSION}

install: vis
	@echo stripping executable
	@strip -s vis
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f vis ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/vis
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < vis.1 > ${DESTDIR}${MANPREFIX}/man1/vis.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/vis.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/vis
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/vis.1

.PHONY: all options clean dist install uninstall debug