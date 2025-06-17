#!/usr/bin/env bash
cmake -S . -B build > /dev/null
make -C build
./build/ConcurrencyInAction