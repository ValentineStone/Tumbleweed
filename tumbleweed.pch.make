obj/tumbleweed.pch:
	@clang++ -std=c++2a -x c++-header src/tumbleweed.h -Iskia_include -Iinclude -o obj/tumbleweed.pch
clean:
	@del obj\tumbleweed.pch