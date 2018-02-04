using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SerialPortListener.Serial;
using System.IO;
using System.IO.Ports;

namespace SerialPortListener
{
    public partial class MainForm : Form
    {
        //double xAnalogV = 0, yAnalogV = 0, zAnalogV = 0, vs = 0;
        //int jx = 0, jy = 0, jz = 0, jv = 0;
        SerialPortManager _spManager;
        double[] data = new double[100];
        double[] xAnalogVArray = new double[100];
        double[] yAnalogVArray = new double[100];
        double[] zAnalogVArray = new double[100];
        double[] vsAnalogVArray = new double[100];
        string path = @"c:\temp\MyTest.txt";
        //string RSSIBARrawdata;
        public MainForm()
        {
            InitializeComponent();
            UserInitialization();
        }
    
        private void UserInitialization()
        {
            _spManager = new SerialPortManager();
            SerialSettings mySerialSettings = _spManager.CurrentSerialSettings;
            serialSettingsBindingSource.DataSource = mySerialSettings;
            portNameComboBox.DataSource = mySerialSettings.PortNameCollection;
            baudRateComboBox.DataSource = mySerialSettings.BaudRateCollection;
            dataBitsComboBox.DataSource = mySerialSettings.DataBitsCollection;
            parityComboBox.DataSource = Enum.GetValues(typeof(System.IO.Ports.Parity));
            stopBitsComboBox.DataSource = Enum.GetValues(typeof(System.IO.Ports.StopBits));
            _spManager.NewSerialDataRecieved += new EventHandler<SerialDataEventArgs>(_spManager_NewSerialDataRecieved);
            this.FormClosing += new FormClosingEventHandler(MainForm_FormClosing);
        }

        
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            _spManager.Dispose();  
        }

        void _spManager_NewSerialDataRecieved(object sender, SerialDataEventArgs e)
        {
            if (this.InvokeRequired)
            {
                // Using this.Invoke causes deadlock when closing serial port, and BeginInvoke is good practice anyway.
                this.BeginInvoke(new EventHandler<SerialDataEventArgs>(_spManager_NewSerialDataRecieved), new object[] { sender, e });
                return;
            }

            int maxTextLength = 204; // maximum text length in text box nissim? 220
            if (tbData.TextLength > maxTextLength)
                tbData.Text = tbData.Text.Remove(0, tbData.TextLength - maxTextLength);

            // This application is connected to a GPS sending ASCCI characters, so data is converted to text
            string str = Encoding.ASCII.GetString(e.Data);
            tbData.AppendText(str); // here to split data!!1234
            //dataSplitter(str);
            dataParser(str);
            //RSSIBAR(RSSIBARrawdata);
            tbData.ScrollToCaret();

        }

