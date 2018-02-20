using System;
using System.IO;
using System.IO.Ports;
using atpLib.Messages;
using pc_gui.Messages;

namespace atpLib.Devices
{
    class BinaryListenerSerialDevice : SerialDevice
    {
        public const int STATUS_DATA_LENTGH = 26;
        public const byte SYNC_BYTE_0 = 0xFB;
        public const byte SYNC_BYTE_1 = 0x60;

        public BinaryListenerSerialDevice(string portName) : base (portName) {}
        public BinaryListenerSerialDevice(string portName, int baudRate, Parity parity) : base(portName, baudRate, parity) { }

        public override IResponse receiveAnswer()
        {
            byte[] data = new byte[STATUS_DATA_LENTGH];
            log.Info("receiving status data...");

            int idx = 0;
            while(idx < STATUS_DATA_LENTGH)
            {
                data[idx] = (byte)port.ReadByte();
                if(idx == 0 && data[0] != SYNC_BYTE_0 ||
                    idx == 1 && data[1] != SYNC_BYTE_1)
                {
                    idx = 0;
                } else
                {
                    idx++;
                }
            }
                
            if (idx != STATUS_DATA_LENTGH)
            {
                // maybe wait for a while?
                log.Info("error reading data from device!");
                throw new InvalidDataException();
            }


            BinaryResponse answer = new GetStatusResponse();

            byte[] header = new byte[BinaryResponse.HEADER_LENTGH];
            header[4] = BinaryListenerSerialDevice.STATUS_DATA_LENTGH;

            answer.fromByteArray(header, data);
            
            return answer;
        }

        public override IResponse sendRecieve(Messages.IMessage message)
        {
            throw new NotImplementedException();
        }

        public override void sendMsg(IMessage message)
        {
            //if (port == null || !port.IsOpen)
            //{
            //    throw new DeviceNotConnectedException("tried to send data while the device is not connected!");
            //}

            //BinaryMessage m = message as BinaryMessage;

            //log.Info("sending " + m.opcode.ToString());
            //port.Write(m.asByteArray(), 0, m.asByteArray().Length); 
            
        }

        public override bool isAlive()
        {
            return isConnected();
        }

        
    }
}
