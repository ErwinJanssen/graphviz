# Import helper functions from tests/regressions_tests
import os.path, sys
sys.path.insert(0, os.path.abspath('../'))
from regression_test_helpers import compare_graphs, render_graph

shapes = [
    'box',
    'polygon',
    'ellipse',
    'oval',
    'circle',
    'point',
    'egg',
    'triangle',
    'none',
    'plaintext',
    'plain',
    'diamond',
    'trapezium',
    'parallelogram',
    'house',
    'pentagon',
    'hexagon',
    'septagon',
    'octagon',
    'note',
    'tab',
    'folder',
    'box3d',
    'component',
    'cylinder',
    'rect',
    'rectangle',
    'square',
    'star',
    'doublecircle',
    'doubleoctagon',
    'tripleoctagon',
    'invtriangle',
    'invtrapezium',
    'invhouse',
    'underline',
    'Mdiamond',
    'Msquare',
    'Mcircle',
    # biological circuit shapes
    # gene expression symbols
    'promoter',
    'cds',
    'terminator',
    'utr',
    'insulator',
    'ribosite',
    'rnastab',
    'proteasesite',
    'proteinstab',
    # dna construction symbols
    'primersite',
    'restrictionsite',
    'fivepoverhang',
    'threepoverhang',
    'noverhang',
    'assembly',
    'signature',
    'rpromoter',
    'larrow',
    'rarrow',
    'lpromoter'
]

output_types = [
    'gv',
    'svg',
    'xdot'
]

failures = 0
for shape in shapes:
    for output_type in output_types:
        render_graph(shape, output_type, 'graph G { a [label="" shape=' + shape + '] }')
        if not compare_graphs(shape, output_type):
            failures += 1

print('')
print('Results for "shapes" regression test:')
print('    Number of tests: ' + str(len(shapes) * len(output_types)))
print('    Number of failures: ' + str(failures))

if not failures == 0:
    exit(1) 
