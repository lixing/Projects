using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

using System.Runtime.InteropServices;
using System.Reflection;



namespace WindowsFormsApplication1
{
    public partial class main : Form
    {
        
        


        useraction user = new useraction();


        public main()
        {
            InitializeComponent();
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void main_Load(object sender, EventArgs e)
        {
            timer1.Enabled = true;
            timer1.Interval = 10;
            progressBarX1.Maximum = 100;
        

          

        }

        private void button1_Click(object sender, EventArgs e)
        {
            label1.Show(); label2.Show(); textBox1.Show(); textBox2.Show();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form k = new AddCustomer();
            k.Show();


        }





        private void progressBar1_Click(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (progressBarX1.Value < progressBarX1.Maximum)
            {
                progressBarX1.Value++;
            }
            else
            {

                timer1.Enabled = false;
               
                progressBarX1.Hide();

                button1.Show();
                button2.Show();

            }
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            useraction user = new useraction();
            if (textBox1.Text == "") pictureBox1.Visible = false;
            else if (user.isUserExist(textBox1.Text) )
            {
                pictureBox1.Image = Properties.Resources.correct;
                label6.Visible = false;
                pictureBox1.Visible = true;
            }
            else
            {
                pictureBox1.Image = Properties.Resources.error;
                label6.Text = "This user doesn't exist!";
                label6.Visible = true;
                pictureBox1.Visible = true;
            }
       

            user.dropUser();
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            timer2.Enabled = true;
            timer2.Interval = 100;
          
        }



        private void crystalButton1_Click(object sender, EventArgs e)
        {
            if (user.login(Convert.ToInt32(textBox1.Text), textBox2.Text))
            {



                Form k = new Form1(this);
                k.Show();
                MessageBox.Show("success!");
            }
        }


        private void textBox1_Leave(object sender, EventArgs e)
        {
            
        }

        private void axWindowsMediaPlayer1_Enter(object sender, EventArgs e)
        {

        }

        private void textBox2_Leave(object sender, EventArgs e)
        {
            
        }

        private void crystalButton1_Click_1(object sender, EventArgs e)
        {
            if (user.login(Convert.ToInt32(textBox1.Text), textBox2.Text))
            {



                Form k = new Form1(this);
                k.Show();
                MessageBox.Show("success!");
            }
        }

        private void progressBarX1_Click(object sender, EventArgs e)
        {

        }

        

        private void pictureBox1_LoadProgressChanged(object sender, ProgressChangedEventArgs e)
        {

        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {

        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            if (textBox2.Text == "") pictureBox2.Visible = false;
            if (label6.Visible == false && textBox2.Text == user.getUserData(Convert.ToInt32(textBox1.Text), "password"))
            {
                pictureBox2.Image = Properties.Resources.correct;
                crystalButton1.Visible = true;
                timer2.Enabled = false;
                pictureBox2.Visible = true;
            }
            else
            {
                pictureBox2.Image = Properties.Resources.error;
                crystalButton1.Visible = false; ;

                pictureBox2.Visible = true;
            }
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!(Char.IsNumber(e.KeyChar) || e.KeyChar == '\b'))
            {
                e.Handled = true;
            }
        }

        private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!(Char.IsNumber(e.KeyChar) || e.KeyChar == '\b'))
            {
                e.Handled = true;
            }
        }

     

            }

        }



    


      
        
        

        

    

