# cluster
It comes with:
Very clean code to my standards
Alot of hooks
Nice logging (console output)
A good amount of interfaces
Clean and easy to understand file structure
A class that handles and caches module handles for faster access (module_manager.h)
A vaporwave-looking ImGui menu, that uses the latest version of imgui to my knowledge
Proper thridperson with proper angle setting, ignoring other players so they dont block your tp https://cdn.discordapp.com/attachmen...TzRbyjZgDC.gif
Full dx9 renderer, including pretty nice and easy to use text rendering (Stream-proof!)
Somewhat good error handeling
Uninjection without crashing (Press delete & end at the same time)
C++ casts used everywhere
Proper input handling for the menu, enabling you to move around, switch weapons and all of that while using the menu
A config system thats worth looking into, it saves the instance of my config class containing all variables into a file as binary
Consistant coding style, everything is snake case too
All the other stuff you expect from a proper base
Seperate file for every hook, depends on your opinion if this is a up- or downside
Use of somewhat modern C++

(Uses Minhook, but wrapped)
List of hooks:
CreateMove
PaintTraverse
EndScene
Reset
FrameStageNotify
CheckFileCrcsWithServer
LooseFileAllowed
DrawModelExecute
LockCursor
GetViewmodelFOV
GetColorModulation
GetScreenAspectRatio
IsUsingStaticPropDebug
CvarGetBool
DoPostScreenEffects
IsConnected
FireEvents
IsHTLV
ListLeavesInBox
IsFollowingEntity
ShouldSkipAnimationFrame
StandardBlendingRules
UpdateClientSideAnimations
DoProceduralFootPlant
SetupBones
GetViewAngles
RunCommand
CalcViewBob
CalcView
PlayStepSound

List of interfaces:
ClientMode
Globals
ClientState
EntityList
Client
Panel
DirectX
FileSystem
ModelRender
Surface
Engine
DebugOverlay
Convar
Prediction
CCSPlayer
Input
Trace

Note that some hooks may have been commented out because of reasons i cant remember.
There is some stuff in there that fixes some game bullshit, cant remember what exactly.

Stuff im not proud about:
Macro abuse to its finest (hooks.h and menu)
Netvar manager is pasted as far as i can remember
Some menu stuff has hardcoded values
I had no idea what std::string_view was at the point of making this, so expect alot of const string references
Neither did i know what fixed width integer types where
std::to_string
Dx renderer is not threadsafe, so expect the esp to do the chacha sometimes
Alot of draw calls for outlined text

WARNING: The last time i updated this was about a month ago, clientstate is probably outdated!


List of features:
Visuals(Box, Name, Flags, HealthBar, HealthText)
Thirdperson
Menu (duh)
Hardcoded nightmode

Feel free to leave feedback (except the stuff i already pointed out obviously)
