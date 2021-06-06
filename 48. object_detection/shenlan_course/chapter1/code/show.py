'''
Author: Liu Weilong
Date: 2021-06-06 18:02:48
LastEditors: Liu Weilong
LastEditTime: 2021-06-06 18:08:34
Description: 
画精度召回率曲线

'''

import matplotlib.pyplot as plt

plt.figure("精度召回率曲线")
plt.xlabel("Recall")
plt.ylabel("Precision")
plt.plot([0.8],[0.6667],'o')
plt.show()
