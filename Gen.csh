#!/bin/bash
for N in  3 4 5 6 7  ; do
   for I in  1 2 3 4 5 ; do
      ./Gen $N "ex_"$N"."$I
   done
done
