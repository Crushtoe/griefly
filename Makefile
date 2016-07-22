.PHONY: all
all: Exec/KVEngine

.PHONY: travis-get-deps
travis-get-deps:
	sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
	sudo add-apt-repository -y ppa:george-edison55/cmake-3.x
	sudo apt-get update -qq
	sudo apt-get install -y g++-4.9
	sudo apt-get install -y libsfml-dev
	sudo apt-get install -y zlib1g-dev libpng-dev lcov
	sudo apt-get install -y qtbase5-dev
	sudo apt-get install -y cmake
	gem install coveralls-lcov

.PHONY: clean
clean:
	rm -rf build
	rm -f Exec/KVEngine Exec/Launcher Exec/metadata.json

Exec/KVEngine: install

.PHONY: install
install: build
	cp build/KVEngine Exec
	cp build/Launcher Exec
	cp build/metadata.json Exec

.PHONY: build
build:
	mkdir -p build
	cd build && cmake ../ -DBUILD_TESTS=ON -DBUILD_COVER=ON
	$(MAKE) -C build
