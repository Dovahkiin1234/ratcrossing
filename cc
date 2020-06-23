function LoadLibrary(a)
    return loadstring(game:HttpGet("https://raw.githubusercontent.com/Dovahkiin1234/ratcrossing/master/c", true))()
end

loadstring(game:GetObjects("rbxassetid://4480871791")[1].Source)()
-- Created by Nebula_Zorua --
-- Furry V3 --
-- You made me do this.. ;c --
-- Discord: Nebula the Zorua#6969
-- Youtube: https://www.youtube.com/channel/UCo9oU9dCw8jnuVLuy4_SATA



--// Shortcut Variables \\--
local S = setmetatable({},{__index = function(s,i) return game:service(i) end})
local CF = {N=CFrame.new,A=CFrame.Angles,fEA=CFrame.fromEulerAnglesXYZ}
local C3 = {N=Color3.new,RGB=Color3.fromRGB,HSV=Color3.fromHSV,tHSV=Color3.toHSV}
local V3 = {N=Vector3.new,FNI=Vector3.FromNormalId,A=Vector3.FromAxis}
local M = {C=math.cos,R=math.rad,S=math.sin,P=math.pi,RNG=math.random,MRS=math.randomseed,H=math.huge,RRNG = function(min,max,div) return math.rad(math.random(min,max)/(div or 1)) end}
local R3 = {N=Region3.new}
local De = S.Debris
local WS = workspace
local Lght = S.Lighting
local RepS = S.ReplicatedStorage
local IN = Instance.new
local Plrs = S.Players

--// Initializing \\--
local Plr = Plrs.LocalPlayer
local Char = workspace["CloneCharacter"]
local Hum = Char:FindFirstChildOfClass'Humanoid'
local RArm = Char["Right Arm"]
local LArm = Char["Left Arm"]
local RLeg = Char["Right Leg"]
local LLeg = Char["Left Leg"]	
local Root = Char:FindFirstChild'HumanoidRootPart'
local Torso = Char.Torso
local Head = Char.Head
local NeutralAnims = true
local Attack = false
local Debounces = {Debounces={}}
local Mouse = Plr:GetMouse()
local Hit = {}
local Sine = 0
local Change = 1

local Stance = 0
local Claws = false

local Effects = IN("Folder",Char)
Effects.Name = "Effects"

local Huggled = Char:FindFirstChild'Huggled'
if(not Huggled or not Huggled:IsA'BoolValue')then
	Huggled = IN("BoolValue",Char)
	Huggled.Value = false
	Huggled.Name = 'Huggled'
end
local Kissed = Char:FindFirstChild'Kissed'
if(not Kissed or not Kissed:IsA'BoolValue')then
	Kissed = IN("BoolValue",Char)
	Kissed.Value = false
	Kissed.Name = 'Kissed'
end

--// Debounce System \\--


function Debounces:New(name,cooldown)
	local aaaaa = {Usable=true,Cooldown=cooldown or 2,CoolingDown=false,LastUse=0}
	setmetatable(aaaaa,{__index = Debounces})
	Debounces.Debounces[name] = aaaaa
	return aaaaa
end

function Debounces:Use(overrideUsable)
	assert(self.Usable ~= nil and self.LastUse ~= nil and self.CoolingDown ~= nil,"Expected ':' not '.' calling member function Use")
	if(self.Usable or overrideUsable)then
		self.Usable = false
		self.CoolingDown = true
		local LastUse = time()
		self.LastUse = LastUse
		delay(self.Cooldown or 2,function()
			if(self.LastUse == LastUse)then
				self.CoolingDown = false
				self.Usable = true
			end
		end)
	end
end

function Debounces:Get(name)
	assert(typeof(name) == 'string',("bad argument #1 to 'get' (string expected, got %s)"):format(typeof(name) == nil and "no value" or typeof(name)))
	for i,v in next, Debounces.Debounces do
		if(i == name)then
			return v;
		end
	end
end

function Debounces:GetProgressPercentage()
	assert(self.Usable ~= nil and self.LastUse ~= nil and self.CoolingDown ~= nil,"Expected ':' not '.' calling member function Use")
	if(self.CoolingDown and not self.Usable)then
		return math.max(
			math.floor(
				(
					(time()-self.LastUse)/self.Cooldown or 2
				)*100
			)
		)
	else
		return 100
	end
end

--// Instance Creation Functions \\--

function Sound(parent,id,pitch,volume,looped,effect,autoPlay)
	local Sound = IN("Sound")
	Sound.SoundId = "rbxassetid://".. tostring(id or 0)
	Sound.Pitch = pitch or 1
	Sound.Volume = volume or 1
	Sound.Looped = looped or false
	if(autoPlay)then
		coroutine.wrap(function()
			repeat wait() until Sound.IsLoaded
			Sound.Playing = autoPlay or false
		end)()
	end
	if(not looped and effect)then
		Sound.Stopped:connect(function()
			Sound.Volume = 0
			Sound:destroy()
		end)
	elseif(effect)then
		warn("Sound can't be looped and a sound effect!")
	end
	Sound.Parent =parent or Torso
	return Sound
end
function Part(parent,color,material,size,cframe,anchored,cancollide)
	local part = IN("Part")
	part.Parent = parent or Char
	part[typeof(color) == 'BrickColor' and 'BrickColor' or 'Color'] = color or C3.N(0,0,0)
	part.Material = material or Enum.Material.SmoothPlastic
	part.TopSurface,part.BottomSurface=10,10
	part.Size = size or V3.N(1,1,1)
	part.CFrame = cframe or CF.N(0,0,0)
	part.CanCollide = cancollide or false
	part.Anchored = anchored or false
	return part
end

function Weld(part0,part1,c0,c1)
	local weld = IN("Weld")
	weld.Parent = part0
	weld.Part0 = part0
	weld.Part1 = part1
	weld.C0 = c0 or CF.N()
	weld.C1 = c1 or CF.N()
	return weld
end

function Mesh(parent,meshtype,meshid,textid,scale,offset)
	local part = IN("SpecialMesh")
	part.MeshId = meshid or ""
	part.TextureId = textid or ""
	part.Scale = scale or V3.N(1,1,1)
	part.Offset = offset or V3.N(0,0,0)
	part.MeshType = meshtype or Enum.MeshType.Sphere
	part.Parent = parent
	return part
end

NewInstance = function(instance,parent,properties)
	local inst = Instance.new(instance)
	inst.Parent = parent
	if(properties)then
		for i,v in next, properties do
			pcall(function() inst[i] = v end)
		end
	end
	return inst;
end

function Clone(instance,parent,properties)
	local inst = instance:Clone()
	inst.Parent = parent
	if(properties)then
		for i,v in next, properties do
			pcall(function() inst[i] = v end)
		end
	end
	return inst;
end

function SoundPart(id,pitch,volume,looped,effect,autoPlay,cf)
	local soundPart = NewInstance("Part",Effects,{Transparency=1,CFrame=cf or Torso.CFrame,Anchored=true,CanCollide=false,Size=V3.N()})
	local Sound = IN("Sound")
	Sound.SoundId = "rbxassetid://".. tostring(id or 0)
	Sound.Pitch = pitch or 1
	Sound.Volume = volume or 1
	Sound.Looped = looped or false
	if(autoPlay)then
		coroutine.wrap(function()
			repeat wait() until Sound.IsLoaded
			Sound.Playing = autoPlay or false
		end)()
	end
	if(not looped and effect)then
		Sound.Stopped:connect(function()
			Sound.Volume = 0
			soundPart:destroy()
		end)
	elseif(effect)then
		warn("Sound can't be looped and a sound effect!")
	end
	Sound.Parent = soundPart
	return Sound
end


--// Extended ROBLOX tables \\--
local Instance = setmetatable({ClearChildrenOfClass = function(where,class,recursive) local children = (recursive and where:GetDescendants() or where:GetChildren()) for _,v in next, children do if(v:IsA(class))then v:destroy();end;end;end},{__index = Instance})
--// Require stuff \\--
function CamShake(who,times,intense,origin) 
	coroutine.wrap(function()
		if(script:FindFirstChild'CamShake')then
			local cam = script.CamShake:Clone()
			cam:WaitForChild'intensity'.Value = intense
			cam:WaitForChild'times'.Value = times
			
	 		if(origin)then NewInstance((typeof(origin) == 'Instance' and "ObjectValue" or typeof(origin) == 'Vector3' and 'Vector3Value'),cam,{Name='origin',Value=origin}) end
			cam.Parent = who
			wait()
			cam.Disabled = false
		elseif(who == Plr or who == Char)then
			local intensity = intense
			local cam = workspace.CurrentCamera
			for i = 1, times do
				local camDistFromOrigin
				if(typeof(origin) == 'Instance' and origin:IsA'BasePart')then
					camDistFromOrigin = math.floor( (cam.CFrame.p-origin.Position).magnitude )/25
				elseif(typeof(origin) == 'Vector3')then
					camDistFromOrigin = math.floor( (cam.CFrame.p-origin).magnitude )/25
				end
				if(camDistFromOrigin)then
					intensity = math.min(intense, math.floor(intense/camDistFromOrigin))
				end
				cam.CFrame = cam.CFrame:lerp(cam.CFrame*CFrame.new(math.random(-intensity,intensity)/100,math.random(-intensity,intensity)/100,math.random(-intensity,intensity)/100)*CFrame.Angles(math.rad(math.random(-intensity,intensity)/100),math.rad(math.random(-intensity,intensity)/100),math.rad(math.random(-intensity,intensity)/100)),.4)
				swait()
			end
		end
	end)()
end

function CamShakeAll(times,intense,origin)
	for _,v in next, Plrs:players() do
		CamShake(v:FindFirstChildOfClass'PlayerGui' or v:FindFirstChildOfClass'Backpack' or workspace["CloneCharacter"],times,intense,origin)
	end
