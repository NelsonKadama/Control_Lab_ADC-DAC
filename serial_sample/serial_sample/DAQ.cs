using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class DAQ : Form
    {
        private string input;
        private double input_voltage;
        private string send;
        private Boolean receiving = true;   // used to check information is being sent or received


        public DAQ()
        {
            InitializeComponent();
        }

        

        private void getData(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            if (receiving)
            {
                input = serialPort1.ReadLine();                     // reads data from serial port
                this.Invoke(new EventHandler(displaydata_event));
            }
        }

        private void displaydata_event(object sender, EventArgs e)
        {

            txtRead.Text = input;       // displays data read from serial port
            
        }
        

        private void btnRead_Click(object sender, EventArgs e)
        {
            receiving = true;
        }

        private void btnSend_Click(object sender, EventArgs e)      //pressed after user selects channel
        {
            string clear;
            receiving = false;

            send = "reset" + 'q';               // sent to arduino to clear previously selected channels
            serialPort1.Write(send);
            clear = serialPort1.ReadLine();
            receiving = true;

            int selectedIndex = cmbChannel.SelectedIndex;       //determines value selected from combobox
            Object selectedItem = cmbChannel.SelectedItem;

            send = selectedItem.ToString() + 'q';       //  'q' used to show end of transmission
            serialPort1.Write(send);                    //sends combobox value via serial port
            clear = serialPort1.ReadLine();             // clears serial port to read new value (value sent (channel) would be read otherwise)
            receiving = true;
        }

        private void DAQ_Load(object sender, EventArgs e)
        {
            txtRead.Enabled = false;            // disables txt read so nothing can be written to it. strictly used to display values read
            btnSend.Enabled = false;            // disables btnSend till COM port is selected
        }

        private void btnPort_Click(object sender, EventArgs e)
        {

            serialPort1.PortName = txtPort.Text;        // port name (COMx)

            serialPort1.Open();

            string clear;
            receiving = false;

            send = "reset" + 'q';
            serialPort1.Write(send);
            clear = serialPort1.ReadLine();
            receiving = true;

            btnPort.Enabled = false;
            btnSend.Enabled = true;

        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

    }
}
