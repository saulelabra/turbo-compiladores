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
                for dest in self.transition_function[self.states.index(origin)][0]:
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
            for dest in self.transition_function[self.states.index(state)][self.alphabet.index(input)+1]:
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
        for symbol in self.alphabet:
            tuple.append([])
        
        #iterate over each origin state and get reachable states wiht each input of the alphabet
        for origin in tuple[0]:
            for i, symbol in enumerate(self.alphabet):
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

        first_tuple = self.generateTuple([self.start_state])
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
            for accept_state in self.accept_states:
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

        return [new_states, self.alphabet, new_transition_function, new_start_state, new_acceptance_states]

class NFA:
    def __init__(self, startId, endId):
        self.startId = startId
        self.endId = endId

class Regex:
    # Precedence
    precedenceDict  = {
    '(': 1,
    '|': 2, # alternate
    '.': 3, # concatenate
    '?': 4, # zero or one
    '*': 4, # zero or more
    '+': 4, # one or one
    # else 6
    }

    # Global variables
    regex_str = ""
    states = []                 # List contains all states
    dictAlphabet = {}           # Dictionary key alphabet, saves column number on transition list
    alphabet = set()

    def __init__(self, regex_str):
        self.regex_str = regex_str

    def precedenceOf(self, token):
        return self.precedenceDict[token] or 6

    # Inserts a . when a concatenation should happen
    def insertConcatenationOperator(self, regex): #TODO
        return None

    # Turns the infix expression to a postfix as it is easier to evaluate by order of precedence
    # As defined per Thompson paper
    def infixToPostfixRegex(self):
        reStr = self.regex_str
        output = []
        stack = Stack()

        for char in reStr:
            if char == '(':
                stack.push(char)
            elif char == ')':
                while (stack.top() != '('): #sss
                    output.append(stack.pop())
                stack.pop() # pop (
            else:
                while stack.size():
                    if self.precedenceDict.get(stack.top(), 6) >= self.precedenceDict.get(char, 6):
                        output.append(stack.pop())
                    else:
                        break
                stack.push(char)
            # If ends
        # Loop ends
        # Offload stack to output
        while (stack.size()):
            output.append(stack.pop())
        return output
    # Func ends

    
    # collections.OrderedDict()

    # Just joins two states
    def createEpsilonTrans(self, transitionList, startId, endId):
        # Receive number of the from state and to where is it going
        transitionList[startId][0] = endId

    def createSymbolTrans(self, transitionList, symbol):
        # Create Start and End state
        newNFA = NFA(len(self.states),len(self.states)+1)
        self.states.append(len(self.states))
        self.states.append(len(self.states))

        # Add transition to list
        transitionList[newNFA.startId][self.dictAlphabet[symbol]]= newNFA.endId

        return newNFA


    # Concat
    def createConcatTrans(self, transitionList, first, second): # NFA A and NFA B
        # Create epsilon between NFA A end and NFA B start
        self.createEpsilonTrans(transitionList, first.endId, second.startId)
        newNFA = NFA(first.startId, second.endId)

        return  newNFA # NFA A start and NFA B end

    # Union                     |
    def createUnionTrans(self, transitionList, first, second):# NFA A and NFA B

        return 0 # Return 2

    # Kleene Star, Closure      *
    def createClosureTrans(self, transitionList, nfa): # NFA
        # Create main NFA
        newNFA = NFA(len(self.states), len(self.states)+1)
        self.states.append(len(self.states))
        self.states.append(len(self.states))

        # Epsilon trans to NFA
        self.createEpsilonTrans(transitionList, newNFA.startId, nfa.startId)

        # Epsilon trans from NFA end to end
        self.createEpsilonTrans(transitionList, nfa.endId, newNFA.endId)

        # Epsilon trans from NFA end to NFA start
        self.createEpsilonTrans(transitionList, nfa.endId, nfa.startId)

        # Epsilon trans start to end 
        self.createEpsilonTrans(transitionList, newNFA.startId, newNFA.endId)

        return newNFA

    # Kleene Plus               +
    # Same as Kleense Star but without epsilon skipping everything
    def createPlusTrans(self, transitionList, nfa):
        # Create main NFA
        newNFA = NFA(len(self.states), len(self.states)+1)
        self.states.append(len(self.states))
        self.states.append(len(self.states))

        # Epsilon trans to NFA
        self.createEpsilonTrans(transitionList, newNFA.startId, nfa.startId)

        # Epsilon trans from NFA end to end
        self.createEpsilonTrans(transitionList, nfa.endId, newNFA.endId)

        # Epsilon trans from NFA end to NFA start
        self.createEpsilonTrans(transitionList, nfa.endId, nfa.startId)

        return newNFA


    # Regex to NFA creator
    def createNFA(self):
        postFixRegex = "".join(self.infixToPostfixRegex())

        # Create Transition list maximum size posible according to regex
        transitionList = []
        # Pre-populate list with -1 to avoid out of rangeto
        transitionList = [ [ -1 for i in range(len(set(postFixRegex))) ] for j in range(len(postFixRegex)*2) ] #TODO

        if postFixRegex == '' or postFixRegex == ' ': # empty regex
            # Creates a epsilon trans with states
            newNFA = NFA(len(self.states),len(self.states)+1) # TODO
            self.states.append(len(self.states))
            self.states.append(len(self.states)+1)
            transitionList[len(self.states)-2][0].append(len(self.states)-1)
            return newNFA
        # Empty Stack
        stack = Stack()
        
        for token in postFixRegex:
            if token == "*":        # Star, closure
                stack.push(self.createClosureTrans(transitionList, stack.pop()))
            elif token == "|":      # Union
                second = stack.pop()
                first = stack.pop()
                stack.push(self.createUnionTrans(transitionList, first, second))
            elif token == ".":      # Concat
                second = stack.pop()
                first = stack.pop()
                stack.push(self.createConcatTrans(transitionList, first, second))
            else:                    # Character 
                if token not in self.alphabet:
                    # Add token to alphabet set
                    self.alphabet.add(token)
                    # Add alphabet symbol to dict, sync with column number
                    self.dictAlphabet[token] = len(self.alphabet)
                stack.push(self.createSymbolTrans(transitionList, token))
        newNFA = stack.pop()
        startState = newNFA.startId
        endState = newNFA.endId
        
        print("\n Transition List")
        print("\n", transitionList)
        print("\n Dict Alphabet :")
        print(self.dictAlphabet)
        print("\n Transition List :")
        print(transitionList)
        print("\n State List :")
        print(self.states)
        print("\n Start State :")
        print(startState)
        print("\n End State :")
        print(endState)
        
        #return stack.pop() # Only one NFA should be there
        return [self.states, self.dictAlphabet, transitionList, startState, endState]

class Stack:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def top(self):
        return self.items[len(self.items)-1] 
    
    def pop(self):
        return self.items.pop()

    def push(self, item):
        self.items.append(item)
    
    def size(self):
        return len(self.items) 


#main ##################################################################################

#   infixToPostfixRegex("a.b.c")       # ab.c.
#   infixToPostfixRegex("a.b|c")       # ab.c|
#   infixToPostfixRegex("a.b+.c")      # ab+.c.
#   infixToPostfixRegex("a.(b.b)+.c")  # abb.+.c.
#print(infixToPostfixRegex("a.b.c.c"))

example_regex = Regex("a*")
automataTuple = example_regex.createNFA()
example_automata = Automata(automataTuple[0], automataTuple[1], automataTuple[2], automataTuple[3], automataTuple[4])

print(example_automata.convertToDFA())