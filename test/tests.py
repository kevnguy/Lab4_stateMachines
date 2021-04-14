# Array of tests to run (in order)
# Each test contains
#   description - 
#   steps - A list of steps to perform, each step can have
#       inputs - A list of tuples for the inputs to apply at that step
#       *iterations - The iterations (in ms) to wait before continuing to the next step 
#           and before checking expected values for this step. The iterations should be a multiple of
#           the period of the system
#       *iterations - The number of clock ticks to wait (periods)
#       expected - The expected value at the end of this step (after the "iterations" has elapsed.) 
#           If this value is incorrect the test will fail early before completing.
#       * only one of these should be used
#   expected - The expected output (as a list of tuples) at the end of this test
# An example set of tests is shown below. It is important to note that these tests are not "unit tests" in 
# that they are not ran in isolation but in the order shown and the state of the device is not reset or 
# altered in between executions (unless preconditions are used).
tests = [
 
    {'description': 'count up to 2 down to 1, PINA: 0x01 => PORTC: 1',
    'steps': [ {'inputs': [('PINA', 0x03)],'iterations': 1}, # Set PIN to val then run one iteration
               {'inputs': [('PINA', 0x03)],'iterations': 1},
               {'inputs': [('PINA', 0x03)],'iterations': 1},
               {'inputs': [('PINA', 0x00)],'iterations': 1},
               ],
    'expected': [('PORTC', 0x01)],
    },
    {'description': 'count up to 2 down to 1, PINA: 0x01 => PORTC: 1',
    'steps': [ {'inputs': [('PINA', 0x00)],'iterations': 1},
	       {'inputs': [('PINA', 0x01)],'iterations': 1}, 
               {'inputs': [('PINA', 0x00)],'iterations': 1},
               {'inputs': [('PINA', 0x01)],'iterations': 1}, 
               {'inputs': [('PINA', 0x00)],'iterations': 1},
               {'inputs': [('PINA', 0x02)],'iterations': 1},
               {'inputs': [('PINA', 0x00)],'iterations': 1},
               ],
    'expected': [('PORTC', 0x01)],
    },
    ]

# Optionally you can add a set of "watch" variables these need to be global or static and may need
# to be scoped at the function level (for static variables) if there are naming conflicts. The 
# variables listed here will display everyiterations you hit (and stop at) a breakpoint
watch = ['main::c_state', 'main::temp']
