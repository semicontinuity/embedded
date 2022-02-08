# Input: GERBER, consisting of 1 closed shape, composed of strokes (lines and arcs)
# Output:
# - OpenSCAD named array of points, if name is provides as 1st command-line argument
# - OpenSCAD polygon, if no name is provided

import sys
import math
import gerber
from gerber.primitives import Arc
from collections import defaultdict

g = gerber.read('/dev/stdin')
R2D = 180.0 / math.pi
ANGLE_DIGITS=5


def arc_points(l: Arc, flip: bool):
    c = f"// ARC {l.start}->{l.end}; {l.start_angle*R2D}->{l.end_angle*R2D} flip={flip}\n"
    if flip:
        start_angle = round(l.end_angle*R2D, ANGLE_DIGITS)
        end_angle = round(l.start_angle*R2D, ANGLE_DIGITS)
    else:
        start_angle = round(l.start_angle * R2D, ANGLE_DIGITS)
        end_angle = round(l.end_angle * R2D, ANGLE_DIGITS)

    if start_angle < 0 or end_angle < 0:
        start_angle += 360.0
        end_angle += 360.0

    if start_angle > 360:
        start_angle -= 360.0
    if end_angle > 360:
        end_angle -= 360.0

    if end_angle > start_angle:
        return c+f"[ for(a = [{start_angle}:1:{end_angle}]) [{l.center[0]} + {l.radius} * cos(a), {l.center[1]} + {l.radius} * sin(a)] ]"
    else:
        return c+f"[ for(a = [{start_angle}:-1:{end_angle}]) [{l.center[0]} + {l.radius} * cos(a), {l.center[1]} + {l.radius} * sin(a)] ]"


def line_points(l, flip: bool):
    c = f"// LINE {l.start}->{l.end}; flip={flip}\n"
    return c + f"[ [{l.end[0]}, {l.end[1]}] ]" if flip else c + f"[ [{l.start[0]}, {l.start[1]}] ]"


def primitive(p, flip: bool):
    return arc_points(p, flip) if type(p) is Arc else line_points(p, flip)


def join_strokes(primitives):
    # XXX round points: round(coord, 5) to overcome mismatches
    point_to_primitives = defaultdict(list)
    for p in primitives:
        point_to_primitives[p.start].append(p)
        point_to_primitives[p.end].append(p)

    result = []
    p = primitives[0]
    point = primitives[0].start

    while True:
        pre_join = point_to_primitives[point]
        pre_join.remove(p)

        if point == p.start:
            result.append((p, False))
            next_point = p.end
        else:
            result.append((p, True))
            next_point = p.start

        post_join = point_to_primitives[next_point]
        if p not in post_join:
            break
        post_join.remove(p)

        if len(post_join) == 0:
            break
        p = post_join[0]
        point = next_point

    return result


def polygon_points(primitives):
    return ",\n".join(primitive(*p) for p in join_strokes(primitives))


if len(sys.argv) == 1:
    print("polygon(concat(")
    print(polygon_points(g.primitives))
    print("));")
else:
    print(sys.argv[1] + " = concat(")
    print(polygon_points(g.primitives))
    print(");")
