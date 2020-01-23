# abc -> a.b.c -> ab.c.
# http://en.wikipedia.org/wiki/Shunting_yard_algorithm
class Stack:
    def __init__(self, itemlist=[]):
        self.items = itemlist

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

def infixToPostfixRegex(reStr):
    output = Stack()
    stack = Stack()

    for char in reStr:
        if char == '(':
            stack.push(char)
        elif char == ')':
            while (stack.top() != '('): #sss
                output.push(stack.pop())
            stack.pop() # pop (
        else:
            while stack.size():
                if precedenceDict[stack.top()] >= precedenceDict[char]:
                    output.push(stack.pop())
                else:
                    break
            stack.push(char)
        # If ends
    # Loop ends
    # Offload stack to output
    while (stack.size()):
        output.push(stack.pop())

    result = output + ""
    print(reStr, " - ", result)

    return result
# Func ends

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

infixToPostfixRegex("a.b.c")       # ab.c.
infixToPostfixRegex("a.b|c")       # ab.c|
infixToPostfixRegex("a.b+.c")      # ab+.c.
infixToPostfixRegex("a.(b.b)+.c")  # abb.+.c.