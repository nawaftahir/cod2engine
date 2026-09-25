#!/usr/bin/env python3
# .text coverage by verified clean TUs (reads build/tu/*.verify from tools/tu_all.sh).
import glob, os, re

T0, TN = 0x0804a4b0, 0xef6a0

iv = []
for f in glob.glob('build/tu/*.verify'):
    lines = open(f).read().splitlines()
    if not lines or lines[-1] != 'TU VERIFIED':
        continue
    for l in lines:
        m = re.match(r'(?:\.text|\.lo\.\S+)\s+0x([0-9a-f]+) size\s+0x([0-9a-f]+): MATCH', l)
        if m:
            a = int(m[1], 16)
            iv.append((a, a + int(m[2], 16)))

iv.sort()
cur, gaps = T0, []
for a, b in iv:
    if a > cur:
        gaps.append((cur, a))
    cur = max(cur, b)
if cur < T0 + TN:
    gaps.append((cur, T0 + TN))

# Linker alignment fill between TUs (nop or zero bytes) is not source.
img = open(os.environ.get('ANCHOR', '../../binaries/linux/cod2_lnxded_1_0a'), 'rb').read()
def is_fill(a, b):
    return set(img[a - T0 + 0x24b0:b - T0 + 0x24b0]) <= {0x90, 0x00}
pad = [(a, b) for a, b in gaps if is_fill(a, b)]
gaps = [g for g in gaps if g not in pad]
print('alignment fill %d B in %d gaps' % (sum(b - a for a, b in pad), len(pad)))
u = sum(b - a for a, b in gaps)
print('uncovered %d B of %d = covered %.2f%%' % (u, TN, 100.0 * (TN - u) / TN))
for a, b in gaps:
    print('%#x %#x %d' % (a, b, b - a))
