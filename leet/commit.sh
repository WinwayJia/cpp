#!/bin/bash

rm -f *_bm
rm -f *_test

git add .
git commit -m 'add file'
git push
