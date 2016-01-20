import subprocess
import itertools
import numpy as np
import math
import matplotlib.pyplot as plt


if __name__ == '__main__' :
  conventionnelT = []
  conventionnelT_deviation = []
  xaxis = [math.pow(2,x) for x in range(3,11)]
  for i in range(3,11):
    results = []
    for j in itertools.permutations(range(1,6),2):
      results.append(float(subprocess.check_output("./conventionnelT -f ex_{}.{} ex_{}.{}".format(i,j[0],i,j[1]),shell=True)))
    conventionnelT.append(np.average(results))
    conventionnelT_deviation.append(np.std(results))
    print("{}\t{}".format(i,conventionnelT[-1]))
  plt.plot(xaxis,conventionnelT)
  plt.plot(xaxis,conventionnelT_deviation)
  plt.show()
