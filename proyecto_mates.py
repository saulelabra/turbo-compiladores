class DFA:
    current_state = None
    def __init__(self, states, alphabet, transition_function, start_state, accept_states):
        self.states = states
        self.alphabet = alphabet
        self.transition_function = transition_function
        self.start_state = start_state
        self.accept_states = accept_states
        self.current_state = start_state
        return

    def transition_to_state_with_input(self, input_value):
        if ((self.current_state, input_value) not in self.transition_function.keys()):
            self.current_state = None
            return
        self.current_state = self.transition_function[(self.current_state, input_value)]
        return

    def in_accept_state(self):
        return self.current_state in accept_states

    def go_to_initial_state(self):
        self.current_state = self.start_state
        return

    def test_input_list(self, input_list):
        self.go_to_initial_state()
        for inp in input_list:
            self.transition_to_state_with_input(inp)
            continue
        return self.in_accept_state()
    pass

#Main 
cadena = input("Dime una cadena: ")

dfa_list=[]
tf = dict()

# file 
f = open('proyecto.txt', 'r')

i=0
for line in f.readlines():
    if i >= 4:
        line.split()
        tf[(int(line[0]),line[2])] = int(line[4])
    else:
        dfa_list.append(line)
    i=i+1


start_state=int(dfa_list[2])
states = {dfa_list[0]}
alphabet = {dfa_list[1]}
accept_states = {int(dfa_list[3])}
f.close()#file close

dfa = DFA(states, alphabet, tf, start_state, accept_states)

input_list = list(cadena)

print (dfa.test_input_list(input_list))