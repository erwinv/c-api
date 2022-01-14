FROM alpine:3 as build
RUN apk add build-base cmake samurai libmicrohttpd-dev jansson-dev
RUN mkdir -p /home/workspace/src /home/workspace/build
WORKDIR /home/workspace/build
COPY ./ ../src/
RUN cmake -S ../src -B ../build -G Ninja
RUN ninja

FROM alpine:3 as run
RUN apk add --no-cache libmicrohttpd jansson
RUN mkdir -p /home/app
WORKDIR /home/app
COPY --from=build /home/workspace/build/c-api .
EXPOSE 80
ENTRYPOINT ./c-api 80 4
