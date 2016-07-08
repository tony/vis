WATCH_FILES=find . -type f -not -path '*/\.*' -and -not -path '*/build/*' | grep -i '.*[.]\(c\|cc\|h\|hh\)$$' 2> /dev/null


test:
	./test/run

mkdir_build:
	[ -d ./build ] | mkdir -p build

entr_warn:
	@echo "----------------------------------------------------------"
	@echo "     ! File watching functionality non-operational !      "
	@echo ""
	@echo "Install entr(1) to automatically run tasks on file change."
	@echo "See http://entrproject.org/"
	@echo "----------------------------------------------------------"


watch_debug:
	if command -v entr > /dev/null; then ${WATCH_FILES} | entr sh -c 'clear; $(MAKE) debug'; else $(MAKE) debug entr_warn; fi

format:
	clang-format *.{c,h}

run:
	./build/vis


build: mkdir_build
	cd build; cmake -GNinja ..
	ninja -C build


debug: mkdir_build
	cd build; cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ..
	ninja -C build