        // split the data to 3 labels
        //private void dataSplitter(string tempstr)
        //{        
        //    for (int i = 0; i < tempstr.Length; i++)
        //    {
        //        if (tempstr[i].ToString() == "X")
        //        {
        //            if ((i + 1) < tempstr.Length) if (tempstr[i + 1].ToString() != "Y")
        //                {
        //                    if ((i + 2) < tempstr.Length) if (tempstr[i + 2].ToString() != "Y")
        //                        {
        //                            if ((i + 3) < tempstr.Length) if (tempstr[i + 3].ToString() != "Y")
        //                                {
        //                                    if ((i + 4) < tempstr.Length) if (tempstr[i + 4].ToString() != "Y")
        //                                        {
        //                                            if ((i + 5) < tempstr.Length) if (tempstr[i + 5].ToString() != "Y")
        //                                                {
        //                                                    xAnalogV = Convert.ToDouble(tempstr[i + 1].ToString() + tempstr[i + 2].ToString() + tempstr[i + 3].ToString() + tempstr[i + 4].ToString() + tempstr[i + 5].ToString());
        //                                                    xAnalogVArray[jx] = xAnalogV;
        //                                                    jx++;
        //                                                    if (jx == 99) jx = 0;
        //                                                }
        //                                        }
        //                                }
        //                        }
        //                }
        //        }
        //        if (tempstr[i].ToString() == "Y")
        //        {
        //            if ((i + 1) < tempstr.Length) if (tempstr[i + 1].ToString() != "Z")
        //                {
        //                    if ((i + 2) < tempstr.Length) if (tempstr[i + 2].ToString() != "Z")
        //                        {
        //                            if ((i + 3) < tempstr.Length) if (tempstr[i + 3].ToString() != "Z")
        //                                {
        //                                    if ((i + 4) < tempstr.Length) if (tempstr[i + 4].ToString() != "Z")
        //                                        {
        //                                            if ((i + 5) < tempstr.Length) if (tempstr[i + 5].ToString() != "Z")
        //                                                {
        //                                                    yAnalogV = Convert.ToDouble(tempstr[i + 1].ToString() + tempstr[i + 2].ToString() + tempstr[i + 3].ToString() + tempstr[i + 4].ToString() + tempstr[i + 5].ToString());
        //                                                    yAnalogVArray[jy] = yAnalogV;
        //                                                    jy++;
        //                                                    if (jy == 99) jy = 0;
        //                                                }
        //                                        }
        //                                }
        //                        }
        //                }
        //        }
        //        if (tempstr[i].ToString() == "Z")
        //        {
        //            if ((i + 1) < tempstr.Length) if (tempstr[i + 1].ToString() != "V")
        //            {
        //                if ((i + 2) < tempstr.Length) if (tempstr[i + 2].ToString() != "V")
        //                {
        //                    if ((i + 3) < tempstr.Length) if (tempstr[i + 3].ToString() != "V")
        //                    {
        //                        if ((i + 4) < tempstr.Length) if (tempstr[i + 4].ToString() != "V")
        //                        {
        //                            if ((i + 5) < tempstr.Length) if (tempstr[i + 5].ToString() != "V")
        //                            {
        //                                zAnalogV = Convert.ToDouble(tempstr[i + 1].ToString() + tempstr[i + 2].ToString() + tempstr[i + 3].ToString() + tempstr[i + 4].ToString() + tempstr[i + 5].ToString());
        //                                zAnalogVArray[jz] = zAnalogV;
        //                                jz++;
        //                                if (jz == 99) jz = 0;
        //                                //dataGridViewStatusDisplay.Rows[rowIndex].Cells[columnIndex].Value = value;
        //                                //dataGridViewDevice.Rows[0].Cells[1].Value = zAnalogV;
        //                                ///////////////////                           
        //                                //text = text + temp + "\n";
        //                                //System.IO.File.WriteAllText(@"C:\d12\WriteTextZ.txt", text);                               
        //                                ///////////////////     
        //                            }
        //                        }
        //                    }
        //                }
        //            }
        //        }
        //        if (tempstr[i].ToString() == "V")
        //        {
        //            if ((i + 1) < tempstr.Length) 
        //            {
        //                if ((i + 2) < tempstr.Length) 
        //                {
        //                    if ((i + 3) < tempstr.Length) 
        //                    {
        //                        if ((i + 4) < tempstr.Length) 
        //                        {
        //                            if ((i + 5) < tempstr.Length) 
        //                            {
        //                                vs = Convert.ToDouble(tempstr[i + 1].ToString() + tempstr[i + 2].ToString() + tempstr[i + 3].ToString() + tempstr[i + 4].ToString() + tempstr[i + 5].ToString());
        //                                vsAnalogVArray[jv] = vs;
        //                                jv++;
        //                                if (jv == 99) jv = 0;
        //                            }
        //                        }
        //                    }
        //                }
        //            }
        //        }
        //    }
            
        //}

        // Handles the "Start Listening"-buttom click event
        private void btnStart_Click(object sender, EventArgs e)
        {
            _spManager.StartListening();
        }

        // Handles the "Stop Listening"-buttom click event
        private void btnStop_Click(object sender, EventArgs e)
        {
            _spManager.StopListening();
        }

        public static string GetTimestamp(DateTime value)
        {
            return value.ToString("yyyyMMddHHmmssffff");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            _spManager.SendData("li17592\r");
            System.Threading.Thread.Sleep(200);
            _spManager.SendData("Q\r");
        }

