#!/bin/sh

for i in 0; do curl -o $i.gif https://www.animatedimages.org/data/media/712/animated-number-image-002$i.gif; done
for i in `seq 1 9`; do curl -o $i.gif https://www.animatedimages.org/data/media/712/animated-number-image-001$i.gif; done

