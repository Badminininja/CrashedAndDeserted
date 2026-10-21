# Build environment for the C++ game (and its googletest unit tests).
# Pinned to Ubuntu 24.04, whose g++ 13 / CMake 3.28 are verified to build this.
FROM ubuntu:24.04

RUN apt-get update \
    && apt-get install -y --no-install-recommends build-essential cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# The CMake project lives in this nested folder and ships its own googletest
# copy, so no git submodules are needed to build.
COPY CrashedAndDeserted/CrashedAndDeserted/ ./

# Configure and compile. Produces ./build/game and ./build/test.
RUN cmake -S . -B build && cmake --build build -j

# By default, launch the game. It reads keyboard input, so run it with a
# terminal attached (docker compose run does this; see docker-compose.yml).
CMD ["./build/game"]
