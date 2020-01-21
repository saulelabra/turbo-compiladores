class NFA:
    def __init__(self, initial_state, final_state, states, alphabet, transitions_states_table):
        self.initial_state = initial_state
        self.final_states = final_state
        self.states = states
        self.alphabet = alphabet
        self.transitions_states = transitions_states_table
        return

    def pre_create_NFA(self, regex):
        #
        NFA = self.create_NFA(self, regex, initial_state, final_state)
        return NFA

    # Recursive
    def create_NFA(self, regex, initial_state, final_state):    
        if (len(regex) == 0):
            return 
        

        return create_NFA(self, regex, initial_state, final_state)

#Main
cadena = input("Insert Regex: ")



    # Check valid symbols (a-z , A-Z , 0-9, (, ), *, |, +) + = aa* 
    # Create initial state and final 
    # Declare 2 stacks (operand, operator)
    
    # If operand, push to the stack
    # If operator
        # If stack empty, push operator stack
        #  If not empty
            # If operator presedence greater than or equal  to top, push it
            # If less do process (generate)
                # Process
    # if character is (  push to operator stack
    # if ) do process until finding )          

    # Generators(transition_list, start_state, end_state) return new start and end 
        # Generate single char
        # Generate single epsilon
        # Generate Concat
        # Generate OR
            # Call 2 times gen epsilion
        # Generate star
            # Call generate epsilon
        # Generate plus ?





#   def __init__(self, states, alphabet, transition_function, start_state, accept_states):
#      self.states = states
#        self.alphabet = alphabet
#       self.start_state = start_state
#       self.accept_states = accept_states
#       self.current_state = start_state
#       self.transition_function = transition_function
#       return