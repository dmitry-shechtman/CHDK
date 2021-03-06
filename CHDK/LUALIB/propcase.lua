--[[ 
This module loads a table which maps camera property case names to 
their respective numbers. It also takes care to load the correct property 
case set for the camera.

Usage: 
  proptable=require "propcase"
  Tv=get_prop(proptable.TV)
--]]

if get_propset()==1 then
  return require("gen/propset1")
elseif get_propset()==2 then
  return require("gen/propset2")
elseif get_propset()==3 then
  return require("gen/propset3")
elseif get_propset()==4 then
  return require("gen/propset4")
elseif get_propset()==5 then
  return require("gen/propset5")
elseif get_propset()==6 then
  return require("gen/propset6")
elseif get_propset()==7 then
  return require("gen/propset7")
elseif get_propset()==8 then
  return require("gen/propset8")
elseif get_propset()==9 then
  return require("gen/propset9")
elseif get_propset()==10 then
  return require("gen/propset10")
else
  error('Unsupported propset ' .. get_propset(), 1)
end
