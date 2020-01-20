class Automata:
    def __init__ (self, states, alphabet, transition_function, start_state, accept_states):
        self.states = states
        self.alphabet = alphabet
        self.transition_function = transition_function
        self.start_state = start_state
        self.accept_states = accept_states

    def eClosureRec(self, origin_states, destination_states):
        if(len(origin_states) > 0):
            new_destination_states = []
        
            for origin in origin_states:
                for dest in transition_function[states.index(origin)][0]:
                    new_destination_states.append(dest)
                    destination_states.append(dest)

            return self.eClosureRec(new_destination_states, destination_states)
        else:
            return destination_states         

    def eClosure(self, current_state):
        origin_states = [current_state]

        destination_states = self.eClosureRec(origin_states, [current_state])

        return destination_states

    def getReachableStates(self, current_state_group, input):
        reachable_states = []
        
        #Obtianing reachable states with defined input from original transition function
        for state in current_state_group:
            for dest in transition_function[states.index(state)][alphabet.index(input)+1]:
                reachable_states.append(dest)

        return reachable_states        

    def convertToDFA(self):
        new_states = []
        new_transition_function = []
        new_start_state = None
        new_accept_states = []

        transition_tuple = [None] * (len(alphabet) + 1)
        new_transition_function.append(transition_tuple)
        new_transition_function[0][0] = [self.eClosure(1)]
        new_transition_function[0]

        while(new_transition_function_size != len(new_transition_function)):
            new_transition_function.append([])

        #get first new state
        self.eClosure("1")

        return 0



states = ["1", "2", "3", "4", "5", "6", "7", "8"]
alphabet = ["a", "b", "c"]

#Order of matrix: epsilon, a, b, c
transition_function = [
    [["5","2"],[],[],[]],
    [[],["3"],[],[]],
    [[],[],[],["4"]],
    [[],[],[],[]],
    [["6","7"],[],[],[]],
    [[],["8"],[],[]],
    [[],[],["8"],[]],
    [[1],[],[],[]],
]

start_state = 1
accept_states = [4]

exampleNFA = Automata(states, alphabet, transition_function, start_state, accept_states)

print(exampleNFA.getReachableStates("2", "a"))