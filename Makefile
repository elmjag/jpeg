CFLAGS := -g $(shell pkg-config --cflags sdl2)
LDFLAGS := $(shell pkg-config --libs sdl2)

all: tst proc

proc: proc.c yuv.c vdbg.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

tst: tst.c
	$(CC) tst.c $(CFLAGS) $(LDFLAGS) -o tst

decode: decode.c encode.c vdbg.c mat.c codex.c
	$(CC) decode.c encode.c codex.c vdbg.c mat.c $(CFLAGS) $(LDFLAGS) -o decode

clean:
	rm -rfv tst decode proc
