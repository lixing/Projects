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
    public partial class friendshome : Form
    {
        
        useraction user = new useraction();
        addfriends f1;
        public friendshome(addfriends f)
        {
      
            f1 = f;
            InitializeComponent();
        }

        private void friendshome_Load(object sender, EventArgs e)
        {
            string s = f1.dataGridView1.CurrentRow.Cells[0].Value.ToString();
            textBox5.Text = s;
            textBox6.Text = user.getUserData(Convert.ToInt32(s), "balance");
            textBox7.Text = user.getUserData(Convert.ToInt32(s), "skilllevel");
            textBox8.Text = user.getUserData(Convert.ToInt32(s), "charmingvalue");
            user.friendhome(Convert.ToInt32(s), pictureBox1, 1, 7, 8);
            user.friendhome(Convert.ToInt32(s),pictureBox2 ,2, 9, 10);
            user.friendhome(Convert.ToInt32(s), pictureBox3, 3, 11, 12);
            user.friendhome(Convert.ToInt32(s), pictureBox4, 4, 13, 14);
            user.friendhome(Convert.ToInt32(s), pictureBox5, 5, 15, 16);
            user.friendhome(Convert.ToInt32(s), pictureBox6, 6, 17, 18);

            
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox8_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox7_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
