import sys

MAX_RB55    = 31.0
MAX_G6      = 63.0

def remap(x, colorbit):
    return round(x * x * colorbit / (255.0 * 255.0))

hex_in = sys.argv[1]

tmp = int(hex_in[:2], 16)
hex_out = remap(tmp, MAX_RB55) << 11

tmp = int(hex_in[2:4], 16)
hex_out = hex_out | remap(tmp, MAX_G6) << 5

tmp = int(hex_in[4:6], 16)
hex_out = hex_out | remap(tmp, MAX_RB55)

print(hex(hex_out))
