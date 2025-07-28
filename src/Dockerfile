FROM ubuntu:22.04

# отключаем все вопросы apt
ENV DEBIAN_FRONTEND=noninteractive

# 1) ставим утилиты и исходники gtest
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      build-essential \
      cmake \
      git \
      lcov \
      valgrind \
      libgtest-dev \
 && rm -rf /var/lib/apt/lists/*

# 2) собираем и инсталлируем gtest из /usr/src/gtest
RUN cd /usr/src/gtest && \
    cmake -S . -B build && \
    cmake --build build && \
    cp build/*.a /usr/lib/


# 3) рабочая папка вашего проекта
WORKDIR /app
COPY . .

# 4) собираем и запускаем тесты
#    предположим, что у вас в корне есть Makefile, который знает, как линковаться с gtest
RUN mkdir build && cd build \
 && cmake .. \
 && make

# по умолчанию — прогон тестов под valgrind’ом
CMD ["valgrind", "--tool=memcheck", "--leak-check=yes", "--track-origins=yes", "./build/test_matrix"]