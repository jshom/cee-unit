FROM ubuntu:18.04

RUN apt-get update \
    && apt-get install g++ valgrind -y --no-install-recommends \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
