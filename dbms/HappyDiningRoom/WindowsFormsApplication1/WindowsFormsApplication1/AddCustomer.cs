using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MySql.Data;
using MySql.Data.MySqlClient;
using System.IO;
using System.Drawing;



namespace WindowsFormsApplication1
{
    public partial class AddCustomer : Form
    {
        private MySqlConnection Conn = null;
        private MySqlCommand Comm = null;




        public AddCustomer()
        {
            InitializeComponent();
        }

        private void AddCustomer_Load(object sender, EventArgs e)
        {

        }

        private void crystalButton1_Click(object sender, EventArgs e)
        {

            try
            {
                MySqlConnectionStringBuilder Builder = new MySqlConnectionStringBuilder();
                Builder.Add("Database", "happydiningroom");
                Builder.Add("Data Source", "localhost");
                Builder.Add("User Id", "root");
                Builder.Add("Password", "admin");

                Conn = new MySqlConnection(Builder.ConnectionString);

                Conn.Open();
                Comm = new MySqlCommand("insert into user values('" + textBox2.Text + "' , '" + maskedTextBox2.Text + "' ,'" + textBox6.Text + "','" + textBox1.Text + "','" + textBox4.Text + "','" + textBox3.Text + "','500','1','100')", Conn);
                Comm.ExecuteNonQuery();
                Comm = new MySqlCommand("insert into warehouse values('" + textBox2.Text + "' ,'0','0','0','0','0','0','0','0','0','0','0','0','0')", Conn);
                Comm.ExecuteNonQuery();
                Comm = new MySqlCommand("insert into friends values('" + textBox2.Text + "' ,'','','')", Conn);
                Comm.ExecuteNonQuery();
      
             
                Comm = new MySqlCommand("insert into furnishings values('" + textBox2.Text + "' ,'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0')", Conn);
              
                Comm.ExecuteNonQuery();
                this.Close();

            }

            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                try
                {
                    if (Conn != null)
                    {
                        Conn.Close();
                        Conn = null;
                    }
                }
                catch (Exception d)
                {
                    MessageBox.Show(d.Message);
                }
            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            useraction user = new useraction();
            if (textBox2.Text == "") { pictureBox2.Visible = false; label12.Visible = false; }
            else if (!user.isUserExist(textBox2.Text))
            {
                pictureBox2.Image = Properties.Resources.correct;
                label12.Visible = false;
                pictureBox2.Visible = true;
            }
            else
            {
                pictureBox2.Image = Properties.Resources.error;
                label12.Text = "User existed!";
                label12.Visible = true;
                pictureBox2.Visible = true;
            }
           

            user.dropUser();
        }

        private void maskedTextBox2_MaskInputRejected(object sender, MaskInputRejectedEventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void maskedTextBox1_Leave(object sender, EventArgs e)
        {
            

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

       

        private void textBox2_Leave(object sender, EventArgs e)
        {
            
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {

        }

        private void bubbleButton1_Click(object sender, DevComponents.DotNetBar.ClickEventArgs e)
        {

        }

        private void dotNetBarManager1_ItemClick(object sender, EventArgs e)
        {

        }

        private void textBox5_Leave(object sender, EventArgs e)
        {
            
        }

        private void pictureBox3_Click(object sender, EventArgs e)
        {

        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {
            if (textBox5.Text == "") pictureBox3.Visible = false;
            else if (textBox5.Text == validateCode1.CodeText)
            {
                pictureBox3.Image = Properties.Resources.correct;
                if ((textBox6.Text == "M" || textBox6.Text == "F") && (label12.Visible == false) && (maskedTextBox2.Text == textBox8.Text && maskedTextBox2.Text != ""))
                    crystalButton1.Visible=true;
                pictureBox3.Visible = true;
            }
            else
            {
                pictureBox3.Image = Properties.Resources.error;
                pictureBox3.Visible = true;
                crystalButton1.Visible = false;
            }
          
        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {
            if (textBox6.Text == "")
                pictureBox4.Visible = false;
            else if (textBox6.Text == "M" || textBox6.Text == "F")
            {
                pictureBox4.Image = Properties.Resources.correct;
                pictureBox4.Visible = true;
            }
            else
            {
                pictureBox4.Image = Properties.Resources.error;
                pictureBox4.Visible = true;
            }
           
        }

        private void pictureBox4_Click(object sender, EventArgs e)
        {

        }

        private void crystalButton1_Validating(object sender, System.ComponentModel.CancelEventArgs e)
        {

        }

        private void textBox6_Leave(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

       

        private void pictureBox5_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void textBox8_TextChanged(object sender, EventArgs e)
        {
            if (textBox8.Text == "") pictureBox1.Visible = false;
            else if (maskedTextBox2.Text == textBox8.Text )
            {
                pictureBox1.Image = Properties.Resources.correct;
                pictureBox1.Visible = true;
            }
            else
            {
                pictureBox1.Image = Properties.Resources.error;
                pictureBox1.Visible = true;
            }
            
        }

        private void crystalButton2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void maskedTextBox2_KeyPress(object sender, KeyPressEventArgs e)
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

        private void textBox8_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!(Char.IsNumber(e.KeyChar) || e.KeyChar == '\b'))
            {
                e.Handled = true;
            }

        }

        private void textBox5_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!(Char.IsNumber(e.KeyChar) || e.KeyChar == '\b'))
            {
                e.Handled = true;
            }
        }

        private void validateCode1_Load(object sender, EventArgs e)
        {

        }
    }
}

        
    

