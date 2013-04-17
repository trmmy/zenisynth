function main(vkCode,scanCode,flags,altdown)

	if scanCode==SC_NONCONVERT then
		scanCode=SC_NUM0
		vkCode=VK_NUMPAD0
	end
	

	sendInput(vkCode,scanCode,flags)

end