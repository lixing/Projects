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
    public partial class Warehouse : Form
    {
        useraction user = new useraction();
        Form1 f1;
        public Warehouse(Form1 f)
        {
            f1 = f;
            InitializeComponent();
        }

        private void dfzgbdfgToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void Warehouse_Load(object sender, EventArgs e)
        {
            textBox2.Text = f1.textBox1.Text;
            label1.Text ="Poireau : "+ user.warehouseshow(Convert.ToInt32(f1.textBox1.Text) ,"Poireau_amount");
            label4.Text = "Onion : " + user.warehouseshow(Convert.ToInt32(f1.textBox1.Text), "Onion_amount");
            label9.Text = "Mango : " + user.warehouseshow(Convert.ToInt32(f1.textBox1.Text), "Mango_amount");
            label8.Text = "Rice : " + user.warehouseshow(Convert.ToInt32(f1.textBox1.Text), "Rice_amount");
            label10.Text = "Pumpkin : " + user.warehouseshow(Convert.ToInt32(f1.textBox1.Text), "Pumpkin_amount");
            label3.Text = "Lobster : " + user.warehouseshow(Convert.ToInt32(f1.textBox1.Text), "Lobster_amount");
            label6.Text = "Fish : " + user.warehouseshow(Convert.ToInt32(f1.textBox1.Text), "Fish_amount");
            label7.Text = "Sausage : " + user.warehouseshow(Convert.ToInt32(f1.textBox1.Text), "Sausage_amount");
            label5.Text = "Hylocereusundatus : " + user.warehouseshow(Convert.ToInt32(f1.textBox1.Text), "Hylocereusundatus_amount");
            label14.Text = "DishA : " + user.warehouseshow(Convert.ToInt32(f1.textBox1.Text), "DishA_amount");
            label13.Text = "DishB : " + user.warehouseshow(Convert.ToInt32(f1.textBox1.Text), "DishB_amount");
            label12.Text = "DishC : " + user.warehouseshow(Convert.ToInt32(f1.textBox1.Text), "DishC_amount");
            label11.Text = "DishD : " + user.warehouseshow(Convert.ToInt32(f1.textBox1.Text), "DishD_amount");
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox9_Click(object sender, EventArgs e)
        {

        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void label10_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void crystalButton1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void crystalButton2_Click(object sender, EventArgs e)
        {

        }

       
       
    }
}
