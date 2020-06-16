local library = loadstring(game:HttpGetAsync("https://raw.githubusercontent.com/Dovahkiin1234/ratcrossing/master/sss?token=ALFI5ALOPLNVE4EWWH7T3RC65C5OA"))()
local w = library:CreateWindow('lol')
w:Button("kill all but u", function()
local damage = 100
local pname = game.Players.LocalPlayer.Name
Players = game:GetService("Players")
for i, player in pairs(Players:GetPlayers()) do
if player.Name ~= pname then
local A_1 = game:GetService("Workspace")[player.Name].Humanoid
local A_2 = damage
local Event = game:GetService("ReplicatedStorage").GunRemotes.TakeDamage
Event:FireServer(A_1, A_2)
end
end
end)
w:Button("kill all", function()
local damage = 100
Players = game:GetService("Players")
for i, player in pairs(Players:GetPlayers()) do
local A_1 = game:GetService("Workspace")[player.Name].Humanoid
local A_2 = damage
local Event = game:GetService("ReplicatedStorage").GunRemotes.TakeDamage
Event:FireServer(A_1, A_2)
end
end)
w:Button("click to kill (buggy)", function()
local player = game.Players.LocalPlayer
local mouse = player:GetMouse()
mouse.Button1Down:connect(function()
local mT = mouse.Target
if mT.Parent.Humanoid then
local dead = mT.Parent.Name
local dead2 = mT.Parent.Parent.Name
local dead3 = mT.Parent.Parent.Parent.Name
local damage = 100
local A_1 = game:GetService("Workspace")[dead].Humanoid
local A_2 = damage
local Event = game:GetService("ReplicatedStorage").GunRemotes.TakeDamage
Event:FireServer(A_1, A_2)
local A_1 = game:GetService("Workspace")[dead2].Humanoid
local A_2 = damage
local Event = game:GetService("ReplicatedStorage").GunRemotes.TakeDamage
Event:FireServer(A_1, A_2)
local A_1 = game:GetService("Workspace")[dead3].Humanoid
local A_2 = damage
local Event = game:GetService("ReplicatedStorage").GunRemotes.TakeDamage
Event:FireServer(A_1, A_2)
print(dead)
end
end)
end)
w:Button("god mode", function()
local damage = -2189047129
local player = game.Players.LocalPlayer.Name
local A_1 = game:GetService("Workspace")[player].Humanoid
local A_2 = damage
local Event = game:GetService("ReplicatedStorage").GunRemotes.TakeDamage
Event:FireServer(A_1, A_2)
end)
