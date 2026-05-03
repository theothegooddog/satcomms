key = open("key.k", "r").read()

def gen_key(l: int):
	open("key.k",
	     "w").write(str(__import__("random").randint(int("1" * l), int("9" * l))))
	return (True)

def string_conv_1(string: str) -> str:
	s = ""
	for num in string.split(","):
		if num:
			s += chr(int(num))

	return s

def parse_instruction(inst: str) -> str:
	inststr = ""
	insts = ""
	def move_motor(m,d,i):
		inststr = i
		inststr += "Instruction: mm (Move Motor)\n"
		motorname = ""
		if m == "lt":
			motorname = "Left; Top"
		elif m == "rt":
			motorname = "Right; Top"
		elif m == "lb":
			motorname = "Left; Bottom"
		elif m == "rb":
			motorname = "Right; Bottom"
		else:
			return "[rej]" #reject
		inststr += f"Motor: {m} ({motorname})\n"
		inststr += f"Direction: {d}°"
		return inststr
	
	def capture_photo(i):
		# photo capturer logic here
		iv = i
		iv += str(True)
		return iv
	
	insts = inst.split("+")
	if insts[0] == "mm":
		i = move_motor(insts[1],insts[2],inststr)
		if i == "[rej]":
			return i
		inststr = i
	elif insts[0] == "cp":
		i = capture_photo(inststr)
		if i == "[rej]":
			return i
		inststr = i
	return inststr

while True:
	code = input("fart")
	if str(int(code.split(":")[0]) // 2573) == key: # STRING. INT. CODE DOT SPLIT. 🗣️🔥
		code = string_conv_1(code.split(":")[1])
		result = parse_instruction(code)
		if result == "[rej]":
			print("REJECT [invalid instructions.]")
		else: print(result)
	else:
		print("REJECT")

