#!/usr/bin/env python3
# .text coverage by verified clean TUs (reads build/verify/*.verify from make verify).
import glob, os, re, sys

sys.path.insert(0, os.path.dirname(__file__))
from tu_verify import OSEC
T0, TN = OSEC['.text'][0], OSEC['.text'][2]
TO = OSEC['.text'][1]

iv = []
for f in glob.glob('build/verify/*.verify'):
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
from tu_verify import ORIG
img = open(ORIG, 'rb').read()
def is_fill(a, b):
    return set(img[a - T0 + TO:b - T0 + TO]) <= {0x90, 0x00}
pad = [(a, b) for a, b in gaps if is_fill(a, b)]
gaps = [g for g in gaps if g not in pad]
print('alignment fill %d B in %d gaps' % (sum(b - a for a, b in pad), len(pad)))
u = sum(b - a for a, b in gaps)
print('uncovered %d B of %d = covered %.2f%%' % (u, TN, 100.0 * (TN - u) / TN))
for a, b in gaps:
    print('%#x %#x %d' % (a, b, b - a))
