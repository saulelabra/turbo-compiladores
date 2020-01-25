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

    #result = output + ""
    #print(reStr, " - ", output) # DEBUG

    return output
# Func ends

class State:
    def __init__(self, isEnd):
        # self.isStart = isStart
        self.isEnd = isEnd
        self.epsilonTransitions = []
        self.transitions = {}



def addEpsilonTransition(froms,to):
    froms.epsilonTransitions.append(to)

def addTransition(froms, to, symbol):
    froms.transitions[symbol] = to 

def createEpsilonTrans():
    # Create Start and End
    start = State(False)
    end = State(True)
    # Receive number of the from state and to where is it going
    addEpsilonTransition(start, end)

    return {start, end}

def createSymbolTrans(symbol):
    # Create Start and End state
    start = State(False)
    end = State(True)
    # Receive number of the from state and to where is it going
    addTransition(start, end ,symbol)
    # from transition to with 
    return {start, end}


# Concat
def createConcatTrans(first, second): # NFA A and NFA B
    # Create epsilon between NFA A end and NFA B start
    addEpsilonTransition(first.end, second.start)
    first.end.isEnd = False
    # Disable end from NFA A end
    return  {first.start, second.end} # NFA A start and NFA B end

# Union                     |
def createUnionTrans(first, second):# NFA A and NFA B
    # Create start state
    start = State(False)
    # Epsilon trans to NFA from start and eps trans to NFA B from start
    addEpsilonTransition(start, first.start)
    addEpsilonTransition(start, second.start)
    # Create end  state
    end = State(True)
    # Epsilon trans from NFA A to end state
    addEpsilonTransition(first.end, end)
    
    first.end.isEnd = False

    # Epsilon trans from NFA B to end state
    addEpsilonTransition(second.end, end)
    # Disable NFA A and NFA B ends
    second.end.isEnd = False

    return {start, end}

# Kleene Star, Closure      *
def createClosureTrans(nfa): # NFA
    # Create start and end state
    start = State(False)
    end = State(True)
    # Add epsilon trans start to end
    addEpsilonTransition(start, end)
    
    # Add epsilon trans start to NFA start
    addEpsilonTransition(start, nfa.start)

    # Add epsilon trans NFA end to end
    addEpsilonTransition(nfa.end, end)
    # Add epsilon trans NFA end to NFA start
    addEpsilonTransition(nfa.end, nfa.start)
    # Disable nfa end 
    nfa.end.isEnd = False

    return {start, end}

# Kleene Plus               +
# Same as Kleense Star but without epsilon skipping everything
def createPlusTrans(nfa):
    # Create start and end state
    start = State(False)
    end = State(True)
    # Add epsilon trans start to NFA start
    addEpsilonTransition(start, nfa.start)
    # Add epsilon trans NFA end to end
    addEpsilonTransition(nfa.end, end)
    # Add epsilon trans NFA end to NFA start
    addEpsilonTransition(nfa.end, nfa.start)
    # Disable nfa end 
    nfa.end.isEnd = False

    return {start, end}

# Regex to NFA creator
def createNFA(postFixRegex):
    if postFixRegex == '' or postFixRegex == ' ': # empty regex
        return createEpsilonTrans()# epsilon transition

    # Empty Stack
    stack = Stack()

    for token in postFixRegex:
        if token == "*":        # Star, closure
            stack.push(createClosureTrans(stack.pop()))
        elif token == "|":      # Union
            first = stack.pop()
            second = stack.pop()
            stack.push(createUnionTrans(first, second))
        elif token == ".":      # Concat
            first = stack.pop()
            second = stack.pop()
            stack.push(createConcatTrans(first, second))
        else:                    # Character 
            stack.push(createSymbolTrans(token))
            print("Token", token, " ", stack.top() ,"\n")

    print(stack.top())
    return stack.pop() # Only one NFA should be there 

#   infixToPostfixRegex("a.b.c")       # ab.c.
#   infixToPostfixRegex("a.b|c")       # ab.c|
#   infixToPostfixRegex("a.b+.c")      # ab+.c.
#   infixToPostfixRegex("a.(b.b)+.c")  # abb.+.c.
str = ""
print(infixToPostfixRegex("(0.1)*.((0.1)|1*)"))
print(infixToPostfixRegex("(0.0*).((0|1)*.1)"))
print(infixToPostfixRegex("(0.1*).((2|3|4|h)*|(0.1)*|5)*"))
# createNFA(str.join(infixToPostfixRegex("a.b.c")))