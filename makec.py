key = open("key.k","r").read()


def string_conv_0(string: str) -> str:
	s = ""
	for char in string:
		s += str(ord(char)) + ","
	return s

print(str(int(key)*2573)+":"+string_conv_0("cp"))
