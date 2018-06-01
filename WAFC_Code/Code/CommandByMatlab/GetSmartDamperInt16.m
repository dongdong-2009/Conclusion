function [ val ] = GetSmartDamperInt16( IP, Addr )
%GETSMARTDAMPERINT16 Summary of this function goes here
%   Detailed explanation goes here
data = GetSmartDamperReg(IP, Addr, 1);
if ~any(isnan(data))
    val = double(data);
else
    val = NaN;
end
end

