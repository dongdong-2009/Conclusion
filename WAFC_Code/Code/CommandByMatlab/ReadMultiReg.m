function [data, ErrorCode] = ReadMultiReg(session,reg_addr,reg_num)

global transId;
protocolId = uint16(0);
dataLeng = uint16(6);
uintId = uint8(1);
funcCode = uint8(3);

reg_addr_from1 =  reg_addr - 1;
reg_addr_hi = high_uint16(reg_addr_from1);
reg_addr_low = low_uint16(reg_addr_from1);

reg_num_hi = high_uint16(reg_num);
reg_num_low = low_uint16(reg_num);

if transId < 65535
    transId = uint16(transId + 1);
else
    transId = uint16(0);
end

MBAP_Header=[high_uint16(transId),low_uint16(transId),...
    high_uint16(protocolId),low_uint16(protocolId),...
    high_uint16(dataLeng),low_uint16(dataLeng),...
    uintId, funcCode];
Data_Body = [reg_addr_hi,reg_addr_low,reg_num_hi,reg_num_low];
PDU = [MBAP_Header,Data_Body];

if session.IsOpened
    fwrite(session.Socket,PDU);
    data = NaN;
    ErrorCode = 5;
    tic
    while(~(session.Socket.BytesAvailable > 0))
        if (toc > 40)
            break
        end
    end
    if(session.Socket.BytesAvailable > 0)
        bytes = fread(session.Socket,session.Socket.BytesAvailable,'uint8');
        bytes';
        %Check transId and funcCode is incorrect!
        if bytes(8) > 128
            ErrorCode = bytes(end);
%             disp('Device is Except!');
        else
            if transId ~= (bytes(1) * 256 + bytes(2))
%                 disp('TransactionId is Err!')
            elseif funcCode ~= bytes(8)
%                 disp('TransactionId is Err!');
            else
                data = zeros(reg_num,1,'uint16');
                for i = 1:1:length(data)
                    data(i) = bytes(2*i +8) * 256 + bytes(2*i +9);
                end
                ErrorCode = 0;
            end
        end
    else
%         disp('Reading is Err!');
    end
else
%     disp('Socket is Err or Except!');
end
% [reg_addr,reg_num]
% PDU
% bytes = bytes'
% ErrorCode
end

function hi = high_uint16(num)
hi = uint8(bitand(bitshift(num,-8),255));
end

function low = low_uint16(num)
low = uint8(bitand(num,255));
end
