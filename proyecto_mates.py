#Enrique Lira & Alejandro Gutierrez - Proyecto Matematicas Computacionales
#-------Clase DFA---------
class DFA:
	def __init__(self, states, alphabet, transition_function, start_state, accept_states):#Constructor, functions and variables declared
		self.states = states;
		self.alphabet = alphabet;
		self.transition_function = transition_function;
		self.start_state = start_state;
		self.accept_states = accept_states;
		self.current_state = start_state;
		return;
	
	def transition_to_state_with_input(self, input_value):#
		if ((self.current_state, input_value) not in self.transition_function.keys()):
			self.current_state = None;
			return;
		self.current_state = self.transition_function[(self.current_state, input_value)];
		print("Transicion q{}".format(self.current_state));
		return;
	
	def in_accept_state(self):#Checa si el estado actual esta en los estados de aceptacion
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

#-------Clase DFA Ends---------

#-----------Main--------------
cadena = raw_input("Dime una cadena: ");
i=0;
myList=[];
tf = dict();

#Using open, the text file called "protecto.txt" is loadad onto the variable 'f' using the parameter 'r' for reading only mode
f = open('proyecto.txt', 'r')


for line in f.readlines():
    if i >= 4:
        line = line.translate(None, 'q');
        line = line.replace(':', ',');
        line = line.split(',')
        tf[(int(line[0]),line[1])] = int(line[2]);
    else:
        myList.append(line)
    i=i+1;

start_state=int(myList[2])		#Add the start
states = {myList[0]};			#
alphabet = {myList[1]};			#
accept_states = {int(myList[3])}#
f.close() #Reading the file ends

#Printing Results
print("\nEstados de transicion:");
d = DFA(states, alphabet, tf, start_state, accept_states); #Transition states printing

inp_program = list(cadena);

 #Runs the function of input list, if string ended on a valid state it prints "aceptada" if it ends on another state that is not accepted then it prints "no aceptada"
if (d.run_with_input_list(inp_program)==True):
    print("\nACEPTADA");
else: 
    print("\nNO ES ACEPTADA");  