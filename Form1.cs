using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        private SerialPort myport;
        private string input;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //this.BackColor = Color.Brown;
            //label1.Text = "HelloWorld!"; // take out

            //myport = new SerialPort();
            //myport.BaudRate = 9600;
            //myport.PortName = "COM9";
            //myport.Parity = Parity.None;
            //myport.DataBits = 8;
            //myport.StopBits = StopBits.One;
            //myport.DataReceived += new SerialDataReceivedEventHandler(myport_DataReceived);

            //try
            //{
            //    myport.Open();
            //}

            //catch (Exception ex)
            //{
            //    MessageBox.Show(ex.Message, "Error");
            //}

            DAQ DAC = new DAQ();
            ////double voltage = DAC.get_voltage();
            ////textBox1.Text = voltage.ToString();

            this.Hide();

            DAC.Show();

        }

        void myport_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            input = myport.ReadLine();
            
            this.Invoke(new EventHandler(displaydata_event));
        }

        private void displaydata_event(object sender, EventArgs e)
        {

            textBox1.Text = input;

        }
    }
}
