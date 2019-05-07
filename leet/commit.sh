#!/bin/bash

rm -f *_bm
rm -f *_test
rm -f core

git add *.cpp
git commit -m 'add file'
git push
