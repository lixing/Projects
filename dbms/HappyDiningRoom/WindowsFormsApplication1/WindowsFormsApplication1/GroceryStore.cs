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
    public partial class GroceryStore : Form
    {
        useraction user = new useraction();
        Form1 f1;
      
        public GroceryStore(Form1 f)
        {
            f1 = f;
            InitializeComponent();
        }

        private void GroceryStore_Load(object sender, EventArgs e)
        {
            label2.Text = DateTime.Now.ToString();

            timer1.Enabled = true;
            timer1.Interval = 1000;
            textBox2.Text = "Money: " + f1.textBox2.Text;

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            label2.Text = DateTime.Now.ToString();
            textBox2.Text = "Money: " + user.getUserData(Convert.ToInt32(f1.textBox1.Text), "balance");
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (user.isaffordable(Convert.ToInt32(f1.textBox1.Text),Convert.ToInt32( numericUpDown1.Value) * 100) == false)
                MessageBox.Show("Money is not enough!");
            else
            {
                user.warehousebuy(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value), "Poireau_amount");
                MessageBox.Show("you have bought " + user.buy("balance", Convert.ToInt32(f1.textBox1.Text), 100, Convert.ToInt32(numericUpDown1.Value)) + " Poireau successfully!");


                textBox2.Text = "Money: " + user.getUserData(Convert.ToInt32(f1.textBox1.Text), "balance");
            }
            



        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
           
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (user.isaffordable(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value) * 200) == false)
                MessageBox.Show("Money is not enough!");
            else
            {
                user.warehousebuy(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value), "Onion_amount");
                MessageBox.Show("you have bought " + user.buy("balance", Convert.ToInt32(f1.textBox1.Text), 200, Convert.ToInt32(numericUpDown1.Value)) + " Onion successfully!");
                textBox2.Text = "Money: " + user.getUserData(Convert.ToInt32(f1.textBox1.Text), "balance");
            }
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (user.isaffordable(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value) * 150) == false)
                MessageBox.Show("Money is not enough!");
            else
            {
                user.warehousebuy(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value), "Mango_amount");
                MessageBox.Show("you have bought " + user.buy("balance",  Convert.ToInt32(f1.textBox1.Text), 150, Convert.ToInt32(numericUpDown1.Value)) + " Mango successfully!");
                textBox2.Text = "Money: " + user.getUserData(Convert.ToInt32(f1.textBox1.Text), "balance");
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (user.isaffordable(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value) * 100) == false)
                MessageBox.Show("Money is not enough!");
            else
            {
                user.warehousebuy(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value), "Rice_amount");
                MessageBox.Show("you have bought " + user.buy("balance",  Convert.ToInt32(f1.textBox1.Text), 100, Convert.ToInt32(numericUpDown1.Value)) + " Rice successfully!");
                textBox2.Text = "Money: " + user.getUserData(Convert.ToInt32(f1.textBox1.Text), "balance");
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (user.isaffordable(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value) * 200) == false)
                MessageBox.Show("Money is not enough!");
            else
            {
                user.warehousebuy(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value), "Pumpkin_amount");
                MessageBox.Show("you have bought " + user.buy("balance",  Convert.ToInt32(f1.textBox1.Text), 200, Convert.ToInt32(numericUpDown1.Value)) + " Pumpkin successfully!");
                textBox2.Text = "Money: " + user.getUserData(Convert.ToInt32(f1.textBox1.Text), "balance");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (user.isaffordable(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value) * 300) == false)
                MessageBox.Show("Money is not enough!");
            else
            {
                user.warehousebuy(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value), "Lobster_amount");
                MessageBox.Show("you have bought " + user.buy("balance",  Convert.ToInt32(f1.textBox1.Text), 300, Convert.ToInt32(numericUpDown1.Value)) + " Lobster successfully!");
                textBox2.Text = "Money: " + user.getUserData(Convert.ToInt32(f1.textBox1.Text), "balance");
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (user.isaffordable(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value) * 130) == false)
                MessageBox.Show("Money is not enough!");
            else
            {
                user.warehousebuy(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value), "Fish_amount");
                MessageBox.Show("you have bought " + user.buy("balance",  Convert.ToInt32(f1.textBox1.Text), 130, Convert.ToInt32(numericUpDown1.Value)) + " Fish successfully!");
                textBox2.Text = "Money: " + user.getUserData(Convert.ToInt32(f1.textBox1.Text), "balance");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (user.isaffordable(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value) * 120) == false)
                MessageBox.Show("Money is not enough!");
            else
            {
                user.warehousebuy(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value), "Sausage_amount");
                MessageBox.Show("you have bought " + user.buy("balance",  Convert.ToInt32(f1.textBox1.Text), 120, Convert.ToInt32(numericUpDown1.Value)) + " Sausage successfully!");
                textBox2.Text = "Money: " + user.getUserData(Convert.ToInt32(f1.textBox1.Text), "balance");
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (user.isaffordable(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value) * 130) == false)
                MessageBox.Show("Money is not enough!");
            else
            {
                user.warehousebuy(Convert.ToInt32(f1.textBox1.Text), Convert.ToInt32(numericUpDown1.Value), "Hylocereusundatus_amount");
                MessageBox.Show("you have bought " + user.buy("balance",  Convert.ToInt32(f1.textBox1.Text), 130, Convert.ToInt32(numericUpDown1.Value)) + " Hylocereusundatus successfully!");
                
            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void toolTip1_Popup(object sender, PopupEventArgs e)
        {

        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {

        }

       

       

       
        private void crystalButton1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button10_Click(object sender, EventArgs e)
        {

        }
    }
}

        
    


