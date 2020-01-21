class Automata:
    def __init__ (self, states, alphabet, transition_function, start_state, accept_states):
        self.states = states
        self.alphabet = alphabet
        self.transition_function = transition_function
        self.start_state = start_state
        self.accept_states = accept_states

    #Recursive function used by eClosure()
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

    #Gets all states reachable with epsilon starting from "current_state"
    def eClosure(self, current_states):
        #destination_states = self.eClosureRec(origin_states, [current_state])
        destination_states = self.eClosureRec(current_states, current_states)

        return destination_states

    #Gets reachable states starting from "current_state_group" list with determined input
    def getReachableStates(self, current_state_group, input):
        reachable_states = []
        
        #Obtianing reachable states with defined input from original transition function
        for state in current_state_group:
            for dest in transition_function[states.index(state)][alphabet.index(input)+1]:
                reachable_states.append(dest)

        return reachable_states

    def appendOnlyNew(self, listA, listB):
        for element in listB:
            if(not(element in listA)):
                listA.append(element)
        return listA

    def generateTuple(self, origin_states):
        tuple = []

        #generate structure of the tuple, one space per input (alphabet)
        #Get reachable states with e-closure
        tuple.append(self.eClosure(origin_states))
        for symbol in alphabet:
            tuple.append([])
        
        #iterate over each origin state and get reachable states wiht each input of the alphabet
        for origin in tuple[0]:
            print("Origin: " + origin)
            for i, symbol in enumerate(alphabet):
                print("Symbol: " + symbol)
                for dest in self.getReachableStates(origin, symbol):
                    tuple[i + 1].append(dest)
                    print("Reachable: " + dest)

        #skip the first element of the tuple (origin states)        
        iter_input_tuples = iter(tuple)
        next(iter_input_tuples)

        #get reachable states with e-closure from last step results
        for i, input_tuple in enumerate(iter_input_tuples, start=1):
            for origin_from_reachable in input_tuple:
                eClosure_res = self.eClosure([origin_from_reachable])
                print("origin_from_reachable: " + str(origin_from_reachable) + " eClosure_res: " + str(eClosure_res))
                if(len(eClosure_res) > 1):
                    print("if: " + str(eClosure_res))
                    self.appendOnlyNew(input_tuple, eClosure_res)

        return tuple

    def convertToDFA(self):
        new_states = []
        new_transition_function = []
        new_start_state = None
        conversion_table = []

        first_tuple = self.generateTuple(["1"])

        print(first_tuple)

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
    [["1"],[],[],[]],
]

start_state = 1
accept_states = [4]

exampleNFA = Automata(states, alphabet, transition_function, start_state, accept_states)

exampleNFA.convertToDFA()