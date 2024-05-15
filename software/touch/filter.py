from matplotlib import pyplot as plt
import numpy as np
import sys

def state_update(z, h):
    x = [0] * len(z)
    for i in range(1, len(z)):
        x[i] = x[i - 1] + h * (z[i] - x[i - 1])

    return x

def state_update2(z, h0, h1, sigma):
    x = [0] * len(z);
    for i in range(1, len(z)):
        h = (h0 - h1) / (sigma * i * 0.05 + 1) + h1
        #h = -sigma * i * 0.02 + h0
        if h < 0.0:
            h = h1
        x[i] = x[i - 1] + h * (z[i] - x[i - 1])

    return x

def state_update2_sigma(h0, h1, R, ts):
    return h0 / (R * h1 * ts)

def kf(z, r, q):
    x = [0] * len(z)
    Kn = [0] * len(z)
    p0 = 80;

    for i in range(1, len(z)):
        Kn[i] = p0 / (p0 + r)
        p1 = (1 - Kn[i]) * p0
        x[i] = x[i - 1] + Kn[i] * (z[i] - x[i - 1])

        p0 = p1 + q

    return x, Kn

x = []
y = []
xtmp = 0
ytmp = 0

with open(sys.argv[1], 'r') as f:
    for line in f:
        digi = line.split("\t")
        try:
            xtmp = float(digi[0])
        except:
            continue

        try: 
            ytmp = float(digi[1])
        except:
            continue

        x.append(xtmp)
        y.append(ytmp)

x = np.array(x)
y = np.array(y)

print("STATE UPDATE")
xsu_fast = np.array(state_update(x[273:], 0.2))
xsu = np.array(state_update(x[273:], 0.03))
ysu = np.array(state_update(y, 0.2))

sigma = state_update2_sigma(1.0, 0.03, 0.05, 2.4)
print("sigma {}".format(sigma))
xsu2 = np.array(state_update2(x[273:], 10.0, 0.01, 300.0))
xsu3 = np.array(state_update2(x[273:], 12.0, 0.005, 200.0))
xstd = np.std(xsu)
ystd = np.std(ysu)
print(xstd, ystd)

print("KALMAN FILTER")
xkf, xKn = kf(x, 1, 0.03)
ykf, yKn = kf(y, 1, 0.1)

'''
plt.plot(x * 0.096, y * 0.0649, '.')
plt.plot(xsu * 0.096, ysu * 0.0649, '.')
'''
plt.plot(x[273:] * 0.096, '.', label='raw')
plt.plot(xsu * 0.096, label='su')
plt.plot(xsu_fast * 0.096, label='su fast')
plt.plot(xsu2 * 0.096, label='su1 0.03 277.7')
plt.plot(xsu3 * 0.096, label='testint')
plt.legend(loc='upper left')

# plt.plot(xKn)
plt.show()

