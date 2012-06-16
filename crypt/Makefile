CC= gcc
CFLAGS+= -pg
LDFLAGS= -lmcrypt -lmhash -pg
ctos_crypt: example.c crypt.c
	    $(CC) $(LDFLAGS)  -o $@ $^

.PHONY:

clean:
	-rm ctos_crypt