         private void dataParser(string tempstr)
        {
            //string[] stringSeparators = new string[] { "," };
            for (int i = 0; i < tempstr.Length-4; i++)
            {

                if (tempstr.Substring(i, 4) == "FREQ") FrequencylabelValue.Text = tempstr.Substring(i + 5, 4);
                if (tempstr.Substring(i,2) == "MO") MOlabelValue.Text = tempstr.Substring(i + 3, 1);
                if (MOlabelValue.Text == "0") MOlabelValue.Text = "PCM-FM";
                if (MOlabelValue.Text == "1") MOlabelValue.Text = "SOQPSK";
                if (MOlabelValue.Text == "2") MOlabelValue.Text = "Carrier only";
                if (MOlabelValue.Text == "3") MOlabelValue.Text = " IQ imbalance";
                if (tempstr.Substring(i, 2) == "IC") BRlabelValue.Text = tempstr.Substring(i + 3, 5);

                if (tempstr.Substring(i, 2) == "DE") DElabelValue.Text = tempstr.Substring(i + 3, 1);
                if (DElabelValue.Text == "0") DElabelValue.Text = "OFF";// else DElabelValue.Text = tempstr.Substring(i + 3, 1); //else DElabelValue.Text = "ON";
                if (DElabelValue.Text == "1") DElabelValue.Text = "ON";
                if (tempstr.Substring(i, 2) == "DS") labelDSValue.Text = tempstr.Substring(i + 3, 1);
                if (labelDSValue.Text == "0") labelDSValue.Text = "External"; //else labelDSValue.Text = "Internal";
                if (labelDSValue.Text == "1") labelDSValue.Text = "Internal";
                if (tempstr.Substring(i, 2) == "RA") RAlabelValue.Text = tempstr.Substring(i + 3, 1);
                if (RAlabelValue.Text == "0") RAlabelValue.Text = "OFF"; //else RAlabelValue.Text = "ON";
                if (RAlabelValue.Text == "1") RAlabelValue.Text = "ON"; 
                if (tempstr.Substring(i, 2) == "DP") DPlabelValue.Text = tempstr.Substring(i + 3, 1);
                if (DPlabelValue.Text == "0") DPlabelValue.Text = "Normal"; //else DPlabelValue.Text = "Invert";
                if (DPlabelValue.Text == "1") DPlabelValue.Text = "Invert";

              //  if (tempstr.Substring(i, 2) == "CP") CPlabelValue.Text = tempstr.Substring(i + 4, 1);
                //if (CPlabelValue.Text == "0") CPlabelValue.Text = "Normal"; //else CPlabelValue.Text = "Invert";
               // if (CPlabelValue.Text == "1") CPlabelValue.Text = "Invert";

                if (tempstr.Substring(i, 4) == "CP=0") CPlabelValue.Text = "Normal";
                if (tempstr.Substring(i, 4) == "CP=1") CPlabelValue.Text = "Inverted";
                if (tempstr.Substring(i, 2) == "CS") CSlabelValue.Text = tempstr.Substring(i + 3, 1);
                if (CSlabelValue.Text == "0") CSlabelValue.Text = "External"; //else CSlabelValue.Text = "Internal";
                if (CSlabelValue.Text == "1") CSlabelValue.Text = "Internal";
                if (tempstr.Substring(i, 2) == "ID") labelIDvalue.Text = tempstr.Substring(i + 3, 1);
                if (labelIDvalue.Text == "0") labelIDvalue.Text = "Const0";
                if (labelIDvalue.Text == "1") labelIDvalue.Text = "Const1";
                if (labelIDvalue.Text == "2") labelIDvalue.Text = "PRBS15";
                if (labelIDvalue.Text == "3") labelIDvalue.Text = "PRBS17";

                if (tempstr.Substring(i, 2) == "RF") TXlabelValue.Text = tempstr.Substring(i + 3, 1);
                if (TXlabelValue.Text == "O") TXlabelValue.Text = "OFF"; //else TXlabelValue.Text = "ON";
                if (TXlabelValue.Text == "1") TXlabelValue.Text = "ON";
                if (tempstr.Substring(i, 2) == "RP") labelRPValue.Text = tempstr.Substring(i + 3, 1);
                if (labelRPValue.Text == "0") labelRPValue.Text = "Low"; //else labelRPValue.Text = "High";
                if (labelRPValue.Text == "1") labelRPValue.Text = "High";
                if (tempstr.Substring(i, 4) == "FFWR") labelVPValue.Text = tempstr.Substring(i + 5, 2);
                if (tempstr.Substring(i, 2) == "VL") labelVLValue.Text = tempstr.Substring(i + 3, 2);
                if (tempstr.Substring(i, 3) == "REV") REVlabelValue.Text = tempstr.Substring(i + 4, 4);
                if (tempstr.Substring(i, 4) == "TEMP") TEMPlabelValue.Text = tempstr.Substring(i + 5, 6);

                if (tempstr.Substring(i, 4) == "RB=0") labelRBValue.Text = "Open = RF ON, GND = RF OFF";
                if (tempstr.Substring(i, 4) == "RB=1") labelRBValue.Text = "Open = RF OFF, GND = RF ON";

                if (tempstr.Substring(i, 4) == "RC=0") labelRCValue.Text = "Open = SV, +3V = VL";
                if (tempstr.Substring(i, 4) == "RC=1") labelRCValue.Text = "Open = VL, +3V = SV";

                //if (tempstr.Substring(i, 2) == "RB") labelRBValue.Text = tempstr.Substring(i + 3, 1);
                //if (labelRBValue.Text == "0") labelRBValue.Text = "Open = RF ON, GND = RF OFF"; //else labelRBValue.Text = "Open = RF ON, GND = RF OFF";
                //if (labelRBValue.Text == "1") labelRBValue.Text = "Open = RF ON, GND = RF OFF";
                //if (tempstr.Substring(i, 2) == "RC") labelRBValue.Text = tempstr.Substring(i + 3, 1);
                //if (labelRCValue.Text == "0") labelRCValue.Text = "Open = SV, +3V = VL";// else labelRCValue.Text = "Open = VL, +3V = SV";
                //if (labelRCValue.Text == "1") labelRCValue.Text = "Open = VL, +3V = SV";
             
            }

        }

