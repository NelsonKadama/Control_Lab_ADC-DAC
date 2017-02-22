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
        private Boolean receiving = true;


        public DAQ()
        {
            InitializeComponent();
        }

        

        private void getData(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            if (receiving)
            {
                input = serialPort1.ReadLine();
                this.Invoke(new EventHandler(displaydata_event));
            }
        }

        private void displaydata_event(object sender, EventArgs e)
        {
            
            txtRead.Text = input;
            
        }
        

        private void btnRead_Click(object sender, EventArgs e)
        {
            receiving = true;
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            string clear;
            receiving = false;

            int selectedIndex = cmbChannel.SelectedIndex;
            Object selectedItem = cmbChannel.SelectedItem;

            send = selectedItem.ToString() + 'q';
            serialPort1.Write(send);
            clear = serialPort1.ReadLine();
            receiving = true;
        }

        private void DAQ_Load(object sender, EventArgs e)
        {
            txtRead.Enabled = false;
            btnSend.Enabled = false;
        }

        private void btnPort_Click(object sender, EventArgs e)
        {
            
            serialPort1.PortName = txtPort.Text;

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
