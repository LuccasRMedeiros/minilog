#! /bin/bash

help() {
	cat << EOF 
This script is used to build this project and perform some simple tasks, like
generate a "tags" file using "ctags" command, and symlink the 
"compile_options.json" to the root of the project so language servers can find
it.

It also cleans everything.

call it with either:
  --build | To build the project
  --clean | To clean the project
  --help  | Displays this message
EOF
}

build() {
	ctags -R --languages=C --exclude=.ccls-cache --exclude=build .
	mkdir -p build
	cd build
	cmake ..
	make -j12
	cd ..
	ln -s build/compile_options.json .
}

clean() {
	rm -rf build
	rm -f compile_options.json
	rm -f tags
	rm -f minilog.a
}

case $1 in
	"--build")
		build
		;;
	"--clean")
		clean
		;;
	"--help")
		help
		;;
	*)
		echo "Invalid option"
		help
		;;
esac
