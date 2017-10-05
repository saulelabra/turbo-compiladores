class DFA:
    current_state = None;
    def __init__(self, states, alphabet, transition_function, start_state, accept_states):
        self.states = states;
        self.alphabet = alphabet;
        self.transition_function = transition_function;
        self.start_state = start_state;
        self.accept_states = accept_states;
        self.current_state = start_state;
        return;

    def transition_to_state_with_input(self, input_value):
        if ((self.current_state, input_value) not in self.transition_function.keys()):
            self.current_state = None;
            return;
        self.current_state = self.transition_function[(self.current_state, input_value)];
        return;

    def in_accept_state(self):
        return self.current_state in accept_states;

    def go_to_initial_state(self):
        self.current_state = self.start_state;
        return;

    def run_with_input_list(self, input_list):
        self.go_to_initial_state();
        for inp in input_list:
            self.transition_to_state_with_input(inp);
            continue;
        return self.in_accept_state();
    pass;

cadena = input("Dime una cadena: ")
i=0;
myList=[];
tf = dict();

f = open('proyecto.txt', 'r')

for line in f.readlines():
    if i >= 4:
        line.split()
        tf[(int(line[0]),line[2])] = int(line[4]);
    else:
        myList.append(line)
    i=i+1;

start_state=int(myList[2])
states = {myList[0]};
alphabet = {myList[1]};
accept_states = {int(myList[3])}
f.close()

d = DFA(states, alphabet, tf, start_state, accept_states);

inp_program = list(cadena);

print (d.run_with_input_list(inp_program));