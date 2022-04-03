build:
	make -C src all
	docker build -t acgi .

buildnocache:
	make -C src all
	docker build --no-cache -t acgi .

clean:
	make -C src clean
	docker rmi -f acgi

run:
	docker run --name=acgi -p 8080:80 --rm -ti acgi

shell:
	docker exec -ti acgi /bin/sh
