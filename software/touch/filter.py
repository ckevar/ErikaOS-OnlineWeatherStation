from matplotlib import pyplot as plt
import numpy as np
import sys

def average4(z):
    x = [0] * len(z)
    for i in range(3, len(z)):
        x[i] = (z[i] + z[i - 1] + z[i - 2] + z[i - 3]) / 4;

    return x

def weight_average4(z):
    x = [0] * len(z)
    for i in range(3, len(z)):
        x[i] = (z[i - 2] + z[i - 3]) / 2;

    return x

def middle_value(z):
    x = [0] * len(z)

    for i in range(3, len(z)):
        if(z[i] > z[i - 1]):
            xH = z[i]
            xL = z[i - 1]
        else:
            xH = z[i - 1]
            xL = z[i]

        if(xH < z[i - 2]):
            x[i] = xH
        else:
            if(xL > z[i - 2]):
                x[i] = xL
            else:
                x[i] = z[i - 2]

    return x

def averaging_da_closest(z):
    x = [0] * len(z)

    for i in range(3, len(z)):
        d0 = abs(z[i] - z[i - 1])
        d1 = abs(z[i - 1] - z[i - 2])
        d2 = abs(z[i - 2] - z[i])

        if(d0 < d1):
            if(d0 < d2):
                x[i] = z[i] + z[i - 1]
            else:
                x[i] = z[i] + z[i - 2]
        else:
            if(d1 < d2):
                x[i] = z[i - 1] + z[i - 2]
            else:
                x[i] = z[i] + z[i - 2]
        
        x[i] = x[i] / 2
    
    return x

def state_update(z, h):
    x = [0] * len(z)
    for i in range(1, len(z)):
        x[i] = x[i - 1] + h * (z[i] - x[i - 1])

    return x

def state_update2(z, h0, h1, sigma):
    x = [0] * len(z);
    for i in range(1, len(z)):
        h = (h0 - h1) / (sigma * i * 0.02 + 1) + h1
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

with open(sys.argv[1], 'r', errors='ignore') as f:
    for line in f:
        digi = line.split("\t")
        try:
            xtmp = float(digi[0])
            if (xtmp > 3000):
                continue
        except:
            continue
        '''
        try: 
            ytmp = float(digi[1])
        except:
            continue
        y.append(ytmp)
        '''
        x.append(xtmp)

i0 = 0
i1 = 15
x = np.array(x[i0:i1]) * (-0.1247) + 340 # 349 -> 247,
# y = np.array(y[i0:]) * 0.065 - 5
t = 0.02 * np.arange(0, len(x))
x_top = 225.0 * np.ones(len(x))

xa4 = np.array(average4(x))
xwa = weight_average4(x)
xmv = middle_value(x)
xac = averaging_da_closest(x)
xsu = state_update(x, 0.20)
xsu2 = state_update2(x, 40.0, 0.001, 750.0)
xsu3 = state_update2(x, 5.8, 0.001, 260.0)

print("Calibrated, std = {}".format(np.std(x)))
print("Average-4, std = {}".format(np.std(xa4)))
print("Weighted Average-4, std = {}".format(np.std(xwa)))
print("Middle Value-3, std = {}".format(np.std(xmv)))
print("Average to the closest-3, std = {}".format(np.std(xac)))
print("State Update, std = {}".format(np.std(xsu)))
print("State Update 2, std = {}".format(np.std(xsu2)))

fig, axs = plt.subplots(2, 3)
fig.suptitle('Fig.2 Filter Comparison')
axs[0, 0].plot(t, x, '.', label='Non filtered')
axs[0, 0].plot(t, xa4, label='Filtered')
axs[0, 0].fill_between(t, x_top, x_top + 30, alpha=0.5, label='Button region')
axs[0, 0].set_title('Average, n=4')
axs[0, 0].set(xlabel='Time[s]', ylabel='Pixels')
axs[0, 0].legend()

axs[0, 1].plot(t, x, '.', label='Non filtered')
axs[0, 1].plot(t, xwa, label='Filtered')
axs[0, 1].fill_between(t, x_top, x_top + 30, alpha=0.5, label='Button region')
axs[0, 1].set_title('Weighted Average, m=2')
axs[0, 1].set(xlabel='Time[s]', ylabel='Pixels')
axs[0, 1].legend()

axs[0, 2].plot(t, x, '.', label='Non filtered')
axs[0, 2].plot(t, xmv, label='Filtered')
axs[0, 2].set_title('Middle Value, n=3')
axs[0, 2].set(xlabel='Time[s]', ylabel='Pixels')
axs[0, 2].fill_between(t, x_top, x_top + 30, alpha=0.5, label='Button region')
axs[0, 2].legend()

axs[1, 0].plot(t, x, '.', label='Non filtered')
axs[1, 0].plot(t, xac, label='Filtered')
axs[1, 0].set_title('Averaging the closest, n=3')
axs[1, 0].set(xlabel='Time[s]', ylabel='Pixels')
axs[1, 0].fill_between(t, x_top, x_top + 30, alpha=0.5, label='Button region')
axs[1, 0].legend()

axs[1, 1].plot(t, x, '.', label='Non filtered')
axs[1, 1].plot(t, xsu, label='Filtered')
axs[1, 1].set_title('State Update, alpha=0.2')
axs[1, 1].set(xlabel='Time[s]', ylabel='Pixels')
axs[1, 1].fill_between(t, x_top, x_top + 30, alpha=0.5, label='Button region')
axs[1, 1].legend()

axs[1, 2].plot(t, x, '.', label='Non filtered')
axs[1, 2].plot(t, xsu3, label='Filtered')
axs[1, 2].set_title('State Update, alpha(t)')
axs[1, 2].set(xlabel='Time[s]', ylabel='Pixels')
axs[1, 2].fill_between(t, x_top, x_top + 30, alpha=0.5, label='Button region')
axs[1, 2].legend()

plt.show()

