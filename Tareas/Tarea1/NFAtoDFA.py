class Automata:
    def __init__ (self, states, alphabet, transition_function, start_state, accept_states):
        self.states = states
        self.alphabet = alphabet
        self.transition_function = transition_function
        self.start_state = start_state
        self.accept_states = accept_states

    def eClosure(current_state):
        destination_states = []
        for dest in transition_function[states.index(current_state)][0]:
            destination_states.append(dest)

            #hacerlo recursivo

    def move(current_state, input):
        

    def convertToDFA():
        new_states = []
        new_transition_function = []
        new_start_state = None
        new_accept_states = []



states = ["1", "2", "3", "4", "5", "6", "7", "8"]
alphabet = ["a", "b", "c"]

#Order of matrix: epsilon, a, b, c
transition_function = [
    [[5,2],[],[],[]],
    [[],[3],[],[]],
    [[],[],[],[4]],
    [[],[],[],[]],
    [[6,7],[],[],[]],
    [[],[8],[],[]],
    [[],[],[8],[]],
    [[1],[],[],[]],
]

start_state = 1
accept_states = [4]

exampleNFA = Automata(states, alphabet, transition_function, start_state, accept_states)

print("index of b: " + str(alphabet.index("a")))