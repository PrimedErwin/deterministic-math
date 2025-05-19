import random
import numpy as np

uniform = random.uniform

class Case:
    def __init__(self, a: float, b: float, op: str):
        self.a = a
        self.b = b
        self.op = op

        if op == "+":
            self.res = a + b
        elif op == "-":
            self.res = a - b
        elif op == "*":
            self.res = a * b
        elif op == "/":
            try:
                self.res = a / b
            except ZeroDivisionError:
                self.res = float("inf") if a > 0 else float("-inf") if a < 0 else float("nan")

ALL_GROUPS = [1, 2, 3]

def random_group(group: int) -> float:
    if group == 1:
        # Very small numbers
        return uniform(-1e-3, -1e-9) * random.choice([-1, 1])
    elif group == 2:
        # Medium range numbers
        return uniform(-1e-3, 1e3) * random.choice([-1, 1])
    elif group == 3:
        # Large numbers
        return uniform(1e3, 1e10) * random.choice([-1, 1])
    elif group == 4:
        # Special values
        return random.choice([float("nan"), float("inf"), float("-inf"), 0.0, -0.0])
    elif group == 5:
        # Close to Inf, -Inf
        return uniform(1e305, 1e300) * random.choice([-1, 1])
    elif group == 6:
        # Close to 0
        return uniform(1e-305, 1e-300) * random.choice([-1, 1])
    assert False

# test random_group
for g in ALL_GROUPS:
    x = [random_group(g) for i in range(10)]
    print(g, x)

cases: list[Case] = []

for i in range(100000):
    g1 = random.choice(ALL_GROUPS)
    g2 = random.choice(ALL_GROUPS)
    op = random.choice(["+", "-", "*", "/"])
    a = random_group(g1)
    b = random_group(g2)
    cases.append(Case(a, b, op))

a = np.linspace(-4*np.pi, 4*np.pi, 10000)

# to C struct
with open('cases.c', 'w') as f:
    f.write('#include "cases.h"\n')
    f.write('\n')
    f.write('struct Case cases[] = {\n')
    for case in a:
        f.write(f'    {{ {case}, {0}, \'{0}\' }},\n')
    f.write('};\n')
    f.write('\n')
    f.write(f'const int CASES_COUNT = {len(cases)};\n')

