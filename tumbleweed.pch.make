obj/tumbleweed.pch: src/tumbleweed.h
	@clang++ -std=c++2a -x c++-header src/tumbleweed.h -Iinclude/skia_include -Iinclude -o obj/tumbleweed.pch
clean:
	@del obj\tumbleweed.pch