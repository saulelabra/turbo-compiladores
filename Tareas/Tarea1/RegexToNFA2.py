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

def precedenceOf(token):
    return precedenceDict[token] or 6

# Inserts a . when a concatenation should happen
def insertConcatenationOperator(regex): #TODO
    return None

# Turns the infix expression to a postfix as it is easier to evaluate by order of precedence
# As defined per Thompson paper
def infixToPostfixRegex(reStr):
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
                if precedenceDict.get(stack.top(), 6) >= precedenceDict.get(char, 6):
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

# Global variables
states = []                 # List contains all states
dictAlphabet = {}           # Dictionary key alphabet, saves column number on transition list
alphabet = set()
# collections.OrderedDict()
class NFA:
    def __init__(self, startId, endId):
        self.startId = startId
        self.endId = endId

# Just joins two states
def createEpsilonTrans(transitionList, startId, endId):
    # Receive number of the from state and to where is it going
    preSymbol = transitionList[startId][0][0] 
    if preSymbol == -1:
        transitionList[startId][0][0] = endId
    else:
        transitionList[startId][0] = [preSymbol, endId]

    

def createSymbolTrans(transitionList, symbol):
    # Create Start and End state
    newNFA = NFA(len(states),len(states)+1)
    states.append(len(states))
    states.append(len(states))

    # Add transition to list
    preSymbol = transitionList[newNFA.startId][dictAlphabet[symbol]][0]
    if preSymbol == -1:
        transitionList[newNFA.startId][dictAlphabet[symbol]][0] = newNFA.endId
    else:
        transitionList[newNFA.startId][dictAlphabet[symbol]] = [preSymbol,newNFA.endId]

    return newNFA


# Concat
def createConcatTrans(transitionList, first, second): # NFA A and NFA B
    # Create epsilon between NFA A end and NFA B start
    createEpsilonTrans(transitionList, first.endId, second.startId)
    newNFA = NFA(first.startId, second.endId)

    return  newNFA # NFA A start and NFA B end

# Union                     |
def createUnionTrans(transitionList, first, second):# NFA A and NFA B

    return 0 # Return 2

# Kleene Star, Closure      *
def createClosureTrans(transitionList, nfa): # NFA
    # Create main NFA
    newNFA = NFA(len(states), len(states)+1)
    states.append(len(states))
    states.append(len(states))

    # Epsilon trans to NFA
    createEpsilonTrans(transitionList, newNFA.startId, nfa.startId)

    # Epsilon trans from NFA end to end
    createEpsilonTrans(transitionList, nfa.endId, newNFA.endId)

    # Epsilon trans from NFA end to NFA start
    createEpsilonTrans(transitionList, nfa.endId, nfa.startId)

    # Epsilon trans start to end 
    createEpsilonTrans(transitionList, newNFA.startId, newNFA.endId)

    return newNFA

# Kleene Plus               +
# Same as Kleense Star but without epsilon skipping everything
def createPlusTrans(transitionList, nfa):
    # Create main NFA
    newNFA = NFA(len(states), len(states)+1)
    states.append(len(states))
    states.append(len(states))

    # Epsilon trans to NFA
    createEpsilonTrans(transitionList, newNFA.startId, nfa.startId)

    # Epsilon trans from NFA end to end
    createEpsilonTrans(transitionList, nfa.endId, newNFA.endId)

    # Epsilon trans from NFA end to NFA start
    createEpsilonTrans(transitionList, nfa.endId, nfa.startId)

    return newNFA


# Regex to NFA creator
def createNFA(postFixRegex):
    # Create Transition list maximum size posible according to regex
    transitionList = []
    # Pre-populate list with -1 to avoid out of range
    transitionList = [ [ [-1 for i in range(1)] for i in range(len(set(postFixRegex))) ] for j in range(len(postFixRegex)*2) ] #TODO

    if postFixRegex == '' or postFixRegex == ' ': # empty regex
        # Creates a epsilon trans with states
        newNFA = NFA(len(states),len(states)+1) # TODO
        states.append(len(states))
        states.append(len(states))
        transitionList[len(states)-2][0][0] = len(states)-1

        return newNFA
    # Empty Stack
    stack = Stack()
    print(transitionList)
    for token in postFixRegex:
        if token == "*":        # Star, closure
            stack.push(createClosureTrans(transitionList, stack.pop()))
        elif token == "|":      # Union
            second = stack.pop()
            first = stack.pop()
            stack.push(createUnionTrans(transitionList, first, second))
        elif token == ".":      # Concat
            second = stack.pop()
            first = stack.pop()
            stack.push(createConcatTrans(transitionList, first, second))
        else:                    # Character 
            if token not in alphabet:
                # Add token to alphabet set
                alphabet.add(token)
                # Add alphabet symbol to dict, sync with column number
                dictAlphabet[token] = len(alphabet)
            stack.push(createSymbolTrans(transitionList, token))
    newNFA = stack.pop()
    startState = newNFA.startId
    endState = newNFA.endId
    
    print("\n Transition List")
    print("\n", transitionList)
    print("\n Dict Alphabet :")
    print(dictAlphabet)
    print("\n Transition List :")
    print(transitionList)
    print("\n State List :")
    print(states)
    print("\n Start State :")
    print(startState)
    print("\n End State :")
    print(endState)

    #return stack.pop() # Only one NFA should be there 

#   infixToPostfixRegex("a.b.c")       # ab.c.
#   infixToPostfixRegex("a.b|c")       # ab.c|
#   infixToPostfixRegex("a.b+.c")      # ab+.c.
#   infixToPostfixRegex("a.(b.b)+.c")  # abb.+.c.
str = "".join(infixToPostfixRegex("a*"))
#print(infixToPostfixRegex("a.b.c.c"))
createNFA(str)
