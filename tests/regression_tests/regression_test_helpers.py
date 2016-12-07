from subprocess import Popen, PIPE
import os.path, filecmp, difflib

def render_graph(name, output_type, input_graph):
    if not os.path.exists('output'):
        os.makedirs('output')

    output_file = 'output/' + name + '.' + output_type
    process = Popen(['dot', '-T' + output_type, '-o', output_file], stdin=PIPE)
    process.communicate(input = input_graph.encode('utf_8'))

    if process.wait() != 0:
        print('An error occurred while generating: ' + output_file)
        exit(1)

    if output_type == 'svg':
        # Remove the number in 'Generated by graphviz version <number>'
        # to able to compare the output to the reference. This version
        # number is different for every Graphviz compilation.
        file = open(output_file, 'r')
        lines = file.readlines()
        file.close()

        file = open(output_file, 'w')
        for line in lines:
            if '<!-- Generated by graphviz version ' in line:
                file.write('<!-- Generated by graphviz version\n')
            else:
                file.write(line)


def compare_graphs(name, output_type):
    filename = name + '.' + output_type
    filename_reference = 'reference/' + filename
    filename_output = 'output/' + filename
    if not os.path.isfile('reference/' + filename):
        print('Failure: ' + filename + ' - No reference file present.')
        return False

    with open(filename_reference) as reference_file:
        with open(filename_output) as output_file:
            reference = reference_file.readlines()
            output = output_file.readlines()
            diff_generator = difflib.context_diff(output, reference, filename_output, filename_reference)

            # if diff contains at least one line, the files are different
            diff = []
            for line in diff_generator:
                diff.append(line)

            if len(diff) == 0:
                print('Success: ' + filename)
                return True
            else:
                if not os.path.exists('difference'):
                    os.makedirs('difference')

                # Write diff to console
                for line in diff:
                    print(line)

                # Store diff in file
                with open('difference/' + filename, 'w') as diff_file:
                    diff_file.writelines(diff)

                print('Failure: ' + filename + ' - Generated file does not match reference file.')
                return False
