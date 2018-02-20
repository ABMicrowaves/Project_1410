using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Configuration;

using atpLib.Scenarios;
using atpLib.Messages;
using atpLib.Devices;
using System.Threading;
using System.IO;
using pc_gui.Messages;
using pc_gui.Scenarios;

namespace pc_gui
{
    public partial class frmMain : Form
    {
        protected static readonly log4net.ILog log = log4net.LogManager.GetLogger
        (System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

        BinaryListenerSerialDevice device;

        Scenario statusScenario;

        public frmMain()
        {
            InitializeComponent();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new frmAbout().ShowDialog();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void btnClearLog_Click(object sender, EventArgs e)
        {
            lstLog.Items.Clear();
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            /* print the program and atplib versions */
            this.Text += " - " + typeof(frmMain).Assembly.GetName().Version;
            log.Info("Statring Program, Version - " + typeof(frmMain).Assembly.GetName().Version +
                ", AtpLib - " + typeof(atpLib.Devices.Device).Assembly.GetName().Version);


            /* load default comport */
            loadDefaultcomPort();

            // TOOD: load default configuration

        }

        private void loadDefaultcomPort()
        {
            Configuration config = ConfigurationManager.OpenExeConfiguration(Application.ExecutablePath);
            string comport;
            try
            {
                comport = config.AppSettings.Settings["DefaultComPort"].Value;
                if(comport == "")
                {
                    throw new NullReferenceException();
                }
            }
            catch(NullReferenceException)
            {
                log.Info("could not read defualt comport from configuration, using COM1 as defualt");
                comport = "1";
            }
            txtDefaultIComPort.Text = comport.ToString();
        }

        private string integerToBinaryString(int data, int numberOfBits, bitName_t[] bitNames)
        {
            StringBuilder sb = new StringBuilder();
            if(bitNames!= null && bitNames.Length != numberOfBits)
            {
                throw new Exception("Error in length of name string array!");
            }
            else
            {
                /* if name array exists */
                sb.AppendLine("0x" + data.ToString("X"));
            }

            for(int i = numberOfBits; i>0; i--)
            {
                int v = data & (1 << (i-1));
                if (bitNames != null)
                {
                    if(bitNames[i - 1].bitName == "")
                    {
                        continue;
                    }
                    sb.Append("--->");
                    sb.Append(bitNames[i-1].bitName);
                    sb.Append(" - ");
                    sb.AppendLine(v > 0 ? bitNames[i-1].high : bitNames[i-1].low);
                }
                else
                {
                    sb.Append(v > 0 ? "1" : "0");
                    sb.Append(" ");
                } 
                    
            }
            return sb.ToString().TrimEnd();
        }


        struct bitName_t
        {
            public string bitName, low, high;
            public bitName_t(string name, string low, string high)
            {
                this.bitName = name;
                this.low = low;
                this.high = high;
            }
        };

        void updateStatus(GetStatusResponse status)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new StatusScenario.updateStatusDelegate(updateStatusThreadSafe), new object[] { status });
            }
            else
            {
                updateStatusThreadSafe(status);
            }
        }

