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
                    self.appendOnlyNew(destination_states, dest)
                    #destination_states.append(dest)

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
            for i, symbol in enumerate(alphabet):
                for dest in self.getReachableStates(origin, symbol):
                    tuple[i + 1].append(dest)

        #skip the first element of the tuple (origin states)        
        iter_input_tuples = iter(tuple)
        next(iter_input_tuples)

        #get reachable states with e-closure from last step results
        for i, input_tuple in enumerate(iter_input_tuples, start=1):
            for origin_from_reachable in input_tuple:
                eClosure_res = self.eClosure([origin_from_reachable])
                if(len(eClosure_res) > 1):
                    self.appendOnlyNew(input_tuple, eClosure_res)

        for sub_tuple in tuple:
            sub_tuple.sort()

        return tuple

    def generateConversionTable(self):
        new_states = []
        new_states_acceptance = []
        conversion_table = []
        appended_new_state = True

        first_tuple = self.generateTuple([start_state])
        new_states.append(first_tuple[0])
        
        i = 0
        while(appended_new_state and i < len(new_states)):
            appended_new_state = False
            new_current_states = self.generateTuple(new_states[i])
            conversion_table.append(new_current_states)

            for state in new_current_states:
                if not state in new_states and state != []:
                    new_states.append(state)
                    appended_new_state = True
            
            i += 1

        conversion_table.append(self.generateTuple(new_states[len(new_states) - 1]))

        for j, state in enumerate(new_states, start=1):
            for accept_state in accept_states:
                if(accept_state in state and not str(j) in new_states_acceptance):
                    new_states_acceptance.append(str(j))

        return [conversion_table, new_states, new_states_acceptance]

    def convertToDFA(self):
        new_states = []
        new_transition_function = []
        new_start_state = "1"
        new_acceptance_states = []
        conversion_table = []

        conversion_table = self.generateConversionTable()

        #convert DFA transition function states into new states
        for tuple in conversion_table[0]:
            new_tuple = []
            for state in tuple:
                if(state == []):
                    new_tuple.append([])
                else:
                    new_tuple.append(conversion_table[1].index(state) + 1)

            new_transition_function.append(new_tuple)

        #get new states list
        for i, state in enumerate(conversion_table[1], start=1):
            new_states.append(str(i))

        #get new acceptance_states
        new_acceptance_states = conversion_table[2]

        return [new_states, alphabet, new_transition_function, new_start_state, new_acceptance_states]



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

start_state = "1"
accept_states = ["4"]

exampleNFA = Automata(states, alphabet, transition_function, start_state, accept_states)

print(exampleNFA.convertToDFA())