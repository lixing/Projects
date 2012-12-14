using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace WindowsFormsApplication1
{
    public partial class Mycookie : Form
    {
        Form1 f1;
        useraction user = new useraction();
        public Mycookie(Form1 f)
        {
            f1 = f;
            InitializeComponent();
        }

        private void Mycookie_Load(object sender, EventArgs e)
        {
            pictureBox2.ImageLocation= "C:\\Users\\hp\\Desktop\\HappyDiningRoom\\HappyDiningRoom\\WindowsFormsApplication1\\WindowsFormsApplication1\\Resources\\" + f1.textBox1.Text + ".jpg";
           

            label7.Text = DateTime.Now.ToString(); 
        
            timer1.Enabled = true;
            timer1.Interval = 1000;
            textBox5.Text = user.getUserData(Convert.ToInt32(f1.textBox1.Text), "firstname");
            textBox4.Text = user.getUserData(Convert.ToInt32(f1.textBox1.Text), "lastname");
            textBox2.Text = user.getUserData(Convert.ToInt32(f1.textBox1.Text), "userid");
            textBox3.Text = user.getUserData(Convert.ToInt32(f1.textBox1.Text), "skilllevel");
            textBox1.Text = user.getUserData(Convert.ToInt32(f1.textBox1.Text), "balance");
            textBox6.Text = user.getUserData(Convert.ToInt32(f1.textBox1.Text), "charmingvalue");
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            label7.Text = DateTime.Now.ToString(); 
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.InitialDirectory = @"c:\";
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string pFromPath = @openFileDialog1.FileName;
                string pToPath = @"C:\Users\hp\Desktop\HappyDiningRoom\HappyDiningRoom\WindowsFormsApplication1\WindowsFormsApplication1\Resources\"+f1.textBox1.Text+".jpg";
                File.Copy(pFromPath, pToPath, true);

              
                
              
                
                pictureBox2.ImageLocation = openFileDialog1.FileName;
            }
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }

        

        private void axWindowsMediaPlayer1_OpenPlaylistSwitch(object sender, AxWMPLib._WMPOCXEvents_OpenPlaylistSwitchEvent e)
        {

        }

        private void axWindowsMediaPlayer1_Enter(object sender, EventArgs e)
        {

        }

        private void crystalButton1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

      

        }
    }