         private void checkBoxOriginalData_CheckedChanged(object sender, EventArgs e)
         {
             if (checkBoxOriginalData.Checked == true)
             {
                 tbData.Visible = true;
                 groupBox1.Visible = true;
                 this.Height = 800;
             }
             else
             {
                 tbData.Visible = false;
                 groupBox1.Visible = false;
                 this.Height = 467;
             }
         }

        

         private void button2_Click(object sender, EventArgs e)
         {
             _spManager.SendData("$S1\r");
             System.Threading.Thread.Sleep(200);
             _spManager.SendData("$Q\r");   
         }

         private void button3_Click(object sender, EventArgs e)
         {
             _spManager.SendData("$S2\r");
             System.Threading.Thread.Sleep(200);
             _spManager.SendData("$Q\r");   
         }

         private void button4_Click(object sender, EventArgs e)
         {
             _spManager.SendData("$S3\r");
             System.Threading.Thread.Sleep(200);
             _spManager.SendData("$Q\r");   
         }

         private void button5_Click(object sender, EventArgs e)
         {
             _spManager.SendData("$S4\r");
             System.Threading.Thread.Sleep(200);
             _spManager.SendData("$Q\r");   
         }

         //private void button8_Click(object sender, EventArgs e)
         //{
         //    _spManager.SendData("$br" + maskedTextBox1.Text + "\r");
         //    System.Threading.Thread.Sleep(100);
         //    _spManager.SendData("$Q\r"); 
         //}

         //private void button14_Click(object sender, EventArgs e)
         //{
         //    if (comboBox7.Text == "0") _spManager.SendData("$cp0" + "\r");
         //    if (comboBox7.Text == "90") _spManager.SendData("$cp90" + "\r");
         //    if (comboBox7.Text == "180") _spManager.SendData("$cp180" + "\r");
         //    if (comboBox7.Text == "270") _spManager.SendData("$cp270" + "\r");
         //    System.Threading.Thread.Sleep(100);
         //    _spManager.SendData("$Q\r"); 
         //}

         //private void button6_Click(object sender, EventArgs e)
         //{
         //    _spManager.SendData("$f" + numericUpDown1.Value.ToString() + "0" + "\r");
         //    System.Threading.Thread.Sleep(100);
         //    _spManager.SendData("$Q\r"); 
         //}

