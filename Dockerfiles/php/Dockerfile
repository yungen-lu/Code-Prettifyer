FROM php:fpm-alpine
RUN apk update
RUN apk add cppcheck
RUN apk add build-base
RUN apk add shadow
RUN usermod -u 1000 www-data
RUN groupmod -g 1000 www-data
