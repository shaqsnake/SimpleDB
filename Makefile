db: src/db.c
	mkdir -p build
	clang src/db.c -o build/db

run: db
	build/db simple.db

test: db
	bundle exec rspec
