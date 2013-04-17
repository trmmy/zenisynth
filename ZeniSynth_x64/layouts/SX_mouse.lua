mouse.setCursorFriction(14000)
local force=18000
local dir={left=false,right=false,up=false,down=false}
local isClicked={L=false,R=false,M=false,X1=false,X2=false}

function SX.mouse()
	
	if SCAN==SC_XL and UP then
		mouse.setCursorForce(0,0)
		dir.left=false
		dir.right=false
		dir.up=false
		dir.down=false
		if(isClicked.L) then mouse.button(VK_LBUTTON,true) isClicked.L=false
		elseif(isClicked.R) then mouse.button(VK_RBUTTON,true) isClicked.R=false
		elseif(isClicked.M) then mouse.button(VK_MBUTTON,true) isClicked.M=false
		end
	end
	
	if XL then
		if SCAN==SC_F then
			if DOWN then dir.right=true mouse.setCursorForceX(force)
			elseif UP then
				dir.right=false
				if dir.left==false then
					mouse.setCursorForceX(0)
				end
			end
			return true
		elseif SCAN==SC_S then
			if DOWN then dir.left=true mouse.setCursorForceX(-force)
			elseif UP then
				dir.left=false
				if dir.right==false then
					mouse.setCursorForceX(0)
				end
			end
			return true
		elseif SCAN==SC_E then
			if DOWN then dir.up=true mouse.setCursorForceY(-force)
			elseif UP then
				dir.up=false
				if dir.down==false then
					mouse.setCursorForceY(0)
				end
			end
			return true
		elseif SCAN==SC_D then
			if DOWN then dir.down=true mouse.setCursorForceY(force)
			elseif UP then
				dir.down=false
				if dir.up==false then
					mouse.setCursorForceY(0)
				end
			end
			return true
		elseif	SCAN==SC_A then
			if UP==false then
				if R==false then
					mouse.button(VK_LBUTTON,UP) isClicked.L=DOWN return true
				end
			else
				mouse.button(VK_LBUTTON,UP) isClicked.L=DOWN return true
			end
			return true
		elseif	SCAN==SC_Z then
			if UP==false then
				if R==false then
					mouse.button(VK_RBUTTON,UP) isClicked.R=DOWN return true
				end
			else
				mouse.button(VK_RBUTTON,UP) isClicked.R=DOWN return true
			end
			return true
		elseif	SCAN==SC_G or SCAN==SC_C then mouse.button(VK_MBUTTON,UP) isClicked.M=DOWN return true
		elseif	SCAN==SC_T or SCAN==SC_X then 
			if DOWN then mouse.wheel(120) return true end
		elseif	SCAN==SC_V then
			if DOWN then mouse.wheel(-120) return true end
		end
	end
	return false
end
