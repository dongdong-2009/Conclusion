function [status, message] = SetSmartDamperReg( IP, Addr, data)
% status: 1: sucess
%        -1: fail
port = 2000;
status = -1;
message = '';

Session = OpenSocket(IP,port);
ii = 5;
while ~Session.IsOpened
    CloseSocket(Session);
    clear Session
    warning('no TCP/IP connection to %s:%d, retry in %d times after 30s',IP,port,ii);
    if ii>0
        ii = ii-1;
    else
        status = -1;
        message = sprintf('no TCP/IP connection to %s:%d',IP,port);
        return;
    end
    pause(30);
    Session = OpenSocket(IP,port);
end

errorcode=WriteMultiReg(Session,Addr,data);
ii = 5;
while errorcode>0
    warning('Write Registers Fails with error code %g, retry in %d times after 30s',errorcode,ii);
    if ii>0
        ii = ii-1;
    else
        status = -1;
        warning('Write Registers Fails with error code %g',errorcode);
        return;
    end
    pause(30);
    errorcode=WriteMultiReg(Session,Addr,data);
end
CloseSocket(Session);
clear Session
status = 1;
message = '';
end
