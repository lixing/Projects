using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace BankSystem
{
    public partial class FormWelcome : Form
    {
        public FormWelcome()
        {
            InitializeComponent();
        }

        private int  _time = 0;
        private int seconds = 10;

        private void button1_Click(object sender, EventArgs e)
        {
            FormMain f = new FormMain();
            f.Show();
            this.Hide();
            _time = 0;
            seconds = 10;
            timerMain.Enabled = false;
        }

        private void FormWelcome_Load(object sender, EventArgs e)
        {
            timerMain.Enabled = true;
            lblStatus.Text = "Login in " + seconds + " Sconds.";
        }

        private void timerMain_Tick(object sender, EventArgs e)
        {
            _time += 1000;
            if (seconds>=0){
            seconds -= 1;
            lblStatus.Text = "Login in " + seconds + " Seconds.";
        }
            if (_time>=10000)
            {
                FormMain f = new FormMain();
                f.Show();
                this.Hide();
                  _time = 0;
               seconds = 10;
                timerMain.Enabled = false;
            }
        }

    

      


    }
}