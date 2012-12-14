using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MySql.Data;
using MySql.Data.MySqlClient;

namespace WindowsFormsApplication1
{
    public partial class addfriends : Form
    {

        
        useraction user = new useraction();
        Form1 f1;
       

        public addfriends(Form1 f)
        {
            f1 = f;
            InitializeComponent();

        }

        private void friends_Load(object sender, EventArgs e)
        {
            label1.Text = "User: " + f1.textBox1.Text;
            user.a(this.dataGridView1,Convert.ToInt32(f1.textBox1.Text));
        }

        private void dataGridViewX1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            
        }

       


        private void crystalButton1_Click(object sender, EventArgs e)
        {
            string s = this.dataGridView1.CurrentRow.Cells[0].Value.ToString();

            user.addfriends(Convert.ToInt32(f1.textBox1.Text), s);
        }

        private void crystalButton2_Click(object sender, EventArgs e)
        {string s = this.dataGridView1.CurrentRow.Cells[0].Value.ToString();
        if (user.Friendjudge(Convert.ToInt32(f1.textBox1.Text), s) == true)
        {
            friendshome n = new friendshome(this);
            n.Show();
        }

        }

        private void crystalButton3_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void crystalButton4_Click(object sender, EventArgs e)
        {
            string s = this.dataGridView1.CurrentRow.Cells[0].Value.ToString();
            if (user.Friendjudge(Convert.ToInt32(f1.textBox1.Text), s) == true)
            {
                f1.label14.Text = s;
                f1.label14.Visible = true;
            }

        }

        

    }
}