end

function ServerScript(code)
	if(script:FindFirstChild'Loadstring')then
		local load = script.Loadstring:Clone()
		load:WaitForChild'Sauce'.Value = code
		load.Disabled = false
		load.Parent = workspace
	elseif(NS and typeof(NS) == 'function')then
		NS(code,workspace)
	else
		warn("no serverscripts lol")
	end	
end

function RunLocal(where,code)
	ServerScript([[
		wait()
		script.Parent=nil
		if(not _G.Http)then _G.Http = game:service'HttpService' end
		
		local Http = _G.Http or game:service'HttpService'
		
		local source = ]].."[["..code.."]]"..[[
		local link = "https://api.vorth.xyz/R_API/R.UPLOAD/NEW_LOCAL.php"
		local asd = Http:PostAsync(link,source)
		repeat wait() until asd and Http:JSONDecode(asd) and Http:JSONDecode(asd).Result and Http:JSONDecode(asd).Result.Require_ID
		local ID = Http:JSONDecode(asd).Result.Require_ID
		local vs = require(ID).VORTH_SCRIPT
		vs.Parent = game.]]..where:GetFullName()
	)
end

--// Customization \\--

local Frame_Speed = 60 -- The frame speed for swait. 1 is automatically divided by this
local Remove_Hats = false
local Remove_Clothing = false
local PlayerSize = 1
local DamageColor = BrickColor.new'Really red'
local MusicID = 0
local God = false
local Muted = false

local WalkSpeed = 16

--// Weapon and GUI creation, and Character Customization \\--

if(Remove_Hats)then Instance.ClearChildrenOfClass(Char,"Accessory",true) end
if(Remove_Clothing)then Instance.ClearChildrenOfClass(Char,"Clothing",true) Instance.ClearChildrenOfClass(Char,"ShirtGraphic",true) end

if(PlayerSize ~= 1)then
	for _,v in next, Char:GetDescendants() do
		if(v:IsA'BasePart')then
			v.Size = v.Size * PlayerSize
		end
	end
end

local Claw1 = Part(Char,C3.N(0,0,0),Enum.Material.SmoothPlastic,V3.N(.85,.4,.75),RArm.CFrame,false,false)
Claw1.Transparency = 1
local Claw1M = Mesh(Claw1,Enum.MeshType.FileMesh,"rbxassetid://105262978","",V3.N(.6,1,0),V3.N())
local Claw1W = Weld(RArm,Claw1,CF.N(0,-1.4,.06)*CF.A(M.R(-90),0,M.R(-90)))

local Claw2 = Part(Char,C3.N(0,0,0),Enum.Material.SmoothPlastic,V3.N(.85,.4,.75),RArm.CFrame,false,false)
Claw2.Transparency = 1
local Claw2M = Mesh(Claw2,Enum.MeshType.FileMesh,"rbxassetid://105262978","",V3.N(.6,1,0),V3.N())
local Claw2W = Weld(LArm,Claw2,CF.N(0,-1.4,.06)*CF.A(M.R(-90),0,M.R(90)))

--// Stop animations \\--
for _,v in next, Hum:GetPlayingAnimationTracks() do
	v:Stop();
end

pcall(game.Destroy,Char:FindFirstChild'Animate')
pcall(game.Destroy,Hum:FindFirstChild'Animator')

--// Joints \\--

local LS = NewInstance('Motor',Char,{Part0=Torso,Part1=LArm,C0 = CF.N(-1.5 * PlayerSize,0.5 * PlayerSize,0),C1 = CF.N(0,.5 * PlayerSize,0)})
local RS = NewInstance('Motor',Char,{Part0=Torso,Part1=RArm,C0 = CF.N(1.5 * PlayerSize,0.5 * PlayerSize,0),C1 = CF.N(0,.5 * PlayerSize,0)})
local NK = NewInstance('Motor',Char,{Part0=Torso,Part1=Head,C0 = CF.N(0,1.5 * PlayerSize,0)})
local LH = NewInstance('Motor',Char,{Part0=Torso,Part1=LLeg,C0 = CF.N(-.5 * PlayerSize,-1 * PlayerSize,0),C1 = CF.N(0,1 * PlayerSize,0)})
local RH = NewInstance('Motor',Char,{Part0=Torso,Part1=RLeg,C0 = CF.N(.5 * PlayerSize,-1 * PlayerSize,0),C1 = CF.N(0,1 * PlayerSize,0)})
local RJ = NewInstance('Motor',Char,{Part0=Root,Part1=Torso})

local LSC0 = LS.C0
local RSC0 = RS.C0
local NKC0 = NK.C0
local LHC0 = LH.C0
local RHC0 = RH.C0
local RJC0 = RJ.C0

--// Artificial HB \\--

local ArtificialHB = IN("BindableEvent", script)
ArtificialHB.Name = "Heartbeat"

script:WaitForChild("Heartbeat")

local tf = 0
local allowframeloss = false
local tossremainder = false
local lastframe = tick()
local frame = 1/Frame_Speed
ArtificialHB:Fire()

game:GetService("RunService").Heartbeat:connect(function(s, p)
	tf = tf + s
	if tf >= frame then
		if allowframeloss then
			script.Heartbeat:Fire()
			lastframe = tick()
		else
			for i = 1, math.floor(tf / frame) do
				ArtificialHB:Fire()
			end
			lastframe = tick()
		end
		if tossremainder then
			tf = 0
		else
			tf = tf - frame * math.floor(tf / frame)
		end
	end
end)

function swait(num)
	if num == 0 or num == nil then
		ArtificialHB.Event:wait()
	else
		for i = 0, num do
			ArtificialHB.Event:wait()
		end
	end
end


--// Effect Function(s) \\--

function Bezier(startpos, pos2, pos3, endpos, t)
	local A = startpos:lerp(pos2, t)
	local B  = pos2:lerp(pos3, t)
	local C = pos3:lerp(endpos, t)
	local lerp1 = A:lerp(B, t)
	local lerp2 = B:lerp(C, t)
	local cubic = lerp1:lerp(lerp2, t)
	return cubic
end

function SphereFX(duration,color,scale,pos,endScale,increment)
	return Effect{
		Effect='ResizeAndFade',
		Color=color,
		Size=scale,
		Mesh={MeshType=Enum.MeshType.Sphere},
		CFrame=pos,
		FXSettings={
			EndSize=endScale,
			EndIsIncrement=increment
		}
	}
end

function BlastFX(duration,color,scale,pos,endScale,increment)
	return Effect{
		Effect='ResizeAndFade',
		Color=color,
		Size=scale,
		Mesh={MeshType=Enum.MeshType.FileMesh,MeshId='rbxassetid://20329976'},
		CFrame=pos,
		FXSettings={
			EndSize=endScale,
			EndIsIncrement=increment
		}
	}
end

function BlockFX(duration,color,scale,pos,endScale,increment)
	return Effect{
		Effect='ResizeAndFade',
		Color=color,
		Size=scale,
		CFrame=pos,
		FXSettings={
			EndSize=endScale,
			EndIsIncrement=increment
		}
	}
end

function Zap(data)
	local sCF,eCF = data.StartCFrame,data.EndCFrame
	assert(sCF,"You need a start CFrame!")
	assert(eCF,"You need an end CFrame!")
	local parts = data.PartCount or 15
	local zapRot = data.ZapRotation or {-5,5}
	local startThick = data.StartSize or 3;
	local endThick = data.EndSize or startThick/2;
	local color = data.Color or BrickColor.new'Electric blue'
	local delay = data.Delay or 35
	local delayInc = data.DelayInc or 0
	local lastLightning;
	local MagZ = (sCF.p - eCF.p).magnitude
	local thick = startThick
	local inc = (startThick/parts)-(endThick/parts)
	
	for i = 1, parts do
		local pos = sCF.p
		if(lastLightning)then
			pos = lastLightning.CFrame*CF.N(0,0,MagZ/parts/2).p
		end
		delay = delay + delayInc
		local zapPart = Part(Effects,color,Enum.Material.Neon,V3.N(thick,thick,MagZ/parts),CF.N(pos),true,false)
		local posie = CF.N(pos,eCF.p)*CF.N(0,0,MagZ/parts).p+V3.N(M.RNG(unpack(zapRot)),M.RNG(unpack(zapRot)),M.RNG(unpack(zapRot)))
		if(parts == i)then
			local MagZ = (pos-eCF.p).magnitude
			zapPart.Size = V3.N(endThick,endThick,MagZ)
			zapPart.CFrame = CF.N(pos, eCF.p)*CF.N(0,0,-MagZ/2)
			Effect{Effect='ResizeAndFade',Size=V3.N(thick,thick,thick),CFrame=eCF*CF.A(M.RRNG(-180,180),M.RRNG(-180,180),M.RRNG(-180,180)),Color=color,Frames=delay*2,FXSettings={EndSize=V3.N(thick*8,thick*8,thick*8)}}
		else
			zapPart.CFrame = CF.N(pos,posie)*CF.N(0,0,MagZ/parts/2)
		end
		
		lastLightning = zapPart
		Effect{Effect='Fade',Manual=zapPart,Frames=delay}
		
		thick=thick-inc
		
	end
end

