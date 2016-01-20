import subprocess
import itertools
import numpy as np
import matplotlib.pyplot as plt


if __name__ == '__main__' :
  conventionnelT = []
  for i in range(3,7):
    results = []
    for j in itertools.permutations(range(1,6),2):
      results.append(float(subprocess.check_output("./conventionnelT -f ex_{}.{} ex_{}.{}".format(i,j[0],i,j[1]),shell=True)))
    conventionnelT.append(np.average(results))
    print("{}\t{}".format(i,conventionnelT[-1]))
  plt.plot(conventionnelT,range(3,10))
  plt.show()
  print(conventionnelT)
