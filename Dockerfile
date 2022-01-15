FROM alpine:3 as buildbase
RUN apk add musl-dev gcc cmake samurai

FROM buildbase as build
RUN apk add libmicrohttpd-dev jansson-dev curl-dev
RUN mkdir -p /home/workspace/src /home/workspace/build
WORKDIR /home/workspace/build
COPY ./ ../src/
RUN cmake -S ../src -B ../build -G Ninja
RUN ninja

FROM alpine:3 as run
RUN apk add --no-cache libmicrohttpd jansson libcurl
RUN mkdir -p /home/app
WORKDIR /home/app
COPY --from=build /home/workspace/build/c-api .
EXPOSE 80
ENTRYPOINT ./c-api 80 4
