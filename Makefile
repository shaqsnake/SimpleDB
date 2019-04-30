db: src/db.c
	mkdir -p build
	gcc src/db.c -o build/db

run: db
	build/db

test: db
	bundle exec rspec