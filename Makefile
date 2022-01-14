docker-build:
	docker build -t c-api .

docker-run:
	docker run -P c-api

docker-ports:
	docker ps --filter "ancestor=c-api" --format "{{.Ports}}"
