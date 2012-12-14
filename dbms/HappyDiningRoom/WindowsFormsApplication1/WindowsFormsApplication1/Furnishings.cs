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
    public partial class Furnishings : Form
    {
        useraction user = new useraction();
        Form1 f1;
        public Furnishings(Form1 f)
        {
            f1 = f;
            InitializeComponent();
        }

        private void Furnishings_Load(object sender, EventArgs e)
        {
            timer1.Enabled = true;
            timer1.Interval = 1000;
        }

        private void button1_Click(object sender, EventArgs e)
        {
           
            user.fur_buy(Convert.ToInt32(f1.textBox1.Text), "fur1", f1.pictureBox16, 500,"Post");
            f1.timer2.Interval -= 100;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            
            user.fur_buy(Convert.ToInt32(f1.textBox1.Text), "fur2", f1.pictureBox17, 1000, "Board");
            f1.timer2.Interval -= 100;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            
            user.fur_buy(Convert.ToInt32(f1.textBox1.Text), "fur3", f1.pictureBox13, 1500, "Swinghorse");
            f1.timer2.Interval -= 100;
        }

        private void button4_Click(object sender, EventArgs e)
        {
           
            user.fur_buy(Convert.ToInt32(f1.textBox1.Text), "fur4", f1.pictureBox10, 800, "Flower");
            f1.timer2.Interval -= 100;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            
            user.fur_buy(Convert.ToInt32(f1.textBox1.Text), "fur5", f1.pictureBox15, 5000, "Fountain");
            f1.timer2.Interval -= 100;
        }

        private void button6_Click(object sender, EventArgs e)
        {
           
            user.fur_buy(Convert.ToInt32(f1.textBox1.Text), "fur6", f1.pictureBox14, 1800, "Fridge");
            f1.timer2.Interval -= 100;
        }

        private void pictureBox6_Click(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            textBox1.Text = user.getUserData(Convert.ToInt32(f1.textBox1.Text), "balance");
        }

        private void crystalButton1_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
