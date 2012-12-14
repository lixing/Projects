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
    public partial class Menu : Form
    {
        Form1 f1;
        useraction user = new useraction();
        public Menu(Form1 f)
        {
            f1 = f;
            InitializeComponent();
        }

        private void Menu_Load(object sender, EventArgs e)
        {
            timer1.Enabled = true;
            timer1.Interval = 1000;
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            label11.Text = DateTime.Now.ToString(); 
        }

        private void buttonItem1_Click(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {

            if (user.cook(Convert.ToInt32(f1.textBox1.Text), 700, "Lobster_amount", "Onion_amount", "Poireau_amount", "DishA_amount"))
            {
                label12.Visible = true;
                timer2.Enabled = true;
                timer2.Interval = 1000;
                progressBar1.Maximum = 100;
                progressBar1.Visible = true;
                
            }
        }

        private void progressBar1_Click(object sender, EventArgs e)
        {

        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            int time; 
            if (progressBar1.Value < progressBar1.Maximum&&Convert.ToInt32(label12.Text)>=0)
            {
                
            
              
                progressBar1.Value = progressBar1.Value+20;
                time = Convert.ToInt32(label12.Text) - 1;
                label12.Text = time.ToString();
             
            }
            else
            {
                label12.Text = "5";
                label12.Visible = false; progressBar1.Visible = false; progressBar1.Value = 0; timer2.Enabled = false;
            
            }
        }

        private void label12_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (user.cook(Convert.ToInt32(f1.textBox1.Text), 600, "Rice_amount", "Sausage_amount", "Pumpkin_amount", "DishB_amount"))
            {
                label13.Visible = true;
                timer3.Enabled = true;
                timer3.Interval = 1000;
                progressBar4.Maximum = 100;
                progressBar4.Visible = true;
                
            }
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            int time;
            if (progressBar4.Value < progressBar4.Maximum &&Convert.ToInt32(label13.Text) >= 0)
            {



                progressBar4.Value = progressBar4.Value + 25;
                time = Convert.ToInt32(label13.Text) - 1;
                label13.Text = time.ToString();

            }
            else
            {
                label13.Text = "4";
                label13.Visible = false; progressBar4.Visible = false; progressBar4.Value = 0; timer3.Enabled = false;

            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (user.cook(Convert.ToInt32(f1.textBox1.Text), 700, "Mango_amount", "Hylocereusundatus_amount", "Pumpkin_amount", "DishC_amount"))
            {
                label14.Visible = true;
                timer4.Enabled = true;
                timer4.Interval = 1000;
                progressBar3.Maximum = 100;
                progressBar3.Visible = true;
               
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (user.cook(Convert.ToInt32(f1.textBox1.Text), 800, "Fish_amount", "Onion_amount", "Poireau_amount", "DishD_amount"))
            {
                label15.Visible = true;
                timer5.Enabled = true;
                timer5.Interval = 1000;
                progressBar2.Maximum = 100;
                progressBar2.Visible = true;
                
            }
        }

        private void progressBar3_Click(object sender, EventArgs e)
        {

        }

        private void label14_Click(object sender, EventArgs e)
        {

        }

        private void timer4_Tick(object sender, EventArgs e)
        {
            int time;
            if (progressBar3.Value < progressBar3.Maximum && Convert.ToInt32(label14.Text) >= 0)
            {



                progressBar3.Value = progressBar3.Value + 20;
                time = Convert.ToInt32(label14.Text) - 1;
                label14.Text = time.ToString();

            }
            else
            {
                label14.Text = "5";
                label14.Visible = false; progressBar3.Visible = false; progressBar3.Value = 0; timer4.Enabled = false;

            }
        
        }

        private void progressBar2_Click(object sender, EventArgs e)
        {

        }

        private void timer5_Tick(object sender, EventArgs e)
        {
            int time;
            if (progressBar2.Value < progressBar2.Maximum && Convert.ToInt32(label15.Text) >= 0)
            {



                progressBar2.Value = progressBar2.Value + 10;
                time = Convert.ToInt32(label15.Text) - 1;
                label15.Text = time.ToString();

            }
            else
            {
                label15.Text = "10";
                label15.Visible = false; progressBar2.Visible = false; progressBar2.Value = 0; timer5.Enabled = false;

            }
        
        }

        private void label13_Click(object sender, EventArgs e)
        {

        }

        private void wareHouseToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void crystalButton1_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
