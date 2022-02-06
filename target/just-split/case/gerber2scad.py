import sys
import math
import gerber
from gerber.primitives import Arc

g = gerber.read('/dev/stdin')
R2D = 180.0 / math.pi

def arc(l: Arc):
    # angle_step = 1 if l.end_angle > l.start_angle else -1
    # return f"[ for(a = [{R2D*l.start_angle}:{angle_step}:{R2D*l.end_angle}]) [{l.center[0]} + {l.radius} * cos(a), {l.center[1]} + {l.radius} * sin(a)] ]"
    return f"[ for(a = [{R2D*l.end_angle}:1:{R2D*l.start_angle}]) [{l.center[0]} + {l.radius} * cos(a), {l.center[1]} + {l.radius} * sin(a)] ]"


def line(l):
    return f"[ [{l.start[0]}, {l.start[1]}] ]"
#    return f"[{l.end[0]}, {l.end[1]}], [{l.start[0]}, {l.start[1]}],"


def primitive(p):
    return arc(p) if type(p) is Arc else line(p)

def polygon(primitives):
    return ",\n".join(primitive(p) for p in primitives)

#      print(f"ARC {p.center} from={p.start} {p.start_angle} to={p.end} {p.end_angle} r={p.radius}")
#     
#    else:
#      print(p)


# [
#    for(a = [angles[0]:1:angles[1]]) [radius * cos(a), radius * sin(a)]
# ]


print(sys.argv[1] + " = polygon(concat(")
print(polygon(g.primitives))
print("));")