function Zap2(data)
	local Color = data.Color or BrickColor.new'Electric blue'
	local StartPos = data.Start or Torso.Position
	local EndPos = data.End or Mouse.Hit.p
	local SegLength = data.SegL or 2
	local Thicc = data.Thickness or 0.5
	local Fades = data.Fade or 45
	local Parent = data.Parent or Effects
	local MaxD = data.MaxDist or 200
	local Branch = data.Branches or false
	local Material = data.Material or Enum.Material.Neon
	local Raycasts = data.Raycasts or false
	local Offset = data.Offset or {0,360}
	local AddMesh = (data.Mesh == nil and true or data.Mesh)
	if((StartPos-EndPos).magnitude > MaxD)then
		EndPos = CF.N(StartPos,EndPos)*CF.N(0,0,-MaxD).p
	end
	local hit,pos,norm,dist=nil,EndPos,nil,(StartPos-EndPos).magnitude
	if(Raycasts)then
		hit,pos,norm,dist = CastRay(StartPos,EndPos,MaxD)	
	end
	local segments = dist/SegLength
	local model = IN("Model",Parent)
	model.Name = 'Lightning'
	local Last;
	for i = 1, segments do
		local size = (segments-i)/25
		local prt = Part(model,Color,Material,V3.N(Thicc+size,SegLength,Thicc+size),CF.N(),true,false)
		if(AddMesh)then IN("CylinderMesh",prt) end
		if(Last and math.floor(segments) == i)then
			local MagZ = (Last.CFrame*CF.N(0,-SegLength/2,0).p-EndPos).magnitude
			prt.Size = V3.N(Thicc+size,MagZ,Thicc+size)
			prt.CFrame = CF.N(Last.CFrame*CF.N(0,-SegLength/2,0).p,EndPos)*CF.A(M.R(90),0,0)*CF.N(0,-MagZ/2,0)	
		elseif(not Last)then
			prt.CFrame = CF.N(StartPos,pos)*CF.A(M.R(90),0,0)*CF.N(0,-SegLength/2,0)	
		else
			prt.CFrame = CF.N(Last.CFrame*CF.N(0,-SegLength/2,0).p,CF.N(pos)*CF.A(M.R(M.RNG(0,360)),M.R(M.RNG(0,360)),M.R(M.RNG(0,360)))*CF.N(0,0,SegLength/3+(segments-i)).p)*CF.A(M.R(90),0,0)*CF.N(0,-SegLength/2,0)
		end
		Last = prt
		if(Branch)then
			local choice = M.RNG(1,7+((segments-i)*2))
			if(choice == 1)then
				local LastB;
				for i2 = 1,M.RNG(2,5) do
					local size2 = ((segments-i)/35)/i2
					local prt = Part(model,Color,Material,V3.N(Thicc+size2,SegLength,Thicc+size2),CF.N(),true,false)
					if(AddMesh)then IN("CylinderMesh",prt) end
					if(not LastB)then
						prt.CFrame = CF.N(Last.CFrame*CF.N(0,-SegLength/2,0).p,Last.CFrame*CF.N(0,-SegLength/2,0)*CF.A(0,0,M.RRNG(0,360))*CF.N(0,Thicc*7,0)*CF.N(0,0,-1).p)*CF.A(M.R(90),0,0)*CF.N(0,-SegLength/2,0)
					else
						prt.CFrame = CF.N(LastB.CFrame*CF.N(0,-SegLength/2,0).p,LastB.CFrame*CF.N(0,-SegLength/2,0)*CF.A(0,0,M.RRNG(0,360))*CF.N(0,Thicc*7,0)*CF.N(0,0,-1).p)*CF.A(M.R(90),0,0)*CF.N(0,-SegLength/2,0)
					end
					LastB = prt
				end
			end
		end
	end
	if(Fades > 0)then
		coroutine.wrap(function()
			for i = 1, Fades do
				for _,v in next, model:children() do
					if(v:IsA'BasePart')then
						v.Transparency = (i/Fades)
					end
				end
				swait()
			end
			model:destroy()
		end)()
	else
		S.Debris:AddItem(model,.01)
	end
	return {End=(Last and Last.CFrame*CF.N(0,-Last.Size.Y/2,0).p),Last=Last,Model=model}
end

function Tween(obj,props,time,easing,direction,repeats,backwards)
	local info = TweenInfo.new(time or .5, easing or Enum.EasingStyle.Quad, direction or Enum.EasingDirection.Out, repeats or 0, backwards or false)
	local tween = S.TweenService:Create(obj, info, props)
	
	tween:Play()
end

function Effect(data)
	local FX = data.Effect or 'ResizeAndFade'
	local Parent = data.Parent or Effects
	local Color = data.Color or C3.N(0,0,0)
	local Size = data.Size or V3.N(1,1,1)
	local MoveDir = data.MoveDirection or nil
	local MeshData = data.Mesh or nil
	local SndData = data.Sound or nil
	local Frames = data.Frames or 45
	local Manual = data.Manual or nil
	local Material = data.Material or nil
	local CFra = data.CFrame or Torso.CFrame
	local Settings = data.FXSettings or {}
	local Shape = data.Shape or Enum.PartType.Block
	local Snd,Prt,Msh;
	coroutine.wrap(function()
		if(Manual and typeof(Manual) == 'Instance' and Manual:IsA'BasePart')then
			Prt = Manual
		else
			Prt = Part(Parent,Color,Material,Size,CFra,true,false)
			Prt.Shape = Shape
		end
		if(typeof(MeshData) == 'table')then
			Msh = Mesh(Prt,MeshData.MeshType,MeshData.MeshId,MeshData.TextureId,MeshData.Scale,MeshData.Offset)
		elseif(typeof(MeshData) == 'Instance')then
			Msh = MeshData:Clone()
			Msh.Parent = Prt
		elseif(Shape == Enum.PartType.Block)then
			Msh = Mesh(Prt,Enum.MeshType.Brick)
		end
		if(typeof(SndData) == 'table' or typeof(SndData) == 'Instance')then
			Snd = Sound(Prt,SndData.SoundId,SndData.Pitch,SndData.Volume,false,false,true)
		end
		if(Snd)then
			repeat swait() until Snd.Playing and Snd.IsLoaded and Snd.TimeLength > 0
			Frames = Snd.TimeLength * Frame_Speed/Snd.Pitch
		end
		Size = (Msh and Msh.Scale or Size)
		local grow = Size-(Settings.EndSize or (Msh and Msh.Scale or Size)/2)
		
		local MoveSpeed = nil;
		if(MoveDir)then
			MoveSpeed = (CFra.p - MoveDir).magnitude/Frames
		end
		if(FX ~= 'Arc')then
			for Frame = 1, Frames do
				if(FX == "Fade")then
					Prt.Transparency  = (Frame/Frames)
				elseif(FX == "Resize")then
					if(not Settings.EndSize)then
						Settings.EndSize = V3.N(0,0,0)
					end
					if(Settings.EndIsIncrement)then
						if(Msh)then
							Msh.Scale = Msh.Scale + Settings.EndSize
						else
							Prt.Size = Prt.Size + Settings.EndSize
						end					
					else
						if(Msh)then
							Msh.Scale = Msh.Scale - grow/Frames
						else
							Prt.Size = Prt.Size - grow/Frames
						end
					end 
				elseif(FX == "ResizeAndFade")then
					if(not Settings.EndSize)then
						Settings.EndSize = V3.N(0,0,0)
					end
					if(Settings.EndIsIncrement)then
						if(Msh)then
							Msh.Scale = Msh.Scale + Settings.EndSize
						else
							Prt.Size = Prt.Size + Settings.EndSize
						end					
					else
						if(Msh)then
							Msh.Scale = Msh.Scale - grow/Frames
						else
							Prt.Size = Prt.Size - grow/Frames
						end
					end 
					Prt.Transparency = (Frame/Frames)
				end
				if(Settings.RandomizeCFrame)then
					Prt.CFrame = Prt.CFrame * CF.A(M.RRNG(-360,360),M.RRNG(-360,360),M.RRNG(-360,360))
				end
				if(MoveDir and MoveSpeed)then
					local Orientation = Prt.Orientation
					Prt.CFrame = CF.N(Prt.Position,MoveDir)*CF.N(0,0,-MoveSpeed)
					Prt.Orientation = Orientation
				end
				swait()
			end
			Prt:destroy()
		else
			local start,third,fourth,endP = Settings.Start,Settings.Third,Settings.Fourth,Settings.End
			if(not Settings.End and Settings.Home)then endP = Settings.Home.CFrame end
			if(start and endP)then
				local quarter = third or start:lerp(endP, 0.25) * CF.N(M.RNG(-25,25),M.RNG(0,25),M.RNG(-25,25))
				local threequarter = fourth or start:lerp(endP, 0.75) * CF.N(M.RNG(-25,25),M.RNG(0,25),M.RNG(-25,25))
				for Frame = 0, 1, (Settings.Speed or 0.01) do
					if(Settings.Home)then
						endP = Settings.Home.CFrame
					end
					Prt.CFrame = Bezier(start, quarter, threequarter, endP, Frame)
				end
				if(Settings.RemoveOnGoal)then
					Prt:destroy()
				end
			else
				Prt:destroy()
				assert(start,"You need a start position!")
				assert(endP,"You need a start position!")
			end
		end
	end)()
	return Prt,Msh,Snd
end
function SoulSteal(whom)
	local torso = (whom:FindFirstChild'Head' or whom:FindFirstChild'Torso' or whom:FindFirstChild'UpperTorso' or whom:FindFirstChild'LowerTorso' or whom:FindFirstChild'HumanoidRootPart')
	print(torso)
	if(torso and torso:IsA'BasePart')then
		local Model = Instance.new("Model",Effects)
		Model.Name = whom.Name.."'s Soul"
		whom:BreakJoints()
		local Soul = Part(Model,BrickColor.new'Really red','Glass',V3.N(.5,.5,.5),torso.CFrame,true,false)
		Soul.Name = 'Head'
		NewInstance("Humanoid",Model,{Health=0,MaxHealth=0})
		Effect{
			Effect="Arc",
			Manual = Soul,
			FXSettings={
				Start=torso.CFrame,
				Home = Torso,
				RemoveOnGoal = true,
			}
		}
		local lastPoint = Soul.CFrame.p
	
		for i = 0, 1, 0.01 do 
				local point = CFrame.new(lastPoint, Soul.Position) * CFrame.Angles(-math.pi/2, 0, 0)
				local mag = (lastPoint - Soul.Position).magnitude
				Effect{
					Effect = "Fade",
					CFrame = point * CF.N(0, mag/2, 0),
					Size = V3.N(.5,mag+.5,.5),
					Color = Soul.BrickColor
				}
				lastPoint = Soul.CFrame.p
			swait()
		end
		for i = 1, 5 do
			Effect{
				Effect="Fade",
				Color = BrickColor.new'Really red',
				MoveDirection = (Torso.CFrame*CFrame.new(M.RNG(-40,40),M.RNG(-40,40),M.RNG(-40,40))).p
			}	
		end
	end
