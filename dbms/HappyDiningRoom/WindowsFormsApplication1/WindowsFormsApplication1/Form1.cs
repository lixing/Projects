using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;



namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        
        int i = 0,m=0;
        int x = 40, y = 276;
        int p = 2, q= 263;

        useraction user = new useraction();
        main f1;
        Point clickPoint;
        const short VK_LBUTTON = 0x01;

        [DllImport("user32 ")]
        public static extern short GetAsyncKeyState(int vKey);

        bool IsKeyDown(short vkey)
        {
            return (GetAsyncKeyState(vkey) & 0x8000) > 0;
        }


        public Form1(main f)
        {
            f1 = f;
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

            this.SetStyle(ControlStyles.UserPaint, true);
            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true); // 禁止擦除背景.
            this.SetStyle(ControlStyles.DoubleBuffer, true); // 双缓冲 
            label1.Text = DateTime.Now.ToString();

            timer1.Enabled = true;
            timer1.Interval = 1000;
            timer2.Enabled = true;
            timer2.Interval = 4000;
            

            textBox1.Text = f1.textBox1.Text;
            user.fur_location(Convert.ToInt32(textBox1.Text), 7, 8, pictureBox16, 1);
            user.fur_location(Convert.ToInt32(textBox1.Text), 9, 10, pictureBox17, 2);
            user.fur_location(Convert.ToInt32(textBox1.Text), 11, 12, pictureBox13, 3);
            user.fur_location(Convert.ToInt32(textBox1.Text), 13, 14, pictureBox10, 4);
            user.fur_location(Convert.ToInt32(textBox1.Text), 15, 16, pictureBox15, 5);
            user.fur_location(Convert.ToInt32(textBox1.Text), 17, 18, pictureBox14, 6);



        }


        private void timer1_Tick(object sender, EventArgs e)
        {
            label1.Text = DateTime.Now.ToString();
            textBox2.Text = user.getUserData(Convert.ToInt32(f1.textBox1.Text), "balance");
            textBox3.Text = user.getUserData(Convert.ToInt32(f1.textBox1.Text), "skilllevel");
            textBox4.Text = user.getUserData(Convert.ToInt32(f1.textBox1.Text), "charmingvalue");
            if (comboBox1.Text != "")
                textBox5.Text = user.dishamount(Convert.ToInt32(textBox1.Text), comboBox1.Text).ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form k = new Mycookie(this);
            k.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Form k = new GroceryStore(this);
            k.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form k = new Menu(this);
            k.Show();
        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            Warehouse f = new Warehouse(this);
            f.Show();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            addfriends g = new addfriends(this);
            g.Show();
           
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {

        }

        
        

        private void pictureBox3_Click(object sender, EventArgs e)
        {


            switch (i)
            {
                case 0:
                    {
                        pictureBox6.Visible = true;
                        timer3.Enabled = true;
                        timer3.Interval = 12000; i = 1; pictureBox3.Visible = false;  break;
                    }
                case 1:
                    {
                        pictureBox2.Visible = true;
                        timer4.Enabled = true;
                        timer4.Interval = 10000;
                        i = 2; pictureBox3.Visible = false;  break;
                    }
                case 2:
                    {
                        pictureBox4.Visible = true;
                        timer5.Enabled = true;
                        timer5.Interval = 10000; i = 0; pictureBox3.Visible = false; break;
                    }
            }

        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            pictureBox3.Visible = true;

        }

        private void pictureBox6_Click(object sender, EventArgs e)
        {

        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            pictureBox6.Visible = false;
            timer3.Enabled = false;
            pictureBox7.Visible = false; 
        }

        private void timer4_Tick(object sender, EventArgs e)
        {
            pictureBox4.Visible = false;
            timer4.Enabled = false;
            pictureBox8.Visible = false; 
        }

        private void timer5_Tick(object sender, EventArgs e)
        {
            pictureBox2.Visible = false;
            timer5.Enabled = false;
            pictureBox9.Visible = false; 
        }





        private void textBox5_TextChanged(object sender, EventArgs e)
        {

        }

        private void crystalButton1_Click(object sender, EventArgs e)
        {
            if (comboBox1.Text.Equals(""))
                MessageBox.Show("You have to choose dish first!");
            else{


                if (textBox5.Text != "0")
                {
                    user.servefood(Convert.ToInt32(textBox1.Text), comboBox1.Text);

                    x = 40; y = 276;
                    p = 2; q = 263;
                    pictureBox11.Visible = true;

                    switch (m)
                    {
                        case 0:
                            {
                                timer6.Enabled = true;
                                timer6.Interval = 100;
                                m = 1;
                                break;
                            }
                        case 1:
                            {
                                timer7.Enabled = true;
                                timer7.Interval = 100;
                                m = 2;
                                break;
                            }
                        case 2:
                            {
                                timer8.Enabled = true;
                                timer8.Interval = 100;
                                m = 0;
                                break;
                            }
                    }
                } 
                else MessageBox.Show("You have to cook first!");
               
            }
                
          

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

         

           private void timer6_Tick_1(object sender, EventArgs e)
        {
            
               if (x < 200 || y > 220)
               {
                   label14.Location = new Point(x, y);
                   pictureBox11.Location = new Point(x, y);
                   pictureBox5.Location = new Point(p, q);
                   x = x + 3; y = y - 1;
                   p=p+3;q=q-1;
                  
               }
               else
               {
                   timer6.Enabled = false;
                   pictureBox7.Visible = true;
                   pictureBox11.Visible = false;
                   label14.Location = new Point(2, 263);
                   pictureBox11.Location = new Point(40,276);
                   pictureBox5.Location = new Point(2, 263);
                   
               }
           }

           private void pictureBox7_Click(object sender, EventArgs e)
           {

           }

          

           private void pictureBox11_Click(object sender, EventArgs e)
           {

           }

           private void pictureBox15_Click(object sender, EventArgs e)
           {

           }

           private void pictureBox12_Click(object sender, EventArgs e)
           {

           }

           private void timer7_Tick(object sender, EventArgs e)
           {
              
               if (x < 371 || y > 220)
               {
                   label14.Location = new Point(x, y);
                   pictureBox11.Location = new Point(x, y);
                   pictureBox5.Location = new Point(p, q);
                   x = x + 6; y = y - 1;
                   p = p + 6; q = q - 1;
               }
               else
               {
                   timer7.Enabled = false;
                   pictureBox9.Visible = true;
                   pictureBox11.Visible = false;
                   label14.Location = new Point(2, 263);
                   pictureBox11.Location = new Point(40, 276);
                   pictureBox5.Location = new Point(2, 263);

               }
           }

           private void timer8_Tick(object sender, EventArgs e)
           {
               
               if (x < 371 || y > 298)
               {
                   label14.Location = new Point(x, y);
                   pictureBox11.Location = new Point(x, y);
                   pictureBox5.Location = new Point(p,q);
                   x = x + 20; y = y - 1;
                   p = p + 20; q = q - 1;
               }
               else
               {
                   timer8.Enabled = false;
                   pictureBox8.Visible = true;
                   pictureBox11.Visible = false;
                   label14.Location = new Point(2, 263);
                   pictureBox11.Location = new Point(40, 276);
                   pictureBox5.Location = new Point(2, 263);
                   

               }
           }

           private void pictureBox5_Click(object sender, EventArgs e)
           {

           }

           private void button6_Click(object sender, EventArgs e)
           {
               Furnishings k = new Furnishings(this);
               k.Show();
           }

           private void pictureBox17_MouseDown(object sender, MouseEventArgs e)
           {
               clickPoint.X = e.X;
               clickPoint.Y = e.Y;
           }

           private void pictureBox17_MouseMove(object sender, MouseEventArgs e)
           {
               if (IsKeyDown(VK_LBUTTON))
               {
                   (sender as Control).Cursor = Cursors.Hand;
                   (sender as Control).Left += e.X - clickPoint.X;
                   (sender as Control).Top += e.Y - clickPoint.Y;
                   

               }
               user.fur_save(Convert.ToInt32(textBox1.Text), pictureBox17.Location.X, pictureBox17.Location.Y, pictureBox17, "fur2_x", "fur2_y");
           }

           private void pictureBox17_Click(object sender, EventArgs e)
           {

           }

           private void pictureBox14_MouseDown(object sender, MouseEventArgs e)
           {
               clickPoint.X = e.X;
               clickPoint.Y = e.Y;
           }

           private void pictureBox14_MouseMove(object sender, MouseEventArgs e)
           {
               if (IsKeyDown(VK_LBUTTON))
               {
                   (sender as Control).Cursor = Cursors.Hand;
                   (sender as Control).Left += e.X - clickPoint.X;
                   (sender as Control).Top += e.Y - clickPoint.Y;

               }
               user.fur_save(Convert.ToInt32(textBox1.Text), pictureBox14.Location.X, pictureBox14.Location.Y, pictureBox14, "fur6_x", "fur6_y");
           }

           private void pictureBox15_Click_1(object sender, EventArgs e)
           {

           }

           private void pictureBox15_MouseDown(object sender, MouseEventArgs e)
           {
               clickPoint.X = e.X;
               clickPoint.Y = e.Y;
           }

           private void pictureBox15_MouseMove(object sender, MouseEventArgs e)
           {
               if (IsKeyDown(VK_LBUTTON))
               {
                   (sender as Control).Cursor = Cursors.Hand;
                   (sender as Control).Left += e.X - clickPoint.X;
                   (sender as Control).Top += e.Y - clickPoint.Y;

               }
               user.fur_save(Convert.ToInt32(textBox1.Text), pictureBox15.Location.X, pictureBox15.Location.Y, pictureBox15, "fur5_x", "fur5_y");
           }

           private void pictureBox10_Click(object sender, EventArgs e)
           {

           }

           private void pictureBox10_MouseDown(object sender, MouseEventArgs e)
           {
               clickPoint.X = e.X;
               clickPoint.Y = e.Y;
           }

           private void pictureBox10_MouseMove(object sender, MouseEventArgs e)
           {
               if (IsKeyDown(VK_LBUTTON))
               {
                   (sender as Control).Cursor = Cursors.Hand;
                   (sender as Control).Left += e.X - clickPoint.X;
                   (sender as Control).Top += e.Y - clickPoint.Y;

               }
               user.fur_save(Convert.ToInt32(textBox1.Text), pictureBox10.Location.X, pictureBox10.Location.Y, pictureBox10, "fur4_x", "fur4_y");
           }

           private void pictureBox13_MouseDown(object sender, MouseEventArgs e)
           {
               
               clickPoint.X = e.X;
               clickPoint.Y = e.Y;
           
           }

           private void pictureBox13_MouseMove(object sender, MouseEventArgs e)
           {
               if (IsKeyDown(VK_LBUTTON))
               {
                   (sender as Control).Cursor = Cursors.Hand;
                   (sender as Control).Left += e.X - clickPoint.X;
                   (sender as Control).Top += e.Y - clickPoint.Y;

               }
               user.fur_save(Convert.ToInt32(textBox1.Text), pictureBox13.Location.X, pictureBox13.Location.Y, pictureBox13, "fur3_x", "fur3_y");
           }

           private void pictureBox16_MouseMove(object sender, MouseEventArgs e)
           {
               if (IsKeyDown(VK_LBUTTON))
               {
                   (sender as Control).Cursor = Cursors.Hand;
                   (sender as Control).Left += e.X - clickPoint.X;
                   (sender as Control).Top += e.Y - clickPoint.Y;

               }
               user.fur_save(Convert.ToInt32(textBox1.Text), pictureBox16.Location.X, pictureBox16.Location.Y, pictureBox16, "fur1_x", "fur1_y");
           }

           private void pictureBox16_MouseDown(object sender, MouseEventArgs e)
           {
               clickPoint.X = e.X;
               clickPoint.Y = e.Y;

           }

           private void bubbleButton1_Click(object sender, DevComponents.DotNetBar.ClickEventArgs e)
           {

           }

           private void pictureBox14_Click(object sender, EventArgs e)
           {

           }
           
           }
       }
    