        void updateStatusThreadSafe(GetStatusResponse status)
        {
            bitName_t[] bitStatus1Names = new bitName_t[8] { new bitName_t("Data Source","External", "Internal"),
                                                        new bitName_t("Data Inverted","Normal", "Inverted"),
                                                        new bitName_t("Data Random","Off", "On"),
                                                        new bitName_t("Clock Source","External", "Internal"),
                                                        new bitName_t("Clock Inverted","Normal", "Inverted"),
                                                        new bitName_t("Differential Encoding", "Off", "On"),
                                                        new bitName_t("","", "" ),
                                                        new bitName_t("", "", "" )
            };

            bitName_t[] bitStatus2Names = new bitName_t[8] { new bitName_t("Polarity","Off", "On"),
                                                        new bitName_t("Polarity","Low", "High"),
                                                        new bitName_t("Power","Off", "On"),
                                                        new bitName_t("Power","Low", "High"),
                                                        new bitName_t("Uart Status","Off", "On"),
                                                        new bitName_t("Reverse Power", "Good", "Bad"),
                                                        new bitName_t("","", "" ),
                                                        new bitName_t("", "", "" )
            };

            StringBuilder sb = new StringBuilder();
            sb.AppendLine("TX Counter: " + status.tx_counter);
            sb.AppendLine("Frequency: " + status.frequency.ToString());
            sb.AppendLine("Mode: " + status.mode.ToString());
            sb.AppendLine("Bit Status 1: " + integerToBinaryString(status.bits_status1, 8, bitStatus1Names));
            sb.AppendLine("Current Temperature: " + status.current_temperaure.ToString());
            sb.AppendLine("Bitrate: " + status.bit_rate.ToString());
            sb.AppendLine("Current Power: " + status.current_power.ToString());
            sb.AppendLine("Internal Pattern: " + status.internal_pattern.ToString());
            sb.AppendLine("Bit Status 2: " + integerToBinaryString(status.bits_status2, 8, bitStatus2Names));
            sb.AppendLine("Bitlow Power Level: " + status.bitlow_power_level.ToString());
            sb.AppendLine("Bit Power Level: " + status.bit_power_level.ToString());
            sb.AppendLine("Reverse Power: " + status.reverse_power.ToString());
            sb.AppendLine("Version: " + status.version.ToString());
            sb.AppendLine("Unit Id: " + status.unit_id.ToString());
            sb.AppendLine("Checksum OK: " + status.checksum_ok.ToString());

            txtStatus.Text = sb.ToString();
            
            if(!status.checksum_ok)
            {
                /* in case the CS is incorrect, stop the thread */
                statusScenario?.backgroundFinish();
                log.Info("Checksum Failed!!!");
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
        }

        private string getComPort()
        {
            string comport = txtDefaultIComPort.Text;
            comport = comport.ToUpper();
            if (!comport.StartsWith("COM"))
            {
                comport = "COM" + comport;
            }
            return comport;
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            Button b = (Button)sender;
            try
            {
                if (device == null || !device.isConnected())
                {
                    string comport = getComPort();


                    /* currently not connected */
                    // device = new BinaryTCPDevice(txtDefaultIComPort.Text);
                    device = new BinaryListenerSerialDevice(getComPort(), 38400, System.IO.Ports.Parity.None);
                    if (device.connect())
                    {
                        log.Info("Connected to " + comport);
                        b.Text = "Disconnect";
                        b.BackColor = Color.LightGreen;
                    }
                }
                else
                {
                    device.disconnect();
                    device = null;
                    b.Text = "Connect";
                    b.BackColor = Color.Red;
                }
            }
            catch(Exception ex)
            {
                log.Error("error in entered COMPORT: " + txtDefaultIComPort.Text, ex);
            }            
        }

        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            statusScenario?.backgroundFinish();
            if (device != null && device.isConnected())
            {
                device.disconnect();
            }
        }

        private void btnSaveComPort_Click(object sender, EventArgs e)
        {
            Configuration config = ConfigurationManager.OpenExeConfiguration(Application.ExecutablePath);

            string comport = getComPort();
            config.AppSettings.Settings.Remove("DefaultComPort");
            config.AppSettings.Settings.Add("DefaultComPort", comport);
            config.Save(ConfigurationSaveMode.Modified);

            if(comport != txtDefaultIComPort.Text)
            {
                txtDefaultIComPort.Text = comport;
            }
        }


        private void btnGetStatus(object sender, EventArgs e)
        {
            if (device.isConnected())
            {
                device.flushRx();
            }
            Scenario.ScenarioResult r = new SingleMessageSingleDeviceScenario("Get Status", new GetStatusMessage(), true, false, device).run(10000);
            if (r != null && r.result == Scenario.ScenarioResult.RunResult.Pass)
            {
                GetStatusResponse resp = (GetStatusResponse)r.resultObj;
                updateStatus(resp);
            }
        }

        private void btnStartStatusThread(object sender, EventArgs e)
        {
            statusScenario?.backgroundFinish();
            statusScenario = new StatusScenario("Status Scenario", device, updateStatus);
            statusScenario.backgroundStart();
        }

        private void btnStopStatusThread(object sender, EventArgs e)
        {
            statusScenario?.backgroundFinish();
        }
    }
}