         //private void button7_Click(object sender, EventArgs e)
         //{
         //    if (comboBox1.Text == "Narrow") _spManager.SendData("$BWN" + "\r");
         //    if (comboBox1.Text == "Wide") _spManager.SendData("$BWW" + "\r");
         //    System.Threading.Thread.Sleep(100);
         //    _spManager.SendData("$Q\r"); 
         //}

         //private void button9_Click(object sender, EventArgs e)
         //{
         //    if (comboBox2.Text == "Low") _spManager.SendData("$IML" + "\r");
         //    if (comboBox2.Text == "High") _spManager.SendData("$IMH" + "\r");
         //    System.Threading.Thread.Sleep(100);
         //    _spManager.SendData("$Q\r"); 
         //}

         //private void button13_Click(object sender, EventArgs e)
         //{
         //    try
         //    {

         //        if (Convert.ToDouble(comboBox3.Text) > 2.0) comboBox3.Text = "2.0";
         //    }
         //    catch
         //    {

         //    };

         //    _spManager.SendData("$l" + comboBox3.Text + "\r");
         //    System.Threading.Thread.Sleep(100);
         //    _spManager.SendData("$Q\r"); 
         //}

         //private void button12_Click(object sender, EventArgs e)
         //{
         //    if (comboBox4.Text == "On") _spManager.SendData("$DF1" + "\r");
         //    if (comboBox4.Text == "Off") _spManager.SendData("$DF0" + "\r");
         //    System.Threading.Thread.Sleep(100);
         //    _spManager.SendData("$Q\r"); 
         //}

         //private void button11_Click(object sender, EventArgs e)
         //{
         //    if (comboBox5.Text == "0") _spManager.SendData("$R0" + "\r");
         //    if (comboBox5.Text == "9") _spManager.SendData("$R9" + "\r");
         //    if (comboBox5.Text == "11") _spManager.SendData("$R11" + "\r");
         //    if (comboBox5.Text == "15") _spManager.SendData("$R15" + "\r");
         //    System.Threading.Thread.Sleep(100);
         //    _spManager.SendData("$Q\r"); 
         //}

         //private void button10_Click(object sender, EventArgs e)
         //{
         //    if (comboBox6.Text == "NRZL") _spManager.SendData("$de0" + "\r");
         //    if (comboBox6.Text == "NRZM") _spManager.SendData("$de1" + "\r");
         //    if (comboBox6.Text == "NRZS") _spManager.SendData("$de2" + "\r");
         //    if (comboBox6.Text == "BI-PHASE L") _spManager.SendData("$de3" + "\r");
         //    if (comboBox6.Text == "BI-PHASE M") _spManager.SendData("$de4" + "\r");
         //    System.Threading.Thread.Sleep(100);
         //    _spManager.SendData("$Q\r"); 
         //}

