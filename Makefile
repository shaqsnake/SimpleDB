db: src/db.c
	gcc src/db.c -o build/db

run: db
	build/db

test: db
	bundle exec rspec