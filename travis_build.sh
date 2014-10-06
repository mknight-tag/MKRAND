#!/bin/bash
# Script run in the travis CI

set -e

autoreconf -i
./configure
make