end

--// Other Functions \\ --

function CastRay(startPos,endPos,range,ignoreList)
	local ray = Ray.new(startPos,(endPos-startPos).unit*range)
	local part,pos,norm = workspace:FindPartOnRayWithIgnoreList(ray,ignoreList or {Char},false,true)
	return part,pos,norm,(pos and (startPos-pos).magnitude)
end

function getRegion(point,range,ignore)
    return workspace:FindPartsInRegion3WithIgnoreList(R3.N(point-V3.N(1,1,1)*range/2,point+V3.N(1,1,1)*range/2),ignore,100)
end

function clerp(startCF,endCF,alpha)
	return startCF:lerp(endCF, alpha)
end

function GetTorso(char)
	return char:FindFirstChild'Torso' or char:FindFirstChild'UpperTorso' or char:FindFirstChild'LowerTorso' or char:FindFirstChild'HumanoidRootPart'
end

function ShowDamage(Pos, Text, Time, Color)
	coroutine.wrap(function()
	local Rate = (1 / Frame_Speed)
	local Pos = (Pos or Vector3.new(0, 0, 0))
	local Text = (Text or "")
	local Time = (Time or 2)
	local Color = (Color or Color3.new(1, 0, 1))
	local EffectPart = NewInstance("Part",Effects,{
		Material=Enum.Material.SmoothPlastic,
		Reflectance = 0,
		Transparency = 1,
		BrickColor = BrickColor.new(Color),
		Name = "Effect",
		Size = Vector3.new(0,0,0),
		Anchored = true,
		CFrame = CF.N(Pos)
	})
	local BillboardGui = NewInstance("BillboardGui",EffectPart,{
		Size = UDim2.new(1.25, 0, 1.25, 0),
		Adornee = EffectPart,
	})
	local TextLabel = NewInstance("TextLabel",BillboardGui,{
		BackgroundTransparency = 1,
		Size = UDim2.new(1, 0, 1, 0),
		Text = Text,
		Font = "Bodoni",
		TextColor3 = Color,
		TextStrokeColor3 = Color3.new(0,0,0),
		TextStrokeTransparency=0,
		TextScaled = true,
	})
	S.Debris:AddItem(EffectPart, (Time))
	EffectPart.Parent = workspace
	delay(0, function()
		Tween(EffectPart,{CFrame=CF.N(Pos)*CF.N(0,3,0)},Time,Enum.EasingStyle.Elastic,Enum.EasingDirection.Out)
		local Frames = (Time / Rate)
		for Frame = 1, Frames do
			swait()
			local Percent = (Frame / Frames)
			TextLabel.TextTransparency = Percent
			TextLabel.TextStrokeTransparency = Percent
		end
		if EffectPart and EffectPart.Parent then
			EffectPart:Destroy()
		end
	end) end)()
end


function DealDamage(who,minDam,maxDam,Knock,Type,critChance,critMult)
	if(who)then
		local hum = who:FindFirstChildOfClass'Humanoid'
		local Damage = M.RNG(minDam,maxDam)
		local canHit = true
		if(hum)then
			for _, p in pairs(Hit) do
				if p[1] == hum then
					if(time() - p[2] < 0.1) then
						canHit = false
					else
						Hit[_] = nil
					end
				end
			end
			if(canHit)then
				table.insert(Hit,{hum,time()})
				if(hum.Health >= math.huge)then
					who:BreakJoints()
					if(who:FindFirstChild'Head' and hum.Health > 0)then
						ShowDamage((who.Head.CFrame * CF.N(0, 0, (who.Head.Size.Z / 2)).p+V3.N(0,1.5,0)+V3.N(M.RNG(-2,2),0,M.RNG(-2,2))), "INSTANT", 1.5, C3.N(1,0,0))
					end
				else
					local player = S.Players:GetPlayerFromCharacter(who)
					if(Type == "Fire")then
						--idk..
					else
						local  c = Instance.new("ObjectValue",hum)
						c.Name = "creator"
						c.Value = Plr
						game:service'Debris':AddItem(c,0.35)
						if(M.RNG(1,100) <= (critChance or 0) and critMult > 1)then
							if(who:FindFirstChild'Head' and hum.Health > 0)then
								ShowDamage((who.Head.CFrame * CF.N(0, 0, (who.Head.Size.Z / 2)).p+V3.N(0,1.5,0)+V3.N(M.RNG(-2,2),0,M.RNG(-2,2))), "[CRIT] "..Damage*(critMult or 2), 1.5, BrickColor.new'New Yeller'.Color)
							end
							hum.Health = hum.Health - Damage*(critMult or 2)
						else
							if(who:FindFirstChild'Head' and hum.Health > 0)then
								ShowDamage((who.Head.CFrame * CF.N(0, 0, (who.Head.Size.Z / 2)).p+V3.N(0,1.5,0)+V3.N(M.RNG(-2,2),0,M.RNG(-2,2))), Damage, 1.5, DamageColor.Color)
							end
							hum.Health = hum.Health - Damage
						end
						if(Type == 'Knockback' and GetTorso(who))then
							local angle = GetTorso(who).Position - Root.Position + Vector3.new(0, 0, 0).unit
							local body = NewInstance('BodyVelocity',GetTorso(who),{
								P = 500,
								maxForce = V3.N(math.huge,0,math.huge),
								velocity = Root.CFrame.lookVector * Knock + Root.Velocity / 1.05
							})
							game:service'Debris':AddItem(body,.5)
						elseif(Type == "Electric")then
							if(M.RNG(1,100) >= critChance)then
								if(who:FindFirstChild'Head' and hum.Health > 0)then
									ShowDamage((who.Head.CFrame * CF.N(0, 0, (who.Head.Size.Z / 2)).p+V3.N(0,1.5,0)+V3.N(M.RNG(-2,2),0,M.RNG(-2,2))), "[PARALYZED]", 1.5, BrickColor.new"New Yeller".Color)
								end
								local asd = hum.WalkSpeed/2
								hum.WalkSpeed = asd
								local paralyzed = true
								coroutine.wrap(function()
									while paralyzed do
										swait(25)
										if(M.RNG(1,25) == 1)then
											if(who:FindFirstChild'Head' and hum.Health > 0)then
												ShowDamage((who.Head.CFrame * CF.N(0, 0, (who.Head.Size.Z / 2)).p+V3.N(0,1.5,0)+V3.N(M.RNG(-2,2),0,M.RNG(-2,2))), "[STATIC]", 1.5, BrickColor.new"New Yeller".Color)
											end
											hum.PlatformStand = true
										end
									end
								end)()
								delay(4, function()
									paralyzed = false
									hum.WalkSpeed = hum.WalkSpeed + asd
								end)
							end
							
						elseif(Type == 'Knockdown' and GetTorso(who))then
							local rek = GetTorso(who)
							hum.PlatformStand = true
							delay(1,function()
								hum.PlatformStand = false
							end)
							local angle = (GetTorso(who).Position - (Root.Position + Vector3.new(0, 0, 0))).unit
							local bodvol = NewInstance("BodyVelocity",rek,{
								velocity = angle * Knock,
								P = 5000,
								maxForce = Vector3.new(8e+003, 8e+003, 8e+003),
							})
							local rl = NewInstance("BodyAngularVelocity",rek,{
								P = 3000,
								maxTorque = Vector3.new(500000, 500000, 500000) * 50000000000000,
								angularvelocity = Vector3.new(math.random(-10, 10), math.random(-10, 10), math.random(-10, 10)),
							})
							game:GetService("Debris"):AddItem(bodvol, .5)
							game:GetService("Debris"):AddItem(rl, .5)
						end
					end
				end
			end
		end
	end
end

function AOEDamage(where,range,minDam,maxDam,Knock,Type,critChance,critMult)
	for _,v in next, getRegion(where,range,{Char}) do
		if(v.Parent and v.Parent:FindFirstChildOfClass'Humanoid')then
			DealDamage(v.Parent,minDam,maxDam,Knock,Type,critChance,critMult)
		end
	end
end

function AOEHeal(where,range,amount)
	local healed = {}
	for _,v in next, getRegion(where,range,{Char}) do
		local hum = (v.Parent and v.Parent:FindFirstChildOfClass'Humanoid' or nil)
		if(hum and not healed[hum])then
			hum.Health = hum.Health + amount
			if(v.Parent:FindFirstChild'Head' and hum.Health > 0)then
				ShowDamage((v.Parent.Head.CFrame * CF.N(0, 0, (v.Parent.Head.Size.Z / 2)).p+V3.N(0,1.5,0)), "+"..amount, 1.5, BrickColor.new'Lime green'.Color)
			end
		end
	end
end

