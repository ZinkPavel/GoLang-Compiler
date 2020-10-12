#!/bin/bash

./bin/app
./bin/app --dump-tokens
./bin/app --dump-ast
./bin/app --dump-symbol-table
./bin/app --tests

gcc -no-pie output/output.s -o output/output

./output/output