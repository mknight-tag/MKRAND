#!/bin/bash
# Script run in the travis CI

autoreconf -i
./configure
make
