obj/tumbleweed.pch: include/tumbleweed.h
	@clang++ -std=c++2a -x c++-header include/tumbleweed.h -Iinclude/external/skia -Iinclude/external -o obj/tumbleweed.pch
clean:
	@del obj\tumbleweed.pch