         private void button1_Click_1(object sender, EventArgs e)
         {
             //MessageBox.Show("You Must Select State S1/S2/S3/S4 Before Burn Setup ! ");
             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);//44
                 _spManager.SendData("sv\r");
                 //System.Threading.Thread.Sleep(100);
                 //_spManager.SendData("Q\r");
             }
             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void button2_Click_1(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("re\r");
                 //System.Threading.Thread.Sleep(200);
                 //_spManager.SendData("Q\r");
             }
             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonSetMO_Click(object sender, EventArgs e)
         {   
             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
                 System.Threading.Thread.Sleep(200);
                 if (comboBoxMO.Text == "PCM-FM")
                     _spManager.SendData("MO0\r");
                 if (comboBoxMO.Text == "SOQPSK")
                     _spManager.SendData("MO1\r");
                 if (comboBoxMO.Text == "Carrier only")
                     _spManager.SendData("MO2\r");
                 if (comboBoxMO.Text == "IQ imbalance")
                     _spManager.SendData("MO3\r");
                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonSetFR_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);
               
                 _spManager.SendData("FR" + numericUpDownFR.Value.ToString() + "\r");
                 System.Threading.Thread.Sleep(100);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonSetBR_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);
                // _spManager.SendData("Q\r");
                 _spManager.SendData("ic" + maskedTextBoxBR.Text + "\r");
                 System.Threading.Thread.Sleep(100);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonSetDE_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                // System.Threading.Thread.Sleep(200);
               
                 System.Threading.Thread.Sleep(200);
                 if (comboBoxDE.Text == "OFF")
                     _spManager.SendData("DE0\r");
                 if (comboBoxDE.Text == "ON")
                     _spManager.SendData("DE1\r");
               
                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonDS_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxDS.Text == "External")
                     _spManager.SendData("DS0\r");
                 if (comboBoxDS.Text == "Internal")
                     _spManager.SendData("DS1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonSetRA_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxRA.Text == "OFF")
                     _spManager.SendData("RA0\r");
                 if (comboBoxRA.Text == "ON")
                     _spManager.SendData("RA1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonSetDP_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxDP.Text == "Normal")
                     _spManager.SendData("DP0\r");
                 if (comboBoxDP.Text == "Invert")
                     _spManager.SendData("DP1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonSetCP_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxCP.Text == "Normal")
                     _spManager.SendData("CP0\r");
                 if (comboBoxCP.Text == "Invert")
                     _spManager.SendData("CP1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonSetCS_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxCS.Text == "External")
                     _spManager.SendData("CS0\r");
                 if (comboBoxCS.Text == "Internal")
                     _spManager.SendData("CS1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonID_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
                 System.Threading.Thread.Sleep(200);
                 if (comboBoxID.Text == "Const 0")
                     _spManager.SendData("ID0\r");
                 if (comboBoxID.Text == "Const 1")
                     _spManager.SendData("ID1\r");
                 if (comboBoxID.Text == "PRBS15")
                     _spManager.SendData("ID2\r");
                 if (comboBoxID.Text == "PRBS17")
                     _spManager.SendData("ID3\r");
                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonSetTX_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxTX.Text == "OFF")
                     _spManager.SendData("RF0\r");
                 if (comboBoxTX.Text == "ON")
                     _spManager.SendData("RF1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonRP_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxRP.Text == "Low")
                     _spManager.SendData("RP0\r");
                 if (comboBoxRP.Text == "High")
                     _spManager.SendData("RP1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonVL_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);

                 _spManager.SendData("VL" + numericUpDownVL.Value.ToString() + "\r");
                 System.Threading.Thread.Sleep(100);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonVP_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);

                 _spManager.SendData("VP" + numericUpDownVP.Value.ToString() + "\r");
                 System.Threading.Thread.Sleep(100);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonRB_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxRB.Text == "Open = RF ON   |  GND = RF OFF")
                     _spManager.SendData("RB0\r");
                 if (comboBoxRB.Text == "Open = RF OFF  |  GND = RF ON")
                     _spManager.SendData("RB1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void buttonRC_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxRC.Text == "Open = SV  |  +3V = VL")
                     _spManager.SendData("RC0\r");
                 if (comboBoxRC.Text == "Open = VL  |  +3V = SV")
                     _spManager.SendData("RC1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }
         }

         private void btnSetAll_Click(object sender, EventArgs e)
         {
             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
                 System.Threading.Thread.Sleep(200);
                 if (comboBoxMO.Text == "PCM-FM")
                     _spManager.SendData("MO0\r");
                 if (comboBoxMO.Text == "SOQPSK")
                     _spManager.SendData("MO1\r");
                 if (comboBoxMO.Text == "Carrier only")
                     _spManager.SendData("MO2\r");
                 if (comboBoxMO.Text == "IQ imbalance")
                     _spManager.SendData("MO3\r");
                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }

             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);

                 _spManager.SendData("FR" + numericUpDownFR.Value.ToString() + "\r");
                 System.Threading.Thread.Sleep(100);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }

             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);
                 // _spManager.SendData("Q\r");
                 _spManager.SendData("ic" + maskedTextBoxBR.Text + "\r");
                 System.Threading.Thread.Sleep(100);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }

             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxDE.Text == "OFF")
                     _spManager.SendData("DE0\r");
                 if (comboBoxDE.Text == "ON")
                     _spManager.SendData("DE1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }


             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxDS.Text == "External")
                     _spManager.SendData("DS0\r");
                 if (comboBoxDS.Text == "Internal")
                     _spManager.SendData("DS1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }

             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxRA.Text == "OFF")
                     _spManager.SendData("RA0\r");
                 if (comboBoxRA.Text == "ON")
                     _spManager.SendData("RA1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }

             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxDP.Text == "Normal")
                     _spManager.SendData("DP0\r");
                 if (comboBoxDP.Text == "Invert")
                     _spManager.SendData("DP1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }

             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxCP.Text == "Normal")
                     _spManager.SendData("CP0\r");
                 if (comboBoxCP.Text == "Invert")
                     _spManager.SendData("CP1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }

             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxCS.Text == "External")
                     _spManager.SendData("CS0\r");
                 if (comboBoxCS.Text == "Internal")
                     _spManager.SendData("CS1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }


             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
                 System.Threading.Thread.Sleep(200);
                 if (comboBoxID.Text == "Const 0")
                     _spManager.SendData("ID0\r");
                 if (comboBoxID.Text == "Const 1")
                     _spManager.SendData("ID1\r");
                 if (comboBoxID.Text == "PRBS15")
                     _spManager.SendData("ID2\r");
                 if (comboBoxID.Text == "PRBS17")
                     _spManager.SendData("ID3\r");
                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }


             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxTX.Text == "OFF")
                     _spManager.SendData("RF0\r");
                 if (comboBoxTX.Text == "ON")
                     _spManager.SendData("RF1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }

             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxRP.Text == "Low")
                     _spManager.SendData("RP0\r");
                 if (comboBoxRP.Text == "High")
                     _spManager.SendData("RP1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }

             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);

                 _spManager.SendData("VL" + numericUpDownVL.Value.ToString() + "\r");
                 System.Threading.Thread.Sleep(100);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }

             try
             {
                 _spManager.SendData("li17592\r");
                 System.Threading.Thread.Sleep(200);

                 _spManager.SendData("VP" + numericUpDownVP.Value.ToString() + "\r");
                 System.Threading.Thread.Sleep(100);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }

             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxRB.Text == "Open = RF ON   |  GND = RF OFF")
                     _spManager.SendData("RB0\r");
                 if (comboBoxRB.Text == "Open = RF OFF  |  GND = RF ON")
                     _spManager.SendData("RB1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }

             try
             {
                 _spManager.SendData("li17592\r");
                 // System.Threading.Thread.Sleep(200);

                 System.Threading.Thread.Sleep(200);
                 if (comboBoxRC.Text == "Open = SV  |  +3V = VL")
                     _spManager.SendData("RC0\r");
                 if (comboBoxRC.Text == "Open = VL  |  +3V = SV")
                     _spManager.SendData("RC1\r");

                 System.Threading.Thread.Sleep(200);
                 _spManager.SendData("Q\r");
             }

             catch
             {
                 MessageBox.Show("can't write to selected COM");
             }

         }

         private void saveToFile()
         {
             
             if (!File.Exists(path))
             {
                 // Create a file to write to.
                 using (StreamWriter sw = File.CreateText(path))
                 {
                     if (comboBoxMO.Text == "PCM-FM")
                         sw.WriteLine("PCM-FM");
                     if (comboBoxMO.Text == "SOQPSK")
                         sw.WriteLine("SOQPSK");
                     if (comboBoxMO.Text == "Carrier only")
                         sw.WriteLine("Carrier only");
                     if (comboBoxMO.Text == "IQ imbalance")
                         sw.WriteLine("IQ imbalance");

                     sw.WriteLine(numericUpDownFR.Value.ToString());

                     sw.WriteLine(maskedTextBoxBR.Text);

                     if (comboBoxDE.Text == "OFF")
                         sw.WriteLine("OFF");
                     if (comboBoxDE.Text == "ON")
                         sw.WriteLine("ON");

                     if (comboBoxDS.Text == "External")
                         sw.WriteLine("External");
                     if (comboBoxDS.Text == "Internal")
                         sw.WriteLine("Internal");

                     if (comboBoxRA.Text == "OFF")
                         sw.WriteLine("OFF");
                     if (comboBoxRA.Text == "ON")
                         sw.WriteLine("ON");

                     if (comboBoxDP.Text == "Normal")
                         sw.WriteLine("Normal");
                     if (comboBoxDP.Text == "Invert")
                         sw.WriteLine("Invert");

                     if (comboBoxCP.Text == "Normal")
                         sw.WriteLine("Normal");
                     if (comboBoxCP.Text == "Invert")
                         sw.WriteLine("Invert");

                     if (comboBoxCS.Text == "External")
                         sw.WriteLine("External");
                     if (comboBoxCS.Text == "Internal")
                         sw.WriteLine("Internal");

                     if (comboBoxID.Text == "Const 0")
                         sw.WriteLine("Const 0");
                     if (comboBoxID.Text == "Const 1")
                         sw.WriteLine("Const 1");
                     if (comboBoxID.Text == "PRBS15")
                         sw.WriteLine("PRBS15");
                     if (comboBoxID.Text == "PRBS17")
                         sw.WriteLine("PRBS17");

                     if (comboBoxRB.Text == "Open = RF ON   |  GND = RF OFF")
                         sw.WriteLine("Open = RF ON   |  GND = RF OFF");
                     if (comboBoxRB.Text == "Open = RF OFF  |  GND = RF ON")
                         sw.WriteLine("Open = RF OFF  |  GND = RF ON");

                     if (comboBoxRC.Text == "Open = SV  |  +3V = VL")
                         sw.WriteLine("Open = SV  |  +3V = VL");
                     if (comboBoxRC.Text == "Open = VL  |  +3V = SV")
                         sw.WriteLine("Open = VL  |  +3V = SV");

                     if (comboBoxTX.Text == "OFF")
                         sw.WriteLine("OFF");
                     if (comboBoxTX.Text == "ON")
                         sw.WriteLine("ON");

                     if (comboBoxRP.Text == "Low")
                         sw.WriteLine("Low");
                     if (comboBoxRP.Text == "High")
                         sw.WriteLine("High");

                     sw.WriteLine(numericUpDownVL.Value.ToString());
                     sw.WriteLine(numericUpDownVP.Value.ToString());

                 }
             }


         }

         private void loadFromFile()
         {
             using (StreamReader sr = File.OpenText(path))
             {
                 string s = "";
                 //while ((s = sr.ReadLine()) != null)
                 //{
                 //    MessageBox.Show(s);
                 //}
                 if ((s = sr.ReadLine()) != null) comboBoxMO.Text = s;
                 if ((s = sr.ReadLine()) != null) numericUpDownFR.Value = Convert.ToDecimal(s);
                 if ((s = sr.ReadLine()) != null) maskedTextBoxBR.Text = s;
                 if ((s = sr.ReadLine()) != null) comboBoxDE.Text = s;

                 if ((s = sr.ReadLine()) != null) comboBoxDS.Text = s;
                 if ((s = sr.ReadLine()) != null) comboBoxRA.Text = s;
                 if ((s = sr.ReadLine()) != null) comboBoxDP.Text = s;
                 if ((s = sr.ReadLine()) != null) comboBoxCP.Text = s;

                 if ((s = sr.ReadLine()) != null) comboBoxCS.Text = s;
                 if ((s = sr.ReadLine()) != null) comboBoxID.Text = s;
                 if ((s = sr.ReadLine()) != null) comboBoxRB.Text = s;
                 if ((s = sr.ReadLine()) != null) comboBoxRC.Text = s;

                 if ((s = sr.ReadLine()) != null) comboBoxTX.Text = s;
                 if ((s = sr.ReadLine()) != null) comboBoxRP.Text = s;
                 if ((s = sr.ReadLine()) != null) numericUpDownVL.Value = Convert.ToDecimal(s);
                 if ((s = sr.ReadLine()) != null) numericUpDownVP.Value = Convert.ToDecimal(s);
             }

         }

         private void button5_Click_1(object sender, EventArgs e)
         {
             try
             {//saveFileDialog1.FileName = path;
                 saveFileDialog1.ShowDialog();
                 path = saveFileDialog1.FileName;
                 saveToFile();
             }
             catch { };
             
         }

         private void button6_Click(object sender, EventArgs e)
         {
             try
             {
                 openFileDialog1.ShowDialog();
                 path = openFileDialog1.FileName;
                 loadFromFile();
             }
             catch { };
         }

         private void MainForm_Load(object sender, EventArgs e)
         {
             
         }
     

     

    }
}
