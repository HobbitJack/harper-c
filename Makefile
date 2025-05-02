libharper.so:
	cargo build --release

install: libharper.so
	cp -f ./target/release/libharper.so /usr/local/lib/libharper.so

install-docs:
	rm -f ./harper.h.3.gz
	gzip -k ./harper.h.3
	cp -f ./harper.h.3.gz /usr/local/share/man/man3/harper.h.3.gz

install-header:
	cp -f ./harper.h /usr/local/include/harper.h

install-all: libharper.so
	install
	install-docs
	install-header

uninstall:
	rm -r /usr/local/lib/libharper.so

clean:
	rm -rf ./target
	rm -f ./harper.h.3.gz
	rm -f ./example

example: libharper.so
	cc -o example -L./target/release/ -lharper example.c