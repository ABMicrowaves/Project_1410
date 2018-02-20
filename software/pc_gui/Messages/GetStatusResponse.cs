using atpLib.Devices;
using atpLib.Messages;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace pc_gui.Messages
{
    public class GetStatusResponse : BinaryResponse
    {
        public int tx_counter { get; set; }
        public int frequency { get; set; }
        public int mode { get; set; }
        public int bits_status1 { get; set; }
        public int current_temperaure { get; set; }
        public int bit_rate { get; set; }
        public int current_power { get; set; }
        public int internal_pattern { get; set; }
        public int bits_status2 { get; set; }
        public int bitlow_power_level { get; set; }
        public int bit_power_level { get; set; }
        public int reverse_power { get; set; }
        public int version { get; set; }
        public int unit_id { get; set; }

        public bool checksum_ok { get; set; }
        public bool sync_ok { get; set; }

        public GetStatusResponse() : base()
        {
            
        }

        public override object getUniqueIdentifier()
        {
            return null;
        }

        public override void parametesFromData()
        {
            sync_ok = false;
            if(rawData[0] == BinaryListenerSerialDevice.SYNC_BYTE_0 &&
                rawData[1] == BinaryListenerSerialDevice.SYNC_BYTE_1)
            {
                sync_ok = true;
            }

            tx_counter = (int)(rawData[2]);
            frequency = (int)((((UInt16)rawData[3]) << 8) + (((UInt16)rawData[4]) << 0));
            mode = (int)(rawData[5]);
            bits_status1 = (int)(rawData[6]);
            current_temperaure = (int)((((UInt16)rawData[7]) << 8) + (((UInt16)rawData[8]) << 0));
            bit_rate = (int)((((UInt16)rawData[9]) << 8) + (((UInt16)rawData[10]) << 0));
            current_power = (int)(rawData[11]);
            internal_pattern = (int)(rawData[12]);
            bits_status2 = (int)(rawData[13]);
            bitlow_power_level = (int)(rawData[14]);
            bit_power_level = (int)(rawData[15]);
            reverse_power = (int)(rawData[16]);
            version = (int)(rawData[17]);
            unit_id = (int)((((UInt16)rawData[18]) << 8) + (((UInt16)rawData[19]) << 0)) ;

            /* 
             * the CS is sent LSB first and the calculated CS is MSB first
             *  so read the cs from the message swapped so that they both will be MSB first 
             */
            UInt16 cs = (UInt16)((((UInt16)rawData[25]) << 8) + (((UInt16)rawData[24]) << 0));

            UInt16 calculated_cs = 0;
            for(int i = 0; i<BinaryListenerSerialDevice.STATUS_DATA_LENTGH-2; i++)
            {
                calculated_cs += rawData[i];
            }
            if(calculated_cs == cs)
            {
                checksum_ok = true;
            } else
            {
                checksum_ok = false;
            }
        }

    }
}
