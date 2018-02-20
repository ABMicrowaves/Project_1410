using atpLib.Messages;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace pc_gui.Messages
{
    public class GetStatusMessage : BinaryMessage
    {
        public GetStatusMessage() : base(OP.GET_STATUS)
        {

        }

        public override byte[] parametersToByteArr()
        {
            return new byte[] { };
        }
    }
}
