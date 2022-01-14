docker-build:
	docker build -t c-api .

docker-run:
	docker run -itP c-api

docker-ports:
	docker ps --filter "ancestor=c-api" --format "{{.Ports}}"
