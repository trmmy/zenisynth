function SX.QwertyToSX()

	if SCAN==SC_Q then sendScan(SC_X,UP) return true
	elseif SCAN==SC_W then sendScan(SC_W,UP) return true
	elseif SCAN==SC_E then sendScan(SC_L,UP) return true
	elseif SCAN==SC_R then sendScan(SC_Z,UP) return true
	elseif SCAN==SC_T then sendScan(SC_J,UP) return true
	elseif SCAN==SC_Y then sendScan(SC_Q,UP) return true
	elseif SCAN==SC_U then sendScan(SC_G,UP) return true
	elseif SCAN==SC_I then sendScan(SC_H,UP) return true
	elseif SCAN==SC_O then sendScan(SC_C,UP) return true
	elseif SCAN==SC_P then sendScan(SC_Y,UP) return true
	elseif SCAN==SC_LSQUAREBRACKET then
		if XL then
			sendScan(SC_LSHIFT,false) sendScan(SC_SLASH,UP) sendScan(SC_LSHIFT,true) return true
		else
			sendScan(SC_SLASH,UP) return true
		end
	
	elseif SCAN==SC_A then sendScan(SC_O,UP) return true
	elseif SCAN==SC_S then sendScan(SC_I,UP) return true
	elseif SCAN==SC_D then sendScan(SC_E,UP) return true
	elseif SCAN==SC_F then sendScan(SC_A,UP) return true	
	elseif SCAN==SC_G then sendScan(SC_F,UP) return true
	elseif SCAN==SC_H then sendScan(SC_B,UP) return true
	elseif SCAN==SC_J then sendScan(SC_T,UP) return true
	elseif SCAN==SC_K then sendScan(SC_R,UP) return true
	elseif SCAN==SC_L then sendScan(SC_N,UP) return true
	elseif SCAN==SC_SEMICOLON then sendScan(SC_S,UP) return true
	elseif SCAN==SC_QUOTE then
		if SHIFT or XL then
			sendScan(SC_LSHIFT,false) sendScan(SC_REVERSESOLIDUS,UP) sendScan(SC_LSHIFT,true)
		else
			sendScan(SC_MINUS,UP)
		end
		
	return true
	elseif SCAN==SC_Z then sendScan(SC_SEMICOLON,UP) return true
	elseif SCAN==SC_X then sendScan(SC_PERIOD,UP) return true
	elseif SCAN==SC_C then sendScan(SC_K,UP) return true
	elseif SCAN==SC_V then sendScan(SC_U,UP) return true
	elseif SCAN==SC_B then sendScan(SC_LSQUAREBRACKET,UP) return true
	elseif SCAN==SC_N then sendScan(SC_D,UP) return true
	elseif SCAN==SC_M then sendScan(SC_M,UP) return true
	elseif SCAN==SC_COMMA then sendScan(SC_P,UP) return true
	elseif SCAN==SC_PERIOD then sendScan(SC_V,UP) return true
	elseif SCAN==SC_SLASH then sendScan(SC_COMMA,UP) return true
	end
	return false
end