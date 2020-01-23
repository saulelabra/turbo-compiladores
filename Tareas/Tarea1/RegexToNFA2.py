class Stack:
    def __init__(self, itemlist=[]):
        self.items = itemlist

    def isEmpty(self):
        if self.items == []:
            return True
        else:
            return False

    def top(self):
        return self.items[-1] #d
    
    def pop(self):
        return self.items.pop()

    def push(self, item):
        self.items.append(item)
        return 1

class State:
    def __init__(self, transitions):
        

class NFA:
    def __init__(self, initial_state, final_state, states, alphabet, transitions_states_table):
        self.initial_state = initial_state
        self.final_states = final_state
        self.states = states
        self.alphabet = alphabet
        self.transitions_states = transitions_states_table
        return

    # Turns the infix expression to a postfix as it is easier to evaluate by order of precedence
    # As defined per Thompson paper
    def inFixToPostFix


    def createEpsilonTrans(self, from, to):
        # Create Start and End
        # Receive number of the from state and to where is it going
        #from.epsilonTransition.push(to)
        return start, end
    
    def createSymbolTrans(self, symbol):
        # Create Start and End state
        # Receive number of the from state and to where is it going
        # from transition to with 
        return start, end


    # Concat
    def createConcatTrans(): # NFA A and NFA B
        # Create epsilon between NFA A end and NFA B start
        # Disable end from NFA A end
        return  start, end # NFA A start and NFA B end

    # Union                     |
    def createUnionTrans():# NFA A and NFA B
        # Create start state
        # Epsilon trans to NFA from start and eps trans to NFA B from start

        # Create end  state
        # Epsilon trans from NFA A to end state
        # Epsilon trans from NFA B to end state
        # Disable NFA A and NFA B ends
        return start, end

    # Kleene Star, Closure      *
    def createClosureTrans(): # NFA
        # Create start and end state
        # Add epsilon trans start to end
        # Add epsilon trans start to NFA start

        # Add epsilon trans NFA end to end
        # Add epsilon trans NFA end to NFA start

        # Disable nfa end 

        return start, end

    # Kleene Plus               +
    # Same as Kleense Star but without epsilon skipping everything
    def createPlusTrans():
        # Create start and end state
        # Add epsilon trans start to NFA start

        # Add epsilon trans NFA end to end
        # Add epsilon trans NFA end to NFA start

        # Disable nfa end 

        return start, end

    # Regex to NFA creator
    def createNFA(self, postFixRegex):
        if postFixRegex == '' OR postFixRegex == ' ': # empty regex
            return # epsilon transition

        # Empty Stack
        stack = []

        for token in postFixRegex:
            if token == "*":        # Star
            
            elif token == "|":      # Union
            
            elif token == ".":      # Concat

