import matplotlib.pyplot as plt

xReal = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
yReal = [1, 1, 2, 4, 6, 7, 6, 9, 6, 8, 10, 12, 14, 16, 19, 25]
xReg = [i/100 for i in range(0, 1500)]
yRegLin = [1.32059 * i - 0.779412 for i in xReg]
yRegPara = [0.0833333 * i * i + 0.0705882 * i + 2.13725 for i in xReg]

plt.title("Courbes de régression")
plt.scatter(xReal, yReal)
plt.plot(xReg, yRegLin, label="Linéaire")
plt.plot(xReg, yRegPara, label="Parabolique")
plt.legend()
plt.savefig("output.png")
plt.show()
