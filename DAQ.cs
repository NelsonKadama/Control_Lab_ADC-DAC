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
        public DAQ()
        {
            InitializeComponent();
        }

        public void PortOpen()
        {
            serialPort1.Open();
        }

        private void getData(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            input = serialPort1.ReadLine();
            this.Invoke(new EventHandler(displaydata_event));
        }

        private void displaydata_event(object sender, EventArgs e)
        {

            textBox1.Text = input;

        }
        

        public void PortClose()
        {
            serialPort1.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            PortOpen();
        }
    }
}