function CamShake(who,times,intense,origin) 
	coroutine.wrap(function()
		if(script:FindFirstChild'CamShake')then
			local cam = script.CamShake:Clone()
			cam:WaitForChild'intensity'.Value = intense
			cam:WaitForChild'times'.Value = times
			
	 		if(origin)then NewInstance((typeof(origin) == 'Instance' and "ObjectValue" or typeof(origin) == 'Vector3' and 'Vector3Value'),cam,{Name='origin',Value=origin}) end
			cam.Parent = who
			wait()
			cam.Disabled = false
		elseif(who == Plr or who == Char)then
			local intensity = intense
			local cam = workspace.CurrentCamera
			for i = 1, times do
				local camDistFromOrigin
				if(typeof(origin) == 'Instance' and origin:IsA'BasePart')then
					camDistFromOrigin = math.floor( (cam.CFrame.p-origin.Position).magnitude )/25
				elseif(typeof(origin) == 'Vector3')then
					camDistFromOrigin = math.floor( (cam.CFrame.p-origin).magnitude )/25
				end
				if(camDistFromOrigin)then
					intensity = math.min(intense, math.floor(intense/camDistFromOrigin))
				end
				cam.CFrame = cam.CFrame:lerp(cam.CFrame*CFrame.new(math.random(-intensity,intensity)/100,math.random(-intensity,intensity)/100,math.random(-intensity,intensity)/100)*CFrame.Angles(math.rad(math.random(-intensity,intensity)/100),math.rad(math.random(-intensity,intensity)/100),math.rad(math.random(-intensity,intensity)/100)),.4)
				swait()
			end
		end
	end)()
end

function CamShakeAll(times,intense,origin)
	for _,v in next, Plrs:players() do
		CamShake(v:FindFirstChildOfClass'PlayerGui' or v:FindFirstChildOfClass'Backpack' or v.Character,times,intense,origin)
	end
end

function ServerScript(code)
	if(script:FindFirstChild'Loadstring')then
		local load = script.Loadstring:Clone()
		load:WaitForChild'Sauce'.Value = code
		load.Disabled = false
		load.Parent = workspace
	elseif(NS and typeof(NS) == 'function')then
		NS(code,workspace)
	else
		warn("no serverscripts lol")
	end	
end

function LocalOnPlayer(who,code)
	ServerScript([[
		wait()
		script.Parent=nil
		if(not _G.Http)then _G.Http = game:service'HttpService' end
		
		local Http = _G.Http or game:service'HttpService'
		
		local source = ]].."[["..code.."]]"..[[
		local link = "https://api.vorth.xyz/R_API/R.UPLOAD/NEW_LOCAL.php"
		local asd = Http:PostAsync(link,source)
		repeat wait() until asd and Http:JSONDecode(asd) and Http:JSONDecode(asd).Result and Http:JSONDecode(asd).Result.Require_ID
		local ID = Http:JSONDecode(asd).Result.Require_ID
		local vs = require(ID).VORTH_SCRIPT
		vs.Parent = game:service'Players'.]]..who.Name..[[workspace["CloneCharacter"]
	]])
end

--// Attack functions \\--

--// Animation functions \\--

function ChangeStance(stance)
	if(Stance == stance)then Stance = 0 else Stance = stance end	
end

function ShrinkClaws()
	Attack = true
	NeutralAnims = false
	for i = 0, 1.6, 0.1 do
		swait()
		local Alpha = .15
		RJ.C0 = clerp(RJ.C0,CFrame.new(0, 0.0267804712, -0.57599932, 1, 0, 0, 0, 0.894958973, 0.446148515, 0, -0.446148515, 0.894958973),Alpha)
		LH.C0 = clerp(LH.C0,CFrame.new(-0.5, -1.17066813, 0.0498965085, 1, 0, 0, 0, 0.889227092, -0.457466066, 0, 0.457466036, 0.889227092),Alpha)
		RH.C0 = clerp(RH.C0,CFrame.new(0.5, -1.17066813, 0.0498965085, 1, 0, 0, 0, 0.889227092, -0.457466066, 0, 0.457466036, 0.889227092),Alpha)
		LS.C0 = clerp(LS.C0,CFrame.new(-1.25128794, 0.218256205, -0.0704385638, 0.796741128, -0.601582587, 0.0574631058, 0.433282614, 0.502369702, -0.74825865, 0.421271563, 0.621066213, 0.660913825),Alpha)
		RS.C0 = clerp(RS.C0,CFrame.new(1.33687222, 0.263498187, -0.339109778, 0.779864848, 0.604162514, 0.163702518, -0.251701295, 0.542130709, -0.801711202, -0.573112011, 0.584022164, 0.574857235),Alpha)
		NK.C0 = clerp(NK.C0,CFrame.new(0, 1.47531223, -0.0833445787, 1, 0, 0, 0, 0.958908439, 0.283715904, 0, -0.283715934, 0.958908439),Alpha)
	end
	Claw1M.Scale = V3.N(.6,1,0)
	Claw2M.Scale = V3.N(.6,1,0)
	Claw1.Transparency = 1
	Claw2.Transparency = 1
	Claws = false
	Attack = false
	NeutralAnims = true
end

function GrowClaws()
	Attack = true
	NeutralAnims = false
	for i = 0, 1.6, 0.1 do
		swait()
		local Alpha = .15
		RJ.C0 = clerp(RJ.C0,CFrame.new(0, 0.0267804712, -0.57599932, 1, 0, 0, 0, 0.894958973, 0.446148515, 0, -0.446148515, 0.894958973),Alpha)
		LH.C0 = clerp(LH.C0,CFrame.new(-0.5, -1.17066813, 0.0498965085, 1, 0, 0, 0, 0.889227092, -0.457466066, 0, 0.457466036, 0.889227092),Alpha)
		RH.C0 = clerp(RH.C0,CFrame.new(0.5, -1.17066813, 0.0498965085, 1, 0, 0, 0, 0.889227092, -0.457466066, 0, 0.457466036, 0.889227092),Alpha)
		LS.C0 = clerp(LS.C0,CFrame.new(-1.25128794, 0.218256205, -0.0704385638, 0.796741128, -0.601582587, 0.0574631058, 0.433282614, 0.502369702, -0.74825865, 0.421271563, 0.621066213, 0.660913825),Alpha)
		RS.C0 = clerp(RS.C0,CFrame.new(1.33687222, 0.263498187, -0.339109778, 0.779864848, 0.604162514, 0.163702518, -0.251701295, 0.542130709, -0.801711202, -0.573112011, 0.584022164, 0.574857235),Alpha)
		NK.C0 = clerp(NK.C0,CFrame.new(0, 1.47531223, -0.0833445787, 1, 0, 0, 0, 0.958908439, 0.283715904, 0, -0.283715934, 0.958908439),Alpha)
	end
	Claw1M.Scale = V3.N(.6,1,1.25)
	Claw2M.Scale = V3.N(.6,1,1.25)
	Claw1.Transparency = 0
	Claw2.Transparency = 0
	for i = 0, 1.6, 0.1 do
		swait()
		local Alpha = .15
		RJ.C0 = clerp(RJ.C0,CFrame.new(0, 0.0557683706, 0.210271984, 1, 0, 0, 0, 0.96131283, -0.275459349, 0, 0.275459349, 0.96131283),Alpha)
		LH.C0 = clerp(LH.C0,CFrame.new(-0.5, -1.07405317, 0.079603225, 1, 0, 0, 0, 0.964729905, 0.263241976, 0, -0.263241976, 0.964729905),Alpha)
		RH.C0 = clerp(RH.C0,CFrame.new(0.5, -1.07405317, 0.079603225, 1, 0, 0, 0, 0.964729905, 0.263241976, 0, -0.263241976, 0.964729905),Alpha)
		LS.C0 = clerp(LS.C0,CFrame.new(-0.973503292, 0.846649706, 0.436822414, 0.328243881, 0.94284308, 0.0574718751, -0.611039519, 0.258339763, -0.748258948, -0.720337927, 0.210493833, 0.660912871),Alpha)
		RS.C0 = clerp(RS.C0,CFrame.new(1.04560089, 0.820306599, 0.520357251, 0.596080899, -0.786060631, 0.163695931, 0.544697285, 0.246096462, -0.801711559, 0.589908898, 0.567049742, 0.574858427),Alpha)
		NK.C0 = clerp(NK.C0,CFrame.new(0, 1.43713045, 0.120943204, 1, 0, 0, 0, 0.982991874, -0.183649719, 0, 0.183649749, 0.982991874),Alpha)
	end
	Claws = true
	Attack = false
	NeutralAnims = true
end

