# Dockerfile
FROM ubuntu:22.04

# Отключаем интерактивный режим apt
ENV DEBIAN_FRONTEND=noninteractive

# Устанавливаем необходимые пакеты: компилятор, make, библиотеку check, lcov и valgrind
RUN apt-get update && apt-get install -y \
    build-essential \
    check \
    lcov \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

# Устанавливаем рабочую директорию
WORKDIR /app

# Копируем файлы проекта
COPY . /app

# Собираем проект (цель test в вашем Makefile)
RUN make test

CMD ["valgrind", "--tool=memcheck", "--leak-check=yes", "--track-origins=yes", "./matrix"]