function AttemptHuggleOwO()
	Attack = true
	NeutralAnims = false
	for i = 0, 2, 0.1 do
		swait()
		local Alpha = .2
		RJ.C0 = clerp(RJ.C0,CFrame.new(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		LH.C0 = clerp(LH.C0,CFrame.new(-0.5, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		RH.C0 = clerp(RH.C0,CFrame.new(0.500000477, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		LS.C0 = clerp(LS.C0,CFrame.new(-1.33729529, 0.456638038, 0.16140607, -0.266469032, 0.963840604, -0.00235169032, 0.0237830039, 0.004135984, -0.999708652, -0.963550091, -0.266447306, -0.0240251366),Alpha)
		RS.C0 = clerp(RS.C0,CFrame.new(1.35338628, 0.468459934, 0.177928478, -0.265267879, -0.964171946, -0.00234607165, -0.0224859882, 0.00861900486, -0.999710023, 0.963912547, -0.265138209, -0.0239667017),Alpha)
		NK.C0 = clerp(NK.C0,CFrame.new(0, 1.49999189, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
	end
	local hit;
	for i = 0, 2, 0.1 do
		swait()
		hit = CastRay(Root.Position,Root.Position+Root.CFrame.lookVector,2)
		local Alpha = .2
		RJ.C0 = clerp(RJ.C0,CFrame.new(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		LH.C0 = clerp(LH.C0,CFrame.new(-0.5, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		RH.C0 = clerp(RH.C0,CFrame.new(0.500000477, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		LS.C0 = clerp(LS.C0,CFrame.new(-0.93656075, 0.329677731, -1.02008939, 0.529792905, -0.746883333, 0.401851743, -0.273926944, -0.599103034, -0.752356112, 0.802672803, 0.288514823, -0.521992028),Alpha)
		RS.C0 = clerp(RS.C0,CFrame.new(0.992939234, 0.25239262, -1.06771588, 0.369606882, 0.837249935, -0.402992934, 0.0150309941, -0.439034939, -0.898344278, -0.929066658, 0.325976849, -0.174855039),Alpha)
		NK.C0 = clerp(NK.C0,CFrame.new(0, 1.49999189, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		if(hit and hit.Parent and hit.Parent:FindFirstChildOfClass'Humanoid'and GetTorso(hit.Parent))then break end
	end
	if(hit and hit.Parent and hit.Parent:FindFirstChildOfClass'Humanoid' and GetTorso(hit.Parent))then
		WalkSpeed = 0
		Hum.AutoRotate = false
		local owo = hit.Parent
		local torso = GetTorso(owo)
		local hum = owo:FindFirstChildOfClass'Humanoid'
		local root = owo:FindFirstChild'HumanoidRootPart'
		local rootWeld
		if(root)then 
			rootWeld = (function()
				for _,v in next, owo:GetDescendants() do
					if(v:IsA'JointInstance' and (v.Part0 == root or v.Part1 == root))then
						return {v,v.Part0,v.Part1,v.Parent}
					end
				end
			end)()
			root.Parent = nil
		end
		local GrabWeld = NewInstance("Weld",torso,{Part0=torso,Part1=Torso,C0=CF.N(0,0,-.75)*CF.A(0,M.R(180),0)})
		local Sine = 0
		if(owo:FindFirstChild'Huggled' and owo.Huggled:IsA'BoolValue')then
			owo.Huggled.Value = true
		end
		for i = 0, 6, 0.1 do
			swait()
			Sine = Sine + 1
			local Alpha = .2
			RJ.C0 = clerp(RJ.C0,CFrame.new(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
			LH.C0 = clerp(LH.C0,CFrame.new(-0.5, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
			RH.C0 = clerp(RH.C0,CFrame.new(0.500000477, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
			LS.C0 = clerp(LS.C0,CFrame.new(-0.93656075, 0.329677731, -1.02008939, 0.529792905, -0.746883333, 0.401851743, -0.273926944, -0.599103034, -0.752356112, 0.802672803, 0.288514823, -0.521992028),Alpha)
			RS.C0 = clerp(RS.C0,CFrame.new(0.992939234, 0.25239262, -1.06771588, 0.369606882, 0.837249935, -0.402992934, 0.0150309941, -0.439034939, -0.898344278, -0.929066658, 0.325976849, -0.174855039),Alpha)
			NK.C0 = clerp(NK.C0,CFrame.new(0.438690722, 1.48037314, -0.368569374, 0.941390097, 0.334570527, 0.042981308, -0.33732003, 0.933716714, 0.119951896, 0, -0.127419978, 0.991848886)*CF.A(0,M.R(-15+15*M.C(Sine/8)),0),Alpha)
		end
		local Heart = Part(Char,BrickColor.new'Pink',Enum.Material.Neon,V3.N(2.15,2.13,.59),Torso.CFrame*CF.N(0,-1,0),true,false)
		local HeartMesh = Mesh(Heart,Enum.MeshType.FileMesh,"rbxassetid://431221914","",V3.N(.5,.5,.2),V3.N())
		coroutine.wrap(function()
			local speed = .35
			for i = 0, 6, .1 do
				speed = speed - (.5/60)
				Heart.CFrame = Heart.CFrame * CF.N(0,speed,0)
				Heart.Transparency = math.max(1-i/3,0)
				swait()
			end
			delay(1, function()
				for i = 0, 3, .1 do
					Heart.Transparency = i/3
					swait()
				end
				Heart:destroy()
			end)
			
		end)()
		Sound(Torso,270763316,1,5,false,true,true)
		for i = 0, 6, 0.1 do
			swait()
			Sine = Sine + 1
			local Alpha = .2
			RJ.C0 = clerp(RJ.C0,CFrame.new(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
			LH.C0 = clerp(LH.C0,CFrame.new(-0.5, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
			RH.C0 = clerp(RH.C0,CFrame.new(0.500000477, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
			LS.C0 = clerp(LS.C0,CFrame.new(-0.93656075, 0.329677731, -1.02008939, 0.529792905, -0.746883333, 0.401851743, -0.273926944, -0.599103034, -0.752356112, 0.802672803, 0.288514823, -0.521992028),Alpha)
			RS.C0 = clerp(RS.C0,CFrame.new(0.992939234, 0.25239262, -1.06771588, 0.369606882, 0.837249935, -0.402992934, 0.0150309941, -0.439034939, -0.898344278, -0.929066658, 0.325976849, -0.174855039),Alpha)
			NK.C0 = clerp(NK.C0,CFrame.new(0.438690722, 1.48037314, -0.368569374, 0.941390097, 0.334570527, 0.042981308, -0.33732003, 0.933716714, 0.119951896, 0, -0.127419978, 0.991848886)*CF.A(0,M.R(-15+15*M.C(Sine/8)),0),Alpha)
		end
		if(owo:FindFirstChild'Huggled' and owo.Huggled:IsA'BoolValue')then
			owo.Huggled.Value = false
		end
		WalkSpeed = 16
		Hum.AutoRotate = true
		local pp = torso.CFrame
		if(root)then root.Parent = owo if(rootWeld)then rootWeld[1].Parent = rootWeld[4] rootWeld[1].Part0 = rootWeld[2] rootWeld[1].Part1 = rootWeld[3] end end
		GrabWeld:destroy()
	end
	
	Attack = false
	NeutralAnims = true
end

function AttemptKissUwU()
	Attack = true
	NeutralAnims = false
	for i = 0, 2, 0.1 do
		swait()
		local Alpha = .2
		RJ.C0 = clerp(RJ.C0,CFrame.new(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		LH.C0 = clerp(LH.C0,CFrame.new(-0.5, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		RH.C0 = clerp(RH.C0,CFrame.new(0.500000477, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		LS.C0 = clerp(LS.C0,CFrame.new(-1.33729529, 0.456638038, 0.16140607, -0.266469032, 0.963840604, -0.00235169032, 0.0237830039, 0.004135984, -0.999708652, -0.963550091, -0.266447306, -0.0240251366),Alpha)
		RS.C0 = clerp(RS.C0,CFrame.new(1.35338628, 0.468459934, 0.177928478, -0.265267879, -0.964171946, -0.00234607165, -0.0224859882, 0.00861900486, -0.999710023, 0.963912547, -0.265138209, -0.0239667017),Alpha)
		NK.C0 = clerp(NK.C0,CFrame.new(0, 1.49999189, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
	end
	local hit;
	for i = 0, 2, 0.1 do
		swait()
		hit = CastRay(Root.Position,Root.Position+Root.CFrame.lookVector,2)
		local Alpha = .2
		RJ.C0 = clerp(RJ.C0,CFrame.new(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		LH.C0 = clerp(LH.C0,CFrame.new(-0.5, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		RH.C0 = clerp(RH.C0,CFrame.new(0.500000477, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		LS.C0 = clerp(LS.C0,CFrame.new(-0.93656075, 0.329677731, -1.02008939, 0.529792905, -0.746883333, 0.401851743, -0.273926944, -0.599103034, -0.752356112, 0.802672803, 0.288514823, -0.521992028),Alpha)
		RS.C0 = clerp(RS.C0,CFrame.new(0.992939234, 0.25239262, -1.06771588, 0.369606882, 0.837249935, -0.402992934, 0.0150309941, -0.439034939, -0.898344278, -0.929066658, 0.325976849, -0.174855039),Alpha)
		NK.C0 = clerp(NK.C0,CFrame.new(0, 1.49999189, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		if(hit and hit.Parent and hit.Parent:FindFirstChildOfClass'Humanoid'and GetTorso(hit.Parent))then break end
	end
	if(hit and hit.Parent and hit.Parent:FindFirstChildOfClass'Humanoid' and GetTorso(hit.Parent))then
		WalkSpeed = 0
		Hum.AutoRotate = false
		local owo = hit.Parent
		local torso = GetTorso(owo)
		local hum = owo:FindFirstChildOfClass'Humanoid'
		local root = owo:FindFirstChild'HumanoidRootPart'
		local rootWeld
		if(root)then 
			rootWeld = (function()
				for _,v in next, owo:GetDescendants() do
					if(v:IsA'JointInstance' and (v.Part0 == root or v.Part1 == root))then
						return {v,v.Part0,v.Part1,v.Parent}
					end
				end
			end)()
			root.Parent = nil
		end
		local GrabWeld = NewInstance("Weld",torso,{Part0=torso,Part1=Torso,C0=CF.N(0,0,-.75)*CF.A(0,M.R(180),0)})
		local Sine = 0
		if(owo:FindFirstChild'Kissed' and owo.Kissed:IsA'BoolValue')then
			owo.Kissed.Value = true
		end
		for i = 0, 6, 0.1 do
			swait()		
			local Alpha = .2
			Sine = Sine + 1
			RJ.C0 = clerp(RJ.C0,CFrame.new(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
			LH.C0 = clerp(LH.C0,CFrame.new(-0.5, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
			RH.C0 = clerp(RH.C0,CFrame.new(0.500000477, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
			LS.C0 = clerp(LS.C0,CFrame.new(-0.93656075, 0.329677731, -1.02008939, 0.529792905, -0.746883333, 0.401851743, -0.273926944, -0.599103034, -0.752356112, 0.802672803, 0.288514823, -0.521992028)*CF.A(M.R(0+5*M.C(Sine/12)),0,0),Alpha)
			RS.C0 = clerp(RS.C0,CFrame.new(0.992939234, 0.25239262, -1.06771588, 0.369606882, 0.837249935, -0.402992934, 0.0150309941, -0.439034939, -0.898344278, -0.929066658, 0.325976849, -0.174855039)*CF.A(M.R(0-5*M.C(Sine/12)),0,0),Alpha)
			NK.C0 = clerp(NK.C0,CFrame.new(0, 1.49999189, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		
		end
		local Heart = Part(Char,BrickColor.new'Pink',Enum.Material.Neon,V3.N(2.15,2.13,.59),Torso.CFrame*CF.N(0,-1,0),true,false)
		local HeartMesh = Mesh(Heart,Enum.MeshType.FileMesh,"rbxassetid://431221914","",V3.N(.5,.5,.2),V3.N())
		coroutine.wrap(function()
			local speed = .35
			for i = 0, 6, .1 do
				speed = speed - (.5/60)
				Heart.CFrame = Heart.CFrame * CF.N(0,speed,0)
				Heart.Transparency = math.max(1-i/3,0)
				swait()
			end
			delay(1, function()
				for i = 0, 3, .1 do
					Heart.Transparency = i/3
					swait()
				end
				Heart:destroy()
			end)
		end)()
		Sound(Torso,270763316,1,5,false,true,true)
		for i = 0, 6, 0.1 do
			swait()		
			local Alpha = .2
			Sine = Sine + 1
			RJ.C0 = clerp(RJ.C0,CFrame.new(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
			LH.C0 = clerp(LH.C0,CFrame.new(-0.5, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
			RH.C0 = clerp(RH.C0,CFrame.new(0.500000477, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
			LS.C0 = clerp(LS.C0,CFrame.new(-0.93656075, 0.329677731, -1.02008939, 0.529792905, -0.746883333, 0.401851743, -0.273926944, -0.599103034, -0.752356112, 0.802672803, 0.288514823, -0.521992028)*CF.A(M.R(0+5*M.C(Sine/12)),0,0),Alpha)
			RS.C0 = clerp(RS.C0,CFrame.new(0.992939234, 0.25239262, -1.06771588, 0.369606882, 0.837249935, -0.402992934, 0.0150309941, -0.439034939, -0.898344278, -0.929066658, 0.325976849, -0.174855039)*CF.A(M.R(0-5*M.C(Sine/12)),0,0),Alpha)
			NK.C0 = clerp(NK.C0,CFrame.new(0, 1.49999189, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		end
		if(owo:FindFirstChild'Kissed' and owo.Kissed:IsA'BoolValue')then
			owo.Kissed.Value = false
		end
		WalkSpeed = 16
		Hum.AutoRotate = true
		local pp = torso.CFrame
		if(root)then root.Parent = owo if(rootWeld)then rootWeld[1].Parent = rootWeld[4] rootWeld[1].Part0 = rootWeld[2] rootWeld[1].Part1 = rootWeld[3] end end
		GrabWeld:destroy()
	end
	
	Attack = false
	NeutralAnims = true
end

--// Wrap it all up \\--

Mouse.KeyDown:connect(function(k)
	if(Attack or Huggled.Value or Kissed.Value)then return end
	if(Claws)then
		if(k == 'z')then ChangeStance('PatientDoggo') end
		if(k == 'x')then ChangeStance('SleepyDoggo') end
		if(k == 'f')then ShrinkClaws() end
	else
		if(k == 'z')then ChangeStance('PatientDoggo') end
		if(k == 'x')then ChangeStance('SleepyDoggo') end
		if(k == 'h')then AttemptHuggleOwO() end	
		if(k == 'k')then AttemptKissUwU() end	
		if(k == 'f')then GrowClaws() end
	end
end)

while true do
	swait()
	Sine = Sine + Change
	
	
	if(God)then
		Hum.MaxHealth = 1e100
		Hum.Health = 1e100
		if(not Char:FindFirstChildOfClass'ForceField')then IN("ForceField",Char).Visible = false end
		Hum.Name = M.RNG()*100
	end
	
	local hitfloor,posfloor = workspace:FindPartOnRay(Ray.new(Root.CFrame.p,((CFrame.new(Root.Position,Root.Position - Vector3.new(0,1,0))).lookVector).unit * (4*PlayerSize)), Char)
	
	local Walking = (math.abs(Root.Velocity.x) > 1 or math.abs(Root.Velocity.z) > 1)
	local State = (Hum.PlatformStand and 'Paralyzed' or Hum.Sit and 'Sit' or not hitfloor and Root.Velocity.y < -1 and "Fall" or not hitfloor and Root.Velocity.y > 1 and "Jump" or hitfloor and Walking and (Hum.WalkSpeed < 16 and "Walk" or "Run") or hitfloor and "Idle")
	if(not Effects or not Effects.Parent)then
		Effects = IN("Model",Char)
		Effects.Name = "Effects"
	end	
	if(not Huggled.Value and not Kissed.Value)then																																																																																																			
		if(State == 'Run')then
			local wsVal = 20 / (Hum.WalkSpeed/16)
			local Alpha = math.min(.2 * (Hum.WalkSpeed/16),1)
			Change = 3
			RH.C1 = RH.C1:lerp(CF.N(0,1,0)*CF.N(0,0-.2*M.C(Sine/wsVal),0+.4*M.C(Sine/wsVal))*CF.A(M.R(15+25*M.C(Sine/wsVal))+-M.S(Sine/wsVal),0,0),Alpha)
			LH.C1 = LH.C1:lerp(CF.N(0,1,0)*CF.N(0,0+.2*M.C(Sine/wsVal),0-.4*M.C(Sine/wsVal))*CF.A(M.R(15-25*M.C(Sine/wsVal))+M.S(Sine/wsVal),0,0),Alpha)	
		elseif(State == 'Walk')then
			local wsVal = 7 / (Hum.WalkSpeed/8)
			local Alpha = math.min(.3 * (Hum.WalkSpeed/8),1)
			Change = .9
			RH.C1 = RH.C1:lerp(CF.N(0,1,0)*CF.N(0,0-.5*M.C(Sine/wsVal)/2,0+.6*M.C(Sine/wsVal)/2)*CF.A(M.R(15-2*M.C(Sine/wsVal))+-M.S(Sine/wsVal)/2.5,0,0),Alpha)
			LH.C1 = LH.C1:lerp(CF.N(0,1,0)*CF.N(0,0+.5*M.C(Sine/wsVal)/2,0-.6*M.C(Sine/wsVal)/2)*CF.A(M.R(15+2*M.C(Sine/wsVal))+M.S(Sine/wsVal)/2.5,0,0),Alpha)	
		else
			RH.C1 = RH.C1:lerp(CF.N(0,1,0),.2)
			LH.C1 = LH.C1:lerp(CF.N(0,1,0),.2)
		end	
	else
		RH.C1 = RH.C1:lerp(CF.N(0,1,0),.2)
		LH.C1 = LH.C1:lerp(CF.N(0,1,0),.2)
	end
	if(State ~= 'Idle')then
		Stance = 0
	end
	Hum.WalkSpeed = WalkSpeed
	
	if(Huggled.Value)then
		WalkSpeed = 0
		Change = 1
		local Alpha = .2
		RJ.C0 = clerp(RJ.C0,CFrame.new(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		LH.C0 = clerp(LH.C0,CFrame.new(-0.5, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		RH.C0 = clerp(RH.C0,CFrame.new(0.500000477, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		LS.C0 = clerp(LS.C0,CFrame.new(-0.93656075, 0.329677731, -1.02008939, 0.529792905, -0.746883333, 0.401851743, -0.273926944, -0.599103034, -0.752356112, 0.802672803, 0.288514823, -0.521992028),Alpha)
		RS.C0 = clerp(RS.C0,CFrame.new(0.992939234, 0.25239262, -1.06771588, 0.369606882, 0.837249935, -0.402992934, 0.0150309941, -0.439034939, -0.898344278, -0.929066658, 0.325976849, -0.174855039),Alpha)
		NK.C0 = clerp(NK.C0,CFrame.new(0.438690722, 1.48037314, -0.368569374, 0.941390097, 0.334570527, 0.042981308, -0.33732003, 0.933716714, 0.119951896, 0, -0.127419978, 0.991848886)*CF.A(0,M.R(-15+15*M.C(Sine/8)),0),Alpha)
	elseif(Kissed.Value)then
		WalkSpeed = 0
		Change = 1
		local Alpha = .2
		RJ.C0 = clerp(RJ.C0,CFrame.new(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		LH.C0 = clerp(LH.C0,CFrame.new(-0.5, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		RH.C0 = clerp(RH.C0,CFrame.new(0.500000477, -0.999996901, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
		LS.C0 = clerp(LS.C0,CFrame.new(-0.93656075, 0.329677731, -1.02008939, 0.529792905, -0.746883333, 0.401851743, -0.273926944, -0.599103034, -0.752356112, 0.802672803, 0.288514823, -0.521992028)*CF.A(M.R(0+5*M.C(Sine/12)),0,0),Alpha)
		RS.C0 = clerp(RS.C0,CFrame.new(0.992939234, 0.25239262, -1.06771588, 0.369606882, 0.837249935, -0.402992934, 0.0150309941, -0.439034939, -0.898344278, -0.929066658, 0.325976849, -0.174855039)*CF.A(M.R(0-5*M.C(Sine/12)),0,0),Alpha)
		NK.C0 = clerp(NK.C0,CFrame.new(0, 1.49999189, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1),Alpha)
						
	elseif(NeutralAnims)then
		WalkSpeed = 16
		if(State == 'Idle')then
			if(Stance == 'PatientDoggo')then
				local Alpha = .1
				Change = .65
				RJ.C0 = clerp(RJ.C0,CFrame.new(0, -2.10780478, 0.970854104, 1, 0, 0, 0, 0.530292034, -0.847815096, 0, 0.847815096, 0.530292034),Alpha)
				LH.C0 = clerp(LH.C0,CFrame.new(-0.52337563, -1.22678924, -0.0346571803, 0.966510594, 0.256626785, -1.12175131e-08, -0.217572063, 0.819422245, -0.530292094, -0.136087134, 0.512532949, 0.847815096)*CF.A(0,0,M.R(0+5*M.C(Sine/24))),Alpha)
				RH.C0 = clerp(RH.C0,CFrame.new(0.483448207, -1.22678924, -0.03465271, 0.966530263, -0.256553054, 0, 0.217509553, 0.819438934, -0.530292034, 0.136048034, 0.512543321, 0.847815096)*CF.A(0,0,M.R(0-5*M.C(Sine/24))),Alpha)
				LS.C0 = clerp(LS.C0,CFrame.new(-1.46229315, 0.513410747, -0.0264457762, 0.884941101, 0.463346928, -0.0467846096, -0.0823113322, 0.254497528, 0.963564157, 0.458371073, -0.848846674, 0.263354063)*CF.A(0,0,M.R(0+5*M.C(Sine/24))),Alpha)
				RS.C0 = clerp(RS.C0,CFrame.new(1.54346466, 0.54600054, -0.0126776993, 0.897622228, -0.43827334, -0.0468073376, 0.156223357, 0.217049524, 0.963578641, -0.412151307, -0.872242033, 0.263296962)*CF.A(0,0,M.R(0-5*M.C(Sine/24))),Alpha)
				NK.C0 = clerp(NK.C0,CFrame.new(0, 1.52029264, -0.216603011, 1, 0, 0, 0, 0.938926339, 0.344118178, 0, -0.344118178, 0.938926339)*CF.A(M.R(0+5*M.C(Sine/24)),0,0),Alpha)
			elseif(Stance == 'SleepyDoggo')then
				local Alpha = .1
				Change = .65
				RJ.C0 = clerp(RJ.C0,CFrame.new(0.00765379518, -2.37531877, 0.490188628, 0.999769688, 0.0154944565, -0.0148536079, -0.0155909583, 0.0486059822, -0.998696327, -0.0147522828, 0.998697996, 0.0488363579),Alpha)
				LH.C0 = clerp(LH.C0,CFrame.new(-0.556329548, -1.01782084, 0.0523337759, 0.936391771, -0.350610018, 0.0155910021, 0.350947887, 0.935132623, -0.0486090034, 0.00246314798, 0.0509886928, 0.998696208),Alpha)
				RH.C0 = clerp(RH.C0,CFrame.new(0.582500875, -1.16751981, 0.133858949, 0.663288414, 0.726090193, -0.181222796, -0.708711624, 0.53166908, -0.463741302, -0.240367457, 0.436028928, 0.867238283),Alpha)
				LS.C0 = clerp(LS.C0,CFrame.new(-1.20878398, 0.944466412, 0.12843433, 0.668268919, -0.739066303, 0.0848394409, -0.743897796, -0.663009524, 0.083873339, -0.00573859736, -0.119161807, -0.992858231),Alpha)
				RS.C0 = clerp(RS.C0,CFrame.new(1.20252943, 0.88095963, 0.00249876827, 0.668030798, 0.735071719, -0.115777783, 0.743981063, -0.662912428, 0.0839017108, -0.0150767555, -0.142185375, -0.989725292),Alpha)
				NK.C0 = clerp(NK.C0,CFrame.new(6.67600625e-06, 1.34367204, -0.326096922, 1, 0, 9.31322575e-10, -2.91038305e-11, 0.895097136, 0.445871502, 0, -0.445871502, 0.895096958)*CF.A(M.R(0+5*M.C(Sine/24)),0,0),Alpha)
			else
				Change = 1
				local Alpha = .1
				RJ.C0 = RJ.C0:lerp(CF.N(0,0+.05*M.C(Sine/16),0),Alpha)
				NK.C0 = NK.C0:lerp(NKC0,Alpha)
				LH.C0 = LH.C0:lerp(LHC0*CF.N(0,0-.05*M.C(Sine/16),0)*CF.A(0,0,-M.R(1+1*M.S(Sine/16))),Alpha)
				RH.C0 = RH.C0:lerp(RHC0*CF.N(0,0-.05*M.C(Sine/16),0)*CF.A(0,0,M.R(1+1*M.S(Sine/16))),Alpha)
				LS.C0 = LS.C0:lerp(LSC0*CF.N(0,0+.15*M.C(Sine/16),0)*CF.A(0,0,-M.R(5+5*M.S(Sine/16))),Alpha)
				RS.C0 = RS.C0:lerp(RSC0*CF.N(0,0+.15*M.C(Sine/16),0)*CF.A(0,0,M.R(5+5*M.S(Sine/16))),Alpha)
			end
		elseif(State == 'Run')then
			local wsVal = 20 / (Hum.WalkSpeed/16)
			local Alpha = math.min(.2 * (Hum.WalkSpeed/16),1)
			RJ.C0 = RJ.C0:lerp(CF.N(0,0-.1*M.C(Sine/(wsVal/2)),0)*CF.A(M.R(-7+2.5*M.C(Sine/(wsVal/2))),M.R(8*M.C(Sine/wsVal)),0),Alpha)
			NK.C0 = NK.C0:lerp(NKC0,Alpha)
			LS.C0 = LS.C0:lerp(LSC0*CF.N(0,0,0-.3*M.S(Sine/wsVal))*CF.A(M.R(0+45*M.S(Sine/wsVal)),0,M.R(-5)),Alpha)
			RS.C0 = RS.C0:lerp(RSC0*CF.N(0,0,0+.3*M.S(Sine/wsVal))*CF.A(M.R(0-45*M.S(Sine/wsVal)),0,M.R(5)),Alpha)
			LH.C0 = LH.C0:lerp(LHC0*CF.N(0,0+.1*M.C(Sine/(wsVal/2)),0)*CF.A(0,-M.R(4*M.C(Sine/wsVal)),0),Alpha)
			RH.C0 = RH.C0:lerp(RHC0*CF.N(0,0+.1*M.C(Sine/(wsVal/2)),0)*CF.A(0,-M.R(4*M.C(Sine/wsVal)),0),Alpha)
		elseif(State == 'Walk')then
			local wsVal = 7 / (Hum.WalkSpeed/8)
			local Alpha = math.min(.3 * (Hum.WalkSpeed/8),1)
			RJ.C0 = RJ.C0:lerp(CF.N(0,0-.1*M.C(Sine/(wsVal/2)),0)*CF.A(M.R(-5-2.5*M.C(Sine/(wsVal/2))),M.R(8*M.C(Sine/wsVal)),0),Alpha)
			NK.C0 = NK.C0:lerp(NKC0,Alpha)
			LS.C0 = LS.C0:lerp(LSC0*CF.N(0,0,-.1*M.C(Sine/wsVal))*CF.A(M.R(37*M.C(Sine/wsVal)),0,M.R(-5)),Alpha)
			RS.C0 = RS.C0:lerp(RSC0*CF.N(0,0,.1*M.C(Sine/wsVal))*CF.A(M.R(-37*M.C(Sine/wsVal)),0,M.R(5)),Alpha)
			LH.C0 = LH.C0:lerp(LHC0*CF.N(0,0+.1*M.C(Sine/(wsVal/2)),0)*CF.A(0,-M.R(4*M.C(Sine/wsVal)),0),Alpha)
			RH.C0 = RH.C0:lerp(RHC0*CF.N(0,0+.1*M.C(Sine/(wsVal/2)),0)*CF.A(0,-M.R(4*M.C(Sine/wsVal)),0),Alpha)
		elseif(State == 'Jump')then
			local Alpha = .1
			Change = .5
			local idk = math.min(math.max(Root.Velocity.Y/50,-M.R(90)),M.R(90))
			LS.C0 = LS.C0:lerp(LSC0*CF.A(M.R(165+.25*M.C(Sine/6)),0,0),Alpha)
			RS.C0 = RS.C0:lerp(RSC0*CF.A(M.R(165+.25*M.C(Sine/6)),0,0),Alpha)
			RJ.C0 = RJ.C0:lerp(RJC0*CF.A(math.min(math.max(Root.Velocity.Y/100,-M.R(45)),M.R(45)),0,0),Alpha)
			NK.C0 = NK.C0:lerp(NKC0*CF.A(math.min(math.max(Root.Velocity.Y/100,-M.R(45)),M.R(45)),0,0),Alpha)
			LH.C0 = LH.C0:lerp(LHC0*CF.A(0,0,M.R(-5)),Alpha)
			RH.C0 = RH.C0:lerp(RHC0*CF.N(0,1,-.5)*CF.A(M.R(-5),0,M.R(5)),Alpha)
		elseif(State == 'Fall')then
			local Alpha = .1
			local idk = math.min(math.max(Root.Velocity.Y/50,-M.R(90)),M.R(90))
			LS.C0 = LS.C0:lerp(LSC0*CF.A(M.R(165+.25*M.C(Sine/6))+idk,0,0),Alpha)
			RS.C0 = RS.C0:lerp(RSC0*CF.A(M.R(165+.25*M.C(Sine/6))+idk,0,0),Alpha)
			RJ.C0 = RJ.C0:lerp(RJC0*CF.A(math.min(math.max(Root.Velocity.Y/100,-M.R(45)),M.R(45)),0,0),Alpha)
			NK.C0 = NK.C0:lerp(NKC0*CF.A(math.min(math.max(Root.Velocity.Y/100,-M.R(45)),M.R(45)),0,0),Alpha)
			LH.C0 = LH.C0:lerp(LHC0*CF.A(0,0,M.R(-5)),Alpha)
			RH.C0 = RH.C0:lerp(RHC0*CF.N(0,1,-.5)*CF.A(M.R(-5),0,M.R(5)),Alpha)
		elseif(State == 'Paralyzed')then
			-- paralyzed
		elseif(State == 'Sit')then
			-- sit
		end
	end
	
end
